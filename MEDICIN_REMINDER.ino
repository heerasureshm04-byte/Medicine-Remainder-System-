#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>

RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin definitions
const int buzzer = 8;
const int button = 2;

// First reminder time
const int reminderHour = 4;
const int reminderMinute = 45;

bool firstReminderDone = false;
bool alarmOn = false;

unsigned long lastReminderTime = 0;
const unsigned long interval = 30000; // 30 seconds

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(button, INPUT_PULLUP);

  digitalWrite(buzzer, LOW);

  Wire.begin();
  lcd.init();
  lcd.backlight();

  if (!rtc.begin()) {
    lcd.setCursor(0, 0);
    lcd.print("RTC ERROR");
    while (1);
  }

  // Upload ONCE to set RTC to 04:45:00
  rtc.adjust(DateTime(2026, 7, 9, 4, 45, 0));

  lcd.clear();
}

void loop() {

  DateTime now = rtc.now();

  // Display current time
  lcd.setCursor(0, 0);
  lcd.print("Time:");
  if (now.hour() < 10) lcd.print("0");
  lcd.print(now.hour());
  lcd.print(":");
  if (now.minute() < 10) lcd.print("0");
  lcd.print(now.minute());
  lcd.print(":");
  if (now.second() < 10) lcd.print("0");
  lcd.print(now.second());
  lcd.print(" ");

  // First reminder at 04:45
  if (!firstReminderDone &&
      now.hour() == reminderHour &&
      now.minute() == reminderMinute &&
      !alarmOn) {

    alarmOn = true;
    digitalWrite(buzzer, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("Take Medicine ");
  }

  // Next reminder every 30 seconds after button press
  if (firstReminderDone &&
      !alarmOn &&
      millis() - lastReminderTime >= interval) {

    alarmOn = true;
    digitalWrite(buzzer, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("Take Medicine ");
  }

  // Button pressed
  if (alarmOn && digitalRead(button) == LOW) {

    digitalWrite(buzzer, LOW);
    alarmOn = false;

    firstReminderDone = true;
    lastReminderTime = millis();

    lcd.setCursor(0, 1);
    lcd.print("Medicine Taken");

    delay(1500);

    lcd.setCursor(0, 1);
    lcd.print("Next:30 Seconds");
  }

  delay(200);
}
