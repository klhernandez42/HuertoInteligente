/* Este código es para probrar el correcto funcionamiento del servo motor
   puedes encontrar el esquematico y mas detalles de como conectarlo en el repositorio de Github:
   https://github.com/klhernandez42/HuertoInteligente
*/
#include <Servo.h> //Libreria para servomotor

Servo servo1; //Declaración de la variable del servomotor

void setup() {
  servo1.attach(9); //Pin donde esta conectado el servomotor
  Serial.begin(9600);
}

void loop() {
  servo1.write(0);   //Posicion de 0 grados
  delay(1000);

  //servo1.write(90);//Posicion de 90 grados
  //delay(1000);

  servo1.write(160);//Posicion de 180 grados
  delay(1000);

  //Nota: El rango de movimiento de muchos servos va de 0 a 180
  //grados, sin embargo algunos servos tienen menos rango, por
  //lo que se dejan 20 grados como margen de seguridad.
}
