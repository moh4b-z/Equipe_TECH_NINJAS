#include <Wire.h>
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

// Definição dos pinos dos sensores de linha
const int lineSensorLeft = 44;
const int lineSensorRight = 46;

// Giroscópio
MPU6050 mpu;

// Variáveis para controle de tempo
unsigned long lastLineDetectionTime = 0;
const unsigned long lineDetectionTimeout = 5000; // 5 segundos

// Funções de controle dos motores
void avancar();
void pararMotores();
void virarEsquerda();
void virarDireita();
void virarParaTras();

// Função de detecção de cores
String detectarCor(int S2, int S3, int out);

void setup() {
  // Inicialização dos motores
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(motor3Pin1, OUTPUT);
  pinMode(motor3Pin2, OUTPUT);
  pinMode(motor4Pin1, OUTPUT);
  pinMode(motor4Pin2, OUTPUT);

  // Inicialização dos sensores de cor
  pinMode(leftS0, OUTPUT);
  pinMode(leftS1, OUTPUT);
  pinMode(leftS2, OUTPUT);
  pinMode(leftS3, OUTPUT);
  pinMode(leftOut, INPUT);
  pinMode(rightS0, OUTPUT);
  pinMode(rightS1, OUTPUT);
  pinMode(rightS2, OUTPUT);
  pinMode(rightS3, OUTPUT);
  pinMode(rightOut, INPUT);

  // Configuração dos sensores de cor para máxima resolução
  digitalWrite(leftS0, HIGH);
  digitalWrite(leftS1, LOW);
  digitalWrite(rightS0, HIGH);
  digitalWrite(rightS1, LOW);

  // Inicialização dos sensores de linha
  pinMode(lineSensorLeft, INPUT);
  pinMode(lineSensorRight, INPUT);

  // Inicialização do sensor ultrassônico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Inicialização do giroscópio
  Wire.begin();
  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("Conexão com MPU6050 falhou");
    while (1);
  }

  // Inicialização da comunicação serial
  Serial.begin(9600);
}

void loop() {
  // Ler as informações dos sensores de cor
  String leftColor = detectarCor(leftS2, leftS3, leftOut);
  String rightColor = detectarCor(rightS2, rightS3, rightOut);

  // Ler as informações dos sensores de linha
  bool leftLine = digitalRead(lineSensorLeft);
  bool rightLine = digitalRead(lineSensorRight);

  // Atualizar o tempo da última detecção de linha
  if (leftLine || rightLine) {
    lastLineDetectionTime = millis();
  }

  // Verificar material reflexivo
  if (millis() - lastLineDetectionTime > lineDetectionTimeout) {
    FIM();
  }

  // Verificar obstáculos
  if (verificarDistancia() <= 5) {
    Desvio();
  }

  // Exibir informações no monitor serial
  Serial.println("=== Informações dos Sensores ===");
  Serial.println("Cor do Sensor Esquerdo: " + leftColor);
  Serial.println("Cor do Sensor Direito: " + rightColor);
  Serial.println("Sensor de Linha Esquerdo: " + String(leftLine));
  Serial.println("Sensor de Linha Direito: " + String(rightLine));
  Serial.println("===============================");

  // Verificar a condição para ativar a função "FIM"
  if (leftColor == "Vermelho" || rightColor == "Vermelho") {
    FIM();
  }

  // Controle do movimento do robô com base nos sensores de linha e cor
  if (leftColor == "Verde" && rightColor == "Verde") {
    virarParaTras();
  } else if (leftColor == "Verde") {
    virarEsquerda();
  } else if (rightColor == "Verde") {
    virarDireita();
  } else {
    seguirLinha(leftLine, rightLine);
  }

  delay(1000); // Delay de 1 segundo
}

void seguirLinha(bool leftLine, bool rightLine) {
  if (leftLine && rightLine) {
    avancar();
  } else if (!leftLine && rightLine) {
    virarEsquerda();
  } else if (leftLine && !rightLine) {
    virarDireita();
  } else {
    pararMotores();
  }
}

String detectarCor(int S2, int S3, int out) {
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  unsigned int redValue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);

  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  unsigned int whiteValue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);

  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  unsigned int blueValue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);

  digitalWrite(S2, HIGH);
  digitalWrite(S3, LOW);
  unsigned int greenValue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);

  int threshold = 200; // Ajuste conforme necessário

  if (redValue > threshold && redValue > greenValue && redValue > blueValue) {
    return "Vermelho";
  } else if (greenValue > threshold && greenValue > redValue && greenValue > blueValue) {
    return "Verde";
  } else if (blueValue > threshold && blueValue > redValue && blueValue > greenValue) {
    return "Azul";
  } else {
    return "Branco";
  }
}

float verificarDistancia() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;

  return distance;
}

void FIM() {
  pararMotores();
  delay(1000);
}

void Desvio() {
  virarEsquerda();
  delay(1000);
  avancar();
  delay(4000);
  virarDireita();
  delay(1000);
  avancar();
  delay(1000);
  virarDireita();
  delay(1000);
}

void avancar() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  digitalWrite(motor3Pin1, HIGH);
  digitalWrite(motor3Pin2, LOW);
  digitalWrite(motor4Pin1, HIGH);
  digitalWrite(motor4Pin2, LOW);
}

void pararMotores() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  digitalWrite(motor3Pin1, LOW);
  digitalWrite(motor3Pin2, LOW);
  digitalWrite(motor4Pin1, LOW);
  digitalWrite(motor4Pin2, LOW);
}

void virarEsquerda() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  digitalWrite(motor3Pin1, LOW);
  digitalWrite(motor3Pin2, HIGH);
  digitalWrite(motor4Pin1, HIGH);
  digitalWrite(motor4Pin2, LOW);
}

void virarDireita() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  digitalWrite(motor3Pin1, HIGH);
  digitalWrite(motor3Pin2, LOW);
  digitalWrite(motor4Pin1, LOW);
  digitalWrite(motor4Pin2, HIGH);
}

void virarParaTras() {
  virarEsquerda();
  delay(1000);
  virarEsquerda();
  delay(1000);
}
