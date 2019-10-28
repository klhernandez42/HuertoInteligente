//Pantalla LCD  16x2
#include  <LiquidCrystal.h> //Libreria para LCD 
LiquidCrystal  lcd(12, 11, 5, 4, 3, 2); //lcd(rs,enable,d4,d5,d6,d7);

//Sensor de temperatura y humedad en aire
#include "DHT.h" //Libreria del sensor
#define DHTPIN 10 //Pin D10
#define DHTTYPE DHT22 //modelo del sensor
DHT dht(DHTPIN, DHTTYPE);

//Sensor de humedad en tierra
int saHumedad = A0;//Pin analogico desde el pin SIG del sensor
int sHumedad = 6;//Pin D6 desde el pin vcc en el sensor
int umbralSensorHumedo = 800;//variable de calibración
int val = 0;

//Control de la bomba de agua por medio del relay
const int cBomba = 7 ;//Pin D7

int rutina = 5000;//retardo para la duración en la lcd de los datos

void setup() {
  lcd.begin(16, 2); //dimensiones de la pantalla en este caso LCD de 16x2
  dht.begin(); //captura de las lecturas del sensor
  pinMode(sHumedad, OUTPUT);//sensor de humedad en tierra
  digitalWrite(sHumedad, LOW);//sensor de humedad en tierra
  pinMode(cBomba,  OUTPUT) ;//bomba de agua
}

void loop() {
  pantalla();//mensajes de bienvenida en la lcd
  dht1();    //control del sensor de temperatura
  
  //control de la bomba de agua con respecto a la humedad en tierra
  humedad(); 
}

void pantalla() {
  lcd.setCursor(0, 0);//El mensaje se iniciara en la posición (0,0)
  lcd.print("Hola            ");//mensaje en 1ra linea
  lcd.setCursor(0, 1);//mensaje a imprimir en segunda linea
  lcd.print("Bienvenido      ");//mensaje en 2da linea
  delay(3000);

  lcd.setCursor(0, 0); //El mensaje se iniciara en la posición (0,0)
  lcd.print("La temperatura     ");//mensaje en 1ra linea
  lcd.setCursor(0, 1);//mensaje a imprimir en segunda linea
  lcd.print("actualmente es:    ");//mensaje en 2da linea
  delay(3000);
}

void dht1() {

  float h = dht.readHumidity();       //Leemos el nivel de Humedad
  float t = dht.readTemperature();    //Leemos la temperatura en grados Celsius
  float f = dht.readTemperature(true);//Leemos la temperatura en grados Fahrenheit
  lcd.setCursor(0, 0);//El mensaje se iniciara en la posición (0,0)
  lcd.print(t);//mensaje a imprimir en primer linea
  lcd.print(": C          ");
  lcd.setCursor(0, 1);//El mensaje se iniciara en la posición (0,0)
  lcd.print(f);//mensaje a imprimir en primer linea
  lcd.print(": F          ");
  delay(rutina);

}

void humedad() {

  lcd.setCursor(0, 0); //mensaje a imprimir en segunda linea
  lcd.print("Estado Tierra :");
  
  //Si la tierra no esta humeda entonces esta reseca
  if (lectorsHumedad() >= umbralSensorHumedo) {
    lcd.setCursor(0, 1);//mensaje a imprimir en segunda linea
    lcd.print(lectorsHumedad());
    lcd.print(":humedo");

    digitalWrite(cBomba, HIGH);//la bomba de agua se apaga
  }
  else {
    lcd.setCursor(0, 1);//mensaje a imprimir en segunda linea
    lcd.print(lectorsHumedad());
    lcd.print(":seco");

    digitalWrite(cBomba, LOW);//la bomba de agua se enciende
  }
  delay(rutina);

}

//Calculo y captura del valor de humedad de tierra desde el sensor
int lectorsHumedad()
{
  digitalWrite(sHumedad, HIGH);//pin D6 "encendido"
  delay(10);

  val = analogRead(saHumedad);//Lectura del pin SIG del sensor de humedad

  digitalWrite(sHumedad, LOW);//pin D6 "apagado"
  return val;//se envia valor del sensor
}
