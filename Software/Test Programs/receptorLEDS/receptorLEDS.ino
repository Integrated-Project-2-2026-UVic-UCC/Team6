#include <esp_now.h>
#include <WiFi.h>

// Pins provats i confirmats
const int led1 = 9;  // D10
const int led2 = 8;  // D9
const int led3 = 7;  // D8
const int led4 = 44; // D7

typedef struct struct_message {
  bool s1; bool s2; bool s3; bool s4;
} struct_message;

struct_message dadesRebudes;

void alRebre(const esp_now_recv_info *info, const uint8_t *data, int len) {
  memcpy(&dadesRebudes, data, sizeof(dadesRebudes));

  // Apliquem l'estat rebut als LEDs
  digitalWrite(led1, dadesRebudes.s1 ? HIGH : LOW);
  digitalWrite(led2, dadesRebudes.s2 ? HIGH : LOW);
  digitalWrite(led3, dadesRebudes.s3 ? HIGH : LOW);
  digitalWrite(led4, dadesRebudes.s4 ? HIGH : LOW);

  // Feedback pel Monitor Sèrie
  Serial.print("Ordre rebuda -> L1:"); Serial.print(dadesRebudes.s1);
  Serial.print(" L2:"); Serial.print(dadesRebudes.s2);
  Serial.print(" L3:"); Serial.print(dadesRebudes.s3);
  Serial.print(" L4:"); Serial.println(dadesRebudes.s4);
}

void setup() {
  Serial.begin(115200);
  pinMode(led1, OUTPUT); pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT); pinMode(led4, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error ESP-NOW");
    return;
  }
  
  esp_now_register_recv_cb(alRebre);
  Serial.println("RECEPTOR A PUNT - Esperant ordres...");
}

void loop() {
  // No cal fer res, el callback 'alRebre' ho gestiona tot
}