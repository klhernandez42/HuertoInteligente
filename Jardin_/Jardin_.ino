#include <LiquidCrystal.h>
#include <Servo.h>

//Cantidad de cultivos a vigilar. Cada cultivo cuenta con
//su propio sensor de humedad y servomotor para compuerta
const int totalCultivos = 1;

//Pines donde se conectan los sensores y los servomotores
const int pinSensor[totalCultivos] = { A1 };
const int pinServo[totalCultivos] = { 2 };

//Instancias de clase de la pantalla LCD y los servomotores
LiquidCrystal pantalla(12, 11, 5, 4, 3, 2);
Servo compuerta[totalCultivos];

//Estructura que contiene el estado global del sistema
typedef struct {
  //Banderas que indican el estado de riego individual
  //de cada cultivo
  bool riegoActivo[totalCultivos];
} ESTADO_SISTEMA;

//Instancia de la estructura con el estado global del sistema
ESTADO_SISTEMA es;  //es significa "Estado del sistema"

void setup() {
  int i;

  //Inicializa la pantalla LCD e imprime el texto fijo
  //de los indicadores
  pantalla.begin(16, 2);
  pantalla.setCursor(0, 0);
  pantalla.print("Riego 1 -");

  //Inicializa los servo motores de las compuertas
  //(Las cierra inicialmente)
  for (i = 0; i < totalCultivos; i++) {
    compuerta[i].attach(pinServo[i]);
    compuerta[i].write(0);
  }
}

void loop() {
  //Primero se leen todas las entradas del sistema
  leerEntradas();

  //Luego se actualizan todas las salidas
  actualizarSalidas();

  //Se retarda la ejecucion de forma que el sistema se
  //refresque 10 veces por segundo
  delay(100); //100ms = 0.1s
}

void leerEntradas() {
  int i;
  int valorSensor;

  //Procede a recorrer cada uno de los sensores instalados
  //en cada cultivo para leerlos
  for (i = 0; i < totalCultivos; i++) {
    //Lee el valor de humedad del sensor
    valorSensor = analogRead(pinSensor[i]);

    //Si la lectura esta abajo del umbral de resequedad,
    //se habilita el riego para este cultivo
    if (valorSensor <= umbralSensorSeco) {
      es.riegoActivo[i] = true;
    }

    //Si la lectura esta arriba del umbral de humedad,
    //se deshabilita el riego para el cultivo
    if (valorSensor >= umbralSensorHumedo) {
      es.riegoActivo[i] = false;
    }
  }
}

void actualizarSalidas() {
  int i;

  //Actualiza los indicadores de la pantalla LCD
  pantalla.setCursor(8, 0); //Actualiza el Riego 1
  if (es.riegoActivo[0])
    pantalla.print("ON ");
  else
    pantalla.print("OFF");

  pantalla.setCursor(8, 1); //Actualiza el Riego 2
  if (es.riegoActivo[1])
    pantalla.print("ON ");
  else
    pantalla.print("OFF");

  //Actualiza los servomotores de las compuertas instaladas
  //en cada cultivo
  for (i = 0; i < totalCultivos; i++) {
    if (es.riegoActivo[i])
      //Si el riego esta activo en este cultivo abre
      //la compuerta
      compuerta[i].write(100);
    else
      //Caso contrario cierra la compuerta
      compuerta[i].write(0);
  }
}
