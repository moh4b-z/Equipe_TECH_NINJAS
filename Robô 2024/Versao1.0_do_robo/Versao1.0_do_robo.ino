#include <Wire.h>
#include <TCS3200.h>
#include <MPU6050.h>

// Definição dos pinos dos motores
const int motor1Pin1 = 2;
const int motor1Pin2 = 3;
const int motor2Pin1 = 4;
const int motor2Pin2 = 5;
const int motor3Pin1 = 6;
const int motor3Pin2 = 7;
const int motor4Pin1 = 8;
const int motor4Pin2 = 9;

// Definição dos pinos dos sensores de cor
const int leftS0 = 22;
const int leftS1 = 24;
const int leftS2 = 26;
const int leftS3 = 28;
const int leftOut = 30;

const int rightS0 = 32;
const int rightS1 = 34;
const int rightS2 = 36;
const int rightS3 = 38;
const int rightOut = 40;

// Definição dos pinos do sensor ultrassônico
const int trigPin = 12;
const int echoPin = 13;

// Criação dos objetos do sensor de cor
TCS3200 leftSensor(leftS0, leftS1, leftS2, leftS3, leftOut);
TCS3200 rightSensor(rightS0, rightS1, rightS2, rightS3, rightOut);

// Criação do objeto do giroscópio
MPU6050 mpu;

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

  // Inicializa os pinos do sensor ultrassônico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Inicializa o giroscópio
  Wire.begin();
  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
    while (1);
  }
}

void loop() {
  // Ler a cor detectada pelos sensores de cor
  bool leftDetectedGreen = isGreenDetected(leftSensor);
  bool rightDetectedGreen = isGreenDetected(rightSensor);

  // Ler a distância do sensor ultrassônico
  long distance = readUltrasonicDistance(trigPin, echoPin);

  // Ler o ângulo do giroscópio
  float angle = readAngle();

  // Controla a velocidade dos motores com base no ângulo do giroscópio
  int motorSpeed;
  if (angle > 18) {
    motorSpeed = 255; // 100% da velocidade
  } else if (angle < -5) {
    motorSpeed = 51; // 20% da velocidade máxima (255 * 0.2)
  } else {
    motorSpeed = 204; // 80% da velocidade máxima (255 * 0.8)
  }

  // Lógica de controle dos motores
  if (distance < 5) {  // Ajuste a distância conforme necessário
    // Executa a manobra especial ao detectar um obstáculo próximo
    specialManeuver();
  } else if (leftDetectedGreen && rightDetectedGreen) {
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
    moveForward(motorSpeed);
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

long readUltrasonicDistance(int trigPin, int echoPin) {
  // Envia um pulso de 10us ao pino de trigger
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Mede o tempo de resposta do pino de echo
  long duration = pulseIn(echoPin, HIGH);

  // Calcula a distância em centímetros
  long distance = duration * 0.034 / 2;

  return distance;
}

float readAngle() {
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  return atan2(ay, az) * 180 / PI; // Calcula o ângulo de inclinação
}

void moveForward(int speed) {
  // Move todos os motores para frente com velocidade controlada
  analogWrite(motor1Pin1, speed);
  analogWrite(motor1Pin2, 0);
  analogWrite(motor2Pin1, speed);
  analogWrite(motor2Pin2, 0);
  analogWrite(motor3Pin1, speed);
  analogWrite(motor3Pin2, 0);
  analogWrite(motor4Pin1, speed);
  analogWrite(motor4Pin2, 0);
}

void turnRight() {
  // Curva de 90 graus para a direita (motores esquerdos para frente, motores direitos para trás)
  analogWrite(motor1Pin1, 255);
  analogWrite(motor1Pin2, 0);
  analogWrite(motor2Pin1, 255);
  analogWrite(motor2Pin2, 0);
  analogWrite(motor3Pin1, 0);
  analogWrite(motor3Pin2, 255);
  analogWrite(motor4Pin1, 0);
  analogWrite(motor4Pin2, 255);
  delay(500); // Ajuste o tempo para completar a curva de 90 graus
  stopMotors();
}

void turnLeft() {
  // Curva de 90 graus para a esquerda (motores direitos para frente, motores esquerdos para trás)
  analogWrite(motor1Pin1, 0);
  analogWrite(motor1Pin2, 255);
  analogWrite(motor2Pin1, 0);
  analogWrite(motor2Pin2, 255);
  analogWrite(motor3Pin1, 255);
  analogWrite(motor3Pin2, 0);
  analogWrite(motor4Pin1, 255);
  analogWrite(motor4Pin2, 0);
  delay(500); // Ajuste o tempo para completar a curva de 90 graus
  stopMotors();
}

void turnAround() {
  // Curva de 180 graus (todos os motores giram no sentido oposto)
  analogWrite(motor1Pin1, 0);
  analogWrite(motor1Pin2, 255);
  analogWrite(motor2Pin1, 0);
  analogWrite(motor2Pin2, 255);
  analogWrite(motor3Pin1, 0);
  analogWrite(motor3Pin2, 255);
  analogWrite(motor4Pin1, 0);
  analogWrite(motor4Pin2, 255);
  delay(1000); // Ajuste o tempo para completar a curva de 180 graus
  stopMotors();
}

void stopMotors() {
  // Para todos os motores
  analogWrite(motor1Pin1, 0);
  analogWrite(motor1Pin2, 0);
  analogWrite(motor2Pin1, 0);
  analogWrite(motor2Pin2, 0);
  analogWrite(motor3Pin1, 0);
  analogWrite(motor3Pin2, 0);
  analogWrite(motor4Pin1, 0);
  analogWrite(motor4Pin2, 0);
}

void specialManeuver() {
  // Curva de 90 graus para a direita
  turnRight();
  delay(500); // Aguarda a curva completar
  stopMotors();
  
  // Anda para frente por 0,5 segundos
  moveForward(255);
  delay(500);
  stopMotors();
  
  // Curva de 90 graus para a esquerda
  turnLeft();
  delay(500);
  stopMotors();
  
  // Anda para frente por 2 segundos
  moveForward(255);
  delay(2000);
  stopMotors();
  
  // Curva de 90 graus para a esquerda
  turnLeft();
  delay(500);
  stopMotors();
  
  // Anda para frente por 0,5 segundos
  moveForward(255);
  delay(500);
  stopMotors();
  
  // Curva de 90 graus para a esquerda
  turnLeft();
  delay(500);
  stopMotors();
  
  // Anda para frente por 0,5 segundos
  moveForward(255);
  delay(500);
  stopMotors();
  
  // Verifica se uma linha foi detectada durante o percurso
  bool leftDetectedGreen = isGreenDetected(leftSensor);
  bool rightDetectedGreen = isGreenDetected(rightSensor);
  
  if (leftDetectedGreen || rightDetectedGreen) {
    // Continua seguindo a linha
    return;
  }
}
