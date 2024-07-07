//
// Created by George on 7/7/2024.
//
#include "PeopleCounter.h"

PeopleCounter::PeopleCounter() {
    instance = nullptr;
}

PeopleCounter::PeopleCounter(uint8_t s1Pin, uint8_t s2Pin, MODE mode) {
    instance = nullptr;
    this->sensor1Pin = s1Pin;
    this->sensor2Pin = s2Pin;
    this->mode = mode;
    switch (mode) {
        case ACTIVE_LOW:
            // if active low
            sensor1Val = true;
            sensor2Val = true;
            ////////////////
            break;
        case ACTIVE_HIGH:
            // if active high
            sensor1Val = LOW;
            sensor2Val = LOW;
            ////////////////
            break;
    }

}

void PeopleCounter::setSensor1Pin(uint8_t s1Pin){
    this->sensor1Pin = s1Pin;
}

void PeopleCounter::setSensor2Pin(uint8_t s2Pin){
    this->sensor2Pin = s2Pin;
}

void PeopleCounter::setMode(MODE mode){
    this->mode = mode;
}

bool PeopleCounter::begin() {
//    if (!areValidPins()) return false;
    instance = this;
    pinMode(digitalPinToInterrupt(sensor1Pin), INPUT);
    attachInterrupt(sensor1Pin, action1, CHANGE);
    pinMode(sensor2Pin, INPUT);
    attachInterrupt(digitalPinToInterrupt(sensor2Pin), action2, CHANGE);
    return true;
}

void PeopleCounter::action1(){
    if (instance != nullptr) {
        instance->sensor1Val = digitalRead(instance->sensor1Pin);
    }
}

void PeopleCounter::action2(){
    if (instance != nullptr) {
        instance->sensor2Val = digitalRead(instance->sensor2Pin);
    }
}

bool PeopleCounter::areValidPins(){
    return (digitalPinToInterrupt(sensor1Pin) >= 0) && (digitalPinToInterrupt(sensor2Pin) >= 0);
}

int PeopleCounter::getCount() {
    return counter;
}

void PeopleCounter::runAlgorithm() {
    while (!sensor1Val) {
        if (!sensor2Val) {
            flag2In = true;
        }else{
            flag2In = false;
        }
        Serial.println("s1");
    }

    if(!sensor2Val && flag2In){
        counter ++;
        digitalWrite(13, HIGH);
        flag2In = false;
    }

    while (!sensor2Val) {
        if (!sensor1Val) {
            flag2Out = true;
        }else{
            flag2Out = false;
        }
        Serial.println("s2");
    }

    if(!sensor1Val && flag2Out){
        counter --;
        digitalWrite(13, LOW);
        flag2Out = false;
    }
}