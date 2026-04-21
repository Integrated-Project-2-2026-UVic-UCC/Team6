#include <esp_now.h>
#include <WiFi.h>
#include <ESP32Servo.h>

Servo pinçaServo;
const int pinServo = 1; // D0

// Pins de sortida
const int ledMomentani = 9; // D10 (S'activa amb B1)
const int ledObert = 7;     // D8
const int ledTancat = 44;   // D7

typedef struct struct_message {
  bool s1;
  bool s2;
  bool s3;
  bool s4;
} struct_message;

struct_message dadesRebudes;

void alRebre(const esp_now_recv_info *info, const uint8_t *data, int len) {
  memcpy(&dadesRebudes, data, sizeof(dadesRebudes));

  // 1. CONTROL MOMENTANI (LED 1)
  digitalWrite(ledMomentani, dadesRebudes.s1 ? HIGH : LOW);

  // 2. CONTROL PINÇA (Servo i LEDs de feedback)
  if (dadesRebudes.s3 == true) {
    pinçaServo.write(70); 
    digitalWrite(ledObert, HIGH);
    digitalWrite(ledTancat, LOW);
  } else {
    pinçaServo.write(0);
    digitalWrite(ledObert, LOW);
    digitalWrite(ledTancat, HIGH);
  }
}

void setup() {
  Serial.begin(115200);
  
  ESP32PWM::allocateTimer(0);
  pinçaServo.setPeriodHertz(50); 
  pinçaServo.attach(pinServo, 500, 2400); 

  pinMode(ledMomentani, OUTPUT);
  pinMode(ledObert, OUTPUT);
  pinMode(ledTancat, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  esp_now_init();
  esp_now_register_recv_cb(alRebre);
}

void loop() {}