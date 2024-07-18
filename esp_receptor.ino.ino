#include <esp_now.h>
#include <WiFi.h>

// Estrutura para receber dados
typedef struct struct_message {
  char a[32];
  int b;
  float c;
  bool d;
} struct_message;

struct_message incomingData;

void OnDataRecv(const esp_now_recv_info *info, const uint8_t *data, int len) {
  // Copia os dados recebidos para a estrutura
  memcpy(&incomingData, data, sizeof(incomingData));
  
  // Exibe os dados recebidos
  Serial.print("Bytes recebidos: ");
  Serial.println(len);
  Serial.print("String: ");
  Serial.println(incomingData.a);
  Serial.print("Inteiro: ");
  Serial.println(incomingData.b);
  Serial.print("Float: ");
  Serial.println(incomingData.c);
  Serial.print("Bool: ");
  Serial.println(incomingData.d);
}

void setup() {
  Serial.begin(115200);

  // Inicializa Wi-Fi
  WiFi.mode(WIFI_STA);
  Serial.println(WiFi.macAddress());

  // Inicializa ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Erro ao inicializar ESP-NOW");
    return;
  }
  Serial.println("ESP-NOW inicializado");

  // Registra callback
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // Loop vazio
}
