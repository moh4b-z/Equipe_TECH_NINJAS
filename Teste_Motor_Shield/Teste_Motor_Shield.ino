// Definição dos pinos para controle dos motores na Motor Shield L293D
const int motor1Pin1 = 2;  // Pino para controle do motor 1 (sentido 1)
const int motor1Pin2 = 3;  // Pino para controle do motor 1 (sentido 2)
const int motor2Pin1 = 4;  // Pino para controle do motor 2 (sentido 1)
const int motor2Pin2 = 5;  // Pino para controle do motor 2 (sentido 2)
const int motor3Pin1 = 6;  // Pino para controle do motor 3 (sentido 1)
const int motor3Pin2 = 7;  // Pino para controle do motor 3 (sentido 2)
const int motor4Pin1 = 8;  // Pino para controle do motor 4 (sentido 1)
const int motor4Pin2 = 9;  // Pino para controle do motor 4 (sentido 2)

void setup() {
  // Define os pinos como saída
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(motor3Pin1, OUTPUT);
  pinMode(motor3Pin2, OUTPUT);
  pinMode(motor4Pin1, OUTPUT);
  pinMode(motor4Pin2, OUTPUT);

  // Inicia com os motores parados
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  digitalWrite(motor3Pin1, LOW);
  digitalWrite(motor3Pin2, LOW);
  digitalWrite(motor4Pin1, LOW);
  digitalWrite(motor4Pin2, LOW);
}

void loop() {
  // Gira os motores 1 e 2 para frente por 5 segundos
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);

  // Gira os motores 3 e 4 para frente por 5 segundos
  digitalWrite(motor3Pin1, HIGH);
  digitalWrite(motor3Pin2, LOW);
  digitalWrite(motor4Pin1, HIGH);
  digitalWrite(motor4Pin2, LOW);

  delay(5000);  // Mantém os motores girando por 5 segundos

  // Pausa por 0,5 segundos
  delay(500);

  // Gira os motores 1 e 2 para trás por 5 segundos
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);

  // Gira os motores 3 e 4 para trás por 5 segundos
  digitalWrite(motor3Pin1, LOW);
  digitalWrite(motor3Pin2, HIGH);
  digitalWrite(motor4Pin1, LOW);
  digitalWrite(motor4Pin2, HIGH);

  delay(5000);  // Mantém os motores girando por 5 segundos

  // Pausa por 0,5 segundos
  delay(500);
}
