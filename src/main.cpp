#include <Arduino.h>
#include "rtos.h"
#include "travel.h"

#define KEY 2

void setup() {
  Serial.begin(9600);
  elevator.begin();

  pinMode(KEY, INPUT_PULLUP);

  xTaskCreate(TaskKey, "Key", 128, NULL, 0, NULL);
  xTaskCreate(TaskLimits, "Limits", 128, NULL, 1, NULL);
  xTaskCreate(TaskExec, "Exec", 128, NULL, 2, NULL);
  xTaskCreate(TaskBlink, "Blink", 128, NULL, 3, NULL);

  interruptSemaphore = xSemaphoreCreateBinary();
  if (interruptSemaphore != NULL) {
    attachInterrupt(digitalPinToInterrupt(KEY), interruptHandler, FALLING);
  }
}

void loop() {}
