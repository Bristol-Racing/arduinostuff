// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <Wire.h> 
#include "RTClib.h"
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3E,20,4); 
RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

int lastSecond = 0;

void setup () {
  Serial.begin(57600);

#ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
#endif

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
//    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));

  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight 
}

void loop () {
    DateTime now = rtc.now();
    char out[20];

    if (lastSecond != now.second()) {
      lcd.clear();
      lastSecond = now.second();  
    }

    sprintf(out, "                    ");
    sprintf(out, "%d/%d/%d", now.day(), now.month(), now.year());
    lcd.setCursor ( 0, 0 );            // go to the top left corner
    lcd.print(out); // write this string on the top row

    sprintf(out, "                    ");
    sprintf(out, "%d:%d:%d", now.hour(), now.minute(), now.second());
    lcd.setCursor ( 0, 1 );            // go to the 2nd row
    lcd.print(out); // pad string with spaces for centering
//    lcd.setCursor ( 0, 2 );            // go to the third row
//    lcd.print("  20 cols, 4 rows   "); // pad with spaces for centering
//    lcd.setCursor ( 0, 3 );            // go to the fourth row
//    lcd.print(" www.sunfounder.com ");

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

    Serial.print("Temperature: ");
    Serial.print(rtc.getTemperature());
    Serial.println(" C");

    Serial.println();
    delay(10);
}
