// Hello LoRa - ABP TTN Packet Sender (Multi-Channel)
// Tutorial Link: https://learn.adafruit.com/the-things-network-for-feather/using-a-feather-32u4
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Copyright 2015, 2016 Ideetron B.V.
//
// Modified by Brent Rubell for Adafruit Industries, 2018
/************************** Configuration ***********************************/
#include <TinyLoRa.h>
#include <SPI.h>

// Visit your thethingsnetwork.org device console
// to create an account, or if you need your session keys.

// Network Session Key (MSB)
uint8_t NwkSkey[16] = { 0x7E, 0x7B, 0x51, 0x7F, 0xAD, 0x46, 0x99, 0xD9, 0x28, 0x03, 0x1B, 0xCE, 0x15, 0x94, 0x41, 0x44 };

// Application Session Key (MSB)
uint8_t AppSkey[16] = { 0x57, 0x34, 0x8D, 0xC8, 0x30, 0x7C, 0xEF, 0xDE, 0x41, 0xCC, 0xF5, 0x20, 0x97, 0xD7, 0x8B, 0x10 };

// Device Address (MSB)
uint8_t DevAddr[4] = { 0x26, 0x01, 0x1A, 0x75 };

/************************** Example Begins Here ***********************************/
// Data Packet to Send to TTN
// unsigned char loraData[11] = {"hello LoRa"};
unsigned char loraData[4];


// How many times data transfer should occur, in seconds
const unsigned int sendInterval = 20;

// Pinout for Adafruit Feather 32u4 LoRa
TinyLoRa lora = TinyLoRa(7, 8, 4);

// Pinout for Adafruit Feather M0 LoRa
//TinyLoRa lora = TinyLoRa(3, 8, 4);

/* Sensor Monitor */
const int m_time = 10;      //Meassuretime in Seconds
int wind_ct = 0;
float wind = 0.0;
unsigned long time = 0;

const int ValeursNumerisees[16] = {66,84,93,126,184,244,287,406,461,599,630,702,785,827,886,944};

void setup()
{
  delay(2000);
  Serial.begin(9600);
  while (! Serial);
  
  // Initialize pin LED_BUILTIN as an output
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Initialize LoRa
  Serial.print("Starting LoRa...");
  // define multi-channel sending
  lora.setChannel(MULTI);
  // set datarate
  lora.setDatarate(SF7BW125);
  if(!lora.begin())
  {
    Serial.println("Failed");
    Serial.println("Check your radio");
    while(true);
  }

  // Optional set transmit power. If not set default is +17 dBm.
  // Valid options are: -80, 1 to 17, 20 (dBm).
  // For safe operation in 20dBm: your antenna must be 3:1 VWSR or better
  // and respect the 1% duty cycle.

  // lora.setPower(17);

  Serial.println("OK");

  /* Sensor Monitor */
  time = millis();
  pinMode(3,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3), countWind, RISING);
}

void loop()
{
  int16_t sensorValue = analogRead(A1);
  Serial.print("sensor ");
  Serial.println(sensorValue);

  // initialisation de l'indice de boucle 'tant que'
  int16_t k = 0; 
  // comparaison de la mesure avec la moyenne de 2 résistances successives
  while(sensorValue > int((ValeursNumerisees[k]+ValeursNumerisees[k+1])/2)){    
    k = k+1; 
  }
  
  measure();

  Serial.print("Windgeschwindigkeit: ");
  Serial.print(wind);       //Speed in Km/h
  Serial.print(" km/h - ");
  Serial.print(wind / 3.6); //Speed in m/s
  Serial.println(" m/s");

  int16_t wind_km = round(wind * 100);
  int16_t wind_ms = round(wind/ 3.6 * 100);

  // encode int as bytes
  //byte payload[2];
  loraData[0] = highByte(wind_km);
  loraData[1] = lowByte(wind_km);

  loraData[2] = highByte(k);
  loraData[3] = lowByte(k);
    
  Serial.println("Sending LoRa Data...");
  lora.sendData(loraData, sizeof(loraData), lora.frameCounter);
  // Optionally set the Frame Port (1 to 255)
  // uint8_t framePort = 1;
  // lora.sendData(loraData, sizeof(loraData), lora.frameCounter, framePort);
  Serial.print("Frame Counter: ");Serial.println(lora.frameCounter);
  lora.frameCounter++;

  // blink LED to indicate packet sent
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  
  Serial.println("delaying...");
  delay(sendInterval * 1000);
}

void countWind() {
  wind_ct ++;
}

void measure() {
  wind_ct = 0;
  time = millis();
  delay(1000 * m_time);
  //detachInterrupt(9);
  // tour/s * 2pi * r * 3.6
  wind = ((float)wind_ct / (float)m_time * 2 * 3.14 * 0.072)*3.6 ;
  //wind = 2*3.1415*0.031*5*wind_ct;
  Serial.print("windCt" + wind_ct);
}
