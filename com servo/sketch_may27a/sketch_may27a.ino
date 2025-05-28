// Micro Servo
#include <Servo.h>
#define pinServo 12
Servo servo;

// Definindo variaveis
int motorEsquerdo1 = 5;
int motorEsquerdo2 = 3;
int motorDireito1 = 6;
int motorDireito2 = 11;
int cm;
int atual;
int frente;
int direita;
int esquerda;

// Move o servo para posicao desejada
// recebe a posicao como argumento
// move o servo
// espera meio segundo
void moveServo(int posicao) {
  servo.write(posicao);
  delay(500);
}

// Mede todas as direcoes
// move o servo apontado para frente
// atribui a distancia para a variavel frente
// move o servo apontado para esquerda
// atribui a distancia para a variavel esquerda
// move o servo apontado para direita
// atribue a distancia para a variavel direita
void medeTodasAsDirecoes() {
  moveServo(100);
  frente = distanciaAtual();
  moveServo(180);
  esquerda = distanciaAtual();
  moveServo(20);
  direita = distanciaAtual();
  moveServo(100);
}

// Sensor Ultrassonico
// triggerPin envia um pulso
// echoPin recebe o reflexo do pulso
// retorna echoPin
long sensorUltrassonico(int tringgerPin, int echoPin) {
  pinMode(tringgerPin, OUTPUT);
  digitalWrite(tringgerPin, LOW);
  delay(2);
  digitalWrite(tringgerPin, HIGH);
  delay(10);
  digitalWrite(tringgerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}

// Mede distancia atual
// trasforma echoPin para cm
// atribui o valor para variavel atual
// retorna variavel atual
long distanciaAtual() {
  atual = 0.01723 * sensorUltrassonico(A0, A1);
  delay(100);
  return atual;
}

// Configura o motor para seguir em frente
// Define o numero do motor para se movimentar para frente
// recebe a distancia atual
// para os motores
void motorFrente() {
  analogWrite(motorEsquerdo2, 155);
  analogWrite(motorEsquerdo1, 0);
  analogWrite(motorDireito2, 155);
  analogWrite(motorDireito1, 0);
  frente = distanciaAtual();
  if (frente < 20) {
    pararMotores();
  }
}

// Configura o motor para seguir para esquerda
// Define o numero do motor para se movimentar para esquerda
// Para os motores
// Chama a funcao para medir todas as direcoes
void motorEsquerda() {
  analogWrite(motorEsquerdo2, 0);
  analogWrite(motorEsquerdo1, 0);
  analogWrite(motorDireito1, 0);
  analogWrite(motorDireito2, 155);
  delay(250);
  pararMotores();
  medeTodasAsDirecoes();
  escolherDirecao(frente, esquerda, direita);
}

// Configura o motor para seguir para direita
// Define o numero do motor para se movimentar para direita
// para os motores
// Chama a funcao para medir todas as direcoes
void motorDireita() {
  analogWrite(motorEsquerdo2, 155);
  analogWrite(motorEsquerdo1, 0);
  analogWrite(motorDireito1, 0);
  analogWrite(motorDireito2, 0);
  delay(250);
  pararMotores();
  medeTodasAsDirecoes();
  escolherDirecao(frente, esquerda, direita);
}

// Configura o motor para parar
// Define o pwm de todos os motores para 0
void pararMotores() {
  analogWrite(motorEsquerdo2, 0);
  analogWrite(motorEsquerdo1, 0);
  analogWrite(motorDireito1, 0);
  analogWrite(motorDireito2, 0);
}

// Função para escolher a direção
// Laco que define qual das direcoes e a ideal
void escolherDirecao(int frente, int esquerda, int direita) {
  if (frente > esquerda && frente > direita) {
    motorFrente();
    Serial.println("Direção escolhida: Frente");
  } else if (esquerda > frente && esquerda > direita) {
    motorEsquerda();
    Serial.println("Direção escolhida: Esquerda");
  } else if (direita > frente && direita > esquerda) {
    motorDireita();
    Serial.println("Direção escolhida: Direita");
  }
}

// Define a comunicacao com o serial monitor
// Define o servo para a porta
void setup() {
  Serial.begin(9600);
  servo.attach(12);
  medeTodasAsDirecoes();
  escolherDirecao(frente, esquerda, direita);
}

// Sensor apontado para frete recebe a distancia atual
// Se a distancia atual for menor que 20 cm
// Os motores param
// Função mede todas as direções
// Função escolhe qual é a melhor direceção e faz ele andar para direção escolhida
void loop() {
  frente = distanciaAtual();
  if (frente < 20) {
    pararMotores();
    medeTodasAsDirecoes();
    escolherDirecao(frente, esquerda, direita);
  }
}
