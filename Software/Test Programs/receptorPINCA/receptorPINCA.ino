#include <esp_now.h>
#include <WiFi.h>
#include <ESP32Servo.h> // Instal·la aquesta llibreria!

Servo elMeuServo;
const int pinServo = 1; // D0 (GPIO 1)

// Pins dels LEDs
const int led1 = 9; const int led2 = 8; const int led3 = 7; const int led4 = 44;

typedef struct struct_message {
  bool s1; bool s2; bool s3; bool s4;
} struct_message;

struct_message dadesRebudes;

void alRebre(const esp_now_recv_info *info, const uint8_t *data, int len) {
  memcpy(&dadesRebudes, data, sizeof(dadesRebudes));

  // Control dels LEDs
  digitalWrite(led1, dadesRebudes.s1 ? HIGH : LOW);
  digitalWrite(led2, dadesRebudes.s2 ? HIGH : LOW);
  digitalWrite(led4, dadesRebudes.s4 ? HIGH : LOW);

  // CONTROL DEL SERVO (Amb el Botó 3)
  if (dadesRebudes.s3 == true) {
    elMeuServo.write(70); // Angle obert
    digitalWrite(led3, HIGH);
  } else {
    elMeuServo.write(0);  // Angle tancat
    digitalWrite(led3, LOW);
  }
  
  Serial.print("Servo a: "); Serial.println(dadesRebudes.s3 ? "90 graus" : "0 graus");
}

void setup() {
  Serial.begin(115200);
  
  // Setup Servo
  ESP32PWM::allocateTimer(0);
  elMeuServo.setPeriodHertz(50); 
  elMeuServo.attach(pinServo, 500, 2400); 

  pinMode(led1, OUTPUT); pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT); pinMode(led4, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  esp_now_init();
  esp_now_register_recv_cb(alRebre);
}

void loop() {}