#include "bateria.h"

double tensao_bateria = 12.00;

void init_bateria(){
    pinMode(leitura_da_bateria, INPUT);
}

void atualiza_tensao_bateria(){
    float media_bateria = 0;
    for (int i = 0; i<5 ;i++){
        int bateria_agora = analogRead(leitura_da_bateria);
        
        media_bateria += bateria_agora;
    }
    media_bateria = media_bateria/5;

    float resultado = TENSAO_MAXIMA_BATERIA * (media_bateria/2496)* (12.2/16.11); 

    tensao_bateria = resultado;

    if (tensao_bateria >= 11.5){
        troca_todos_leds(GREEN);}
    else if (tensao_bateria >= 10.5){
        troca_todos_leds(YELLOW);}
    else {
        troca_todos_leds(RED);}

    String message = "Tensão da bateria: " + String(tensao_bateria) + "\n";
    send_bluetooth_message(message);
}