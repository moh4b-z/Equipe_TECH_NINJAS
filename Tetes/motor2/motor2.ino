// Definição dos pinos dos motores
const int motor1Pin1 = 2;
const int motor1Pin2 = 3;
const int motor2Pin1 = 4;
const int motor2Pin2 = 5;

void setup() {
  // Configura os pinos dos motores como saídas
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  // Inicializa a comunicação serial para depuração
  Serial.begin(9600);
  Serial.println("Teste dos motores iniciado");
}

void loop() {
  // Liga o Motor 1 para frente
  Serial.println("Motor 1 para frente");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  delay(2000);

  // Liga o Motor 1 para trás
  Serial.println("Motor 1 para trás");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  delay(2000);

  // Desliga o Motor 1
  Serial.println("Motor 1 desligado");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  delay(1000);

  // Liga o Motor 2 para frente
  Serial.println("Motor 2 para frente");
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  delay(2000);

  // Liga o Motor 2 para trás
  Serial.println("Motor 2 para trás");
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  delay(2000);

  // Desliga o Motor 2
  Serial.println("Motor 2 desligado");
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  delay(1000);

  // Liga ambos os motores para frente
  Serial.println("Ambos os motores para frente");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  delay(2000);

  // Liga ambos os motores para trás
  Serial.println("Ambos os motores para trás");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  delay(2000);

  // Desliga ambos os motores
  Serial.println("Ambos os motores desligados");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  delay(1000);
}
