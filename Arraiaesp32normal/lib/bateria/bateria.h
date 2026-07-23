#ifndef _BATERIA_H_
#define _BATERIA_H_

#include "pinout.h"
#include <Arduino.h>
#include "led.h"

#define TENSAO_MAXIMA_BATERIA      12.44


extern double tensao_bateria;


void init_bateria();
void atualiza_tensao_bateria();

#endif