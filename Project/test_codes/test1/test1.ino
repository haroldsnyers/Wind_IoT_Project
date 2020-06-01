void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(A1);
  int sensorValue2 = digitalRead(9);
  Serial.println(sensorValue);
  Serial.println(sensorValue2);
  Serial.println("hello");
  delay(100);
}
//
//#include <time.h>
//int compteurfm = 0;
//int nbrtour = 0;
//unsigned long compte_temps;
//int increm_temps = 1;
//int anemometre = 0;
//
//void setup()
//{
//  pinMode (6, INPUT);
//  attachInterrupt (4, anemometre, RISING);
//  Serial.begin(9600);
//}
//
//void loop()
//{
//  int i = 1;
//  while(i)
//  {
//    anemometre = 0;
//    long temps_depart = millis();
//    long duree = 6000;
//    while((temps_depart - millis()) < duree)
//    {
//      if (digitalRead(6) ==1)
//      {
//        anemometre = anemometre + 1;
//      }
//    }
//  nbrtour = anemometre / 2;   
//  Serial.print(2 * 3.1415 * 0.05 * nbrtour);
//  Serial.println (" m/s");
//  i = 0;
//  }
//}

// read RPM
// int half_revolutions = 0;
// int rpm = 0;
// unsigned long lastmillis = 0;
// 
// void setup(){
//   Serial.begin(9600); 
//   attachInterrupt(0, rpm_fan, FALLING);
// }
// 
// void loop(){
////   if (millis() - lastmillis == 1000){ //Uptade every one second, this will be equal to reading frecuency (Hz).
//     detachInterrupt(0);//Disable interrupt when calculating
//     rpm = half_revolutions * 60; // Convert frecuency to RPM, note: this works for one interruption per full rotation. For two interrups per full rotation use half_revolutions * 30.
//     Serial.print("RPM =\t"); //print the word "RPM" and tab.
//     Serial.print(rpm); // print the rpm value.
//     Serial.print("\t Hz=\t"); //print the word "Hz".
//     Serial.println(half_revolutions); //print revolutions per second or Hz. And print new line or enter.
//     half_revolutions = 0; // Restart the RPM counter
//     lastmillis = millis(); // Uptade lasmillis
//     attachInterrupt(0, rpm_fan, FALLING); //enable interrupt
//     delay(200);
////    }
// }
// // this code will be executed every time the interrupt 0 (pin2) gets low.
// void rpm_fan(){
//  half_revolutions++;
// }
