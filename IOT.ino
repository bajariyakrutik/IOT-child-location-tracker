#include <SoftwareSerial.h>

SoftwareSerial sim(10, 11);
int _timeout;
String _buffer;
String number = "+91XXXXXXXXXX"; //-> change with your number

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
float latitude;
float longitude;

void setup(){
  Serial.begin(9600);
  sim.begin(9600);
  Serial.println("GSM System Started...");
  ss.begin(GPSBaud);
  Serial.println("GPS System Started...");
}

void loop(){
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      latitude = gps.location.lat();
      longitude = gps.location.lng();
      Serial.print("Latitude= ");
      Serial.print(latitude, 6);
      Serial.print(" Longitude= ");
      Serial.println(longitude, 6);
      delay(1000);
      Serial.println ("Sending Message");
      sim.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
      delay(1000);
      sim.println("AT+CMGS=\"" + number + "\"\r"); //Mobile phone number to send message
      delay(1000);
      String SMS ="Your Tracking Device Location is "+String(latitude)+","+String(longitude)+"If you want to see it on the map click this link:https://www.google.com/maps/@"+String(latitude)+","+String(longitude)+",17z";
      sim.println(SMS);
      delay(100);
      sim.println((char)26);// ASCII code of CTRL+Z
      delay(30000);
    }
  }
}
