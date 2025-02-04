#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"


// Variáveis Globais
static uint8_t contador = 0;
int pinos[3] = {13, 12, 11};

// Declaração das funções
void setup();
void turnoff();
bool repeating_timer_callback(struct repeating_timer *t);

int main()
{
    // Inicializações
    stdio_init_all(); 
    setup();
    
    // Configura o timer
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Rotina principal
    while (true) {
        printf("Rotina principal funcionando\r\n");
        sleep_ms(1000);
    }
}

void setup(){
    gpio_init(13); //inicializa a porta 13 do microcontrolador
    gpio_set_dir(13, GPIO_OUT); //configura a porta como saída

    gpio_init(12); //inicializa a porta 12 do microcontrolador
    gpio_set_dir(12, GPIO_OUT); //configura a porta 12 como saída

    gpio_init(11); //inicializa a porta 11 do microcontrolador
    gpio_set_dir(11, GPIO_OUT); //configura a porta 11 como saída
}

void turnoff(){
    // Desliga todos os LEDs
    for (int i = 0; i < 3; i++){
        gpio_put(pinos[i], false);
    }
}

bool repeating_timer_callback(struct repeating_timer *t){
    // Função que garante a simulação do semáforo
    turnoff();
    gpio_put(pinos[contador], true);
    contador += 1;
    if (contador == 3){
        contador = 0;
    }
    return true;
}