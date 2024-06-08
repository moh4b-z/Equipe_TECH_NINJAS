// Definição dos pinos dos motores
const int motor1Pin1 = 2;
const int motor1Pin2 = 3;
const int motor2Pin1 = 4;
const int motor2Pin2 = 5;
const int motor3Pin1 = 6;
const int motor3Pin2 = 7;
const int motor4Pin1 = 8;
const int motor4Pin2 = 9;

// Definição dos pinos dos sensores de linha
const int lineSensorLeft = 44;
const int lineSensorRight = 46;

// Funções de controle dos motores
void avancar();
void pararMotores();
void virarEsquerda();
void virarDireita();
void virarParaTras();

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

  Serial.begin(9600);
}

void loop() {
  // Ler as informações dos sensores de linha
  bool leftLine = digitalRead(lineSensorLeft) == LOW; // LOW significa linha preta detectada
  bool rightLine = digitalRead(lineSensorRight) == LOW; // LOW significa linha preta detectada

  // Monitorar as leituras dos sensores de linha
  Serial.print("Left Line: ");
  Serial.print(leftLine);
  Serial.print(" - Right Line: ");
  Serial.println(rightLine);

  // Seguir a linha com base nas leituras dos sensores
  seguirLinha(leftLine, rightLine);

  delay(100); // Pequeno atraso para estabilidade
}

void seguirLinha(bool leftLine, bool rightLine) {
  if (leftLine && rightLine) {
    avancar(); // Seguir em frente
  } else if (!leftLine && rightLine) {
    virarEsquerda(); // Ajustar para a esquerda
  } else if (leftLine && !rightLine) {
    virarDireita(); // Ajustar para a direita
  } else {
    pararMotores(); // Parar se nenhuma linha for detectada
  }
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
  digitalWrite(motor4Pin1, LOW);
  digitalWrite(motor4Pin2, HIGH);
}

void virarDireita() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  digitalWrite(motor3Pin1, HIGH);
  digitalWrite(motor3Pin2, LOW);
  digitalWrite(motor4Pin1, HIGH);
  digitalWrite(motor4Pin2, LOW);
}

void virarParaTras() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  digitalWrite(motor3Pin1, HIGH);
  digitalWrite(motor3Pin2, LOW);
  digitalWrite(motor4Pin1, LOW);
  digitalWrite(motor4Pin2, HIGH);
}
