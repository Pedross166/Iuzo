#ifndef _SENSOR_DE_LINHA_
#define _SENSOR_DE_LINHA_

#include <Arduino.h>
#include "ADC.h"
#include "pinout.h"
#include "bluetooth.h"
#include <string>

//Linha
#define BRANCO                       1
#define PRETO                        0
#define COR_LINHA               BRANCO

// Macros dos sensores
#define N_SENSORES_FRONTAIS     9
#define N_SENSORES_LATERAIS     4

// Macros de calibração dos sensores
#define TEMPO_DE_CALIBRACAO             6000 //ms
#define N_DE_AMOSTRAS                      3 
#define VALOR_MAXIMO_NORMALIZADO        5000


struct sensor_frontal{
    int max_calibracao[N_SENSORES_FRONTAIS];
    int min_calibracao[N_SENSORES_FRONTAIS];
    int sensores[N_SENSORES_FRONTAIS];
};
extern sensor_frontal SF;

struct sensor_lateral{
    int max_calibracao;
    int min_calibracao;

    int se[2];
    int sd[2];
};
extern sensor_lateral SL;


void sensores_init();
void calibra_sensores();
void leitura_calibrada();
void testa_posicao();
void testa_leitura_calibrada();
void caibra_sensores_laterais();
float calcula_posicao();
void ler_sl();

#endif