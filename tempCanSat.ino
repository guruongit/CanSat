/* States 

0 -> Off
1 -> On - gorund
2 -> On - Ready/start sending telementry
3 -> On - Max altitude
4 -> After Deployement
5 -> Descent One
6 -> Descent two
7 -> postflight

*/
// Libraries
#include <Wire.h>   //To intitialise I2C connections
#include <BMP388_DEV.h>
#include<FaBo9Axis_MPU9250.h>
#include "ublox.h" // Neo M8n



// Sensor Decleration
BMP388_DEV bmp388; 
FaBo9Axis mpu9250;
ublox neoM8n;

/*Variable Decleartions*/

// general 
  int state = 0; 
  int pinStartButton = 2;
  int pinLedGreen = 3;

// BMP
float temperature, pressure, altitude;  

// MPU 9250
float ax,ay,az;
float gx,gy,gz;
float mx,my,mz;
float mputemp;

// NEO_M8N

float gpsAltitude, gpsLatitude, gpsLongitude, gpsSatsInUse;



void setup() {
  Serial.begin(9600);

  // General

    pinMode(pinStartButton,OUTPUT); // For Button
    pinMode(pinLedGreen,INPUT); // For On LED
  


  // BMP
  if(bmp388.begin()){
    // Serial.println("configured bmp388");
  } else {
    Serial.println("device error bmp388");
    while(1);
  }                                 // Default initialisation, place the BMP388 into SLEEP_MODE 
  bmp388.setTimeStandby(TIME_STANDBY_1280MS);     // Set the standby time to 1.3 seconds
  bmp388.startNormalConversion();                 // Start BMP388 continuous conversion in NORMAL_MODE 

  // MPU-9250
  if(mpu9250.begin()){
    //Serial.println("configured mpu9250");
  } else {
    Serial.println("device error mpu9250");
    while(1);
  }

  // Neo - M8N
  Serial1.begin(9600);

  if(!Serial.avalable()){
      Serial.println("device error neo-m8n");
  }

  


  
}

void loop() {
    
    // State Check
    state = digitalRead(pinStartButton); // checking switch is On/OFF.
    if(state1==0)  return;

    digitalWrite(pinLedGreen,HIGH);  //On status


    /*  BMP */
    if (bmp388.getMeasurements(temperature, pressure, altitude))    // Check if the measurement is complete
    { 
      /* // Display the results   
      Serial.print(temperature);                     
      Serial.print(F("*C   "));
      Serial.print(pressure);    
      Serial.print(F("hPa   "));
      Serial.print(altitude);
      Serial.println(F("m"));  
      */
    }
    else{
      Serial.println("Mesurement is not complete");
    }

    /* MPU-9250 */

    // To get readings
    mpu9250.readAccelXYZ(&ax,&ay,&az);
    mpu9250.readGyroXYZ(&gx,&gy,&gz);
    mpu9250.readMagnetXYZ(&mx,&my,&mz);
    mpu9250.readTemperature(&mputemp);

    // To Display

      // Serial.print("ax: ");
      // Serial.print(ax);
      // Serial.print(" ay: ");
      // Serial.print(ay);
      // Serial.print(" az: ");
      // Serial.println(az);

      // Serial.print("gx: ");
      // Serial.print(gx);
      // Serial.print(" gy: ");
      // Serial.print(gy);
      // Serial.print(" gz: ");
      // Serial.println(gz);

      // Serial.print("mx: ");
      // Serial.print(mx);
      // Serial.print(" my: ");
      // Serial.print(my);
      // Serial.print(" mz: ");
      // Serial.println(mz);

      // Serial.print("temp: ");
      // Serial.println(mputemp);

    /* Neo M8N */
    
    // For Readings
    while(Serial1.available()){
        char c = Serial1.read();
        if (M8_Gps.encode(c)) {
          gpsAltitude = M8_Gps.altitude;
          gpsLatitude = M8_Gps.latitude;
          gpsLongitude = M8_Gps.longitude; 
          gpsSatsInUse = M8_Gps.sats_in_use;
        }
    }
    // For Display
      // for(byte i = 0; i < N_FLOATS; i++) {
      //   Serial.print(gpsArray[i], 6);Serial.print(" ");
      // }
      // Serial.println("");

    
    
 



    delay(1000);
}
