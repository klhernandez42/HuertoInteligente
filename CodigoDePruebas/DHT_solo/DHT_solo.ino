/* Este código es para probrar el correcto funcionamiento del sensor de humedad y temperatura
 * puedes encontrar el esquematico y mas detalles de como conectarlo en el repositorio de Github: 
 * https://github.com/klhernandez42/HuertoInteligente
 */
 
#include "DHT.h" //Libreria del sensor de humedad y temperatura

#define DHTPIN 10 // Pin donde está conectado el sensor de humedad y temperatura

//Descomenta la linea según la clase del sensor que usas
//#define DHTTYPE DHT11 // (suele ser azul)
#define DHTTYPE DHT22   // (suele ser blanco)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("Espera...");//mensaje mientras se inicializan   
  dht.begin(); //captura de las lecturas
}
void loop() {
  delay(1000);
  float h = dht.readHumidity();       //Leemos el nivel de Humedad
  float t = dht.readTemperature();    //Leemos la temperatura en grados Celsius
  float f = dht.readTemperature(true);//Leemos la temperatura en grados Fahrenheit
  
  //Enviamos las lecturas por el puerto serial hacia el monitor serie
  Serial.print("Humedad ");
  Serial.print(h);
  Serial.print(" %t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.println(" *F");
}
