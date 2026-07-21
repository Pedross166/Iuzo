#include "mapeamento.h"

bool inicou_volta = false;

int contador_esq = 0;
int contador_dir = 0;
int contador_cruzamentos = 0;

ESTADO_SL estado_atual = NADA;
ESTADO_SL estado_anterior = NADA;

void atualiza_SL(){
    estado_anterior = estado_atual;
    ler_sl();

    bool sl_esq_le_branco = SL.se[0] <= VALOR_MAXIMO_NORMALIZADO/2 || SL.se[1] <= VALOR_MAXIMO_NORMALIZADO/2;
    bool sl_dir_le_branco = SL.sd[0] <= VALOR_MAXIMO_NORMALIZADO/2 || SL.sd[1] <= VALOR_MAXIMO_NORMALIZADO/2;


    if (sl_esq_le_branco && sl_dir_le_branco){
        estado_atual = CRUZAMENTO;
    }
    else if (!sl_esq_le_branco && !sl_dir_le_branco){
        estado_atual = NADA;
    }
    else if (sl_esq_le_branco && !sl_esq_le_branco){
        estado_atual = ESQUERDO;
    }
    else if (!sl_esq_le_branco && sl_esq_le_branco){
        estado_atual = DIREITO;
    }
}

void atualiza_contadores_sl(){


}
