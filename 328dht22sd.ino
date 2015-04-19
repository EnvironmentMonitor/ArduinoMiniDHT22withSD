/*
 ___/'¬_         /\
{_-_ ^  \_______//
     /           \
     \ _  _____  /
     || ||     |||
     || ||     |||  
BadTail Projects ALL RIGHTS GRANTED this is OPEN SOURCE and 
without any Implied or Otherwise "Gaurantees" of a 
Particular Part in Whole or Function
and free to use in any or all parts.........
Libraries are part of Standard GNU License........
Rod Con ..... The Road to Contentment.............

This is a just one Reliable approach to IOT Logging, put it on the SDCARD then
PUSH The Data to the Remote Server Seperately allowing Local Analyssis and backup.

The error checking is done to allow the ignoring of
1 missing sensor but to log from the other if you only have 1.

This Only Requires the DHT & SD Library to compile.


*/

#include "DHT.h"
#include <SD.h>
#define DHTPIN 2
#define DHTPIN1 3
#define DHTTYPE DHT22
const int chipSelect = 4;
DHT dht(DHTPIN, DHTTYPE);
DHT dht1(DHTPIN1, DHTTYPE);

void setup() {
  Serial.begin(9600); 
  Serial.println("DHT22 Digital Temperature And Hunidity Logging Starting....");
    Serial.print("Initializing SD card...");
    pinMode(10, OUTPUT);
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
  return;
  }
  Serial.println("card initialized.");
delay(2000); 
  dht.begin();
  dht1.begin();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor 1 !");
  }
  float hi = dht.computeHeatIndex(f, h);
  float h1 = dht1.readHumidity();
  float t1 = dht1.readTemperature();
  float f1 = dht1.readTemperature(true);
  if (isnan(h1) || isnan(t1) || isnan(f1)) {
    Serial.println("Failed to read from DHT sensor 2 !");
    return;
  }
  float hi1 = dht1.computeHeatIndex(f1, h1);
  Serial.print("2ndCavity "); 
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.print(" *C   ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("  Heat index: ");
  Serial.print(hi);
  Serial.println(" *F ");
  Serial.print("  Bedroom "); 
  Serial.print("Humidity: "); 
  Serial.print(h1);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t1);
  Serial.print(" *C   ");
  Serial.print(f1);
  Serial.print(" *F\t");
  Serial.print("  Heat index: ");
  Serial.print(hi1);
  Serial.println(" *F");
        File dataFile1 = SD.open("humidlog.CSV", FILE_WRITE);
    if (dataFile1) {
      dataFile1.print("2nd Cavity Humidity = ");
      dataFile1.print(h);
      dataFile1.print("   2nd  Cavity  Temp  = ");
      dataFile1.print(t);
      dataFile1.println(" Celsius ");
      dataFile1.print("   Bedroom Humidity = ");
      dataFile1.print(h1);
      dataFile1.print("  Bedroom Temperature = ");
      dataFile1.print(t1);
      dataFile1.println(" Celsius ");
      dataFile1.close();
    delay(5000);// Pause here to ensure when power off FILE CLOSED!!
      }         // Wait for Pin 13 LED (SPI Activity) to Flash before power off!
    else {
      Serial.println("error opening humidlog.CSV");
    }
}
