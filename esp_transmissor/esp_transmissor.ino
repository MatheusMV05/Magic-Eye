#include <Wire.h>
#include <esp_now.h>
#include <WiFi.h>

uint8_t broadcastAddress[] = {0x24, 0x0A, 0xC4, 0x00, 0x00, 0x00}; // Endereço MAC da ESP-CAM

typedef struct struct_message {
  int estadoMaçaneta;
  int estadoPorta;
} struct_message;

struct_message myData;

const int sensorMaçaneta = 26; // Pin conectado ao sensor Reed da maçaneta
const int sensorPorta = 32; // Pin conectado ao sensor Reed da porta

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Status do envio: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Sucesso" : "Falha");
}

void setup() {
  Serial.begin(115200);
  pinMode(sensorMaçaneta, INPUT_PULLUP);
  pinMode(sensorPorta, INPUT_PULLUP);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Erro ao inicializar o ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Erro ao adicionar o peer");
    return;
  }
}

void loop() {
  myData.estadoMaçaneta = digitalRead(sensorMaçaneta);
  myData.estadoPorta = digitalRead(sensorPorta);

  if (myData.estadoMaçaneta == LOW && myData.estadoPorta == HIGH) {
    Serial.println("MAÇANETA ATIVADA");
    esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));
    delay(100);
  } else if (myData.estadoMaçaneta == HIGH && myData.estadoPorta == LOW) {
    Serial.println("PORTA ABERTA");
    esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));
    delay(100);
  }
}
