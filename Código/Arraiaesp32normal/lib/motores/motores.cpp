#include "motores.h"

void init_motores(){
    analogWriteFrequency(FREQUENCiA_PWM);
    analogWriteResolution(8);
    
    motor_direito.Aciona(0);
    motor_esquerdo.Aciona(0);
    turbina.Aciona(0);
}

Motores::Motores(int p1, int p2) {
    pino1 = p1;
    pino2 = p2;

    pinMode(pino1, OUTPUT);
    pinMode(pino2, OUTPUT);
}
    
void Motores::Aciona(float tensao){
    int pwm = round(255* tensao/tensao_bateria);
    pwm = constrain(pwm, -255, 255);
    
    if (pwm >=0 ){
        analogWrite(pino1, 255-pwm);
        analogWrite(pino2, 255);} 
    else{
        analogWrite(pino1, 255);
        analogWrite(pino2, 255-abs(pwm));} 
}

void Motores::Freia() {
    analogWrite(pino1, LOW);
    analogWrite(pino2, LOW);
}

Motores motor_direito = Motores(pino_1_motor_direito, pino_2_motor_direito);
Motores motor_esquerdo = Motores(pino_1_motor_esquerdo, pino_2_motor_esquerdo);
Motores turbina = Motores(pino_1_turbina, pino_2_turbina);


void para_frente(float potencia){
    motor_direito.Aciona(potencia);
    motor_esquerdo.Aciona(potencia);
}

//para esquerda se intensidade_de_curva é positivo e para direita e negativo
void curva(float potencia, float intensidade_de_curva){
    motor_direito.Aciona(potencia - intensidade_de_curva);
    motor_esquerdo.Aciona(potencia + intensidade_de_curva);
}

void testa_motores(){
    //Função que testa se os motores estão com a pinagem correta
    
    //para por 1 segundo
    motor_direito.Aciona(0);
    motor_esquerdo.Aciona(0);
    delay(1000);

    //liga pra frente por 2 segundos
    motor_direito.Aciona(3.0);
    motor_esquerdo.Aciona(3.0);
    delay(2000);

    //para por 1 segundo
    motor_direito.Aciona(0);
    motor_esquerdo.Aciona(0);
    delay(1000);

    //liga pra trás por 2 segundos
    motor_direito.Aciona(-3.0);
    motor_esquerdo.Aciona(-3.0);
    delay(2000);
}

void testa_turbina(){
    //Função que testa se a turbina está com a pinagem correta
    
    //liga pra frente por 10 segundos
    turbina.Aciona(3.0);
    delay(5000);

    //para por 1 segundo
    turbina.Aciona(0);
    delay(1000);

    //liga pra trás por 10 segundos
    turbina.Aciona(-3.0);
    delay(5000);
}