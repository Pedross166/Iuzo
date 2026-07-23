#include "bluetooth.h"

BLEServer *pServer = NULL;
BLECharacteristic *characteristicMessage = NULL;
String message = "";
bool deviceConnected = false;
bool oldDeviceConnected = false;

void decode_message(String message, BLECharacteristic *characteristic);

class MyServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer *server) {
        deviceConnected = true;
        Serial.println("Conectado à Bia!");
    };

    void onDisconnect(BLEServer *server) {
        deviceConnected = false;
        Serial.println("Desconectado da Bia.");
    }
};

class MessageCallbacks : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *characteristic) {
        std::string data = characteristic->getValue();
        message = data.c_str();
    }

    void onRead(BLECharacteristic *characteristic) {
        characteristic->setValue("Comunicação OK");
    }
};

void bluetooth_init() {
    
    // Setup BLE Server
    BLEDevice::init(DEVICE_NAME);
    
    // Configurações de BLE para evitar erro GATT 133
    BLEDevice::setMTU(517); // MTU máximo
    
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    // Register message service - SERVIÇO PRINCIPAL
    BLEService *service = pServer->createService(SERVICE_UUID);
    
    characteristicMessage = service->createCharacteristic(
        MESSAGE_UUID, 
        BLECharacteristic::PROPERTY_READ | 
        BLECharacteristic::PROPERTY_WRITE |
        BLECharacteristic::PROPERTY_NOTIFY
    );
    
    characteristicMessage->setCallbacks(new MessageCallbacks());
    characteristicMessage->addDescriptor(new BLE2902());
    characteristicMessage->setValue("Pronto");
    
    service->start();

    // Configurar advertising
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);  // Ajuda com conexão iOS
    pAdvertising->setMinPreferred(0x12);
    
    BLEDevice::startAdvertising();
}

void bluetooth_resume() {
    message = "";
}

String read_bluetooth_message() {
    String aux = "";
    int index = message.indexOf("\r");
    if (index > 0) {
        aux = message.substring(0, index);
        bluetooth_resume();
    }

    return aux;
}

void send_bluetooth_message(String msg) {
    if (deviceConnected && characteristicMessage != NULL) {
        characteristicMessage->setValue(msg.c_str());
        characteristicMessage->notify();
        delay(10); // Pequeno delay para garantir envio
    }
}

// Loop de verificação de conexão (chamar periodicamente)
void bluetooth_check_connection() {
    // Detecting disconnect and restart advertising
    if (!deviceConnected && oldDeviceConnected) {
        delay(500); // Tempo para stack BLE se resetar
        pServer->startAdvertising();
        Serial.println("Aguardando nova conexão...");
        oldDeviceConnected = deviceConnected;
    }
    
    // Detecting connect
    if (deviceConnected && !oldDeviceConnected) {
        oldDeviceConnected = deviceConnected;
    }
}