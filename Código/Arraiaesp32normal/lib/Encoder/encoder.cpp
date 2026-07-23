#include "encoder.h"

ESP32Encoder encoder_direito;
ESP32Encoder encoder_esquerdo;

void init_encoder(){
    //encoder direito
    pinMode(ENCODER_DIREITO_A, INPUT);
    pinMode(ENCODER_DIREITO_B, INPUT);

    encoder_direito.attachFullQuad(ENCODER_DIREITO_A, ENCODER_DIREITO_B);
    encoder_direito.clearCount();
    encoder_direito.useInternalWeakPullResistors = puType::none;

    //encoder esquerdo
    pinMode(ENCODER_ESQUERDO_A, INPUT);
    pinMode(ENCODER_ESQUERDO_B, INPUT);
    
    encoder_esquerdo.attachFullQuad(ENCODER_ESQUERDO_A, ENCODER_ESQUERDO_B);
    encoder_esquerdo.clearCount();
    encoder_esquerdo.useInternalWeakPullResistors = puType::none;
}

void reseta_encoders(){
    encoder_direito.clearCount();
    encoder_esquerdo.clearCount();
}

float calculaDistancia(ESP32Encoder encoder){
    int contagem = encoder.getCount();
    float dist = (DIAMETRO_DA_RODA * PI * contagem / CONTAGENS_POR_REVOLUCAO)*(DENTES_NO_ENCODER/DENTES_NA_RODA); //mm
    return dist/1000.0;
}

float calculaVelocidade(ESP32Encoder encoder){
    float distancia_atual = calculaDistancia(encoder);
    float velocidade = 0;
    if (&encoder == &encoder_direito){
        velocidade = (distancia_atual - ultima_distancia_d)/AMOSTRAGEM_ENCODER;
    }
    else if (&encoder == &encoder_esquerdo){
        velocidade = (distancia_atual - ultima_distancia_e)/AMOSTRAGEM_ENCODER;
    }
    return velocidade;
}