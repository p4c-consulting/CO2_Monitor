#include <U8g2lib.h>
#include <Wire.h>
#include "SparkFun_SCD30_Arduino_Library.h" //Click here to get the library: http://librarymanager/All#SparkFun_SCD30
U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ 15, /* data=*/ 4, /* reset=*/ 16);
SCD30 airSensor;
#define gn  2
#define gelb  12
#define rot   13

void setup()
{
  Wire.begin();
  airSensor.begin();
  airSensor.setMeasurementInterval(2); //Change number of seconds between measurements: 2 to 1800 (30 minutes)
  airSensor.setAltitudeCompensation(245); //Set altitude of the sensor in m
  airSensor.setAmbientPressure(1030); //Current ambient pressure in mBar: 700 to 1200
  u8x8.begin();
  pinMode(gn, OUTPUT);
  pinMode(gelb, OUTPUT);
  pinMode(rot, OUTPUT);
}

void loop()
{
    u8x8.clearDisplay();
    u8x8.setFont(u8x8_font_inr33_3x6_n);
    u8x8.setCursor (0, 0);
    u8x8.print(airSensor.getCO2());
    u8x8.setFont(u8x8_font_7x14_1x2_r);
    u8x8.setCursor (0, 6);
    u8x8.print(airSensor.getTemperature(), 1);
    u8x8.print(" C");
    u8x8.setCursor (9, 6);
    u8x8.print(airSensor.getHumidity(), 1);
    u8x8.print(" %");
    switch (airSensor.getCO2()) {
      case 2000 ... 20000:
      digitalWrite(gn, LOW);
      digitalWrite(gelb, LOW);
      digitalWrite(rot, HIGH);
      break;
      case 1000 ... 1999:
      digitalWrite(gn, LOW);
      digitalWrite(gelb, HIGH);
      digitalWrite(rot, LOW);
      break;
      default:
      digitalWrite(gn, HIGH);
      digitalWrite(gelb, LOW);
      digitalWrite(rot, LOW);
      break;
      }
    delay(10000);
}
