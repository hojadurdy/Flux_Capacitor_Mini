#include <EEPROM.h>

//------ PIN DEFINITIONS ------//

#define led1    16
#define led2    0
#define led3    1
#define led4    7
#define led5    8
#define led6    9
#define led7    10
#define led8    11
#define button  14

//-- BUTTON HOLD TIME PRESETS --//

//Counter Value
float pressLength_ms = 0;

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
    pinMode(led1, OUTPUT); 
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);
    pinMode(led5, OUTPUT);
    pinMode(led6, OUTPUT);
    pinMode(led7, OUTPUT);
    pinMode(led8, OUTPUT); 
    pinMode(button, INPUT);   

    EEPROM.write(1, 1);
    EEPROM.write(11, 0);
    EEPROM.write(12, 0);
    EEPROM.write(13, 0);
    EEPROM.write(14, 0);
    EEPROM.write(15, 0);
    EEPROM.write(16, 1);
    EEPROM.write(17, 0);
    EEPROM.write(18, 0);
}

void loop() {
    startUpSequence();
    
    analogWrite(led1, ledBrightness);
    delay(animationSpeed*2);
    checkButton();
    analogWrite(led2, ledBrightness);
    delay(animationSpeed*2);
    checkButton();
    analogWrite(led3, ledBrightness);
    delay(animationSpeed*2);
    checkButton();
    analogWrite(led4, ledBrightness);
    delay(animationSpeed*2);
    checkButton();
    analogWrite(led5, ledBrightness);
    delay(animationSpeed*2);
    checkButton();
    analogWrite(led6, ledBrightness);
    delay(animationSpeed*2);
    checkButton();
    analogWrite(led7, ledBrightness);
    delay(animationSpeed*2);
    checkButton();
    analogWrite(led8, ledBrightness);
    delay(animationSpeed*2);
    checkButton();
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
        analogWrite(led1, 200);
        delay(150);
        analogWrite(led2, 200);
        delay(150);
        analogWrite(led3, 200);
        delay(150);
        analogWrite(led4, 200);
        delay(150);
        analogWrite(led5, 200);
        delay(150);
        analogWrite(led6, 200);
        delay(150);
        analogWrite(led7, 200);
        delay(150);
        analogWrite(led8, 200);
        delay(150);

        startup = 0;
    }
    else {
      //Do Nothing
    }

    //Determine Main Animation Sequence According to Values from 3 EEPROM Addresses
    if(main_animation4_val == 0 && main_animation2_val == 0 && main_animation1_val == 0) {
        main_animationSequence = 1;
    }
    else if(main_animation4_val == 0 && main_animation2_val == 0 && main_animation1_val == 1) {
        main_animationSequence = 2;
    }
    else if(main_animation4_val == 0 && main_animation2_val == 1 && main_animation1_val == 0) {
        main_animationSequence = 3;
    }
    else if(main_animation4_val == 0 && main_animation2_val == 1 && main_animation1_val == 1) {
        main_animationSequence = 4;
    }
    else if(main_animation4_val == 1 && main_animation2_val == 0 && main_animation1_val == 0) {
        main_animationSequence = 5;
    }
    else if(main_animation4_val == 1 && main_animation2_val == 0 && main_animation1_val == 1) {
        main_animationSequence = 6;
    }
    else if(main_animation4_val == 1 && main_animation2_val == 1 && main_animation1_val == 0) {
        main_animationSequence = 7;
    }
    else if(main_animation4_val == 1 && main_animation2_val == 1 && main_animation1_val == 1) {
        main_animationSequence = 8;
    }

    //Determine Flash Animation Sequence According to Value from EEPROM Address
    if(flash_animation1_val == 0) {
        flash_animationSequence = 1;
    }
    else if(flash_animation1_val == 1) {
        flash_animationSequence = 2;
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

void checkButton(){
    while (digitalRead(button) == LOW ){ 
        analogWrite(led1, ledBrightness);
        analogWrite(led2, 0);
        analogWrite(led3, ledBrightness);
        analogWrite(led4, 0);
        analogWrite(led5, ledBrightness);
        analogWrite(led6, 0);
        analogWrite(led7, ledBrightness);
        analogWrite(led8, 0);
    }
}
