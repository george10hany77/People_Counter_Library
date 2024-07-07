// ACTIVE LOW SENSORS

#include "Arduino.h"
#include <LiquidCrystal_I2C.h>
#include  <Wire.h>

#include "PeopleCounter.h"

LiquidCrystal_I2C lcd(0x27,  16, 2);

PeopleCounter pc(2,3,PeopleCounter::ACTIVE_LOW);

int prevCounter = 0;

void setup() {
    Serial.begin(115200);

    pc.begin();

    pinMode(12, OUTPUT);

    lcd.begin();
    // turn on the backlight
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print(pc.getCount());
}

void loop() {

    pc.runAlgorithm();

    Serial.println(pc.getCount());

    if (prevCounter != pc.getCount()){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(pc.getCount());
        prevCounter = pc.getCount();
    }

    if (pc.getCount() > 0) {
        digitalWrite(12, HIGH);
    }else{
        digitalWrite(12, LOW);
    }

    while(pc.getCount() < 0){ // error happened
        digitalWrite(12, HIGH);
        delay(500);
        digitalWrite(12, LOW);
        delay(500);
    }

}
