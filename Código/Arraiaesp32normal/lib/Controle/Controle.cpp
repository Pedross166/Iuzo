#include "Controle.h"

ControladorPID PID_simples;

void controle_setup(){
  PID_simples.kp = KP;
  PID_simples.kd = KD;
  PID_simples.ki = KI;
  PID_simples.alvo = ALVO_PID;
  PID_simples.taxa_atualizacao = TAXA_ATUALIZACAO_PID;
}

double tensao_base = TENSAO_BASE;
double tensao_turbina = TENSAO_TURBINA;

void ControladorPID::Define_kp(double novo_kp){
  kp = novo_kp;
}

void ControladorPID::Define_kd(double novo_kd){
  kd = novo_kd;
}

void ControladorPID::Define_ki(double novo_ki){
  ki = novo_ki;
}

void define_tensao_base(double nova_tensao){
  tensao_base = nova_tensao;
}

void define_tensao_turbina(double novo){
  tensao_turbina = novo;
}

double ControladorPID::Correcao(double input_leitura){
  tempo_atual = micros();
  if (tempo_atual - ultima_leitura>=taxa_atualizacao*1000){
    Calcula_erros(input_leitura);

    correcao = kp*erro_atual + kd*(delta_erro)/taxa_atualizacao + ki*erro_acumulado;
    ultima_leitura = tempo_atual;
  }
  return correcao;
}

void ControladorPID::Calcula_erros(double input_leitura){
  erro_anterior = erro_atual;
  erro_atual = alvo - input_leitura;
  erro_acumulado += erro_atual*taxa_atualizacao;
  delta_erro = erro_atual - erro_anterior;
}

void aplica_correcao(double correcao){
  curva(tensao_base, correcao);
}
