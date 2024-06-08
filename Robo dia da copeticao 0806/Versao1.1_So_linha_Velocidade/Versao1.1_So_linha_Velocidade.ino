#include <Wire.h>

// Definição dos pinos dos motores
const int motor1Pin1 = 2;
const int motor1Pin2 = 3;
const int motor2Pin1 = 4;
const int motor2Pin2 = 5;
const int motor3Pin1 = 6;
const int motor3Pin2 = 7;
const int motor4Pin1 = 8;
const int motor4Pin2 = 9;

// Definição dos pinos do sensor ultrassônico
const int trigPin = 12;
const int echoPin = 13;

// Definição dos pinos dos sensores de linha
const int lineSensorLeft = 44;
const int lineSensorRight = 46;

// Variáveis para controle de tempo
unsigned long lastLineDetectionTime = 0;
const unsigned long lineDetectionTimeout = 5000; // 5 segundos


// Funções de controle dos motores
void avancar();
void pararMotores();
void virarEsquerda();
void virarDireita();
void virarParaTras();

int velocidade = 128;

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


  // Inicialização dos sensores de linha
  pinMode(lineSensorLeft, INPUT);
  pinMode(lineSensorRight, INPUT);

  // Inicialização do sensor ultrassônico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Inicialização da comunicação serial
  Serial.begin(9600);
}

void loop() {
  

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
  digitalWrite(motor1Pin1, velocidade);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, velocidade);
  digitalWrite(motor2Pin2, LOW);
  digitalWrite(motor3Pin1, velocidade);
  digitalWrite(motor3Pin2, LOW);
  digitalWrite(motor4Pin1, velocidade);
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
  digitalWrite(motor1Pin2, velocidade);
  digitalWrite(motor2Pin1, velocidade);
  digitalWrite(motor2Pin2, LOW);
  digitalWrite(motor3Pin1, LOW);
  digitalWrite(motor3Pin2, velocidade);
  digitalWrite(motor4Pin1, velocidade);
  digitalWrite(motor4Pin2, LOW);
}

void virarDireita() {
  digitalWrite(motor1Pin1, velocidade);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, velocidade);
  digitalWrite(motor3Pin1, velocidade);
  digitalWrite(motor3Pin2, LOW);
  digitalWrite(motor4Pin1, LOW);
  digitalWrite(motor4Pin2, velocidade);
}

void virarParaTras() {
  virarEsquerda();
  delay(1000);
  virarEsquerda();
  delay(1000);
}
