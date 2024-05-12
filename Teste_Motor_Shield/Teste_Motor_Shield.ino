#include <AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(1);
AF_DCMotor motor3(1);
AF_DCMotor motor4(1);

void setup() {
  motor1.setSpeed(0);
  motor2.setSpeed(0);
  motor3.setSpeed(0);
  motor4.setSpeed(0);
}

void loop() {
  //MOTOR1
  motor1.setSpeed(255);
  motor1.run(FORWARD);
  delay(5000)
  
  motor1.setSpeed(0);
  motor1.run(RELEASE);
  delay(500)

  motor1.setSpeed(255);
  motor1.run(BACKWARD);
  delay(5000)
  
  motor1.setSpeed(0);
  motor1.run(RELEASE);
  delay(500)

  //MOTOR2
  motor2.setSpeed(255);
  motor2.run(FORWARD);
  delay(5000)
  
  motor2.setSpeed(0);
  motor2.run(RELEASE);
  delay(500)

  motor2.setSpeed(255);
  motor2.run(BACKWARD);
  delay(5000)
  
  motor2.setSpeed(0);
  motor2.run(RELEASE);
  delay(500)

  //MOTOR3
  
  motor3.setSpeed(255);
  motor3.run(FORWARD);
  delay(5000)
  
  motor3.setSpeed(0);
  motor3.run(RELEASE);
  delay(500)

  motor3.setSpeed(255);
  motor3.run(BACKWARD);
  delay(5000)
  
  motor3.setSpeed(0);
  motor3.run(RELEASE);
  delay(500)

  //MOTOR4  
  motor4.setSpeed(255);
  motor4.run(FORWARD);
  delay(5000)
  
  motor4.setSpeed(0);
  motor4.run(RELEASE);
  delay(500)

  motor4.setSpeed(255);
  motor4.run(BACKWARD);
  delay(5000)
  
  motor4.setSpeed(0);
  motor4.run(RELEASE);
  delay(500)
  
}
