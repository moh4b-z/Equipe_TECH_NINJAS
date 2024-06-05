// Pinos de conexao do modulo
#define leftS0 22
#define leftS1 24
#define leftS2 26
#define leftS3 28
#define leftOut 30

#define rightS0 32
#define rightS1 34
#define rightS2 36
#define rightS3 38
#define rightOut 40

unsigned int valorVermelho = 0;
unsigned int valorVerde = 0;
unsigned int valorAzul = 0;
unsigned int valorBranco = 0;

unsigned int valorVermelhoR = 0;
unsigned int valorVerdeR = 0;
unsigned int valorAzulR = 0;
unsigned int valorBrancoR = 0;

void detectaCor();

void setup() {
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
}

void loop() {
  // Detecta a cor
  detectaCor();

  // Mostra valores no serial monitor esquerdo
  Serial.print("Vermelho esquerdo:");
  Serial.print(valorVermelho);

  Serial.print(" Verde esquerdo: ");
  Serial.print(valorVerde);

  Serial.print(" Azul esquerdo: ");
  Serial.print(valorAzul);

  Serial.print(" Branco esquerdo: ");
  Serial.print(valorBranco);
  Serial.println();
  
  // Mostra valores no serial monitor direito
  Serial.print("Vermelho direito:");
  Serial.print(valorVermelhoR);

  Serial.print(" Verde direito: ");
  Serial.print(valorVerdeR);

  Serial.print(" Azul direito: ");
  Serial.print(valorAzulR);

  Serial.print(" Branco direito: ");
  Serial.print(valorBrancoR);
  Serial.println();

  // Verifica se a cor vermelha foi detectada no sensor esquerdo
  if ((valorVermelho < valorAzul) &&
      (valorVermelho < valorVerde) &&
      (valorBranco < 100)) {
    Serial.println("Vermelho no esquerdo");

  } else if ((valorAzul < valorVermelho) &&  // Verifica se a cor azul foi detectada
             (valorAzul < valorVerde) &&
             (valorBranco < 100)) {
    Serial.println("Azul no esquerdo");

  } else if ((valorVerde < valorVermelho) &&  // Verifica se a cor verde foi detectada
             (valorVerde < valorAzul) &&
             (valorBranco < 100)) {
    Serial.println("Verde no esquerdo");

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

  } else if ((valorVermelhoR < 50) && (valorVerdeR < 50) && (valorAzulR < 50) && (valorBrancoR < 50)) { // Verifica se a cor preta foi detectada
    Serial.println("Preto no direito");

  }
  Serial.println();
  delay(1000);
}

// *********** Função de leitura do sensor de cor ********************
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
