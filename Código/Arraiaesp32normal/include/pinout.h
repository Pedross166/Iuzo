#ifndef _pinout_h
#define _pinout_h

#define BIAV1       0
#define BIARO       1
#define ARRAIA      2
#define robo        BIARO

#if robo == BIAV1

//motores de locomoção
#define pino_1_motor_direito           14
#define pino_2_motor_direito           21

#define pino_1_motor_esquerdo          10
#define pino_2_motor_esquerdo           9

//turbina
#define pino_1_turbina                 13
#define pino_2_turbina                 12

//ADC e sensores frontais
#define MOSFET_SENSOR                  30
#define ADC_SLCK                       41
#define ADC_DIN                        42
#define ADC_DOUT                       40
#define ADC_CS                         39


//Sensores laterais
#define SENSOR_LATERAL_ESQ_1            6
#define SENSOR_LATERAL_ESQ_2            5
#define SENSOR_LATERAL_DIR_1            2
#define SENSOR_LATERAL_DIR_2            1

//led
#define pino_led                        4

//bateria
#define leitura_da_bateria              7

//Encoders
#define ENCODER_ESQUERDO_A             18
#define ENCODER_ESQUERDO_B             17
#define ENCODER_DIREITO_A              16
#define ENCODER_DIREITO_B              15

#endif

#if robo == BIARO

//motores de locomoção
#define pino_1_motor_direito           14
#define pino_2_motor_direito           21

#define pino_1_motor_esquerdo          10
#define pino_2_motor_esquerdo           9

//turbina
#define pino_1_turbina                 13
#define pino_2_turbina                 12

//ADC e sensores frontais
#define ADC_SLCK                       15
#define ADC_DIN                        7
#define ADC_DOUT                       16
#define ADC_CS                         6

//led
#define pino_led                         5
#define pino_led_principal              10

//bateria
#define leitura_da_bateria              2

#endif

#endif