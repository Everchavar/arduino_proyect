void encenderLed(int pin, int tiempo) { //se define el pin y tiempo del led como enteros
  digitalWrite(pin, HIGH); // pin en 0 para que se apage
  delay (tiempo);// tiempo en la variable anterior
  digitalWrite(pin, LOW);//pin LOW para que este en 1 y encienda
}


void setup() {
  pinMode(12, OUTPUT); //se define si los pines son de entradas o salidas
  pinMode(7, OUTPUT);
}

void loop(){
  encenderLed(12,1000);//utilizamos la funcion para que funcione correctamente 
  delay (1000);
  
   encenderLed(7,1000);//elegimos el segundo led
  delay (1000);//tiempo que es la variable enterior
}
// Esta funcion es para encender led con funciones y el ejemplo es este 