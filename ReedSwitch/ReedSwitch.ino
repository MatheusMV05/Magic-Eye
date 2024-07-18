const int reedSwitchPinDoor = 32; 
const int reedSwitchPinHandle = 26;
int reedStateDoor = 0;            // Variável para armazenar o estado do reed switch
int reedStateHandle = 0;            // Variável para armazenar o estado do reed switch

void setup() {
  pinMode(reedSwitchPinDoor, INPUT);   // pino para o primeiro reedSwitch  
  pinMode(reedSwitchPinHandle, INPUT);  // pino para o segundo reedSwitch
  Serial.begin(9600);             // Inicializa a comunicação serial a 9600 bps
}

void loop() {
  reedStateDoor = digitalRead(reedSwitchPinDoor);  // Lê o estado do primeiro reed switch
  reedStateHandle = digitalRead(reedSwitchPinHandle);  // Lê o estado do segundo reed switch
  if (reedStateDoor == LOW) {   // Se o reed switch está fechado (ímã próximo)
    Serial.println("Reed switch Porta fechado");
  } else {
    Serial.println("Reed switch Porta aberto");
  }

  if (reedStateHandle == LOW) {   // Se o reed switch está fechado (ímã próximo)
    Serial.println("Reed switch Maçaneta fechado");
  } else {
    Serial.println("Reed switch Maçaneta aberto");
  }

  delay(500);  // Atraso para evitar excesso de mensagens no monitor serial
}
