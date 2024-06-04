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

void setup() {
  Serial.begin(9600); // Inicializando a comunicação serial

  // Configurando os pinos dos sensores como saída
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
}

void loop() {
  // Lendo as cores detectadas pelo sensor esquerdo
  int red1 = analogRead(leftOut);
  int green1 = analogRead(leftOut);
  int blue1 = analogRead(leftOut);

  // Lendo as cores detectadas pelo sensor direito
  int red2 = analogRead(rightOut);
  int green2 = analogRead(rightOut);
  int blue2 = analogRead(rightOut);

  // Exibindo os resultados no monitor serial
  Serial.println("Sensor Esquerdo:");
  Serial.print("Red: ");
  Serial.println(red1);
  Serial.print("Green: ");
  Serial.println(green1);
  Serial.print("Blue: ");
  Serial.println(blue1);

  Serial.println("Sensor Direito:");
  Serial.print("Red: ");
  Serial.println(red2);
  Serial.print("Green: ");
  Serial.println(green2);
  Serial.print("Blue: ");
  Serial.println(blue2);

  delay(1000); // Espera 1 segundo antes de fazer a próxima leitura
}
