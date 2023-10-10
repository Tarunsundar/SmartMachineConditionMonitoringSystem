/* 
 * This sketch shows how nicla can be used in standalone mode.
 * Without the need for an host, nicla can run sketches that 
 * are able to configure the bhi sensors and are able to read all 
 * the bhi sensors data.
*/

#include "Arduino.h"
#include "Arduino_BHY2.h"
#include "SD.h"
#include"SPI.h"
float accelMag;

SensorXYZ accel(SENSOR_ID_ACC);
Sensor temp(SENSOR_ID_TEMP); 
Sensor hum(SENSOR_ID_HUM);
const int CSpin = 10;
String dataString =""; 
File sensorData;
bool label = false;

//------------------------------------------------------------------------------------//
void setup()
{
  Serial.begin(115200);
  while(!Serial);
  const int CSpin = 10;
  BHY2.begin();
  pinMode(8, OUTPUT);
  Serial.print("Initializing SD card...");
  pinMode(CSpin, OUTPUT);
  // see if the card is present and can be initialized:
  if (!SD.begin(CSpin)) {
  Serial.println("Card failed, or not present");
  // don't do anything more:
  return;
  }
  Serial.println("card initialized.");
  accel.begin();
  temp.begin();
  hum.begin();
}

void loop()
{
  BHY2.update();
  delay(300);
  accelMag = calc_mag_acc();
  float temperature = temp.value();
  float humidity = hum.value();
if(accelMag >= 15000 && temperature >=100 && humidity >= 80){
  digitalWrite(8, HIGH);  // turns the indicator light on (HIGH is the voltage level)
  delay(300);                      // wait for a second
  digitalWrite(8, LOW);   // turns the indicator light off by making the voltage LOW
  delay(300);                    
  Serial.println("acceleration magnitude:" + String(accelMag));
  Serial.println(String(", temperature: ") + String(temperature));
  Serial.println(String(", humidity: ") + String(humidity));  
  dataString = "acceleration magnitude = " + String(accelMag) + "," + " temperature = " + String(temperature) + "," + " humidity = " + String(humidity); // convert to CSV
  saveData(); // save to SD card
  }
}

void saveData(){
if(SD.exists("data.csv")){ // check the card is still there
// now append new data file
sensorData = SD.open("data.csv", FILE_WRITE);
if (sensorData){
sensorData.println(dataString);
sensorData.close(); // close the file
}
}
else{
Serial.println("Error writing to file !");
}
}

float calc_mag_acc(){
  float x, y, z;
  x = accel.x();
  y = accel.y();
  z = accel.z();
  float magAccel = sqrt(sq(x)+sq(y)+sq(z));
  return magAccel;
}
