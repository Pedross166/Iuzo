#ifndef _ENCODER_
#define _ENCODER_

#include "pinout.h"
#include <Arduino.h>
#include <ESP32Encoder.h>

//MACROS do encoder
#define CONTAGENS_POR_REVOLUCAO     2048.0
#define DIAMETRO_DA_RODA            24.0    //mm    
#define DENTES_NA_RODA              42.0
#define DENTES_NO_ENCODER           13.0    
#define AMOSTRAGEM_ENCODER          1.0     //ms

extern ESP32Encoder encoder_direito;
extern ESP32Encoder encoder_esquerdo;

extern float distancia_atual[2];
extern float ultima_distancia[2];

void init_encoder();
void reseta_encoders();
float calculaDistancia(ESP32Encoder encoder);
float calculaVelocidade(ESP32Encoder encoder);


#endif