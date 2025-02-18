#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"
#include "inc/font.h"
#include "display/display.h"

#include "hardware/pio.h"
#include "hardware/clocks.h"

// Chamando as funções organizadas em pastas
#include "led/led.h"
#include "buttons/buttons.h"

// Definição do display
ssd1306_t ssd;

int main()
{
    /*
    Toda a estrtura do código foi pensando de forma que o código seja
    de fácil de ler, da maneira que foi organizado,
    facilita a manutenção e a adição de novas funcionalidades.
    */
    char valor = '\0';

    // Inicializa a comunicação serial USB
    stdio_init_all(); // Isso é necessário para usar o printf via USB

    // Inicializa os LEDs e os botões
    init_buttons();

    init_led();

    // Inicializa o display
    init_display(&ssd);

    printf("Iniciando...\n");

    while (true)
    {
        printf("Digite um caractere: ");

        if (stdio_usb_connected()) // Verifica se a conexão USB está ativa
        {
            // Leitura do caractere evitando problemas com buffer
            if (scanf(" %c", &valor) == 1)
            {
                printf("Caractere digitado: %c\n", valor);
                draw_content(&ssd, valor);
            }
            sleep_ms(100);
        }
        sleep_ms(100);
    }

    return 0;
}
