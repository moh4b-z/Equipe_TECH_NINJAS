#include <Wire.h>
#include "Adafruit_TCS34725.h"

// Pinos de alimentação dos sensores
const int sensor1PowerPin = 22;
const int sensor2PowerPin = 23;

// Pinos de controle dos LEDs dos sensores
const int sensor1LEDPin = 24;
const int sensor2LEDPin = 25;

// Criação de dois objetos para os sensores
Adafruit_TCS34725 tcs1 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_TCS34725 tcs2 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Inicializar os pinos de alimentação e LEDs
  pinMode(sensor1PowerPin, OUTPUT);
  pinMode(sensor2PowerPin, OUTPUT);
  pinMode(sensor1LEDPin, OUTPUT);
  pinMode(sensor2LEDPin, OUTPUT);

  // Ligar o primeiro sensor
  digitalWrite(sensor1PowerPin, HIGH);
  digitalWrite(sensor2PowerPin, LOW);
  digitalWrite(sensor1LEDPin, HIGH);
  digitalWrite(sensor2LEDPin, LOW);
  delay(100);  // Esperar o sensor inicializar

  // Inicializar primeiro sensor
  if (!tcs1.begin()) {
    Serial.println("Não foi possível encontrar o sensor TCS34725 (sensor 1)!");
    while (1);
  }

  // Desligar o primeiro sensor
  digitalWrite(sensor1PowerPin, LOW);
  digitalWrite(sensor1LEDPin, LOW);
  delay(100);  // Esperar o sensor desligar

  // Ligar o segundo sensor
  digitalWrite(sensor2PowerPin, HIGH);
  digitalWrite(sensor1PowerPin, LOW);
  digitalWrite(sensor2LEDPin, HIGH);
  delay(100);  // Esperar o sensor inicializar

  // Inicializar segundo sensor
  if (!tcs2.begin()) {
    Serial.println("Não foi possível encontrar o sensor TCS34725 (sensor 2)!");
    while (1);
  }

  // Desligar o segundo sensor
  digitalWrite(sensor2PowerPin, LOW);
  digitalWrite(sensor2LEDPin, LOW);
  delay(100);  // Esperar o sensor desligar
}

void loop() {
  // Ligar o primeiro sensor
  digitalWrite(sensor1PowerPin, HIGH);
  digitalWrite(sensor1LEDPin, HIGH);
  delay(100);  // Esperar o sensor inicializar

  // Ler valores do primeiro sensor
  uint16_t r1, g1, b1, c1;
  tcs1.getRawData(&r1, &g1, &b1, &c1);
  Serial.print("Sensor 1 - R: "); Serial.print(r1);
  Serial.print(" G: "); Serial.print(g1);
  Serial.print(" B: "); Serial.print(b1);
  Serial.print(" C: "); Serial.println(c1);

  // Desligar o primeiro sensor
  digitalWrite(sensor1PowerPin, LOW);
  digitalWrite(sensor1LEDPin, LOW);
  delay(100);  // Esperar o sensor desligar

  // Ligar o segundo sensor
  digitalWrite(sensor2PowerPin, HIGH);
  digitalWrite(sensor2LEDPin, HIGH);
  delay(100);  // Esperar o sensor inicializar

  // Ler valores do segundo sensor
  uint16_t r2, g2, b2, c2;
  tcs2.getRawData(&r2, &g2, &b2, &c2);
  Serial.print("Sensor 2 - R: "); Serial.print(r2);
  Serial.print(" G: "); Serial.print(g2);
  Serial.print(" B: "); Serial.print(b2);
  Serial.print(" C: "); Serial.println(c2);

  // Desligar o segundo sensor
  digitalWrite(sensor2PowerPin, LOW);
  digitalWrite(sensor2LEDPin, LOW);
  delay(1000);  // Esperar o sensor desligar
}
