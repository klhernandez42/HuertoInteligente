const int control    = 7 ;

void setup()
{
  pinMode(control,  OUTPUT) ;
}
void loop()
{
  digitalWrite(control, HIGH);
  delay(1000);
  digitalWrite(control, LOW);
  delay(500);
}
