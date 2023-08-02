#include <SoftwareSerial.h> 
#include "MAX30100_PulseOximeter.h" 
#include <TinyGPS++.h>

const byte button = 7;
byte buttState;

SoftwareSerial gpsSerial(8, 9); 
SoftwareSerial simSerial(4, 3);

PulseOximeter pox;
TinyGPSPlus gps;
float heartRate, lat, lng, spo2;
bool gpsDataAvailable = false;

uint32_t lastMillis = 0;
uint32_t max30100Interval = 1500; 

void(* resetFunc) (void) = 0;

void setup() {
  pinMode(button, INPUT);
  u8g.setColorIndex(1); 
  simSerial.begin(4800);
  simSerial.println(F("AT")); 
  delay(100);
  Serial.begin(4800);
  simSerial.println(F("AT+CMGF=1")); 
  delay(100);
  gpsSerial.begin(9600);
  simSerial.println("AT+CMGS=\"+639\""); //phone number
  delay(100);
  pox.begin();
  pox.setIRLedCurrent(MAX30100_LED_CURR_11MA); 
  delay(100);

}

void loop()
{ 
  buttState = digitalRead(button);

    if(buttState == 1){
      sendSMS();
    } else{inputs();}
}

void inputs(){
  unsigned long currentMillis = millis();

    while (gpsSerial.available() > 0) {
      if (gps.encode(gpsSerial.read())) {
        if (gps.location.isValid()) {
          lat = gps.location.lat();
          lng = gps.location.lng();
          gpsDataAvailable = true;

          gpsSerial.end();
        }
      }
    }
  
  if (currentMillis - lastMillis > max30100Interval)
  {
    lastMillis = currentMillis;

    if (pox.getHeartRate() || pox.getSpO2())
    {
       heartRate = pox.getHeartRate();
       spo2 = pox.getSpO2();
         
      Serial.print(F("Latitude: "));
      Serial.println(lat, 6);
      Serial.print(F("Longitude: "));
      Serial.println(lng, 6);
      Serial.print(F("Heart Rate: "));
      Serial.println(heartRate);
      Serial.print(F("SpO2: "));
      Serial.println(spo2);

    }else{Serial.println(F("Place Finger"));}
   
  }
  pox.update();
}


void sendSMS(){
      
      simSerial.println(F("PIN-tig Emergency Alert!!")); 
      simSerial.println(F("Wearer's Oximetry Readings are:")); 
      simSerial.print(F("Heart Rate: "));
      simSerial.print(heartRate);
      simSerial.println(F("bpm"));
      simSerial.print(F("Spo2: "));
      simSerial.print(spo2);
      simSerial.println(F("%"));
      simSerial.println(F("Located at"));
      simSerial.print(F("Latitude: "));
      simSerial.println(lat, 6);
      simSerial.print(F("Longitude: "));
      simSerial.println(lng, 6);
      simSerial.write(26);

      Serial.println(F("SMS Sent"));
      resetFunc();
 }
