#include <Wire.h>
#include <MPU6050.h>

// Definição dos pinos dos sensores de cor
const int leftS2 = 26;
const int leftS3 = 28;
const int leftOut = 30;

const int rightS2 = 36;
const int rightS3 = 38;
const int rightOut = 40;

// Definição dos pinos do sensor ultrassônico
const int trigPin = 12;
const int echoPin = 13;

MPU6050 mpu;

void setup() {
  // Inicializa a comunicação serial para depuração
  Serial.begin(9600);

  // Inicializa o giroscópio
  Wire.begin();
  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
    while (1);
  }

  // Configuração inicial dos pinos dos sensores de cor
  pinMode(leftS2, OUTPUT);
  pinMode(leftS3, OUTPUT);
  pinMode(leftOut, INPUT);

  pinMode(rightS2, OUTPUT);
  pinMode(rightS3, OUTPUT);
  pinMode(rightOut, INPUT);

  // Configura os pinos dos sensores de linha
  pinMode(10, INPUT);
  pinMode(11, INPUT);
}

void loop() {
  // Ler a cor detectada pelos sensores de cor
  String leftColor = detectColor(leftS2, leftS3, leftOut);
  String rightColor = detectColor(rightS2, rightS3, rightOut);

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

  // Verifica os sensores de linha
  Serial.print("Left Line Sensor: ");
  Serial.println(digitalRead(10) == HIGH ? "High" : "Low");
  Serial.print("Right Line Sensor: ");
  Serial.println(digitalRead(11) == HIGH ? "High" : "Low");

  Serial.println(); // Adiciona uma linha em branco para separar as leituras

  // Não há mais delay aqui para garantir que as leituras sejam exibidas continuamente
}

String detectColor(int pinS2, int pinS3, int pinOut) {
  // Detecta a cor vermelha
  digitalWrite(pinS2, LOW);
  digitalWrite(pinS3, LOW);
  unsigned int redValue = pulseIn(pinOut, digitalRead(pinOut) == HIGH ? LOW : HIGH);

  // Sem filtro
  digitalWrite(pinS2, HIGH);
  unsigned int whiteValue = pulseIn(pinOut, digitalRead(pinOut) == HIGH ? LOW : HIGH);

  // Detecta a cor azul
  digitalWrite(pinS2, LOW);
  digitalWrite(pinS3, HIGH);
  unsigned int blueValue = pulseIn(pinOut, digitalRead(pinOut) == HIGH ? LOW : HIGH);

  // Detecta a cor verde
  digitalWrite(pinS2, HIGH);
  unsigned int greenValue = pulseIn(pinOut, digitalRead(pinOut) == HIGH ? LOW : HIGH);

  // Define os limiares para a detecção das cores
  int threshold = 200; // Ajuste conforme necessário

  if (redValue > threshold && redValue > greenValue && redValue > blueValue) {
    return "Red";
  } else if (greenValue > threshold && greenValue > redValue && greenValue > blueValue) {
    return "Green";
  } else if (blueValue > threshold && blueValue > redValue && blueValue > greenValue) {
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
