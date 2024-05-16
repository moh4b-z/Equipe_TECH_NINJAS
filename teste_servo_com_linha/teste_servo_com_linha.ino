#include <Servo.h>

// Definição do pino do sensor de linha
const int lineSensorPin = A0;

// Criação do objeto servo
Servo myServo;

// Definição do pino do servo
const int servoPin = 9;

// Variável para armazenar o estado do servo
int servoState = 0; // 0: 0 graus, 1: 90 graus

void setup() {
  // Define o pino do sensor de linha como entrada
  pinMode(lineSensorPin, INPUT);

  // Anexa o servo ao pino designado
  myServo.attach(servoPin);

  // Inicializa o servo na posição 0 graus
  myServo.write(0);

  // Inicializa a comunicação serial para depuração
  Serial.begin(9600);
}

void loop() {
  // Lê o valor do sensor de linha
  int sensorValue = digitalRead(lineSensorPin);

  // Depuração: imprime o valor do sensor no Monitor Serial
  Serial.print("Line Sensor: ");
  Serial.println(sensorValue);

  // Controle do servo motor baseado no sensor de linha
  if (sensorValue == HIGH) {
    // Se a linha for detectada, altera o estado do servo
    if (servoState == 0) {
      // Se o servo estiver em 0 graus, gira para 90 graus
      myServo.write(90);
      servoState = 1;
    } else {
      // Se o servo estiver em 90 graus, gira para 0 graus
      myServo.write(0);
      servoState = 0;
    }

    // Espera um pouco para evitar múltiplas detecções rápidas
    delay(500);
  }

  delay(100); // Pausa para estabilização
}
