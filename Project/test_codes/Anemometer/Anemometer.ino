const int m_time = 5;      //Meassuretime in Seconds
int wind_ct = 0;
float wind = 0.0;
unsigned long time = 0;


void setup()
{
  Serial.begin(9600);
  time = millis();
  pinMode(3,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3), countWind, RISING);
}

void loop()
{
  
  meassure();
  Serial.print("windCt");
  Serial.println(wind_ct);
  Serial.print("Windgeschwindigkeit: ");
  Serial.print(wind);       //Speed in Km/h
  Serial.print(" km/h - ");
  Serial.print(wind / 3.6); //Speed in m/s
  Serial.println(" m/s");

}

void countWind() {
  wind_ct ++;
}

void meassure() {
  wind_ct = 0;
  time = millis();
  delay(1000 * m_time);
  //detachInterrupt(9);
  wind = (float)wind_ct / (float)m_time * 2.4;
  Serial.print("windCt" + wind_ct);
}
