#include <WiFi.h>

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Substitua pelo endereço IP da sua ESP-CAM
const char* camIP = "192.168.1.XX";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
}

void loop() {
  int sensor1State = digitalRead(15);
  int sensor2State = digitalRead(13);

  if (sensor1State == LOW) { // Sensor 1 ativado
    sendCommand(camIP, "/startRecording"); // Começa a gravação
    delay(10000); // Espera 10 segundos
    sendCommand(camIP, "/stopRecording"); // Para a gravação
  } else if (sensor2State == LOW) { // Sensor 2 ativado
    sendCommand(camIP, "/deleteVideo"); // Comando para apagar o vídeo
  }
}

void sendCommand(String ip, String command) {
  WiFiClient client;
  if (!client.connect(ip, 80)) {
    return;
  }

  client.println("GET /" + command + " HTTP/1.0");
  client.println("Host: " + ip);
  client.println("Connection: close");
  client.println();
  
  delay(1000);
  client.stop();
}
