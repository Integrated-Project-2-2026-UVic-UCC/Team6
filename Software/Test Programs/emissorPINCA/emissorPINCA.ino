#include <esp_now.h>
#include <WiFi.h>

// MAC del RECEPTOR
uint8_t broadcastAddress[] = {0x8C, 0xBF, 0xEA, 0x8E, 0xDD, 0x6C}; 

const int pinB1 = 4;  const int pinB2 = 5;  
const int pinB3 = 6;  const int pinB4 = 43; 

typedef struct struct_message {
  bool s1; bool s2; bool s3; bool s4;
} struct_message;

struct_message dades;
bool estatS3 = LOW; bool estatS4 = LOW;
bool ultimB3 = HIGH; bool ultimB4 = HIGH;
unsigned long ultimDebounce = 0;

void setup() {
  Serial.begin(115200);
  pinMode(pinB1, INPUT_PULLUP); pinMode(pinB2, INPUT_PULLUP);
  pinMode(pinB3, INPUT_PULLUP); pinMode(pinB4, INPUT_PULLUP);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  if (esp_now_init() != ESP_OK) return;
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  esp_now_add_peer(&peerInfo);
}

void loop() {
  bool b1 = (digitalRead(pinB1) == LOW);
  bool b2 = (digitalRead(pinB2) == LOW);

  // Lògica Interruptor B3 (SERVO)
  bool lectura3 = digitalRead(pinB3);
  if (ultimB3 == HIGH && lectura3 == LOW) {
    if (millis() - ultimDebounce > 250) {
      estatS3 = !estatS3;
      ultimDebounce = millis();
      Serial.print("Estat Servo: "); Serial.println(estatS3 ? "OBERT" : "TANCAT");
    }
  }
  ultimB3 = lectura3;

  bool b4 = (digitalRead(pinB4) == LOW); // El 4 el deixem com a pulsador normal

  if (dades.s1 != b1 || dades.s2 != b2 || dades.s3 != estatS3 || dades.s4 != b4) {
    dades.s1 = b1; dades.s2 = b2; dades.s3 = estatS3; dades.s4 = b4;
    esp_now_send(broadcastAddress, (uint8_t *) &dades, sizeof(dades));
  }
  delay(20);
}