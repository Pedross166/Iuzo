#ifndef _MAQUINA_DE_ESTADOS_
#define _MAQUINA_DE_ESTADOS_

#include "pinout.h"
#include "motores.h"
#include "ADC.h"
#include "bateria.h"
#include "Controle.h"
#include "led.h"
#include "sensor_de_linha.h"
#include "encoder.h"
#include "mapeamento.h"

enum estados{
    INICIALIZACAO,
    CALIBRACAO,
    CONFIGURACAO,
    PRE_CORRIDA,
    CORRIDA,
    PARAR//,
    //TESTES
};

extern estados estado;

void maquina_de_estados();
void troca_estado(estados novo_estado);
void inicializacao();
void calibracao();
void configuracao();
void pre_corrida();
void corrida();
void parar();
void central_de_comando();

#endif