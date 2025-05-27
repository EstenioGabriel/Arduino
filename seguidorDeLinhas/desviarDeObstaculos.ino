// Micro Servo 
#include <Servo.h>
#define pinServo 11
Servo servo;

// Motores
int motorEsquerdo1 = 6;
int motorEsquerdo2 = 5;
int motorDireito1 = 9;
int motorDireito2 = 10;


// Funções // 
  
  //Servo Função
  long moveServo(){
    servo.write(100);
    delay(500);
    servo.write(180);
    delay(500);
    servo.write(100);
    delay(500);
    servo.write(30);
    delay(500);
  }
  ////

void setup() {
  servo.attach(pinServo);
  
  
}

void loop() {

  
  // analogWrite(motorEsquerdo1, 155);
  // digitalWrite(motorEsquerdo2, LOW);

  // analogWrite(motorDireito1, 155);
  // digitalWrite(motorDireito2, LOW);

}

