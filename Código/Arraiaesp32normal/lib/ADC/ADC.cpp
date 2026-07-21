#include "ADC.h"

void ADC_setup(){
    pinMode(ADC_CS, OUTPUT);
    digitalWrite(ADC_CS, HIGH);
    SPI.begin(ADC_SLCK, ADC_DOUT, ADC_DIN, ADC_CS);
    comanda_ADC(0xffff);
    delay(10);
    comanda_ADC(0xffff);
    delay(10);

    int comando = gera_commando_para_ADC(0);
    comanda_ADC(comando); 
}

uint16_t gera_commando_para_ADC(uint16_t endereco){
    uint16_t RC = (
        (RC_WRITE               <<  11) |        
        (RC_SEQ                 <<  10) |
        (endereco               <<   6) | 
        (RC_PM                  <<   4) |
        (RC_SHADOW              <<   3) |       
        (RC_1WEAK_0TRI          <<   2) |  
        (RC_RANGE               <<   1) |       
        (RC_CODING))<<4;
 
    return RC;
}

uint16_t comanda_ADC(uint16_t comando){

    digitalWrite(ADC_CS,LOW);
    
    SPI.beginTransaction(SPISettings(frequencia_SPI, ordem_dos_bits, modo_SPI));
    uint16_t leitura = SPI.transfer16(comando);
    SPI.endTransaction();

    digitalWrite(ADC_CS,HIGH);
    
    return leitura;
}

uint16_t le_ADC(uint16_t endereco){
    if (endereco < 4) endereco = 3 - endereco;
    uint16_t comando = gera_commando_para_ADC(endereco);
    comanda_ADC(comando);


    uint16_t leitura = comanda_ADC(gera_commando_para_ADC(0));
    leitura = (leitura) & 0x0fff;
    return leitura;
}

uint16_t le_sensor(uint16_t endereco){
    int leitura = 0;
    for (int i = 0 ; i< N_MEDIDAS; i++){
        leitura += le_ADC(endereco);
    }
    leitura = leitura/N_MEDIDAS;
    return leitura;
}

void testa_ADC(){
    for (int sensor_atual= 0; sensor_atual < 9; sensor_atual++){
        int leitura = le_sensor(sensor_atual);
        Serial.printf("Sensor %d : %d \n" , sensor_atual, leitura);
        }
    Serial.println();
    delay(2000);
}