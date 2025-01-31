#include <Arduino.h>
#include <freertos/semphr.h>

SemaphoreHandle_t mutex;

void taskWithMutex(void *pvParameters) {
    while (1) {
        if (xSemaphoreTake(mutex, portMAX_DELAY)) {
            Serial.printf("%s: Accesso alla risorsa\n", (char *)pvParameters);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            xSemaphoreGive(mutex);
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void setup() {
    Serial.begin(115200);
    mutex = xSemaphoreCreateMutex();
    if (mutex != NULL) {
        xTaskCreate(taskWithMutex, "Task 1", 2048, (void *)"Task 1", 1, NULL);
        xTaskCreate(taskWithMutex, "Task 2", 2048, (void *)"Task 2", 1, NULL);
    }
}

void loop() {}