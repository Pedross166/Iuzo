#ifndef __CONTROLE_H_
#define __CONTROLE_H_

#include "pinout.h"
#include "motores.h"
#include "ADC.h"
#include "Sensor_de_linha.h"
#include "bateria.h"

//valor bom para 1.4V kp = 0.685 e kd = 0.00205
// Macros
#define TENSAO_BASE                         3.0
#define TENSAO_TURBINA                      4.0

//PID simples de posição
#define ALVO_PID                            0.0
#define KP                                  0.8
#define KD                                  0.0005
#define KI                                  0.0
#define TAXA_ATUALIZACAO_PID                2 //ms


class ControladorPID{
    public:
    //Atributos
    double alvo;
    double kp;
    double kd;
    double ki;
    double taxa_atualizacao; //ms
    
    double erro_atual = 0;
    double erro_anterior = 0;
    double erro_acumulado;
    double delta_erro;
    double correcao;

    unsigned long int tempo_atual;
    unsigned long int ultima_leitura;

    double Correcao(double input_leitura);
    void Calcula_erros(double input_leitura);
    void Define_kp(double novo_kp);
    void Define_kd(double novo_kd);
    void Define_ki(double novo_ki);
};

extern ControladorPID PID_simples;

extern double tensao_base;
extern double tensao_turbina;

void define_tensao_base(double nova_tensao);
void aplica_correcao(double correcao);
void define_tensao_turbina(double novo);

void controle_setup();


#endif