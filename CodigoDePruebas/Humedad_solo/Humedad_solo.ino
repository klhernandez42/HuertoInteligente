int val = 0;
int saHumedad = A0;//Pin Sig en el sensor de humedad
int sHumedad = 6;//Pin vcc en el sensor de humedad

int umbralSensorHumedo = 800;

void setup() {
  Serial.begin(9600);
  Serial.println("Espera...");//mensaje mientras se inicializan

  pinMode(sHumedad, OUTPUT);//pin D6
  digitalWrite(sHumedad, LOW);
}

void loop() {
  delay(500);

  //Si la tierra no esta humeda entonces esta reseca
  if (lectorsHumedad() >= umbralSensorHumedo) {
    Serial.print(lectorsHumedad());
    Serial.println(": esta humedo");
  }
  else {
    Serial.print(lectorsHumedad());
    Serial.println(": esta seco");
  }
}

int lectorsHumedad()
{
  digitalWrite(sHumedad, HIGH);//pin D6 "encendido"
  delay(10);

  val = analogRead(saHumedad);//Lectura del pin SIG del sensor de humedad

  digitalWrite(sHumedad, LOW);//pin D6 "apagado"
  return val;//se envia valor del sensor
}
