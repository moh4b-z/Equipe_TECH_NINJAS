const int sensorPin = 7;  // Pino onde o sensor de linha está conectado
int sensorValue = 0;      // Variável para armazenar o valor lido do sensor

void setup() {
  Serial.begin(9600);     // Inicializa a comunicação serial a 9600 bps
  pinMode(sensorPin, INPUT);  // Define o pino do sensor como entrada
}

void loop() {
  sensorValue = digitalRead(sensorPin);  // Lê o valor do sensor de linha

  if (sensorValue == HIGH) {
    Serial.println("Linha detectada");   // Linha detectada
  } else {
    Serial.println("Linha não detectada");  // Linha não detectada
  }

  delay(500);  // Pausa de 500ms antes da próxima leitura
}
