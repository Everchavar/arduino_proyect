// Pines del L298N para el Motor A
int enA = 9;
int in1 = 8;
int in2 = 7;

// Pines del L298N para el Motor B
int enB = 10;
int in3 = 6;
int in4 = 5;

// Variables para almacenar los comandos recibidos
char command;

void setup() {
  // Configurar los pines como salidas
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Iniciar comunicación serial para recibir comandos del HC-06
  Serial.begin(9600);
}

void loop() {
  // Comprobar si se ha recibido un comando
  if (Serial.available() > 0) {
    command = Serial.read();

    // Ejecutar comandos
    switch (command) {
      case 'F': // Adelante
        forward();
        break;
      case 'B': // Atrás
        backward();
        break;
      case 'L': // Izquierda
        left();
        break;
      case 'R': // Derecha
        right();
        break;
      case 'S': // Parar ambos motores
        stop();
        break;
      case 'A': // Parar motor A
        stopMotorA();
        break;
    }
  }
}

void forward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 255);
  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, 255);
}

void backward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 255);
  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, 255);
}

void left() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 255);
  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, 255);
}

void right() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 255);
  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, 255);
}

void stop() {
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void stopMotorA() {
  analogWrite(enA, 0);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}
