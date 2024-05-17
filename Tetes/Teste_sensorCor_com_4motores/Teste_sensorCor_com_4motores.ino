#include <TCS3200.h>

// Definição dos pinos dos motores
const int motor1Pin1 = 2;
const int motor1Pin2 = 3;
const int motor2Pin1 = 4;
const int motor2Pin2 = 5;
const int motor3Pin1 = 6;
const int motor3Pin2 = 7;
const int motor4Pin1 = 8;
const int motor4Pin2 = 9;

// Definição dos pinos do sensor de cor esquerdo
const int leftS0 = 22;
const int leftS1 = 24;
const int leftS2 = 26;
const int leftS3 = 28;
const int leftOut = 30;

// Definição dos pinos do sensor de cor direito
const int rightS0 = 32;
const int rightS1 = 34;
const int rightS2 = 36;
const int rightS3 = 38;
const int rightOut = 40;

// Criação dos objetos do sensor de cor
TCS3200 leftSensor(leftS0, leftS1, leftS2, leftS3, leftOut);
TCS3200 rightSensor(rightS0, rightS1, rightS2, rightS3, rightOut);

void setup() {
  // Inicializa os pinos dos motores como saída
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(motor3Pin1, OUTPUT);
  pinMode(motor3Pin2, OUTPUT);
  pinMode(motor4Pin1, OUTPUT);
  pinMode(motor4Pin2, OUTPUT);

  // Inicializa a comunicação serial para depuração
  Serial.begin(9600);

  // Inicializa os sensores de cor
  leftSensor.begin();
  rightSensor.begin();
}

void loop() {
  // Ler a cor detectada pelos sensores
  bool leftDetectedGreen = isGreenDetected(leftSensor);
  bool rightDetectedGreen = isGreenDetected(rightSensor);

  // Depuração: imprime os valores detectados no Monitor Serial
  Serial.print("Left Sensor: ");
  Serial.print(leftDetectedGreen);
  Serial.print("  Right Sensor: ");
  Serial.println(rightDetectedGreen);

  // Lógica de controle dos motores
  if (leftDetectedGreen && rightDetectedGreen) {
    // Curva de 180 graus
    turnAround();
  } else if (leftDetectedGreen) {
    // Curva de 90 graus para a esquerda
    turnLeft();
  } else if (rightDetectedGreen) {
    // Curva de 90 graus para a direita
    turnRight();
  } else {
    // Continua em frente
    moveForward();
  }

  delay(100); // Pausa para estabilização
}

bool isGreenDetected(TCS3200 &sensor) {
  sensor.setFilter(TCS3200::FILTER_GREEN);
  delay(100); // Aguarda a leitura estabilizar
  int greenFrequency = sensor.read();

  // Defina o limiar de frequência para detectar a cor verde
  int greenThreshold = 200; // Ajuste conforme necessário
  return greenFrequency > greenThreshold;
}

void moveForward() {
  // Move todos os motores para frente
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  digitalWrite(motor3Pin1, HIGH);
  digitalWrite(motor3Pin2, LOW);
  digitalWrite(motor4Pin1, HIGH);
  digitalWrite(motor4Pin2, LOW);
}

void turnRight() {
  // Curva de 90 graus para a direita (motores esquerdos para frente, motores direitos para trás)
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  digitalWrite(motor3Pin1, LOW);
  digitalWrite(motor3Pin2, HIGH);
  digitalWrite(motor4Pin1, LOW);
  digitalWrite(motor4Pin2, HIGH);
  delay(500); // Ajuste o tempo para completar a curva de 90 graus
  stopMotors();
}

void turnLeft() {
  // Curva de 90 graus para a esquerda (motores direitos para frente, motores esquerdos para trás)
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  digitalWrite(motor3Pin1, HIGH);
  digitalWrite(motor3Pin2, LOW);
  digitalWrite(motor4Pin1, HIGH);
  digitalWrite(motor4Pin2, LOW);
  delay(500); // Ajuste o tempo para completar a curva de 90 graus
  stopMotors();
}

void turnAround() {
  // Curva de 180 graus (todos os motores giram no sentido oposto)
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  digitalWrite(motor3Pin1, LOW);
  digitalWrite(motor3Pin2, HIGH);
  digitalWrite(motor4Pin1, LOW);
  digitalWrite(motor4Pin2, HIGH);
  delay(1000); // Ajuste o tempo para completar a curva de 180 graus
  stopMotors();
}

void stopMotors() {
  // Para todos os motores
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  digitalWrite(motor3Pin1, LOW);
  digitalWrite(motor3Pin2, LOW);
  digitalWrite(motor4Pin1, LOW);
  digitalWrite(motor4Pin2, LOW);
}
