
int motorEsquerdo1 = 6;
int motorEsquerdo2 = 5;
int motorDireito1 = 9;
int motorDireito2 = 10;
//

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  analogWrite(motorEsquerdo1, 155);
  digitalWrite(motorEsquerdo2, LOW);

  analogWrite(motorDireito1, 155);
  digitalWrite(motorDireito2, LOW);

}
