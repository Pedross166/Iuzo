#include "mapeamento.h"

unsigned long int inicou_volta;

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
    else if (sl_esq_le_branco && !sl_dir_le_branco){
        estado_atual = ESQUERDO;
    }
    else if (!sl_esq_le_branco && sl_dir_le_branco){
        estado_atual = DIREITO;
    }
}

void atualiza_contadores_sl(){
    if (estado_anterior == CRUZAMENTO){
        if (estado_atual != CRUZAMENTO) incrementa_contador_cruzamentos();
    }
    else if (estado_anterior == DIREITO){
        if (estado_atual == ESQUERDO) incrementa_contador_cruzamentos();
        else if (estado_atual == NADA) incrementa_contador_direito();
    }
    else if (estado_anterior == ESQUERDO){
        if (estado_atual == DIREITO) incrementa_contador_cruzamentos();
        else if (estado_atual == NADA) incrementa_contador_esquerdo();
    }

}

void incrementa_contador_esquerdo(){
    contador_esq++;
    float distancia_direita = calculaDistancia(encoder_direito);
    float distancia_esquerda = calculaDistancia(encoder_esquerdo);
    float distancia_total = (distancia_direita + distancia_esquerda)/2;

    String message = "Marcador esquerdo nº " + String(contador_esq) + " a distancia " + String(distancia_total) + "\n";
    send_bluetooth_message(message);
}

void incrementa_contador_direito(){
    if(contador_dir == 0){
        reseta_encoders();

        inicou_volta = millis();
    }
    if (contador_dir == 1){
        unsigned long int tempo_volta = (millis() - inicou_volta)*1000;

        String message = "Tempo da volta" + String(tempo_volta) + "s\n";
        send_bluetooth_message(message);
    }
    contador_dir++;
}

void incrementa_contador_cruzamentos(){
    contador_cruzamentos++;
}
