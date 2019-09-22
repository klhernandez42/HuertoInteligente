/* Este código es para probrar el correcto funcionamiento de la LCD de 16x2
 * puedes encontrar el esquematico y mas detalles de como conectarlo en el repositorio de Github: 
 * https://github.com/klhernandez42/HuertoInteligente
 */
#include  <LiquidCrystal.h> //Libreria para LCD (https://www.arduino.cc/en/Reference/LiquidCrystal)

LiquidCrystal  lcd(12, 11, 5, 4, 3, 2); //lcd(rs,enable,d4,d5,d6,d7);
 
void setup()
{
  lcd.begin(16, 2); //dimensiones de la pantalla en este caso LCD de 16x2
  lcd.home();//El mensaje se iniciara en la posición (0,0)
  lcd.print("Hola Mundo");//mensaje a imprimir en primer linea
  lcd.setCursor ( 0, 1 ); //El mensaje se iniciara en la posición (1,0)
  lcd.print("prueba...");//mensaje a imprimir en segunda linea
  delay(1000);
}
 
void loop()
{
  //El efecto que se utiliza es para mover el mensaje de un lado al otro en la LCD
  int i; //Variable para control de ciclos.
 
  // Dezplazando la pantalla a la derecha
  for ( int i = 0; i < 6; i++ ) {
    lcd.scrollDisplayRight();
    delay (1000);
  }
 
  // Dezplazando la pantalla a la izquierda
  for ( int i = 0; i < 6; i++ ) {
    lcd.scrollDisplayLeft();
    delay (1000);
  }
}
