#ifndef MOTORES_H
#define MOTORES_H

#include <Arduino.h>
#include "pinout.h"
#include "bateria.h"


//frequencia de pwm
#define FREQUENCiA_PWM      50000 // Hz


class Motores {
private:
    int pino1;
    int pino2;

public:
    Motores(int p1, int p2);
    void Aciona(float tensao);
    void Freia();
};

extern Motores motor_direito;
extern Motores motor_esquerdo;
extern Motores turbina;

void curva(float potencia, float intensidade_de_curva);
void para_frente(float potencia);
void testa_motores();
void testa_turbina();
void init_motores();

#endif
