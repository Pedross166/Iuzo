#include <Arduino.h>
#include "maquina_de_estados.h"
#include "motores.h"
#include "bateria.h"
#include "pinout.h"

void setup() {
  Serial.begin(9600);
  //init_bateria();
  //init_motores();
  //led_setup();
  //bluetooth_init();
  //ADC_setup();
  //init_encoder();

  //analisa a tensão da bateria
  //atualiza_tensao_bateria();
}

void loop() {
  maquina_de_estados();
  //testa_leitura_calibrada();
  //controle_medio();
  //testa_posicao();
  //turbina.Aciona(2);
  //testa_motores();
  //calibra_sensores(max_calibracao, min_calibracao);
  //testa_ADC();
  //motor_direito.Aciona(2);
  //motor_esquerdo.Aciona(2);
}
