// Definição dos pinos dos motores
const int motor1Pin1 = 2;
const int motor1Pin2 = 3;
const int motor2Pin1 = 4;
const int motor2Pin2 = 5;

// Definição dos pinos dos sensores de linha
const int lineSensorLeft = 10;
const int lineSensorRight = 11;

void setup() {
  // Configura os pinos dos motores como saída
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  
  // Configura os pinos dos sensores de linha como entrada
  pinMode(lineSensorLeft, INPUT);
  pinMode(lineSensorRight, INPUT);

  // Inicializa a comunicação serial para depuração
  Serial.begin(9600);
  Serial.println("Iniciando o robô seguidor de linha...");
}

void loop() {
  // Ler os valores dos sensores de linha
  bool leftSensorValue = digitalRead(lineSensorLeft);
  bool rightSensorValue = digitalRead(lineSensorRight);

  // Mostrar os valores dos sensores no monitor serial para depuração
  Serial.print("Sensor Esquerdo: ");
  Serial.print(leftSensorValue);
  Serial.print(" | Sensor Direito: ");
  Serial.println(rightSensorValue);

  // Lógica de controle dos motores com base nos sensores de linha
  if (leftSensorValue == LOW && rightSensorValue == LOW) {
    // Ambos os sensores estão fora da linha (linha preta)
    pararMotores();
  } else if (leftSensorValue == HIGH && rightSensorValue == LOW) {
    // Apenas o sensor esquerdo está na linha (linha preta)
    virarEsquerda();
  } else if (leftSensorValue == LOW && rightSensorValue == HIGH) {
    // Apenas o sensor direito está na linha (linha preta)
    virarDireita();
  } else {
    // Ambos os sensores estão na linha (linha branca)
    moverFrente();
  }

  delay(50); // Pequeno atraso para evitar leituras muito rápidas
}

void moverFrente() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void pararMotores() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

void virarEsquerda() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void virarDireita() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}
