/************************************************************************************************
 * Ver:     1.1
 * MCU:     ATtiny816-M / ATtiny1616-M
 * Clock:   1MHz Internal
 * Timer:   Enabled (default timer)
 * Startup: 8ms
 * BOD VL:  1.8V
 * EEPROM:  EEPROM Retained
 * 
 * Built in Arduino using Spence Konde's megaTinyCore (https://github.com/SpenceKonde/megaTinyCore)
 * 
 * Copyright 2022, Hojadurdy Durdygylyjov - Curious Design Labs
 * 
 ************************************************************************************************
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
 * and associated documentation files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, publish, distribute, 
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software 
 * is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or 
 * substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 ************************************************************************************************/

#include <EEPROM.h>

//Pin Definitions

#define button  14
const byte leds[8]={16, 0, 1, 7, 8, 9, 10, 11};

//-- BUTTON HOLD TIME PRESETS --//

//Counter Value
uint16_t pressLength_ms = 0;

//Main Animation Sequence - 3bit
#define main_animation1     1000     //LSB   1 Second
#define main_animation2     2000     //      2 Seconds
#define main_animation4     3000     //MSB   3 Seconds

//Flash Animation Sequence - 1bit
#define flash_animation1    4000     //      4 Seconds

//Animation Speed - 2bit
#define speed1              5000     //LSB   5 Seconds
#define speed2              6000     //MSB   6 Seconds

//LED Brightness - 2bit
#define brightness1         7000     //LSB   7 Seconds
#define brightness2         8000     //MSB   8 Seconds

//-- SETTINGS EEPROM ADDRESS --//

#define main_animation1_addr    11
#define main_animation2_addr    12
#define main_animation4_addr    13
#define flash_animation1_addr   14
#define speed1_addr             15
#define speed2_addr             16
#define brightness1_addr        17
#define brightness2_addr        18

byte main_animation1_val;
byte main_animation2_val;
byte main_animation4_val;
byte flash_animation1_val;
byte speed1_val;
byte speed2_val;
byte brightness1_val;
byte brightness2_val;

//-----------------------------//

int buttonState = 1;      //Button state while not being pressed. When pressed pulls pin to GND.

byte startup;
byte startUpState;
byte startUpMode;
byte main_animationSequence;
byte flash_animationSequence;
byte animationSpeed;
byte ledBrightness;

void setup() {     

    for(int i=0;i<=7;i++) {
        pinMode(leds[i], OUTPUT); 
    }
    pinMode(button, INPUT); 
    
    startUpState = digitalRead(button);
    startUpMode = EEPROM.read(1);
    // If button and EEPROM values are same, do nothing.
    if(startUpState == 1 && startUpMode == 1) {
        //Do Nothing
    }
    else if(startUpState == 0 && startUpMode == 0) {
        //Do Nothing
    }
    // If button and EEPROM values are different, then save the new value
    else if(startUpState == 0 && startUpMode == 1) {
        EEPROM.write(1, startUpState);
    }
    else if(startUpState == 1 && startUpMode == 0) {
        EEPROM.write(1, startUpState);
    } 

    //CONFIGURE YOUR EEPROM ONCE. THEN UNCOMMENT LINES BELOW AND REPROGRAM.
    EEPROM.write(1, 1);
    EEPROM.write(11, 0);
    EEPROM.write(12, 0);
    EEPROM.write(13, 0);
    EEPROM.write(14, 0);
    EEPROM.write(15, 0);
    EEPROM.write(16, 1);
    EEPROM.write(17, 0);
    EEPROM.write(18, 0);

    startup = 1;
}

void loop() {
  
    startUpSequence();          
    switch(startUpMode) {
        case 0:
            deviceSettings();
        break;

        case 1:
            deviceRun();
        break;
    }
}

void startUpSequence() {
  
    startUpMode = EEPROM.read(1);
    main_animation1_val = EEPROM.read(main_animation1_addr);
    main_animation2_val = EEPROM.read(main_animation2_addr);
    main_animation4_val = EEPROM.read(main_animation4_addr);
    flash_animation1_val = EEPROM.read(flash_animation1_addr);
    speed1_val = EEPROM.read(speed1_addr);
    speed2_val = EEPROM.read(speed2_addr);
    brightness1_val = EEPROM.read(brightness1_addr);
    brightness2_val = EEPROM.read(brightness2_addr);

    if(startUpMode == 0 && digitalRead(button) == 0 && startup == 1) {
        for(int i=0;i<=7;i++) {
            digitalWrite(leds[i], 1);
            delay(150);
        }
        startup = 0;
    }
    else {
      //Do Nothing
    }

    //Determine Main Animation Sequence According to Values from 3 EEPROM Addresses
    if(main_animation4_val == 0 && main_animation2_val == 0 && main_animation1_val == 0) {
        main_animationSequence = 0;
    }
    else if(main_animation4_val == 0 && main_animation2_val == 0 && main_animation1_val == 1) {
        main_animationSequence = 1;
    }
    else if(main_animation4_val == 0 && main_animation2_val == 1 && main_animation1_val == 0) {
        main_animationSequence = 2;
    }
    else if(main_animation4_val == 0 && main_animation2_val == 1 && main_animation1_val == 1) {
        main_animationSequence = 3;
    }
    else if(main_animation4_val == 1 && main_animation2_val == 0 && main_animation1_val == 0) {
        main_animationSequence = 4;
    }
    else if(main_animation4_val == 1 && main_animation2_val == 0 && main_animation1_val == 1) {
        main_animationSequence = 5;
    }
    else if(main_animation4_val == 1 && main_animation2_val == 1 && main_animation1_val == 0) {
        main_animationSequence = 6;
    }
    else if(main_animation4_val == 1 && main_animation2_val == 1 && main_animation1_val == 1) {
        main_animationSequence = 7;
    }

    //Determine Flash Animation Sequence According to Value from EEPROM Address
    if(flash_animation1_val == 0) {
        flash_animationSequence = 0;
    }
    else if(flash_animation1_val == 1) {
        flash_animationSequence = 1;
    }

    //Determine Animation Speed According to Values from 2 EEPROM Addresses
    if(speed2_val == 0 && speed1_val == 0) {
        animationSpeed = 100;
    }
    else if(speed2_val == 0 && speed1_val == 1) {
        animationSpeed = 75;
    }
    else if(speed2_val == 1 && speed1_val == 0) {
        animationSpeed = 50;
    }
    else if(speed2_val == 1 && speed1_val == 1) {
        animationSpeed = 25;
    }

    //Determine LED Brightness According to Values from 2 EEPROM Addresses
    if(brightness2_val == 0 && brightness1_val == 0) {
        ledBrightness = 63;
    }
    else if(brightness2_val == 0 && brightness1_val == 1) {
        ledBrightness = 127;
    }
    else if(brightness2_val == 1 && brightness1_val == 0) {
        ledBrightness = 191;
    }
    else if(brightness2_val == 1 && brightness1_val == 1) {
        ledBrightness = 255;
    }
}

void deviceSettings() {
  
    showSettings();
    buttonHoldTimer();
    saveSettings();
}

void showSettings() {
  
    while (digitalRead(button) == 1 ) { 
        if(main_animation1_val == 0) {
            analogWrite(leds[0], 10);
        }
        else if(main_animation1_val == 1) {
            analogWrite(leds[0], 255);
        }
        if(main_animation2_val == 0) {
            analogWrite(leds[1], 10);
        }
        else if(main_animation2_val == 1) {
            analogWrite(leds[1], 255);
        }
        if(main_animation4_val == 0) {
            analogWrite(leds[2], 10);
        }
        else if(main_animation4_val == 1) {
            analogWrite(leds[2], 255);
        }
        if(flash_animation1_val == 0) {
            analogWrite(leds[3], 10);
        }
        else if(flash_animation1_val == 1) {
            analogWrite(leds[3], 255);
        }
        if(speed1_val == 0) {
            analogWrite(leds[4], 10);
        }
        else if(speed1_val == 1) {
            analogWrite(leds[4], 255);
        }
        if(speed2_val == 0) {
            analogWrite(leds[5], 10);
        }
        else if(speed2_val == 1) {
            analogWrite(leds[5], 255);
        }
        if(brightness1_val == 0) {
            analogWrite(leds[6], 10);
        }
        else if(brightness1_val == 1) {
            analogWrite(leds[6], 255);
        }
        if(brightness2_val == 0) {
            analogWrite(leds[7], 10);
        }
        else if(brightness2_val == 1) {
            analogWrite(leds[7], 255);
        }
    }
}

void buttonHoldTimer() {
  
    for(int i=0;i<=7;i++) {
        analogWrite(leds[i], 10);
    }
    
    while (digitalRead(button) == LOW ) { 
        delay(50);
        pressLength_ms = pressLength_ms + 50;

        if(pressLength_ms >= 9000) {
            pressLength_ms = 1000;
        }

        else if(pressLength_ms >= brightness2) {
            analogWrite(leds[7], 255);
            analogWrite(leds[6], 10);
        } 
        else if(pressLength_ms >= brightness1) { 
            analogWrite(leds[6], 255);
            analogWrite(leds[5], 10);
        }
        else if(pressLength_ms >= speed2) { 
            analogWrite(leds[5], 255);
            analogWrite(leds[4], 10);
        }
        else if(pressLength_ms >= speed1) {
            analogWrite(leds[4], 255);
            analogWrite(leds[3], 10);
        }
        else if(pressLength_ms >= flash_animation1) { 
            analogWrite(leds[3], 255);
            analogWrite(leds[2], 10);
        }
        else if(pressLength_ms >= main_animation4) { 
            analogWrite(leds[2], 255);
            analogWrite(leds[1], 10);
        }
        else if(pressLength_ms >= main_animation2) { 
            analogWrite(leds[1], 255);
            analogWrite(leds[0], 10);
        }
        else if(pressLength_ms >= main_animation1) {  
            analogWrite(leds[0], 255);
            analogWrite(leds[7], 10); 
        }
    }
}

void saveSettings() {
  
    if(pressLength_ms >= brightness2) {
        if(brightness2_val == 0) {
            EEPROM.write(brightness2_addr, 1);
        }
        if(brightness2_val == 1) {
            EEPROM.write(brightness2_addr, 0);
        }   
    } 
    else if(pressLength_ms >= brightness1) { 
        if(brightness1_val == 0) {
            EEPROM.write(brightness1_addr, 1);
        }
        if(brightness1_val == 1) {
            EEPROM.write(brightness1_addr, 0);
        }   
    }
    else if(pressLength_ms >= speed2) {
        if(speed2_val == 0) {
            EEPROM.write(speed2_addr, 1);
        }
        if(speed2_val == 1) {
            EEPROM.write(speed2_addr, 0);
        }    
    }
    else if(pressLength_ms >= speed1) {
        if(speed1_val == 0) {
            EEPROM.write(speed1_addr, 1);
        }
        if(speed1_val == 1) {
            EEPROM.write(speed1_addr, 0);
        } 
    }
    else if(pressLength_ms >= flash_animation1) { 
        if(flash_animation1_val == 0) {
            EEPROM.write(flash_animation1_addr, 1);
        }
        if(flash_animation1_val == 1) {
            EEPROM.write(flash_animation1_addr, 0);
        } 
    }
    else if(pressLength_ms >= main_animation4) { 
        if(main_animation4_val == 0) {
            EEPROM.write(main_animation4_addr, 1);
        }
        if(main_animation4_val == 1) {
            EEPROM.write(main_animation4_addr, 0);
        }  
    }
    else if(pressLength_ms >= main_animation2) { 
        if(main_animation2_val == 0) {
            EEPROM.write(main_animation2_addr, 1);
        }
        if(main_animation2_val == 1) {
            EEPROM.write(main_animation2_addr, 0);
        }  
    }
    else if(pressLength_ms >= main_animation1) {  
        if(main_animation1_val == 0) {
            EEPROM.write(main_animation1_addr, 1);
        }
        if(main_animation1_val == 1) {
            EEPROM.write(main_animation1_addr, 0);
        }   
    }
    pressLength_ms = 0;
}

//==========================================================================//

void deviceRun() {
  
    buttonState = digitalRead(button);
    if(buttonState == 0){
        if(flash_animationSequence == 0){
            flashAnimateSequence0();
        }
        else if(flash_animationSequence == 1){
            flashAnimateSequence1();
        } 
    }
    else if(buttonState == 1){
        if(main_animationSequence == 0){
            mainAnimateSequence0();
        }
        else if(main_animationSequence == 1){
            mainAnimateSequence1();
        }
        else if(main_animationSequence == 2){
            mainAnimateSequence2();
        } 
        else if(main_animationSequence == 3){
            mainAnimateSequence3();
        } 
        else if(main_animationSequence == 4){
            mainAnimateSequence4();
        } 
        else if(main_animationSequence == 5){
            mainAnimateSequence5();
        } 
        else if(main_animationSequence == 6){
            mainAnimateSequence6();
        } 
        else if(main_animationSequence == 7){
            mainAnimateSequence7();
        } 
    }
}

void flashAnimateSequence0() {
  
    for(int del=50;del>0;del--) {
        analogWrite(leds[0], 31*ledBrightness/255);
        analogWrite(leds[5], 191*ledBrightness/255);
        analogWrite(leds[6], 223*ledBrightness/255);
        delay(del); 
        analogWrite(leds[0], 31*ledBrightness/255);
        analogWrite(leds[1], 63*ledBrightness/255);
        analogWrite(leds[6], 223*ledBrightness/255);
        analogWrite(leds[7], 255*ledBrightness/255);
        analogWrite(leds[5], 0);
        delay(del);
        analogWrite(leds[1], 63*ledBrightness/255);
        analogWrite(leds[2], 95*ledBrightness/255);
        analogWrite(leds[7], 255*ledBrightness/255);
        analogWrite(leds[0], 0);
        analogWrite(leds[6], 0);
        delay(del);
        analogWrite(leds[2], 95*ledBrightness/255);
        analogWrite(leds[3], 127*ledBrightness/255);
        analogWrite(leds[1], 0);
        analogWrite(leds[7], 0);
        delay(del);
        analogWrite(leds[3], 127*ledBrightness/255);
        analogWrite(leds[4], 159*ledBrightness/255);
        analogWrite(leds[2], 0);
        delay(del);
        analogWrite(leds[4], 159*ledBrightness/255);
        analogWrite(leds[5], 191*ledBrightness/255);
        analogWrite(leds[3], 0);
        delay(del);
        analogWrite(leds[4], 0);
    }
    
    for(int i=0;i<2;i++) {
        for(int b=0;b<=7;b++) {
            digitalWrite(leds[b], 0);
        }
        delay(60);
        for(int b=0;b<=7;b++) {
            digitalWrite(leds[b], 1);
        }
        delay(60);
    }
    for(int b=0;b<=7;b++) {
        digitalWrite(leds[b], 0);
    }
}

void flashAnimateSequence1() {
  
    for(int del=50;del>0;del--) {
        analogWrite(leds[0], 10*ledBrightness/255);
        delay(del); 
        analogWrite(leds[1], 30*ledBrightness/255);
        delay(del); 
        analogWrite(leds[2], 60*ledBrightness/255);
        delay(del);
        analogWrite(leds[3], 100*ledBrightness/255);
        delay(del);
        analogWrite(leds[4], 150*ledBrightness/255);
        delay(del);
        analogWrite(leds[0], 0);
        analogWrite(leds[1], 10*ledBrightness/255);
        analogWrite(leds[2], 30*ledBrightness/255);
        analogWrite(leds[3], 60*ledBrightness/255);
        analogWrite(leds[4], 100*ledBrightness/255);
        analogWrite(leds[5], 180*ledBrightness/255);
        delay(del);
        analogWrite(leds[1], 0);
        analogWrite(leds[2], 10*ledBrightness/255);
        analogWrite(leds[3], 30*ledBrightness/255);
        analogWrite(leds[4], 70*ledBrightness/255);
        analogWrite(leds[5], 130*ledBrightness/255);
        analogWrite(leds[6], 200*ledBrightness/255);
        delay(del);
        analogWrite(leds[2], 0);
        analogWrite(leds[3], 20*ledBrightness/255);
        analogWrite(leds[4], 80*ledBrightness/255);
        analogWrite(leds[5], 150*ledBrightness/255);
        analogWrite(leds[6], 180*ledBrightness/255);
        analogWrite(leds[7], 255*ledBrightness/255);
        delay(del);
        analogWrite(leds[3], 0);
        delay(del);
        analogWrite(leds[4], 0);
        delay(del);
        analogWrite(leds[5], 0);
        delay(del);
        analogWrite(leds[6], 0);
        delay(del);
        analogWrite(leds[7], 0);
    }
    
    for(int i=0;i<2;i++) {
        for(int b=0;b<=7;b++) {
            digitalWrite(leds[b], 0);
        }
        delay(60);
        for(int b=0;b<=7;b++) {
            digitalWrite(leds[b], 1);
        }
        delay(60);
    }
    for(int b=0;b<=7;b++) {
        digitalWrite(leds[b], 0);
    }
}

void mainAnimateSequence0() {
  
    analogWrite(leds[0], 31*ledBrightness/255);
    analogWrite(leds[5], 191*ledBrightness/255);
    analogWrite(leds[6], 223*ledBrightness/255);
    delay(animationSpeed); 
    analogWrite(leds[0], 31*ledBrightness/255);
    analogWrite(leds[1], 63*ledBrightness/255);
    analogWrite(leds[6], 223*ledBrightness/255);
    analogWrite(leds[7], 255*ledBrightness/255);
    analogWrite(leds[5], 0);
    delay(animationSpeed);
    analogWrite(leds[1], 63*ledBrightness/255);
    analogWrite(leds[2], 95*ledBrightness/255);
    analogWrite(leds[7], 255*ledBrightness/255);
    analogWrite(leds[0], 0);
    analogWrite(leds[6], 0);
    delay(animationSpeed);
    analogWrite(leds[2], 95*ledBrightness/255);
    analogWrite(leds[3], 127*ledBrightness/255);
    analogWrite(leds[1], 0);
    analogWrite(leds[7], 0);
    delay(animationSpeed);
    analogWrite(leds[3], 127*ledBrightness/255);
    analogWrite(leds[4], 159*ledBrightness/255);
    analogWrite(leds[2], 0);
    delay(animationSpeed);
    analogWrite(leds[4], 159*ledBrightness/255);
    analogWrite(leds[5], 191*ledBrightness/255);
    analogWrite(leds[3], 0);
    delay(animationSpeed);
    analogWrite(leds[4], 0); 
}

void mainAnimateSequence1() {
  
    analogWrite(leds[0], 10*ledBrightness/255);
    delay(animationSpeed); 
    analogWrite(leds[1], 30*ledBrightness/255);
    delay(animationSpeed); 
    analogWrite(leds[2], 60*ledBrightness/255);
    delay(animationSpeed);
    analogWrite(leds[3], 100*ledBrightness/255);
    delay(animationSpeed);
    analogWrite(leds[4], 150*ledBrightness/255);
    delay(animationSpeed);
    analogWrite(leds[0], 0);
    analogWrite(leds[1], 10*ledBrightness/255);
    analogWrite(leds[2], 30*ledBrightness/255);
    analogWrite(leds[3], 60*ledBrightness/255);
    analogWrite(leds[4], 100*ledBrightness/255);
    analogWrite(leds[5], 180*ledBrightness/255);
    delay(animationSpeed);
    analogWrite(leds[1], 0);
    analogWrite(leds[2], 10*ledBrightness/255);
    analogWrite(leds[3], 30*ledBrightness/255);
    analogWrite(leds[4], 70*ledBrightness/255);
    analogWrite(leds[5], 130*ledBrightness/255);
    analogWrite(leds[6], 200*ledBrightness/255);
    delay(animationSpeed);
    analogWrite(leds[2], 0);
    analogWrite(leds[3], 20*ledBrightness/255);
    analogWrite(leds[4], 80*ledBrightness/255);
    analogWrite(leds[5], 150*ledBrightness/255);
    analogWrite(leds[6], 180*ledBrightness/255);
    analogWrite(leds[7], 255*ledBrightness/255);
    delay(animationSpeed);
    analogWrite(leds[3], 0);
    delay(animationSpeed);
    analogWrite(leds[4], 0);
    delay(animationSpeed);
    analogWrite(leds[5], 0);
    delay(animationSpeed);
    analogWrite(leds[6], 0);
    delay(animationSpeed);
    analogWrite(leds[7], 0);
}

void mainAnimateSequence2() {
 
    for(int i=0;i<=7;i++) {
        analogWrite(leds[i-1], 0);
        analogWrite(leds[i], ledBrightness);
        delay(animationSpeed);
    }
    for(int i=7;i>=0;i--) {
        analogWrite(leds[i+1], 0);
        analogWrite(leds[i], ledBrightness);
        delay(animationSpeed);
    } 
}

void mainAnimateSequence3() {
  
    analogWrite(leds[3], ledBrightness);
    analogWrite(leds[4], ledBrightness);
    delay(animationSpeed*2.5);
    analogWrite(leds[3], 0);
    analogWrite(leds[4], 0);
    analogWrite(leds[2], ledBrightness*0.6);
    analogWrite(leds[5], ledBrightness*0.6);
    delay(animationSpeed*1.6);
    analogWrite(leds[2], 0);
    analogWrite(leds[5], 0);
    analogWrite(leds[1], ledBrightness*0.3);
    analogWrite(leds[6], ledBrightness*0.3);
    delay(animationSpeed*1.9);
    analogWrite(leds[1], 0);
    analogWrite(leds[6], 0);
    analogWrite(leds[0], ledBrightness*0.1);
    analogWrite(leds[7], ledBrightness*0.1);
    delay(animationSpeed*2.2);
    analogWrite(leds[0], 0);
    analogWrite(leds[7], 0);
    delay(animationSpeed*2.5);
}

void mainAnimateSequence4() {

    analogWrite(leds[2], 0);
    analogWrite(leds[5], 0);
    analogWrite(leds[3], ledBrightness);
    analogWrite(leds[4], ledBrightness);
    delay(animationSpeed*2.5);
    analogWrite(leds[3], 0);
    analogWrite(leds[4], 0);
    analogWrite(leds[2], ledBrightness*0.6);
    analogWrite(leds[5], ledBrightness*0.6);
    delay(animationSpeed*1.6);
    analogWrite(leds[2], 0);
    analogWrite(leds[5], 0);
    analogWrite(leds[1], ledBrightness*0.3);
    analogWrite(leds[6], ledBrightness*0.3);
    delay(animationSpeed*1.9);
    analogWrite(leds[1], 0);
    analogWrite(leds[6], 0);
    analogWrite(leds[0], ledBrightness*0.1);
    analogWrite(leds[7], ledBrightness*0.1);
    delay(animationSpeed*2.2);
    analogWrite(leds[0], 0);
    analogWrite(leds[7], 0);
    analogWrite(leds[1], ledBrightness*0.3);
    analogWrite(leds[6], ledBrightness*0.3);
    delay(animationSpeed*1.9);
    analogWrite(leds[1], 0);
    analogWrite(leds[6], 0);
    analogWrite(leds[2], ledBrightness*0.6);
    analogWrite(leds[5], ledBrightness*0.6);
    delay(animationSpeed*1.6);
}

void mainAnimateSequence5() {
  
    checkButton();
    morseCode_S();
    checkButton();   
    morseCode_O();
    checkButton();
    morseCode_S();
    checkButton();
    delay(1000);    
}

void mainAnimateSequence6() {
  
    for(int i=0;i<8;i++) {
        analogWrite(leds[i-1], 0);
        analogWrite(leds[i], ledBrightness);
        delay(animationSpeed/4);
    }
    digitalWrite(leds[7], 0);
    delay(60);
    for(int i=0;i<8;i++) {
        analogWrite(leds[i-1], 0);
        analogWrite(leds[i], ledBrightness);
        delay(animationSpeed/4);
    }
    digitalWrite(leds[7], 0);
    delay(500);     
}

void mainAnimateSequence7() {
  
    for(int i=0;i<8;i++) {
        analogWrite(leds[i-1], 0);
        analogWrite(leds[i], ledBrightness);
        delay(animationSpeed);
    }
    digitalWrite(leds[7], 0);
}

void morseCode_S() {
  
    float delayVal;
    
    if(speed2_val == 0 && speed1_val == 0) {
        delayVal = 2.0;
    }
    else if(speed2_val == 0 && speed1_val == 1) {
        delayVal = 1.5;
    }
    else if(speed2_val == 1 && speed1_val == 0) {
        delayVal = 1.0;
    }
    else if(speed2_val == 1 && speed1_val == 1) {
        delayVal = 0.5;
    }
    
    for(int i=0;i<8;i++) {
        analogWrite(leds[i], ledBrightness);
    }
    delay(100*delayVal);
    for(int i=0;i<8;i++) {
        analogWrite(leds[i], 0);
    }
    delay(100*delayVal);
    for(int i=0;i<8;i++) {
        analogWrite(leds[i], ledBrightness);
    }
    delay(100*delayVal);
    for(int i=0;i<8;i++) {
        analogWrite(leds[i], 0);
    }
    delay(100*delayVal);
    for(int i=0;i<8;i++) {
        analogWrite(leds[i], ledBrightness);
    }
    delay(100*delayVal);
    for(int i=0;i<8;i++) {
        analogWrite(leds[i], 0);
    }
    delay(300*delayVal);
}

void morseCode_O() {
    float delayVal;
    
    if(speed2_val == 0 && speed1_val == 0) {
        delayVal = 2.0;
    }
    else if(speed2_val == 0 && speed1_val == 1) {
        delayVal = 1.5;
    }
    else if(speed2_val == 1 && speed1_val == 0) {
        delayVal = 1.0;
    }
    else if(speed2_val == 1 && speed1_val == 1) {
        delayVal = 0.5;
    }
       
    for(int i=0;i<8;i++) {
        analogWrite(leds[i], ledBrightness);
    }
    delay(300*delayVal);
    for(int i=0;i<8;i++) {
        analogWrite(leds[i], 0);
    }
    delay(100*delayVal);
    for(int i=0;i<8;i++) {
        analogWrite(leds[i], ledBrightness);
    }
    delay(300*delayVal);
    for(int i=0;i<8;i++) {
        analogWrite(leds[i], 0);
    }
    delay(100*delayVal);
    for(int i=0;i<8;i++) {
        analogWrite(leds[i], ledBrightness);
    }
    delay(300*delayVal);
    for(int i=0;i<8;i++) {
        analogWrite(leds[i], 0);
    }
    delay(300*delayVal);
}

void checkButton(){
    buttonState = digitalRead(button);
    if(buttonState == 0){
        if(flash_animationSequence == 0){
            flashAnimateSequence0();
        }
        else if(flash_animationSequence == 1){
            flashAnimateSequence1();
        } 
    }
}
