#include <esp_now.h>
#include <WiFi.h>
#include "esp_camera.h"
#include "FS.h"
#include "SD_MMC.h"

typedef struct struct_message {
  int estadoMaçaneta;
  int estadoPorta;
} struct_message;

struct_message incomingData;

void OnDataRecv(const esp_now_recv_info_t *info, const uint8_t *data, int len) {
  memcpy(&incomingData, data, sizeof(incomingData));
  Serial.print("Dados recebidos - Maçaneta: ");
  Serial.print(incomingData.estadoMaçaneta);
  Serial.print(", Porta: ");
  Serial.println(incomingData.estadoPorta);

  if (incomingData.estadoMaçaneta == LOW && incomingData.estadoPorta == HIGH) {
    iniciarGravacao();
  }
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Erro ao inicializar ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = 5;
  config.pin_d1 = 18;
  config.pin_d2 = 19;
  config.pin_d3 = 21;
  config.pin_d4 = 36;
  config.pin_d5 = 39;
  config.pin_d6 = 34;
  config.pin_d7 = 35;
  config.pin_xclk = 0;
  config.pin_pclk = 22;
  config.pin_vsync = 25;
  config.pin_href = 23;
  config.pin_sscb_sda = 26;
  config.pin_sscb_scl = 27;
  config.pin_pwdn = 32;
  config.pin_reset = -1;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  if (psramFound()) {
    config.frame_size = FRAMESIZE_VGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_QVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

  if (esp_camera_init(&config) != ESP_OK) {
    Serial.println("Erro ao inicializar a câmera");
    return;
  }

  if (!SD_MMC.begin()) {
    Serial.println("Erro ao inicializar o cartão SD");
    return;
  }
}

void loop() {
  // Nada a ser feito no loop principal
}

void iniciarGravacao() {
  camera_fb_t * fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Falha ao capturar a imagem");
    return;
  }

  File file = SD_MMC.open("/captura.jpg", FILE_WRITE);
  if (!file) {
    Serial.println("Falha ao abrir o arquivo no cartão SD");
    esp_camera_fb_return(fb);
    return;
  }

  file.write(fb->buf, fb->len);
  Serial.println("Imagem capturada e salva no cartão SD");

  file.close();
  esp_camera_fb_return(fb);
}
