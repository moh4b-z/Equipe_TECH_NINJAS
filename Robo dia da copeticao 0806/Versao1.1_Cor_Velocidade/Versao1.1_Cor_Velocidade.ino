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

// Variáveis para controle de tempo
unsigned long lastLineDetectionTime = 0;
const unsigned long lineDetectionTimeout = 5000; // 5 segundos

// Variável para controle da detecção de cor
bool deteccaoCorAtiva = true;
unsigned long tempoDesativacaoCor = 0;
const unsigned long duracaoDesativacaoCor = 1000; // 1 segundo

// Funções de controle dos motores
void avancar();
void pararMotores();
void virarEsquerda();
void virarDireita();
void virarParaTras();

// Função de detecção de cores
unsigned int valorVermelho = 0;
unsigned int valorVerde = 0;
unsigned int valorAzul = 0;
unsigned int valorBranco = 0;

unsigned int valorVermelhoR = 0;
unsigned int valorVerdeR = 0;
unsigned int valorAzulR = 0;
unsigned int valorBrancoR = 0;
void detectaCor();

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

  Serial.begin(9600);
  digitalWrite(leftS0, HIGH);
  digitalWrite(leftS1, LOW);
  digitalWrite(rightS0, HIGH);
  digitalWrite(rightS1, LOW);

  delay(2000);

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
  
  // Verifica se a detecção de cor está ativa
  if (deteccaoCorAtiva) {
    // Ler as informações dos sensores de cor
    detectaCor();
  }

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

  // Mostra valores no serial monitor esquerdo
  Serial.print("Vermelho esquerdo: ");
  Serial.print(valorVermelho);

  Serial.print(" Verde esquerdo: ");
  Serial.print(valorVerde);

  Serial.print(" Azul esquerdo: ");
  Serial.print(valorAzul);

  Serial.print(" Branco esquerdo: ");
  Serial.print(valorBranco);
  Serial.println();
  
  // Mostra valores no serial monitor direito
  Serial.print("Vermelho direito: ");
  Serial.print(valorVermelhoR);

  Serial.print(" Verde direito: ");
  Serial.print(valorVerdeR);

  Serial.print(" Azul direito: ");
  Serial.print(valorAzulR);

  Serial.print(" Branco direito: ");
  Serial.print(valorBrancoR);
  Serial.println();

  // Verifica se a cor preta foi detectada
  if ((valorVermelho < 50) &&
      (valorVerde < 50) &&
      (valorAzul < 50) &&
      (valorBranco < 50)) {
    // Desativa a detecção de cor por 1 segundo
    deteccaoCorAtiva = false;
    tempoDesativacaoCor = millis();
  }

  // Verifica se o tempo de desativação da detecção de cor foi atingido
  if (!deteccaoCorAtiva && (millis() - tempoDesativacaoCor >= duracaoDesativacaoCor)) {
    // Reativa a detecção de cor
    deteccaoCorAtiva = true;
  }

  // Verifica se a cor vermelha foi detectada no sensor esquerdo
  if ((valorVermelho < valorAzul) &&
      (valorVermelho < valorVerde) &&
      (valorBranco < 100) && 
      (valorVermelhoR < valorAzulR) &&
      (valorVermelhoR < valorVerdeR) &&
      (valorBrancoR < 100)) {
    Serial.println("Vermelho nos dois");
    FIM();
  } else if ((valorAzul < valorVermelho) &&  // Verifica se a cor azul foi detectada
             (valorAzul < valorVerde) &&
             (valorBranco < 100)) {
    Serial.println("Azul no esquerdo");
  } else if ((valorVerde < valorVermelho) &&  // Verifica se a cor verde foi detectada
             (valorVerde < valorAzul) &&
             (valorBranco < 100)) {
    Serial.println("Verde no esquerdo");
    virarEsquerda();
  } else if ((valorVermelho < 50) && (valorVerde < 50) && (valorAzul < 50) && (valorBranco < 50)) { // Verifica se a cor preta foi detectada
    Serial.println("Preto no esquerdo");
  }
  Serial.println();
  
  // Verifica se a cor vermelha foi detectada no sensor direito
  if ((valorVermelhoR < valorAzulR) &&
      (valorVermelhoR < valorVerdeR) &&
      (valorBrancoR < 100)) {
    Serial.println("Vermelho no direito");
  } else if ((valorAzulR < valorVermelhoR) &&  // Verifica se a cor azul foi detectada
             (valorAzulR < valorVerdeR) &&
             (valorBrancoR < 100)) {
    Serial.println("Azul no direito");
  } else if ((valorVerdeR < valorVermelhoR) &&  // Verifica se a cor verde foi detectada
             (valorVerdeR < valorAzulR) &&
             (valorBrancoR < 100)) {
    Serial.println("Verde no direito");
    virarDireita();
  } else if ((valorVermelhoR < 50) && (valorVerdeR < 50) && (valorAzulR < 50) && (valorBrancoR < 50)) { // Verifica se a cor preta foi detectada
    Serial.println("Preto no direito");
  } else if ((valorVerdeR < valorVermelhoR) &&  // Verifica se a cor verde foi detectada nos dois
             (valorVerdeR < valorAzulR) &&
             (valorBrancoR < 100) && 
             (valorVerde < valorVermelho) &&
             (valorVerde < valorAzul) &&
             (valorBranco < 100)) {
    Serial.println("Verde nos dois");
    virarParaTras();
  }
  Serial.println();
  delay(1000);
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

void detectaCor() {
  // Vermelho esquerdo
  digitalWrite(leftS2, LOW);
  digitalWrite(leftS3, LOW);
  valorVermelho = pulseIn(leftOut, digitalRead(leftOut) == HIGH ? LOW : HIGH);

  // Sem filtro esquerdo
  digitalWrite(leftS2, HIGH);
  valorBranco = pulseIn(leftOut, digitalRead(leftOut) == HIGH ? LOW : HIGH);

  // Azul esquerdo
  digitalWrite(leftS2, LOW);
  digitalWrite(leftS3, HIGH);
  valorAzul = pulseIn(leftOut, digitalRead(leftOut) == HIGH ? LOW : HIGH);

  // Verde esquerdo
  digitalWrite(leftS2, HIGH);
  valorVerde = pulseIn(leftOut, digitalRead(leftOut) == HIGH ? LOW : HIGH);


  // Vermelho direito
  digitalWrite(rightS2, LOW);
  digitalWrite(rightS3, LOW);
  valorVermelhoR = pulseIn(rightOut, digitalRead(rightOut) == HIGH ? LOW : HIGH);

  // Sem filtro direito
  digitalWrite(rightS2, HIGH);
  valorBrancoR = pulseIn(rightOut, digitalRead(rightOut) == HIGH ? LOW : HIGH);

  // Azul direito
  digitalWrite(rightS2, LOW);
  digitalWrite(rightS3, HIGH);
  valorAzulR = pulseIn(rightOut, digitalRead(rightOut) == HIGH ? LOW : HIGH);

  // Verde direito
  digitalWrite(rightS2, HIGH);
  valorVerdeR = pulseIn(rightOut, digitalRead(rightOut) == HIGH ? LOW : HIGH);
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
