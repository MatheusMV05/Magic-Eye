#include <esp_now.h>
#include <WiFi.h>

//estrutura usada para armazenar os dados que serão enviados pela rede ESP-NOW e possui quantro campos 
typedef struct struct_message {
  char a[32]; //array de caracteres de tamanho 32
  int b;
  float c;
  bool d;
} struct_message;

//myData é uma instância da estrutura anterior que é usada para armazenar os dados a serem enviados
struct_message myData;

//um array de bytes que representa o endereço MAC do dispositivo receptor
uint8_t broadcastAddress[] = {0x24, 0x6F, 0x28, 0xDA, 0xF6, 0xB4};

//variáveis de status atual do sensor
string sensorpin16 = "off";
string sensorpin17 = "off"

//variáveis para os sensores 
const int sensorpin16 = 16;
const int sensorpin17 = 17;

//função de callback quando os dados forem enviados com sucesso ou falharem. Ele imprime uma mensagem na serial indicando o status de envio
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nStatus da Envio: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Enviado com Sucesso" : "Erro ao Enviar");
}

//é chamada uma vez quando o dispositivo é ligado:
// - inicializa a comunicação serial com taxa de 115200 bps
// - define o modo de operação do Wi-Fi como estação (STA)
// - imprime o endereço MAC do dispositivo
// - Inicializa a biblioteca ESP-OW e registra a função OnDataSent como callback de envio
// - Cria uma estrutura esp_now_peer_info_t que representa o dispositivo receptor e adiciona-o como peer
void setup() {
  Serial.begin(115200);

  pinMode(sensorpin16, OUTPUT); // marca o pin do sensor
  digitalWrite(sensorpin16, 0); // desliga o sensor por padrão 
  pinMode(sensorpin17, OUTPUT); // marca o pin do sensor
  digitalWrite(sensorpin17, 0); // desliga o sensor por padrão 
  WiFi.mode(WIFI_STA);
  Serial.println(WiFi.macAddress());

  if (esp_now_init() != ESP_OK) {
    Serial.println("Erro ao inicializar ESP-NOW");
    return;
  }
  Serial.println("ESP-NOW inicializado");

  esp_now_register_send_cb(OnDataSent);

  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Erro ao adicionar peer");
    return;
  }
}

// Este setup faz:
// - preenche a estrutura muData com dados aleatórios
// - envia os dados para o dispositivo receptor usando a função esp_now_send
// - imprime uma mensagem na serial indicando se os dados foram enviados com sucesso ou falharam
// - aguarda 5 segundos antes de enviar novamente
void loop() {
  strcpy(myData.a, "Mensagem de envio para o receptor: Olá");
  myData.b = random(1,20);
  myData.c = 1.2;
  myData.d = false;

  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

  if (result == ESP_OK) {
    Serial.println("Dados enviados com sucesso");
  }
  else {
    Serial.println("Erro ao enviar dados");
  }
  delay(5000);
}
