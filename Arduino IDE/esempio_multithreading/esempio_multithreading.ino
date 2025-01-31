#include <Arduino.h>

void task1(void *pvParameters) {
    while (1) {
        printf("Task 1 in esecuzione\n");
        vTaskDelay(pdMS_TO_TICKS(1000)); // Ritardo di 1 secondo
    }
}

void task2(void *pvParameters) {
    while (1) {
        printf("Task 2 in esecuzione\n");
        vTaskDelay(pdMS_TO_TICKS(2000)); // Ritardo di 2 secondi
    }
}

void setup() {
    xTaskCreate(task1, "Task 1", 2048, NULL, 1, NULL);
    xTaskCreate(task2, "Task 2", 2048, NULL, 1, NULL);
}

void loop() {}