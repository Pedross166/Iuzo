#include "led.h"

CRGB leds[NUMERO_DE_LEDS];

#if robo == BIARO
CRGB ledsprincipal[3];
#endif

void led_setup() {
    FastLED.addLeds<NEOPIXEL, pino_led>(leds, NUMERO_DE_LEDS);
    leds[0] = CRGB(WHITE);
	leds[1] = CRGB(WHITE);
    #if robo == BIARO
    FastLED.addLeds<NEOPIXEL, pino_led_principal>(leds, 3);
    ledsprincipal[0] = CRGB(GREEN);
    ledsprincipal[1] = CRGB(YELLOW);
    ledsprincipal[2] = CRGB(RED);
    #endif
	FastLED.show();
}

void cor_led(int indice, int r, int g, int b ){
    leds[indice] = CRGB(r, g, b);
    FastLED.show();
}

void troca_todos_leds(int r, int g, int b ){
    for (int i=0; i< NUMERO_DE_LEDS; i++){
        cor_led(i,r,g,b);
    }
    FastLED.show();
}

void troca_led_bluetooth(String string_cor){;

    if (string_cor == "Vermelho"){ 
        troca_todos_leds(RED);
    }
    else if (string_cor == "Azul"){
        troca_todos_leds(BLUE);
    }
    else if (string_cor == "Verde"){
        troca_todos_leds(GREEN);
    }
    else if (string_cor == "Branco"){
        troca_todos_leds(WHITE);
    }
    else if (string_cor == "Desligar led"){
        troca_todos_leds(BLANK_COLOR);
    }
    else if (string_cor == "Ciano"){
        troca_todos_leds(CIAN);
    }
    else if (string_cor == "Rosa"){
        troca_todos_leds(PINK);
    }
    else if (string_cor == "Esmeralda"){
        troca_todos_leds(EMERALD);
    }
    else if (string_cor == "Amarelo"){
        troca_todos_leds(YELLOW);
    }
}