#include <Wire.h>
#define TEMPOLEITURA 100
#define TEMPOESPERA 3000
void setup() {
  Serial.begin(9600);
  Wire.begin();
  while (!Serial);            
}

byte endereco;
byte codigoResultado=0;
byte dispositivosEncontrados=0;


void loop() {
  dispositivosEncontrados=0;
  for (endereco=0; endereco<128; endereco++){
    Wire.beginTransmission(endereco);
    codigoResultado = Wire.endTransmission();
    if (codigoResultado==0){
      Serial.print ("Dispositivo I2c detectado no endereço: ");
      Serial.println(endereco,HEX);
      dispositivosEncontrados++;
      delay(TEMPOESPERA);

    }
    delay(TEMPOLEITURA);
  }
  if (dispositivosEncontrados>0){
    Serial.print("Foi encontrado um total de: ");
    Serial.print(dispositivosEncontrados);
    Serial.println("dispositivos");
  }
  else{
    Serial.println("Nenhum dispositivo foi encontrado !!!");
  }
}
