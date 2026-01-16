const int flamePin  = 34;  // Sensor de llama (DO)
const int ledPin    = 25;  // LED
const int buzzerPin = 26;  // Buzzer activo

void setup() {
  pinMode(flamePin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(115200);
}

void loop() {
  int flame = digitalRead(flamePin);

  // La mayoría de sensores: LOW = llama detectada
  if (flame == LOW) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH); // suena
  } else {
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);  // silencio
  }

 delay(100);
}

