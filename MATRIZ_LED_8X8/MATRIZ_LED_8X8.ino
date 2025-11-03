// Matriz led 8x8 de catodo comun 
// Este codigo funciona con matriz led de catodo comun 
// -----------------------------------------------------------------

// ¡NUEVAS COLUMNAS! (Ánodos/Positivos) - Usan la lista de pines antiguos de FILAS
const int NUEVAS_COLUMNAS_PINS[8] = {13, 2, 3, 4, 10, 5, 6, 1};// Todos estos son positivos del led------1(13),2(3),3(4),4(10),5(6),6(11),7(15),8(16)

// ¡NUEVAS FILAS! (Cátodos/Negativos) Estos pines va al negativo de los led--------1(9),2(14),3(8),4(12),5(1),6(7),7(2),8(5)
const int NUEVAS_FILAS_PINS[8] = {9, 14, 8, 12, 7, 15, 16, 17}; // 14=A0, 15=A1, 16=A2, 17=A3


// Patrón del Corazón (Se usará el patrón original, es probable que se vea rotado)
// -------------------------------------------------------------------------------
byte corazon[8] = {
  0b00000000,
  0b01100110,
  0b11111111,
  0b11111111,
  0b11111111,
  0b01111110,
  0b00111100,
  0b00011000
};

// Patrón de APAGADO total
byte APAGADO[8] = {
  0b00000000, 0b00000000, 0b00000000, 0b00000000,
  0b00000000, 0b00000000, 0b00000000, 0b00000000
};

// Variables para el control de tiempo (500 milisegundos = 0.5 segundos)
unsigned long tiempoUltimoCambio = 0;
const long INTERVALO_PARPADEO = 500; 
bool estadoEncendido = true; 


void setup() {
  // Configuración de Pines
  
  // 1. Configurar NUEVAS COLUMNAS (Ánodos)
  for (int i = 0; i < 8; i++) {
    pinMode(NUEVAS_COLUMNAS_PINS[i], OUTPUT);
    digitalWrite(NUEVAS_COLUMNAS_PINS[i], LOW); // Inician LOW
  }

  // 2. Configurar NUEVAS FILAS (Cátodos)
  for (int i = 0; i < 8; i++) {
    pinMode(NUEVAS_FILAS_PINS[i], OUTPUT);
    digitalWrite(NUEVAS_FILAS_PINS[i], HIGH); // Inician HIGH
  }
}

void loop() {
  // Lógica de tiempo: Alterna entre ENCENDIDO y APAGADO cada 500ms
  if (millis() - tiempoUltimoCambio >= INTERVALO_PARPADEO) {
    tiempoUltimoCambio = millis(); 
    estadoEncendido = !estadoEncendido;
  }

  // Muestra el patrón activo (CORAZON o APAGADO)
  if (estadoEncendido) {
    mostrarPatron(corazon, 10); // Escanea el corazón
  } else {
    mostrarPatron(APAGADO, 10); // Escanea el patrón vacío (apagado)
  }
}


// Función de Multiplexación (Lógica Cátodo Común - Usa los NUEVOS PINES)
void mostrarPatron(byte patron[8], int tiempoTotalMs) {
  int tiempoPorFila = tiempoTotalMs / 8;

  for (int fila = 0; fila < 8; fila++) {
    // 1. Configurar NUEVAS COLUMNAS (Ánodos)
    byte filaData = patron[fila]; 
    for (int col = 0; col < 8; col++) {
      int ledState = bitRead(filaData, 7 - col);
      // Ánodos: HIGH para encender
      digitalWrite(NUEVAS_COLUMNAS_PINS[col], ledState == 1 ? HIGH : LOW);
    }

    // 2. Encender NUEVA FILA (Cátodo/Negativo) con LOW
    digitalWrite(NUEVAS_FILAS_PINS[fila], LOW);
    
    // 3. Esperar
    delay(tiempoPorFila);

    // 4. Apagar NUEVA FILA (Desactivar) con HIGH
    digitalWrite(NUEVAS_FILAS_PINS[fila], HIGH);
  }
}

