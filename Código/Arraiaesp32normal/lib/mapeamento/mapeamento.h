#ifndef _MAPEAMENTO_
#define _MAPEAMENTO_

#include "Sensor_de_linha.h"

enum ESTADO_SL{
    NADA,
    ESQUERDO,
    DIREITO,
    CRUZAMENTO
};

extern ESTADO_SL estado_atual;
extern ESTADO_SL estado_anterior;

extern int contador_esq;
extern int contador_dir;
extern int contador_cruzamentos;

extern bool inicou_volta;

void atualiza_SL();
void atualiza_contadores_sl();

#endif