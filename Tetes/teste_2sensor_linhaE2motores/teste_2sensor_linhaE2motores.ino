// Definição dos pinos para controle dos motores na Motor Shield L293D
const int motor1Pin1 = 2;
const int motor1Pin2 = 3;
const int motor2Pin1 = 4;
const int motor2Pin2 = 5;

// Definição dos pinos dos sensores de linha
const int leftSensorPin = A0;
const int rightSensorPin = A1;

void setup() {
  // Define os pinos dos motores como saída
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  // Define os pinos dos sensores de linha como entrada
  pinMode(leftSensorPin, INPUT);
  pinMode(rightSensorPin, INPUT);

  // Inicializa a comunicação serial para depuração
  Serial.begin(9600);
}

void loop() {
  // Lê o valor dos sensores de linha
  int leftSensorValue = digitalRead(leftSensorPin);
  int rightSensorValue = digitalRead(rightSensorPin);

  // Depuração: imprime os valores dos sensores no Monitor Serial
  Serial.print("Left Sensor: ");
  Serial.print(leftSensorValue);
  Serial.print("  Right Sensor: ");
  Serial.println(rightSensorValue);

  // Lógica de controle do carrinho
  if (leftSensorValue == HIGH && rightSensorValue == LOW) {
    // Linha detectada apenas pelo sensor esquerdo (curva para a direita)
    moveRight();
  } else if (leftSensorValue == LOW && rightSensorValue == HIGH) {
    // Linha detectada apenas pelo sensor direito (curva para a esquerda)
    moveLeft();
  } else if (leftSensorValue == LOW && rightSensorValue == LOW) {
    // Linha detectada por ambos os sensores (vai em frente)
    moveForward();
  } else {
    // Nenhuma linha detectada (para)
    stopMotors();
  }

  delay(100); // Pausa para estabilização
}

void moveForward() {
  // Move todos os motores para frente
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void moveRight() {
  // Curva para a direita (motor esquerdo para frente, motor direito para trás)
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

void moveLeft() {
  // Curva para a esquerda (motor direito para frente, motor esquerdo para trás)
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void stopMotors() {
  // Para todos os motores
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}
