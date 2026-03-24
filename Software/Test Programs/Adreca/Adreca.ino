#include "WiFi.h"

void setup(){
  // 1. Iniciem el port sèrie
  Serial.begin(115200);
  
  // 2. Esperem una mica que el port USB de Windows es desperti
  delay(2000); 

  // 3. Forcem el mode Estació (necessari per a la MAC)
  WiFi.mode(WIFI_STA);
  delay(500);

  Serial.println("");
  Serial.println("-----------------------------------");
  Serial.print("ADREÇA MAC: ");
  Serial.println(WiFi.macAddress());
  Serial.println("-----------------------------------");
}

void loop(){
  // Ho repetim cada 3 segons per si de cas no ho has vist a la primera
  Serial.print("La meva MAC es: ");
  Serial.println(WiFi.macAddress());
  delay(3000);
}