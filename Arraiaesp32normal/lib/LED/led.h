#ifndef _LED_H_
#define _LED_H_

#include <Arduino.h>
#include "pinout.h"
#include <FastLED.h>
#include "bluetooth.h"

#define NUMERO_DE_LEDS 2

extern CRGB leds[NUMERO_DE_LEDS];

void led_setup();
void cor_led(int indice, int r, int g, int b);
void troca_led_bluetooth(String string_cor);
void troca_todos_leds(int r, int g, int b );

#define RED                 255, 0, 0
#define DARK_ORANGE         254, 23, 0  
#define LIGHT_ORANGE        255, 48, 0
#define YELLOW              255, 115, 0
#define LIME_GREEN          163, 251, 0
#define GREEN               0, 230,   0
#define EMERALD             0, 250, 40
#define CIAN                0, 255, 255
#define LIGHT_BLUE          0, 90, 255
#define BLUE                0,   0, 255
#define PURPLE              137,   0, 255
#define PINK                240,   0, 80
#define SCARLET             255, 0, 6
#define WHITE               200, 200, 200
#define BLANK_COLOR         0,0,0


#endif

