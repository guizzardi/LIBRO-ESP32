#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"

static const char *TAG = "ESEMPIO";

#define BLINK_GPIO 2 // GPIO del LED onboard

void app_main(void)
{
    gpio_reset_pin(BLINK_GPIO); // inizializzo il LED
 
    // imposto la GPIO del LED come output
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    while (1) // ciclo infinito
    {
        gpio_set_level(BLINK_GPIO, 1); // accendo il LED
        vTaskDelay(1000 / portTICK_PERIOD_MS); // attendo 1 secondo
        ESP_LOGI(TAG, "LED %s","ACCESO"); // visualizzo sul log

        gpio_set_level(BLINK_GPIO, 0); // spengo il LED
        vTaskDelay(1000 / portTICK_PERIOD_MS); // attendo 1 secondo
        ESP_LOGI(TAG, "LED %s","SPENTO"); // visualizzo sul log
    }
}