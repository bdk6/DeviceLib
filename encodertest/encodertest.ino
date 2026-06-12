void setup() 
{
  // put your setup code here, to run once:
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  Serial.begin(9600);

}

long oldmillis = 0;
int oldread = 0;
void loop() 
{
  int thisread = 0;
  thisread = digitalRead(5) << 2;
  thisread += digitalRead(6) << 1;
  thisread += digitalRead(7);
  long tm = millis();
  if(thisread != oldread)
  {
    Serial.print(tm-oldmillis);
    Serial.print(":");
    Serial.print(oldread);
    Serial.print(":");
    Serial.println(thisread);
    oldread = thisread;
    oldmillis = tm;
  }
  // put your main code here, to run repeatedly:

}
