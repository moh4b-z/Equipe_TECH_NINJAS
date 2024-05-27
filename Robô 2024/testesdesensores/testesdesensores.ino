#include <Wire.h>
#include <TCS3200.h>
#include <MPU6050.h>

// Definição dos pinos dos motores (não utilizados neste código)
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
  String leftColor = detectColor(leftSensor);
  String rightColor = detectColor(rightSensor);

  // Ler a distância do sensor ultrassônico
  long distance = readUltrasonicDistance(trigPin, echoPin);

  // Ler o ângulo do giroscópio
  float angle = readAngle();

  // Mostrar as informações no monitor serial
  Serial.print("Left Color Sensor: ");
  Serial.println(leftColor);
  Serial.print("Right Color Sensor: ");
  Serial.println(rightColor);
  Serial.print("Ultrasonic Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  Serial.print("Gyroscope Angle: ");
  Serial.print(angle);
  Serial.println(" degrees");

  delay(1000); // Pausa de 1 segundo antes da próxima leitura
}

String detectColor(TCS3200 &sensor) {
  // Detecta a cor vermelha
  sensor.setFilter(TCS3200::FILTER_RED);
  delay(100);
  int redFrequency = sensor.read();

  // Detecta a cor verde
  sensor.setFilter(TCS3200::FILTER_GREEN);
  delay(100);
  int greenFrequency = sensor.read();

  // Detecta a cor azul
  sensor.setFilter(TCS3200::FILTER_BLUE);
  delay(100);
  int blueFrequency = sensor.read();

  // Define os limiares para a detecção das cores
  int threshold = 200; // Ajuste conforme necessário

  if (redFrequency > threshold && redFrequency > greenFrequency && redFrequency > blueFrequency) {
    return "Red";
  } else if (greenFrequency > threshold && greenFrequency > redFrequency && greenFrequency > blueFrequency) {
    return "Green";
  } else if (blueFrequency > threshold && blueFrequency > redFrequency && blueFrequency > greenFrequency) {
    return "Blue";
  } else {
    return "Unknown";
  }
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
