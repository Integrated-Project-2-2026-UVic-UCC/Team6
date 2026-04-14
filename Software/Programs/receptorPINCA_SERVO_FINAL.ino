#include <esp_now.h>
#include <WiFi.h>
#include <ESP32Servo.h>

Servo pincaServo;
const int pinServo = 1; 

const int releA = 9; 
const int releB = 8; 
const int ledObert = 7;  
const int ledTancat = 44;

typedef struct {
  bool motorA;
  bool motorB;
  bool pinca;
} struct_message;

struct_message dadesRebudes;

// --- TRUC MULTIVERSION ---
// Això evita errors tant si tens el core v2.x com el v3.x de l'ESP32
#if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
void alRebre(const esp_now_recv_info_t *info, const uint8_t *data, int len) {
#else
void alRebre(const uint8_t *mac, const uint8_t *data, int len) {
#endif
// -------------------------

  memcpy(&dadesRebudes, data, sizeof(dadesRebudes));

  digitalWrite(releA, dadesRebudes.motorA ? HIGH : LOW);
  digitalWrite(releB, dadesRebudes.motorB ? HIGH : LOW);

  if (dadesRebudes.pinca == true) {
    pincaServo.write(70); 
    digitalWrite(ledObert, HIGH);
    digitalWrite(ledTancat, LOW);
  } else {
    pincaServo.write(0);  
    digitalWrite(ledObert, LOW);
    digitalWrite(ledTancat, HIGH);
  }
}

void setup() {
  Serial.begin(115200);
  
  pinMode(releA, OUTPUT);
  pinMode(releB, OUTPUT);
  pinMode(ledObert, OUTPUT);
  pinMode(ledTancat, OUTPUT);

  digitalWrite(releA, LOW);
  digitalWrite(releB, LOW);

  ESP32PWM::allocateTimer(0);
  pincaServo.setPeriodHertz(50); 
  pincaServo.attach(pinServo, 500, 2400); 

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  
  if (esp_now_init() != ESP_OK) return;
  
  esp_now_register_recv_cb(alRebre);
}

void loop() {}