const int reedSwitchPin1 = 32; 
const int reedSwitchPin2 = 26;
int reedState1 = 0;            // Variável para armazenar o estado do reed switch
int reedState2 = 0;            // Variável para armazenar o estado do reed switch

void setup() {
  pinMode(reedSwitchPin1, INPUT);   // pino para o primeiro reedSwitch  
  pinMode(reedSwitchPin2, INPUT);  // pino para o segundo reedSwitch
  Serial.begin(9600);             // Inicializa a comunicação serial a 9600 bps
}

void loop() {
  reedState1 = digitalRead(reedSwitchPin1);  // Lê o estado do primeiro reed switch
  reedState2 = digitalRead(reedSwitchPin2);  // Lê o estado do segundo reed switch
  if (reedState1 == LOW) {   // Se o reed switch está fechado (ímã próximo)
    Serial.println("Reed switch 1 fechado");
  } else {
    Serial.println("Reed switch 1 aberto");
  }

  if (reedState2 == LOW) {   // Se o reed switch está fechado (ímã próximo)
    Serial.println("Reed switch 2 fechado");
  } else {
    Serial.println("Reed switch 2 aberto");
  }

  delay(500);  // Atraso para evitar excesso de mensagens no monitor serial
}
