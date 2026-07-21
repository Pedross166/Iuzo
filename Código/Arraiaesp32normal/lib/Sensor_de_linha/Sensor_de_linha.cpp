#include "Sensor_de_linha.h"

sensor_frontal SF;
sensor_lateral SL;

int contador_esq;
int contador_dir;
int cruzamento;

void sensores_init(){
    pinMode(SENSOR_LATERAL_DIR_1, INPUT);
    pinMode(SENSOR_LATERAL_DIR_2, INPUT);
    pinMode(SENSOR_LATERAL_ESQ_1, INPUT);
    pinMode(SENSOR_LATERAL_ESQ_2, INPUT);
    ADC_setup();
}

void calibra_sensores(){

    // Reseta calibração
    for (int i = 0; i < N_SENSORES_FRONTAIS; i++)
    {
       SF.max_calibracao[i] = 0;
       SF.min_calibracao[i] = 4095;
    }
    

    int inicio = millis();
    int sensor_atual;

    while(millis() - inicio <= TEMPO_DE_CALIBRACAO){
        for (int i=0; i< N_SENSORES_FRONTAIS; i++){
            sensor_atual = le_sensor(i);   
            if (sensor_atual < SF.min_calibracao[i]) SF.min_calibracao[i] = sensor_atual;
            if (sensor_atual > SF.max_calibracao[i]) SF.max_calibracao[i] = sensor_atual; 
        } 
    }


    for(int i = 0; i < 9; i++){
        String message = "Calibração do sensor ";
        message = message + i + ": máximo " + SF.max_calibracao[i] + " mínimo " + SF.min_calibracao[i] + "\n";

        Serial.printf("Calibração do sensor %d: maximo %d  minimo %d \n", i, SF.max_calibracao[i], SF.min_calibracao[i]);
        send_bluetooth_message(message);
    }
    Serial.println();
}

void leitura_calibrada(){
    for (int i = 0; i < N_SENSORES_FRONTAIS; i++)
    {
        int leitura = le_sensor(i);

        if (leitura < SF.min_calibracao[i] * 1.15 ) leitura = SF.min_calibracao[i];
        else if (leitura > SF.max_calibracao[i] * 0.85) leitura = SF.max_calibracao[i];

        SF.sensores[i] = (VALOR_MAXIMO_NORMALIZADO * (float(leitura- SF.min_calibracao[i]))/(SF.max_calibracao[i] - SF.min_calibracao[i]));
    }
}

float calcula_posicao(){
    leitura_calibrada();

    int pos=0;
    int soma = 0;

    #if COR_LINHA == BRANCO
    for (int i = 0; i < N_SENSORES_FRONTAIS; i++){
        soma += (VALOR_MAXIMO_NORMALIZADO - SF.sensores[i]);
        pos += (i-4) * (VALOR_MAXIMO_NORMALIZADO - SF.sensores[i]);
    }
    #endif

    #if COR_LINHA == PRETO
    for (int i = 0; i < N_SENSORES_FRONTAIS; i++){
        soma += (SF.sensores[i]);
        pos += (i-4) * (SF.sensores[i]);
    }
    #endif

    float posicao = 0;

    if (soma != 0) posicao = float(pos)/soma;
    
    return posicao;
}

void testa_posicao(){
    float posicao = calcula_posicao();
    Serial.printf("posicao: %f \n", posicao);
    delay(100);

}

void testa_leitura_calibrada(){
    leitura_calibrada();

    for (int sensor_atual= 0; sensor_atual < 9; sensor_atual++){
        Serial.printf("Sensor %d : %d \n" , sensor_atual, SF.sensores[sensor_atual]);
    }

    Serial.println();
    delay(2000);
}

void caibra_sensores_laterais(){
    SL.max_calibracao = 0;
    SL.min_calibracao = 4095;
    for (int i = 0; i < N_SENSORES_LATERAIS; i++)
    {
        if (SL.max_calibracao < SF.max_calibracao[i]) SL.max_calibracao = SF.max_calibracao[i];
        if (SL.min_calibracao > SF.min_calibracao[i]) SL.min_calibracao = SF.min_calibracao[i];
    }
    
}

void ler_sl(){
    //Le os sensores laterais
    SL.sd[0] = analogRead(SENSOR_LATERAL_DIR_1);
    SL.sd[1] = analogRead(SENSOR_LATERAL_DIR_2);

    SL.se[0] = analogRead(SENSOR_LATERAL_ESQ_1);
    SL.se[1] = analogRead(SENSOR_LATERAL_ESQ_2);

    //calibra e normaliza os sensores
    SL.sd[0] = map(SL.sd[0], 0, 4095, 0, VALOR_MAXIMO_NORMALIZADO);
    SL.sd[1] = map(SL.sd[1], 0, 4095, 0, VALOR_MAXIMO_NORMALIZADO);

    SL.se[0] = map(SL.se[0], 0, 4095, 0, VALOR_MAXIMO_NORMALIZADO);
    SL.se[1] = map(SL.se[1], 0, 4095, 0, VALOR_MAXIMO_NORMALIZADO);
}
