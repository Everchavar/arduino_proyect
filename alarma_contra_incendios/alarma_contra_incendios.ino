#define sensorPin 2 // Pin donde está conectado el DOUT del sensor
#define ledPin 4    // Pin donde está conectado el LED
#define relayPin 7   // Pin donde está conectado el transistor para el relé

void setup() {
  Serial.begin(9600);          // Iniciamos la comunicación serial
  pinMode(sensorPin, INPUT);   // Configuramos el pin del sensor como entrada
  pinMode(ledPin, OUTPUT);      // Configuramos el pin del LED como salida
  pinMode(relayPin, OUTPUT);    // Configuramos el pin del relé como salida
}

void loop() {
  int flameValue = digitalRead(sensorPin); // Leemos el estado del sensor

  // Imprimimos el estado en el Monitor Serial
  Serial.print("Flame detected (1=YES, 0=NO): ");
  Serial.println(flameValue); 

  // Si se detecta llama
  if (flameValue == LOW) { 
    digitalWrite(ledPin, HIGH);  // Encendemos el LED
    digitalWrite(relayPin, HIGH); // Activamos el relé (enciende la alarma)
    Serial.println("Flame detected! LED ON, Relay ON");
  } else {
    digitalWrite(ledPin, LOW);   // Apagamos el LED
    digitalWrite(relayPin, LOW);  // Desactivamos el relé (apaga la alarma)
    Serial.println("No flame detected. LED OFF, Relay OFF");
  }

  delay(100); // Esperamos 100 ms entre lecturas
}

//adapta el codigo como tu lo necesites