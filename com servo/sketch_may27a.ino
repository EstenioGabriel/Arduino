// Micro Servo 
#include <Servo.h>
#define pinServo 12
Servo servo;

// Motores
int motorEsquerdo1 = 5;
int motorEsquerdo2 = 3;
int motorDireito1 = 6;
int motorDireito2 = 11;

// Cm do sensor
int cm = 0;


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
  // Sensor Ultrassonico
  long sensorUltrassonico(int tringgerPin, int echoPin){
    pinMode(tringgerPin, OUTPUT);
    digitalWrite(tringgerPin,LOW);
    delay(2);
    digitalWrite(tringgerPin, HIGH);
    delay(10);
    digitalWrite(tringgerPin, LOW);
    pinMode(echoPin, INPUT);
    return pulseIn (echoPin, HIGH);
  }
  //calculo Da Distancia
  long distancia(){
    cm = 0.01723 * sensorUltrassonico(A0, A1);
    delay(100);
    Serial.println(cm);
  }
  //Motores indo para frente
  long frente (){
    analogWrite(motorEsquerdo1, 155);
    digitalWrite(motorEsquerdo2, LOW);

    analogWrite(motorDireito1, 155);
    digitalWrite(motorDireito2, LOW);
  } 


//----------------------------------------------//
void setup() {
  servo.attach(12);
}

void loop() {
  moveServo();
  frente();

 

}
