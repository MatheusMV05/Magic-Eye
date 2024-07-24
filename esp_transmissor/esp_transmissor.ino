// Código para o ESP32 - Transmissor

#include <Wire.h>

const int sensorMaçaneta = 26; // Pin conectado ao sensor Reed da maçaneta
const int sensorPorta = 32; // Pin conectado ao sensor Reed da porta

void setup() {
  Serial.begin(115200);
  pinMode(sensorMaçaneta, INPUT_PULLUP);
  pinMode(sensorPorta, INPUT_PULLUP);
}

void loop() {
  int estadoMaçaneta = digitalRead(sensorMaçaneta);
  int estadoPorta = digitalRead(sensorPorta);

  if (estadoMaçaneta == LOW && estadoPorta == HIGH) { // Quando a maçaneta é ativada e a porta está fechada
    Serial.println("MAÇANETA ATIVADA");
    delay(100); // Aguarda um pouco antes de enviar outro sinal
  } else if (estadoMaçaneta == HIGH && estadoPorta == LOW) { // Quando ambos os sensores são ativados
    Serial.println("PORTA ABERTA");
    delay(100); // Aguarda um pouco antes de enviar outro sinal
  }
}
