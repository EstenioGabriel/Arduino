#include <Servo.h>

#define pinServo 11

Servo servo;

int cm = 0;
int frente = 0;
int direita = 0;
int esquerda = 0;

int motor1 = 6;
int motor2 = 5;
int motor3 = 10;
int motor4 = 9;

void setup() {
  servo.attach(pinServo);
  Serial.begin(9600);
  servo.write(90);

  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motor3, OUTPUT);
  pinMode(motor4, OUTPUT);

  pararMotores();
}

void loop() {
  pararMotores();

  medirDistancias();

  if (frente <= 15) {
    Serial.println("Obstáculo à frente! Procurando alternativa...");

    servo.write(20);
    delay(600);
    sensorDistancia();
    direita = cm;
    Serial.print("Direita: ");
    Serial.println(direita);

    servo.write(160);
    delay(600);
    sensorDistancia();
    esquerda = cm;
    Serial.print("Esquerda: ");
    Serial.println(esquerda);

    if (direita >= esquerda && direita > 15) {
      virarDireita();
      delay(700);
      frenteReto();
      delay(1000);
    } else if (esquerda > 15) {
      virarEsquerda();
      delay(700);
      frenteReto();
      delay(1000);
    } else {
      Serial.println("Nenhuma direção livre! Parando.");
      pararMotores();
      delay(2000);
    }
  } else {
    pararMotores();
    medirDistancias();
    delay(500);
    

    escolherDirecao();

    delay(3000);

    pararMotores();
  }
}

//---------------- FUNÇÕES ----------------//

void medirDistancias() {
  pararMotores();

  // Frente
  servo.write(90);
  delay(500);
  sensorDistancia();
  frente = cm;
  Serial.print("Frente: ");
  Serial.println(frente);

  // Direita
  servo.write(20);
  delay(500);
  sensorDistancia();
  direita = cm;
  Serial.print("Direita: ");
  Serial.println(direita);

  // Esquerda
  servo.write(160);
  delay(500);
  sensorDistancia();
  esquerda = cm;
  Serial.print("Esquerda: ");
  Serial.println(esquerda);

  servo.write(90);

  Serial.println("----------------------------");
}

void escolherDirecao() {

  if(cm < 10){
    pararMotores();
  }
  if (frente >= direita && frente >= esquerda && frente > 15) {
    frenteReto();
    Serial.println("Decisão: Frente");
  } else if (direita >= esquerda && direita > 15) {
    virarDireita();
    delay(150);
    frenteReto();
    delay(500);
    Serial.println("Decisão: Direita");
  } else if (esquerda > 15) {
    virarEsquerda();
    delay(150);
    frenteReto();
    delay(500);
    Serial.println("Decisão: Esquerda");
  } else {
    Serial.println("Nenhuma direção livre! Parando.");
    pararMotores();
    delay(2000);
  }
}

void frenteReto() {
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, HIGH);
  digitalWrite(motor3, HIGH);
  digitalWrite(motor4, LOW);
}

void virarDireita() {
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, HIGH);
  digitalWrite(motor3, LOW);
  digitalWrite(motor4, LOW);
}

void virarEsquerda() {
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, HIGH);
  digitalWrite(motor4, LOW);
}

void pararMotores() {
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, LOW);
  digitalWrite(motor4, LOW);
}

long readUltrasonicDistance(int triggerPin, int echoPin) {
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}

void sensorDistancia() {
  cm = 0.01723 * readUltrasonicDistance(A0, A1);
  delay(100);
}