#ifndef _adc_h
#define _adc_h

#include <Arduino.h>
#include "pinout.h"
#include <SPI.h>

// Módulo de configuração e transmissão de dados entre o ADC AD7490 que lê os sensores de linha e o microcontrolador.
// LEIA O DATASHEET PRA ENTENDER MELHOR

// Macros de configuração do SPI
#define frequencia_SPI          1e7         // 10 MHz
#define ordem_dos_bits          MSBFIRST
#define modo_SPI                SPI_MODE0

// Macros do registrador de controle
#define RC_WRITE                1
#define RC_SEQ                  0
#define RC_PM                   3
#define RC_SHADOW               0
#define RC_1WEAK_0TRI           1 //na teoria o dout vai ficar flutuando depois de enviar um sinal. trocar se der problema
#define RC_RANGE                1
#define RC_CODING               1 //tensão baixa gera um número pequeno  

#define N_MEDIDAS               2

#if robo == BIAV1
// Macros dos sensores
#define N_SENSORES_FRONTAIS     9
#define N_SENSORES_LATERAIS     4
#endif

#if robo == BIARO || ARRAIA
#define N_SENSORES_FRONTAIS     16
#endif

void ADC_setup();
void testa_ADC();
uint16_t gera_commando_para_ADC(uint16_t endereco);
uint16_t comanda_ADC(uint16_t comando);
uint16_t le_sensor(uint16_t endereco);
uint16_t le_ADC(uint16_t endereco);



#endif