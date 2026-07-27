# Medicine Reminder System using Arduino

## Overview

This project is an **Arduino-based Medicine Reminder System** that uses a **DS3231 Real-Time Clock (RTC)**, a **16x2 I2C LCD**, a **buzzer**, and a **push button** to remind users to take their medicine.

The system triggers an alarm at a predefined time (04:45 AM). Once the user acknowledges the reminder by pressing the button, the buzzer stops, and the system continues reminding the user every 30 seconds.

---

## Features

- Displays current time on a 16×2 LCD.
- Uses DS3231 RTC for accurate timekeeping.
- Sounds a buzzer at the scheduled reminder time.
- Displays "Take Medicine" during an active reminder.
- Stops the alarm when the user presses the button.
- Displays "Medicine Taken" after acknowledgment.
- Automatically reminds the user again every 30 seconds.

---

## Components Required

| Component | Quantity |
|-----------|----------|
| Arduino Uno/Nano | 1 |
| DS3231 RTC Module | 1 |
| 16×2 I2C LCD Display | 1 |
| Active Buzzer | 1 |
| Push Button | 1 |
| Breadboard | 1 |
| Jumper Wires | As required |

---

## Pin Connections

### LCD (I2C)

| LCD Pin | Arduino |
|----------|----------|
| VCC | 5V |
| GND | GND |
| SDA | A4 |
| SCL | A5 |

### DS3231 RTC

| RTC Pin | Arduino |
|----------|----------|
| VCC | 5V |
| GND | GND |
| SDA | A4 |
| SCL | A5 |

### Buzzer

| Buzzer | Arduino |
|---------|----------|
| Positive | D8 |
| Negative | GND |

### Push Button

| Button | Arduino |
|---------|----------|
| One Terminal | D2 |
| Other Terminal | GND |

> The button uses the Arduino's internal pull-up resistor (`INPUT_PULLUP`).

---

## Libraries Used

Install the following libraries using the Arduino Library Manager:

- RTClib
- LiquidCrystal_I2C
- Wire (built into Arduino IDE)

---

## How It Works

1. The RTC continuously keeps track of the current time.
2. The LCD displays the current time in HH:MM:SS format.
3. At **04:45 AM**, the buzzer turns ON and the LCD displays:

```
Take Medicine
```

4. When the user presses the push button:
   - The buzzer turns OFF.
   - The LCD displays:

```
Medicine Taken
```

5. After 30 seconds, the buzzer sounds again to provide another reminder.
6. This reminder repeats every 30 seconds until the system is reset.

---

## Setting the RTC

The sketch contains:

```cpp
rtc.adjust(DateTime(2026, 7, 9, 4, 45, 0));
```

This should only be used **once** to set the RTC.

After uploading the sketch for the first time:

1. Comment out the line.
2. Upload the sketch again.

Otherwise, the RTC will reset to the same date and time every time the Arduino restarts.

---

## Default Configuration

| Parameter | Value |
|-----------|-------|
| Reminder Time | 04:45 AM |
| Reminder Interval | 30 seconds |
| Buzzer Pin | D8 |
| Button Pin | D2 |
| LCD Address | 0x27 |

---

## Possible Improvements

- Multiple medicine schedules.
- Different reminder intervals.
- EEPROM storage for settings.
- Battery backup status display.
- LED indicator along with buzzer.
- Automatic daily reset.
- Bluetooth or Wi-Fi notifications.
- Mobile application integration.

---

## Future Scope

- Support multiple medicines with different timings.
- Voice reminders.
- IoT-based notifications.
- Caregiver alerts.
- Medication history logging.
- OLED or TFT display support.

---
