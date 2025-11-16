#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20, 16, 2);

/*
   mostrar()

   Muestra dos líneas completas al instante (sin animación).
   
   linea1      → texto para la fila superior
   linea2      → texto para la fila inferior
   tiempoFinal → tiempo que la frase permanece visible
*/
void mostrar(String linea1, String linea2, int tiempoFinal) { //mostrar es una funcion creada para simplifica mas el codigo 

  lcd.clear();         // Limpia la pantalla

  lcd.setCursor(0, 0); // Primera línea
  lcd.print(linea1);

  lcd.setCursor(0, 1); // Segunda línea
  lcd.print(linea2);

  delay(tiempoFinal);  // Espera el tiempo indicado
}

void setup() {
  lcd.init();
  lcd.backlight();
}

void loop() {

  // --- FRASES COMPLETAS ---

  mostrar("Baby eres una", "estrella", 2000);

  mostrar("esa boca sabe", "a carambola", 1000);

  mostrar("Fuego desde q", "te vi me puse", 1000);
  mostrar("roja", "", 2000);

  mostrar("Con los ojos", "me quitaste", 1000);
  mostrar("el traje", "", 2000 );

  mostrar("Te tengo baila", "ndo sin modale", 3000);
  mostrar("es (dale)", "", 1000);

  mostrar("Diantre tu y yo", "somos iguales", 3000);

  mostrar("Hoy le dimos", "y manana mas", 2000);

  mostrar("De weekend en", "Coamo", 2000);

  mostrar("En la montana", " te vo'a hacer", 2000);
  mostrar("la rusa", "", 1000);

  mostrar("Que cojones?", "Que tu tienes", 2000);
  mostrar("que me pone", "", 1000);
  mostrar("musa", "", 1000);

  delay(1000);
}
