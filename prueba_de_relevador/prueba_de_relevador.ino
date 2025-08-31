int relePin = 7;  // Pin donde conectaste IN del módulo relé

void setup() {
  pinMode(relePin, OUTPUT); // Configurar el pin como salida
  digitalWrite(relePin, HIGH); // Relé apagado (dependiendo del módulo)
}

void loop() {
  digitalWrite(relePin, LOW);  // Activa el relé (ON)
  delay(1000);                 // Espera 1 segundo
  digitalWrite(relePin, HIGH); // Desactiva el relé (OFF)
  delay(1000);                 // Espera 1 segundo
}

