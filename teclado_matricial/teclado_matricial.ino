#define ROWS 4
#define COLS 4

// Definir los pines de las filas y columnas
byte rowPins[ROWS] = {2, 3, 4, 5};   // Pines de las filas (salidas)
byte colPins[COLS] = {6, 7, 8, 9}; // Pines de las columnas (entradas con pull-up)

// Definir la disposición de teclas
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

void setup() {
  Serial.begin(115200);

  // Configurar filas como salidas
  for (int i = 0; i < ROWS; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH); // Inicialmente en HIGH
  }

  // Configurar columnas como entradas con pull-up interno
  for (int i = 0; i < COLS; i++) {
    pinMode(colPins[i], INPUT_PULLUP);
  }
}

void loop() {
  char key = getKey();
  if (key) {
    Serial.print("Tecla presionada: ");
    Serial.println(key);
  }
}

// Función para leer la tecla presionada
char getKey() {
  for (int row = 0; row < ROWS; row++) {
    digitalWrite(rowPins[row], LOW); // Activar la fila actual

    for (int col = 0; col < COLS; col++) {
      if (digitalRead(colPins[col]) == LOW) { // Si la columna es LOW, hay una tecla presionada
        while (digitalRead(colPins[col]) == LOW); // Esperar a que se suelte la tecla (evita rebote)
        digitalWrite(rowPins[row], HIGH); // Restaurar la fila
        return keys[row][col]; // Devolver la tecla presionada
      }
    }

    digitalWrite(rowPins[row], HIGH); // Restaurar la fila
  }
  return 0; // Si no se presionó ninguna tecla
}

