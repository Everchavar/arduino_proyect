#include <LiquidCrystal_I2C.h>

// Direccion I2C comun. Puede ser 0x27 o 0x3F, pero 0x20 es comun en Tinkercad.
LiquidCrystal_I2C lcd(0x20, 16, 2); 


byte corazon [8] = {
  // Patrón para el corazón (5x8)
  0b00000, // Fila 0 (vacia) - A veces se empieza con espacio
  0b01010, // Fila 1 (p_p)
  0b11111, // Fila 2 (ppppp)
  0b11111, // Fila 3 (ppppp)
  0b11111, // Fila 4 (ppppp)
  0b01110, // Fila 5 (_ppp_)
  0b00100, // Fila 6 (__p__)
  0b00000  // Fila 7 (vacia)
};


  void setup(){
  lcd.init();
  lcd.backlight();
  lcd.createChar(13,corazon); 
 }

void loop() {
  
  lcd.setCursor (1,0);
  lcd.print("YO");
  lcd.write(byte(13));
  lcd.print(" Ever! ");
 
}

