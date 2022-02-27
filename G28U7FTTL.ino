#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// Módulo G28U7FTTL
const int TX_GPS = 4;
const int RX_GPS = 3;
const int GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial ss(TX_GPS, RX_GPS);
#define GPS_SAT gps.satellites.value()
#define GPS_LAT gps.location.lat()
#define GPS_LON gps.location.lng()
#define GPS_ALT gps.altitude.meters()
#define GPS_SEC gps.time.second()
#define GPS_MIN gps.time.minute()
#define GPS_HOU gps.time.hour() + 1


void setup() {
  Serial.begin(9600);
  ss.begin(GPSBaud);
  ss.print("$PUBX,40,GLL,0,0,0,0*5C\r\n");
  ss.print("$PUBX,40,ZDA,0,0,0,0*44\r\n");
  ss.print("$PUBX,40,VTG,0,0,0,0*5E\r\n");
  ss.print("$PUBX,40,GSV,0,0,0,0*59\r\n");
  ss.print("$PUBX,40,GSA,0,0,0,0*4E\r\n");
  ss.print("$PUBX,40,RMC,0,0,0,0*47\r\n");


  delay(1000);
  while (ss.available()) {
    gps.encode(ss.read());
  }
  if (gps.charsProcessed() < 10) {
    Serial.println("No GPS data received: check wiring");
  }

  while (!gps.location.isValid()) {
    while (ss.available()) {
      gps.encode(ss.read());
    }
  }
}


void loop() {


  Serial.print(GPS_SAT);
  Serial.write('\t');
  Serial.print(GPS_LAT, 6);
  Serial.write('\t');
  Serial.print(GPS_LON, 6);
  Serial.write('\t');
  Serial.print(GPS_ALT, 6);
  Serial.write('\t');

  Serial.print(GPS_HOU);
  Serial.write(':');
  Serial.print(GPS_MIN);
  Serial.write(':');
  Serial.print(GPS_SEC);
  Serial.write('\n');


  gps_read();

  //delay(50);

}

void gps_read() {
  char aaa = ss.peek();
  while (ss.available()) {
    aaa = ss.read();
    //Serial.write(aaa);
    gps.encode(aaa);
  }
}


static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}