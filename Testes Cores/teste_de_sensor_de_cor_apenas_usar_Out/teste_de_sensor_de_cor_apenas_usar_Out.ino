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

  // Configurando os sensores na maior frequência de leitura
  digitalWrite(leftS0, HIGH);
  digitalWrite(leftS1, LOW);
  digitalWrite(rightS0, HIGH);
  digitalWrite(rightS1, LOW);
}

int readColor(int s2, int s3, int out) {
  // Configurar o sensor para ler a cor especificada
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  int red = pulseIn(out, LOW);

  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  int green = pulseIn(out, LOW);

  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  int blue = pulseIn(out, LOW);

  return (red + green + blue) / 3;
}

String getColor(int red, int green, int blue) {
  if (red >= 5 && red <= 10 && green >= 5 && green <= 10 && blue >= 5 && blue <= 10) {
    return "branco";
  } else if (red >= 20 && red <= 30 && green >= 20 && green <= 30 && blue >= 20 && blue <= 30) {
    return "azul";
  } else if (red >= 31 && red <= 40 && green >= 31 && green <= 40 && blue >= 31 && blue <= 40) {
    return "verde";
  } else if (red >= 41 && green >= 41 && blue >= 41) {
    return "vermelho";
  } else {
    return "indefinido";
  }
}

void loop() {
  // Lendo as cores detectadas pelo sensor esquerdo
  int red1 = readColor(leftS2, leftS3, leftOut);
  int green1 = readColor(leftS2, leftS3, leftOut);
  int blue1 = readColor(leftS2, leftS3, leftOut);

  // Lendo as cores detectadas pelo sensor direito
  int red2 = readColor(rightS2, rightS3, rightOut);
  int green2 = readColor(rightS2, rightS3, rightOut);
  int blue2 = readColor(rightS2, rightS3, rightOut);

  // Exibindo os resultados no monitor serial
  Serial.println("Sensor Esquerdo:");
  Serial.print("Red: ");
  Serial.println(red1);
  Serial.print("Green: ");
  Serial.println(green1);
  Serial.print("Blue: ");
  Serial.println(blue1);
  Serial.print("Cor verdadeira é: ");
  Serial.println(getColor(red1, green1, blue1));

  Serial.println("Sensor Direito:");
  Serial.print("Red: ");
  Serial.println(red2);
  Serial.print("Green: ");
  Serial.println(green2);
  Serial.print("Blue: ");
  Serial.println(blue2);
  Serial.print("Cor verdadeira é: ");
  Serial.println(getColor(red2, green2, blue2));

  delay(1000); // Espera 1 segundo antes de fazer a próxima leitura
}
