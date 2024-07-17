const int reedSwitchPin = 32;  // Pino onde o reed switch está conectado
int reedState = 0;            // Variável para armazenar o estado do reed switch

void setup() {
  pinMode(reedSwitchPin, INPUT);  // Configura o pino do reed switch como entrada
  Serial.begin(9600);             // Inicializa a comunicação serial a 9600 bps
}

void loop() {
  reedState = digitalRead(reedSwitchPin);  // Lê o estado do reed switch

  if (reedState == LOW) {   // Se o reed switch está fechado (ímã próximo)
    Serial.println("Reed switch fechado");
  } else {
    Serial.println("Reed switch aberto");
  }
  delay(500);  // Atraso para evitar excesso de mensagens no monitor serial
}
