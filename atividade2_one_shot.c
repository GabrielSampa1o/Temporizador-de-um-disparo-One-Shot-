#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/watchdog.h"
#include "hardware/clocks.h"
#include "hardware/uart.h"

// Definição dos pinos de cada LED e do botão
#define LED_BLUE   12
#define LED_RED    13
#define LED_GREEN  11
#define BUTTON     5

// Flag para evitar múltiplos disparos enquanto a sequência de LEDs está em execução
static volatile bool sequence_active = false;

// Callbacks para desligar LEDs em etapas:
int64_t cb_turn_off_green(alarm_id_t id, void *user_data) {
    // Desliga LED verde
    gpio_put(LED_GREEN, 0);
    return 0;
}

int64_t cb_turn_off_blue(alarm_id_t id, void *user_data) {
    // Desliga LED azul
    gpio_put(LED_BLUE, 0);
    return 0;
}

int64_t cb_turn_off_red(alarm_id_t id, void *user_data) {
    // Desliga LED vermelho e permite novo acionamento
    gpio_put(LED_RED, 0);
    sequence_active = false;
    return 0;
}

// Callback inicial: agenda os eventos de desligamento em sequência
int64_t cb_start_sequence(alarm_id_t id, void *user_data) {
    // Desliga o LED verde após 3s
    add_alarm_in_ms(3000, cb_turn_off_green, NULL, false);
    // Desliga o LED azul após 6s
    add_alarm_in_ms(6000, cb_turn_off_blue, NULL, false);
    // Desliga o LED vermelho após 9s e libera o sistema
    add_alarm_in_ms(9000, cb_turn_off_red, NULL, false);
    return 0;
}

// Verifica se o botão foi pressionado
void monitor_button(void) {
    // Botão é pull-up; valor 0 significa pressionado
    if (!sequence_active && (gpio_get(BUTTON) == 0)) {
        sleep_ms(50); // Debounce simples
        // Confirma se o botão ainda está pressionado
        if (gpio_get(BUTTON) == 0) {
            sequence_active = true;

            // Liga todos os LEDs
            gpio_put(LED_BLUE, 1);
            gpio_put(LED_RED, 1);
            gpio_put(LED_GREEN, 1);

            // Inicia a sequência de desligamento
            add_alarm_in_ms(0, cb_start_sequence, NULL, false);

            // Aguarda soltar o botão para evitar múltiplos disparos imediatos
            while (gpio_get(BUTTON) == 0) {
                sleep_ms(20);
            }
        }
    }
}

int main() {
    stdio_init_all();

    // Configura LEDs como saída
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_put(LED_BLUE, 0);

    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_put(LED_RED, 0);

    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_put(LED_GREEN, 0);

    // Configura botão como entrada com pull-up interno
    gpio_init(BUTTON);
    gpio_set_dir(BUTTON, GPIO_IN);
    gpio_pull_up(BUTTON);

    // Loop principal
    while (true) {
        monitor_button();
        sleep_ms(100); // Ajuste conforme desejado
    }

    return 0;
}
