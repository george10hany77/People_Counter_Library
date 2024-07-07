// ACTIVE LOW SENSORS

#include "Arduino.h"
#include <LiquidCrystal_I2C.h>
#include  <Wire.h>

volatile bool sensor1 = true;
volatile bool sensor2 = true;

bool flag2In = false;
bool flag2Out = false;

int counter = 0;
int prevCounter = 0;

LiquidCrystal_I2C lcd(0x27,  16, 2);

void action2();
void action1();

void setup() {
    Serial.begin(115200);
    pinMode(13, OUTPUT);
    pinMode(2, INPUT);
    attachInterrupt(digitalPinToInterrupt(2), action1, CHANGE);
    pinMode(3, INPUT);
    attachInterrupt(digitalPinToInterrupt(3), action2, CHANGE);

    pinMode(12, OUTPUT);

    lcd.begin();
    // turn on the backlight
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print(counter);

}

void loop() {

    while (!sensor1) {
        if (!sensor2) {
            flag2In = true;
        }else{
            flag2In = false;
        }
         Serial.println("s1");
    }

    if(!sensor2 && flag2In){
        counter ++;
        digitalWrite(13, HIGH);
        flag2In = false;
    }

    while (!sensor2) {
        if (!sensor1) {
            flag2Out = true;
        }else{
            flag2Out = false;
        }
         Serial.println("s2");
    }

    if(!sensor1 && flag2Out){
        counter --;
        digitalWrite(13, LOW);
        flag2Out = false;
    }

     Serial.print(counter);
     Serial.print("  ");
     Serial.print(sensor1);
     Serial.print("  ");
     Serial.print(sensor2);
     Serial.print("  ");
     Serial.print(flag2In);
     Serial.print("  ");
     Serial.println(flag2Out);

    if (prevCounter != counter){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(counter);
        prevCounter = counter;
    }

    if (counter > 0) {
        digitalWrite(12, HIGH);
    }else{
        digitalWrite(12, LOW);
    }

    while(counter < 0){
        digitalWrite(12, HIGH);
        delay(500);
        digitalWrite(12, LOW);
        delay(500);
    }

}

void action1(){
    sensor1 = digitalRead(2);
}

void action2(){
    sensor2 = digitalRead(3);
}
