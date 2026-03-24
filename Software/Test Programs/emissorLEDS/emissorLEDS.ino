#include <esp_now.h>
#include <WiFi.h>

// ================================================================
// 1. POSA AQUÍ LA MAC DEL TEU RECEPTOR (la que has tret abans)
// ================================================================
uint8_t broadcastAddress[] = {0x8C, 0xBF, 0xEA, 0x8E, 0xDD, 0x6C}; 

// Pins segons les proves que han funcionat
const int pinB1 = 4;  // D3 (Pulsador)
const int pinB2 = 5;  // D4 (Pulsador)
const int pinB3 = 6;  // D5 (Interruptor)
const int pinB4 = 43; // D6 (Interruptor)

typedef struct struct_message {
  bool s1; bool s2; bool s3; bool s4;
} struct_message;

struct_message dades;
bool estatS3 = LOW; bool estatS4 = LOW;
bool ultimB3 = HIGH; bool ultimB4 = HIGH;
unsigned long ultimDebounce = 0;

void OnDataSent(const esp_now_send_info_t *info, esp_now_send_status_t status) {
  // Opcional: per veure si arriba el senyal
  // Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Enviat OK" : "Error enviament");
}

void setup() {
  Serial.begin(115200);
  pinMode(pinB1, INPUT_PULLUP);
  pinMode(pinB2, INPUT_PULLUP);
  pinMode(pinB3, INPUT_PULLUP);
  pinMode(pinB4, INPUT_PULLUP);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != ESP_OK) return;
  esp_now_register_send_cb(OnDataSent);

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  esp_now_add_peer(&peerInfo);
  
  Serial.println("EMISSOR A PUNT");
}

void loop() {
  // Lògica Pulsadors (Directe)
  bool b1 = (digitalRead(pinB1) == LOW);
  bool b2 = (digitalRead(pinB2) == LOW);

  // Lògica Interruptor B3 (Toggle)
  bool lectura3 = digitalRead(pinB3);
  if (ultimB3 == HIGH && lectura3 == LOW) {
    if (millis() - ultimDebounce > 200) {
      estatS3 = !estatS3;
      ultimDebounce = millis();
    }
  }
  ultimB3 = lectura3;

  // Lògica Interruptor B4 (Toggle)
  bool lectura4 = digitalRead(pinB4);
  if (ultimB4 == HIGH && lectura4 == LOW) {
    if (millis() - ultimDebounce > 200) {
      estatS4 = !estatS4;
      ultimDebounce = millis();
    }
  }
  ultimB4 = lectura4;

  // Si hi ha canvis en algun estat, enviem la informació
  if (dades.s1 != b1 || dades.s2 != b2 || dades.s3 != estatS3 || dades.s4 != estatS4) {
    dades.s1 = b1; dades.s2 = b2; dades.s3 = estatS3; dades.s4 = estatS4;
    
    Serial.printf("Enviant estat: %d %d %d %d\n", dades.s1, dades.s2, dades.s3, dades.s4);
    esp_now_send(broadcastAddress, (uint8_t *) &dades, sizeof(dades));
  }
  delay(20);
}