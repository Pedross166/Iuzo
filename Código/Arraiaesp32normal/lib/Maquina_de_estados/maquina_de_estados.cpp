#include "maquina_de_estados.h"

estados estado = INICIALIZACAO;

void maquina_de_estados(){

    switch (estado){
    case INICIALIZACAO:
        inicializacao();
        break;
    case CALIBRACAO:
        calibracao();
        break;
    case CONFIGURACAO:
        configuracao();
        break;
    case PRE_CORRIDA:
        pre_corrida();
        break;
    case CORRIDA:
        corrida();
        break;
    case PARAR:
        parar();
        break;
    }
};

void troca_estado(estados novo_estado){
    estado = novo_estado;
    maquina_de_estados();
}

void inicializacao(){
    //inicializa os módulos
    init_bateria();
    init_motores();
    led_setup();
    bluetooth_init();
    sensores_init();
    init_encoder();
    controle_setup();

    //analisa a tensão da bateria
    atualiza_tensao_bateria();
    delay(1000);
    troca_estado(CALIBRACAO);
}

void calibracao(){
    troca_todos_leds(CIAN);

    bluetooth_check_connection();
    String comando = read_bluetooth_message();

    if (comando == "Calibra sensores"){
        troca_todos_leds(DARK_ORANGE);
        calibra_sensores();
        caibra_sensores_laterais();
    }

    else if (comando == "Configuração"){
        troca_estado(CONFIGURACAO);
    }
    
    else if (comando == "START"){
        reseta_encoders();
        troca_todos_leds(PINK);
        troca_estado(PRE_CORRIDA);
    }

}

void configuracao(){
    troca_todos_leds(LIGHT_ORANGE);

    bluetooth_check_connection();
    String comando = read_bluetooth_message();
    float valor=0;

    int pos = comando.indexOf(',');
    if (pos != -1){
        valor = comando.substring(pos+1).toFloat();
        comando = comando.substring(0, pos);
    }

    if (comando == "KP"){
        String message = "KP atual é " + String(PID_simples.kp, 6) + "\n";
        send_bluetooth_message(message);

        PID_simples.Define_kp(valor);
        
        message = "KP atualizado para " + String(PID_simples.kp, 6) +"\n";
        send_bluetooth_message(message);
    }

    else if (comando == "KD"){
        String message = "KD atual é " + String(PID_simples.kd, 6) + "\n";
        send_bluetooth_message(message);

        PID_simples.Define_kd(valor);
        
        message = "KD atualizado para " + String(PID_simples.kd, 6) +"\n";
        send_bluetooth_message(message);
    }

    else if (comando == "Tensão base"){
        String message = "Tensão base atual é " + String(tensao_base) + "\n";
        send_bluetooth_message(message);

        define_tensao_base(valor);
        
        message = "Tensão base atualizado para " + String(tensao_base) +"\n";
        send_bluetooth_message(message);
    }

    else if(comando == "Tensão turbina"){
        String message = "Tensão da turbina é " + String(tensao_turbina) + "\n";
        send_bluetooth_message(message);

        define_tensao_turbina(valor);
        
        message = "Tensão da turbina atualizado para " + String(tensao_turbina) +"\n";

        send_bluetooth_message(message);
    }
    else if (comando == "START") {
        reseta_encoders();
        troca_todos_leds(PINK);
        troca_estado(PRE_CORRIDA);
    }
    else if (comando == "Verifica bateria"){
        atualiza_tensao_bateria();
    }
}

void corrida(){
    curva(tensao_base, PID_simples.Correcao(calcula_posicao()));
    
    String message = read_bluetooth_message();
    if (message == "STOP") {
        float distancia_direita = calculaDistancia(encoder_direito);
        float distancia_esquerda = calculaDistancia(encoder_esquerdo);
        float distancia_total = (distancia_direita + distancia_esquerda)/2;

        String message = "Roda esquerda andou: " + String(distancia_esquerda) +  " m \n";
        send_bluetooth_message(message);

        message = "Roda direita andou: " + String(distancia_direita) + " m \n";
        send_bluetooth_message(message);

        message = "Tamanho total: " + String(distancia_total) + " m \n";
        send_bluetooth_message(message);
        troca_todos_leds(RED);
        
        troca_estado(PARAR);
    }
}

void parar(){
    motor_direito.Freia();
    motor_esquerdo.Freia();
    turbina.Freia();

    bluetooth_check_connection();
    String message = read_bluetooth_message();
    if (message == "Calibração"){
        troca_estado(CALIBRACAO);
    }
    else if (message == "Configuração"){
        troca_estado(CONFIGURACAO);
    }
}

void pre_corrida(){
    for(int i = 0; i<101;i++){
        turbina.Aciona(tensao_turbina*i/100);
        delay(50);
    }
    
    String message = read_bluetooth_message();
    if (message == "STOP") {
        troca_estado(PARAR);
    }

    troca_estado(CORRIDA);
}