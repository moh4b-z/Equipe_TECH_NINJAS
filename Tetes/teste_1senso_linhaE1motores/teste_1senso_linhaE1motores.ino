// Definição dos pinos para controle do motor na Motor Shield L293D
const int motorPin1 = 2;
const int motorPin2 = 3;

// Definição do pino do sensor de linha
const int lineSensorPin = A0;

void setup() {
  // Define os pinos do motor como saída
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);

  // Define o pino do sensor de linha como entrada
  pinMode(lineSensorPin, INPUT);

  // Inicializa a comunicação serial para depuração
  Serial.begin(9600);

  // Inicializa o motor para mover-se para frente
  moveForward();
}

void loop() {
  // Lê o valor do sensor de linha
  int sensorValue = digitalRead(lineSensorPin);

  // Depuração: imprime o valor do sensor no Monitor Serial
  Serial.print("Line Sensor: ");
  Serial.println(sensorValue);

  // Lógica para parar o motor se a linha for detectada
  if (sensorValue == HIGH) {
    stopMotor();
  } else {
    moveForward();
  }

  delay(100); // Pausa para estabilização
}

void moveForward() {
  // Move o motor para frente
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
}

void stopMotor() {
  // Para o motor
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
}
