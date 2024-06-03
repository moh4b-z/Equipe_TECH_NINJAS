// Definição dos pinos dos sensores de cor
const int leftS2 = 26;
const int leftS3 = 28;
const int leftOut = 30;

const int rightS2 = 36;
const int rightS3 = 38;
const int rightOut = 40;

// Pinos S0 e S1 dos sensores de cor
const int leftS0 = 22;
const int leftS1 = 24;
const int rightS0 = 32;
const int rightS1 = 34;

void setup() {
  // Inicializa a comunicação serial
  Serial.begin(9600);

  // Configura os pinos dos sensores de cor
  pinMode(leftS2, OUTPUT);
  pinMode(leftS3, OUTPUT);
  pinMode(rightS2, OUTPUT);
  pinMode(rightS3, OUTPUT);

  // Configura os pinos S0 e S1 dos sensores de cor
  pinMode(leftS0, OUTPUT);
  pinMode(leftS1, OUTPUT);
  pinMode(rightS0, OUTPUT);
  pinMode(rightS1, OUTPUT);

  // Define a resolução dos sensores de cor para alta (80%)
  digitalWrite(leftS0, HIGH);
  digitalWrite(leftS1, HIGH);
  digitalWrite(rightS0, HIGH);
  digitalWrite(rightS1, HIGH);
}

void loop() {
  // Ler a cor detectada pelos sensores de cor
  String leftColor = detectColor(leftS2, leftS3, leftOut);
  String rightColor = detectColor(rightS2, rightS3, rightOut);

  // Mostrar as informações no monitor serial
  Serial.print("Left Color: ");
  Serial.println(leftColor);
  Serial.print("Right Color: ");
  Serial.println(rightColor);

  speakColor(leftColor);
  speakColor(rightColor);

  delay(1000); // Delay de 1 segundo
}

String detectColor(int pinS2, int pinS3, int pinOut) {
  // Detecta a cor vermelha
  digitalWrite(pinS2, LOW);
  digitalWrite(pinS3, LOW);
  unsigned int redValue = pulseIn(pinOut, digitalRead(pinOut) == HIGH ? LOW : HIGH);

  // Detecta a cor verde
  digitalWrite(pinS2, HIGH);
  digitalWrite(pinS3, HIGH);
  unsigned int greenValue = pulseIn(pinOut, digitalRead(pinOut) == HIGH ? LOW : HIGH);

  // Detecta a cor azul
  digitalWrite(pinS2, LOW);
  digitalWrite(pinS3, HIGH);
  unsigned int blueValue = pulseIn(pinOut, digitalRead(pinOut) == HIGH ? LOW : HIGH);

  // Detecta a cor branca
  digitalWrite(pinS2, HIGH);
  digitalWrite(pinS3, LOW);
  unsigned int whiteValue = pulseIn(pinOut, digitalRead(pinOut) == HIGH ? LOW : HIGH);

  // Define um limiar para diferenciar as cores
  int threshold = 200; // Ajuste conforme necessário

  if (redValue > threshold && redValue > greenValue && redValue > blueValue && redValue > whiteValue) {
    return "Red";
  } else if (greenValue > threshold && greenValue > redValue && greenValue > blueValue && greenValue > whiteValue) {
    return "Green";
  } else if (blueValue > threshold && blueValue > redValue && blueValue > greenValue && blueValue > whiteValue) {
    return "Blue";
  } else if (whiteValue > threshold && whiteValue > redValue && whiteValue > greenValue && whiteValue > blueValue) {
    return "White";
  } else {
    return "Unknown";
  }
}

void speakColor(String color) {
  // Fala a cor no monitor serial
  if (color == "Red") {
    Serial.println("Detected Red color");
  } else if (color == "Green") {
    Serial.println("Detected Green color");
  } else if (color == "Blue") {
    Serial.println("Detected Blue color");
  } else if (color == "White") {
    Serial.println("Detected White color");
  } else {
    Serial.println("Unknown color detected");
  }
}
