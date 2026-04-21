#include <esp_now.h>
#include <WiFi.h>
#include <ESP32Servo.h>

Servo pincaServo;
const int pinServo = 1; 

const int releA = 9;  // D10
const int releB = 8;  // D9
const int ledObert = 7;  
const int ledTancat = 44;

// NOU: Pin per al Sensor Magnètic de seguretat
const int pinSensor = 2; // Pin D1 de la XIAO

typedef struct {
  bool motorA;
  bool motorB;
  bool pinca;
} struct_message;

struct_message dadesRebudes;

// Variables per memoritzar les ordres de l'emissor
bool ordreMotorA = false;
bool ordreMotorB = false;

// --- TRUC MULTIVERSION ---
#if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
void alRebre(const esp_now_recv_info_t *info, const uint8_t *data, int len) {
#else
void alRebre(const uint8_t *mac, const uint8_t *data, int len) {
#endif
// -------------------------

  memcpy(&dadesRebudes, data, sizeof(dadesRebudes));

  // Guardem el que ens demana l'emissor, però no ho executem aquí
  ordreMotorA = dadesRebudes.motorA;
  ordreMotorB = dadesRebudes.motorB;

  // La pinça la movem directament perquè no té sensor de final de carrera [cite: 45]
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
  
  // NOU: Configurem el sensor amb la resistència pull-up interna
  pinMode(pinSensor, INPUT_PULLUP);

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

void loop() {
  // LLEGIM EL SENSOR: Si detecta l'imant, el pin baixa a LOW
  bool imantDetectat = (digitalRead(pinSensor) == LOW);

  if (imantDetectat) {
    // SEGURETAT ACTIVADA: Imant detectat. Aturem els relés ignorant l'emissor.
    digitalWrite(releA, LOW);
    digitalWrite(releB, LOW);
  } else {
    // FUNCIONAMENT NORMAL: Apliquem les ordres que arriben de l'emissor.
    digitalWrite(releA, ordreMotorA ? HIGH : LOW);
    digitalWrite(releB, ordreMotorB ? HIGH : LOW);
  }
  
  delay(10); // Petita pausa per donar estabilitat al microcontrolador
}