#include <stdio.h>
#include "pico/stdlib.h"

#define LED_BLUE 11
#define LED_RED 12
#define LED_GREEN 13
#define BUTTON 5

static bool button_pressionado = false;
static bool leds_ligada = false;
static int led_atual = 0;
static struct repeating_timer timer;  // Variável para o temporizador

bool repeating_led_callback(struct repeating_timer *t) {
    // Controla a sequência de LEDs conforme o estado atual
    if (led_atual == 1) {
        // Desliga o azul
        gpio_put(LED_BLUE, 0);
        
        led_atual++;
    } else if (led_atual == 2) {
        // Desliga o vermelho
        gpio_put(LED_RED, 0);

        led_atual++;
    } else if (led_atual == 3) {
        // Desliga o verde
        gpio_put(LED_GREEN, 0);
        leds_ligada = false;

        led_atual = 0;        // Reseta a sequência de LEDs
        return false;
    }

    return true;  // Continuar chamando a callback
}

// Função para debouncing do botão
void debounce_button() {
    static uint32_t last_button_estado = 0;
    uint32_t button_estado = gpio_get(BUTTON);

    if (button_estado != last_button_estado) {
        sleep_ms(100); // Espera para evitar bouncing
        last_button_estado = button_estado;
    }

    if (button_estado == 0 && !leds_ligada) {
        // Se o botão foi pressionado e a sequência não está rodando
        leds_ligada = true;

        // Liga todos os LEDs
        gpio_put(LED_BLUE, 1);
        gpio_put(LED_RED, 1);
        gpio_put(LED_GREEN, 1);
        led_atual++;

        // Inicia o temporizador de 3 segundos
        add_repeating_timer_ms(3000, repeating_led_callback, NULL, &timer);
    }
}

int main() {
    // Inicializa o Raspberry Pi Pico
    gpio_init(LED_BLUE);
    gpio_init(LED_RED);
    gpio_init(LED_GREEN);
    gpio_init(BUTTON);

    // Configura os pinos dos LEDs como saída
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(LED_GREEN, GPIO_OUT);

    // Configura o pino do botão como entrada com pull-up
    gpio_set_dir(BUTTON, GPIO_IN);
    gpio_pull_up(BUTTON);

    // Inicia a execução do programa
    while (true) {
        debounce_button();
        sleep_ms(10);  // Pequena espera para evitar que o loop consuma muitos recursos
    }
}