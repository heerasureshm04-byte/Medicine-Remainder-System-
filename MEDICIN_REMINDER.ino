#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myServo;

// ON/OFF times (24-hour format)
int onHour = 11;   // 2 PM
int offHour = 12;  // 6 PM

void setup() {
  Wire.begin();          
  rtc.begin();
  lcd.init();
  lcd.backlight();
  
  myServo.attach(9);     
  myServo.write(0);      // Start OFF
  
  // Uncomment to set RTC time to compile time
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  Serial.begin(9600);
}

void loop() {
  DateTime now = rtc.now();

  // Display time
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  Serial.println("time:");
  if (now.hour() < 10) lcd.print("0");
  lcd.print(now.hour());
   Serial.println(now.hour());
  lcd.print(":");
  Serial.println(':');
  if (now.minute() < 10) lcd.print("0");
  lcd.print(now.minute());
  Serial.println(now.minute());
  // Check if current time is between ON and OFF hours
  if (now.hour() >= onHour && now.hour() < offHour) {
    myServo.write(90); // ON position
    lcd.setCursor(0, 1);
    lcd.print("Switch: ON ");
    Serial.println("Switch: ON ");
  } else {
    myServo.write(0); // OFF position
    lcd.setCursor(0, 1);
    lcd.print("Switch: OFF");
    Serial.println("Switch: OFF");
  }

  delay(1000);
}
