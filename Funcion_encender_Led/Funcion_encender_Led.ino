void setup()
{
  pinMode(12, OUTPUT); //ponemos el pin que se usara en este caso ponemos el pin 12
}

void loop()
{
  encenderLed(); // aqui ponemos la funcion en el void loop se repite para siempre
}

void encenderLed() {
  digitalWrite(12, HIGH); // aqui ponemos el pin del led junto con la funcion esta funcion unicamente lo enciende 
}