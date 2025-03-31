// Copyright (c) 2025, Équipe de robotique FRC 9234, Les aigles d'or
// école secondaire Honoré-Mercier

#include <XInput.h>
#include <FastLED.h>

#define LEFT  //LEFT or RIGHT

#define NUM_LEDS 32
#define LED_DATA_PIN 0

#define PRESSED false
#define RELEASED true

#define DEBOUCE_TIME_MS 20  // measured bounce is sometimes slightly over 20ms

#define BUTTON_A_PIN 1  //bt1
#define BUTTON_B_PIN 2  //bt2
#define BUTTON_X_PIN 3  //bt3
#define BUTTON_Y_PIN 4  //bt4

#define BUTTON_LB_PIN 5     //bt5
#define BUTTON_RB_PIN 6     //bt6
#define BUTTON_BACK_PIN 7   //bt7
#define BUTTON_START_PIN 8  //bt8

#define DPAD_RIGHT_PIN 14  //bt15
#define DPAD_LEFT_PIN 15   //bt14
#define DPAD_UP_PIN 16     //bt12
#define DPAD_DOWN_PIN 17   //bt13

#define JOY1_X_PIN A3  //axis 1
#define JOY1_Y_PIN A2  //axis 2

//normal
#define JOY2_X_PIN A1  //axis 3
#define JOY2_Y_PIN A0  //axis 4

//twist
#define TWIST_1_PIN A10  //axis 4
#define TWIST_2_PIN A11  //axis 4



#define TRIGGER_LEFT_PIN A5
#define TRIGGER_RIGHT_PIN A4
#define DZWIDTH 0.05  //.01



boolean buttonACurrentState = RELEASED;
boolean buttonALastState = RELEASED;
uint32_t buttonALastChange = 0;

boolean buttonBCurrentState = RELEASED;
boolean buttonBLastState = RELEASED;
uint32_t buttonBLastChange = 0;

boolean buttonXCurrentState = RELEASED;
boolean buttonXLastState = RELEASED;
uint32_t buttonXLastChange = 0;

boolean buttonYCurrentState = RELEASED;
boolean buttonYLastState = RELEASED;
uint32_t buttonYLastChange = 0;

boolean buttonLBCurrentState = RELEASED;
boolean buttonLBLastState = RELEASED;
uint32_t buttonLBLastChange = 0;

boolean buttonRBCurrentState = RELEASED;
boolean buttonRBLastState = RELEASED;
uint32_t buttonRBLastChange = 0;

boolean buttonBKCurrentState = RELEASED;
boolean buttonBKLastState = RELEASED;
uint32_t buttonBKLastChange = 0;

boolean buttonSTCurrentState = RELEASED;
boolean buttonSTLastState = RELEASED;
uint32_t buttonSTLastChange = 0;

boolean buttonUPCurrentState = RELEASED;
boolean buttonUPLastState = RELEASED;
uint32_t buttonUPLastChange = 0;

boolean buttonDOWNCurrentState = RELEASED;
boolean buttonDOWNLastState = RELEASED;
uint32_t buttonDOWNLastChange = 0;

boolean buttonLEFTCurrentState = RELEASED;
boolean buttonLEFTLastState = RELEASED;
uint32_t buttonLEFTLastChange = 0;

boolean buttonRIGHTCurrentState = RELEASED;
boolean buttonRIGHTLastState = RELEASED;
uint32_t buttonRIGHTLastChange = 0;

boolean dpadUp = false;
boolean dpadDown = false;
boolean dpadLeft = false;
boolean dpadRight = false;



uint32_t joyLeftXProcessed = 0;
uint32_t joyLeftYProcessed = 0;
uint32_t joyRightXProcessed = 0;
uint32_t joyRightYProcessed = 0;
uint32_t triggerLeftProcessed = 0;
uint32_t triggerRightProcessed = 0;

uint32_t triggerLeftProcessedLastValue = 0;
uint32_t triggerRightProcessedLastValue = 0;
uint32_t triggerLeftRawLastValue = 0;
uint32_t triggerRightRawLastValue = 0;

uint32_t joyLeftXRaw = 0;
uint32_t joyLeftYRaw = 0;
uint32_t joyRightXRaw = 0;
uint32_t joyRightYRaw = 0;
uint32_t triggerLeftRaw = 0;
uint32_t triggerRightRaw = 0;

uint32_t iMin = 0;
uint32_t iMax = 1023;

uint32_t iMidLeftX = 0;
uint32_t iMidLeftY = 0;
uint32_t iMidRightX = 0;
uint32_t iMidRightY = 0;
uint32_t iMidLeftTrigger = 0;
uint32_t iMidRightTrigger = 0;
uint32_t iDZLowLeftX = 0;
uint32_t iDZHighLeftX = 0;
uint32_t iDZLowLeftY = 0;
uint32_t iDZHighLeftY = 0;
uint32_t iDZLowRightX = 0;
uint32_t iDZHighRightX = 0;
uint32_t iDZLowRightY = 0;
uint32_t iDZHighRightY = 0;
uint32_t iDZLowLeftTrigger = 0;
uint32_t iDZHighLeftTrigger = 0;
uint32_t iDZLowRightTrigger = 0;
uint32_t iDZHighRightTrigger = 0;


uint32_t oMin = 0;
uint32_t oMax = 1023;
uint32_t oMid = ((oMin + oMax) / 2);

uint32_t decimator = 0xFFFFFFFC;  //0xFFFFFFF8 0xFFFFFFFC 0xFFFFFFFE


// Define the array of leds
CRGB leds[NUM_LEDS];
uint8_t pos = 0;
uint32_t now = millis();

void setup() {
  XInput.begin();
  //Serial1.begin(9600); // Serial.begin() ou Serial0.begin() est le UART sur USB, et Serial1.begin() est le UART utilisant les pin RX/TX.

  pinMode(BUTTON_A_PIN, INPUT_PULLUP);
  buttonALastState = digitalRead(BUTTON_A_PIN);
  buttonALastChange = millis();

  pinMode(BUTTON_B_PIN, INPUT_PULLUP);
  buttonBLastState = digitalRead(BUTTON_B_PIN);
  buttonBLastChange = millis();

  pinMode(BUTTON_X_PIN, INPUT_PULLUP);
  buttonXLastState = digitalRead(BUTTON_X_PIN);
  buttonXLastChange = millis();

  pinMode(BUTTON_Y_PIN, INPUT_PULLUP);
  buttonYLastState = digitalRead(BUTTON_Y_PIN);
  buttonYLastChange = millis();

  pinMode(BUTTON_LB_PIN, INPUT_PULLUP);
  buttonLBLastState = digitalRead(BUTTON_LB_PIN);
  buttonLBLastChange = millis();

  pinMode(BUTTON_RB_PIN, INPUT_PULLUP);
  buttonRBLastState = digitalRead(BUTTON_RB_PIN);
  buttonRBLastChange = millis();

  pinMode(BUTTON_BACK_PIN, INPUT_PULLUP);
  buttonBKLastState = digitalRead(BUTTON_BACK_PIN);
  buttonBKLastChange = millis();

  pinMode(BUTTON_START_PIN, INPUT_PULLUP);
  buttonSTLastState = digitalRead(BUTTON_START_PIN);
  buttonSTLastChange = millis();

  pinMode(DPAD_UP_PIN, INPUT_PULLUP);
  buttonUPLastState = digitalRead(DPAD_UP_PIN);
  buttonUPLastChange = millis();

  pinMode(DPAD_DOWN_PIN, INPUT_PULLUP);
  buttonDOWNLastState = digitalRead(DPAD_DOWN_PIN);
  buttonDOWNLastState = 0;
  buttonDOWNLastChange = millis();

  pinMode(DPAD_LEFT_PIN, INPUT_PULLUP);
  buttonLEFTLastState = digitalRead(DPAD_LEFT_PIN);
  buttonLEFTLastChange = millis();

  pinMode(DPAD_RIGHT_PIN, INPUT_PULLUP);
  buttonRIGHTLastState = digitalRead(DPAD_RIGHT_PIN);
  buttonRIGHTLastChange = millis();

  XInput.setJoystickRange(0, 1023);  // Set joystick range to the ADC
  XInput.setAutoSend(false);         // Wait for all controls before sending
  XInput.setTriggerRange(0, 1023);




  iMidLeftX = analogRead(JOY1_X_PIN);
  iMidLeftY = analogRead(JOY1_Y_PIN);
  iMidRightX = analogRead(TWIST_1_PIN);
  iMidRightY = analogRead(TWIST_2_PIN);
  iMidLeftTrigger = 511;
  iMidRightTrigger = 511;
  iDZLowLeftX = iMidLeftX * (1 - DZWIDTH);
  iDZHighLeftX = iMidLeftX * (1 + DZWIDTH);
  iDZLowLeftY = iMidLeftY * (1 - DZWIDTH);
  iDZHighLeftY = iMidLeftY * (1 + DZWIDTH);
  iDZLowRightX = iMidRightX * (1 - DZWIDTH);
  iDZHighRightX = iMidRightX * (1 + DZWIDTH);
  iDZLowRightY = iMidRightY * (1 - DZWIDTH);
  iDZHighRightY = iMidRightY * (1 + DZWIDTH);
  iDZLowLeftTrigger = iMidLeftTrigger * (1 - DZWIDTH);
  iDZHighLeftTrigger = iMidLeftTrigger * (1 + DZWIDTH);
  iDZLowRightTrigger = iMidRightTrigger * (1 - DZWIDTH);
  iDZHighRightTrigger = iMidRightTrigger * (1 + DZWIDTH);

  FastLED.addLeds<WS2811, LED_DATA_PIN, RGB>(leds, NUM_LEDS).setCorrection(CRGB(255, 160, 130));
  FastLED.setBrightness(255);
}

void loop() {
  //basic rainbow effect
  pos++;
  leds[0] = leds[1] = CHSV(pos, 255, 255);
  leds[2] = leds[3] = CHSV(pos + 63, 255, 255);
  leds[4] = leds[5] = CHSV(pos + 127, 255, 255);
  leds[6] = leds[7] = CHSV(pos + 191, 255, 255);
  leds[8] = leds[9] = CHSV(pos, 255, 255);
  leds[10] = leds[11] = CHSV(pos + 63, 255, 255);
  leds[12] = leds[13] = CHSV(pos + 127, 255, 255);
  leds[14] = leds[15] = CHSV(pos + 191, 255, 255);
  leds[16] = leds[17] = CHSV(pos, 255, 255);
  leds[18] = leds[19] = CHSV(pos + 63, 255, 255);
  leds[20] = leds[21] = CHSV(pos + 127, 255, 255);
  leds[22] = leds[23] = CHSV(pos + 191, 255, 255);
  leds[24] = leds[25] = CHSV(pos, 255, 255);
  leds[26] = leds[27] = CHSV(pos + 63, 255, 255);
  leds[28] = leds[29] = CHSV(pos + 127, 255, 255);
  leds[30] = leds[31] = CHSV(pos + 191, 255, 255);
  FastLED.show();


  now = millis();
  if (now - buttonALastChange >= DEBOUCE_TIME_MS) {
    buttonACurrentState = digitalRead(BUTTON_A_PIN);
    if ((buttonACurrentState == PRESSED) && (buttonALastState == RELEASED)) {
      XInput.press(BUTTON_A);
      //change color on a registered keystroke
      //leds[0] = CRGB(255, 0, 0);
      //FastLED.show();
      buttonALastState = PRESSED;
      buttonALastChange = now;
    } else if (buttonACurrentState == RELEASED && (buttonALastState == PRESSED)) {
      XInput.release(BUTTON_A);
      //change color on a registered keystroke
      //leds[0] = CRGB(255, 255, 255);
      //FastLED.show();
      buttonALastState = RELEASED;
      buttonALastChange = now;
    }
  }

  if (now - buttonBLastChange >= DEBOUCE_TIME_MS) {
    buttonBCurrentState = digitalRead(BUTTON_B_PIN);
    if ((buttonBCurrentState == PRESSED) && (buttonBLastState == RELEASED)) {
      XInput.press(BUTTON_B);
      buttonBLastState = PRESSED;
      buttonBLastChange = now;
    } else if (buttonBCurrentState == RELEASED && (buttonBLastState == PRESSED)) {
      XInput.release(BUTTON_B);
      buttonBLastState = RELEASED;
      buttonBLastChange = now;
    }
  }

  if (now - buttonXLastChange >= DEBOUCE_TIME_MS) {
    buttonXCurrentState = digitalRead(BUTTON_X_PIN);
    if ((buttonXCurrentState == PRESSED) && (buttonXLastState == RELEASED)) {
      XInput.press(BUTTON_X);
      buttonXLastState = PRESSED;
      buttonXLastChange = now;
    } else if (buttonXCurrentState == RELEASED && (buttonXLastState == PRESSED)) {
      XInput.release(BUTTON_X);
      buttonXLastState = RELEASED;
      buttonXLastChange = now;
    }
  }

  if (now - buttonYLastChange >= DEBOUCE_TIME_MS) {
    buttonYCurrentState = digitalRead(BUTTON_Y_PIN);
    if ((buttonYCurrentState == PRESSED) && (buttonYLastState == RELEASED)) {
      XInput.press(BUTTON_Y);
      buttonYLastState = PRESSED;
      buttonYLastChange = now;
    } else if (buttonYCurrentState == RELEASED && (buttonYLastState == PRESSED)) {
      XInput.release(BUTTON_Y);
      buttonYLastState = RELEASED;
      buttonYLastChange = now;
    }
  }

  if (now - buttonLBLastChange >= DEBOUCE_TIME_MS) {
    buttonLBCurrentState = digitalRead(BUTTON_LB_PIN);
    if ((buttonLBCurrentState == PRESSED) && (buttonLBLastState == RELEASED)) {
      XInput.press(BUTTON_LB);
      buttonLBLastState = PRESSED;
      buttonLBLastChange = now;
    } else if (buttonLBCurrentState == RELEASED && (buttonLBLastState == PRESSED)) {
      XInput.release(BUTTON_LB);
      buttonLBLastState = RELEASED;
      buttonLBLastChange = now;
    }
  }

  if (now - buttonRBLastChange >= DEBOUCE_TIME_MS) {
    buttonRBCurrentState = digitalRead(BUTTON_RB_PIN);
    if ((buttonRBCurrentState == PRESSED) && (buttonRBLastState == RELEASED)) {
      XInput.press(BUTTON_RB);
      buttonRBLastState = PRESSED;
      buttonRBLastChange = now;
    } else if (buttonRBCurrentState == RELEASED && (buttonRBLastState == PRESSED)) {
      XInput.release(BUTTON_RB);
      buttonRBLastState = RELEASED;
      buttonRBLastChange = now;
    }
  }

  if (now - buttonBKLastChange >= DEBOUCE_TIME_MS) {
    buttonBKCurrentState = digitalRead(BUTTON_BACK_PIN);
    if ((buttonBKCurrentState == PRESSED) && (buttonBKLastState == RELEASED)) {
      XInput.press(BUTTON_BACK);
      buttonBKLastState = PRESSED;
      buttonBKLastChange = now;
    } else if (buttonBKCurrentState == RELEASED && (buttonBKLastState == PRESSED)) {
      XInput.release(BUTTON_BACK);
      buttonBKLastState = RELEASED;
      buttonBKLastChange = now;
    }
  }

  if (now - buttonSTLastChange >= DEBOUCE_TIME_MS) {
    buttonSTCurrentState = digitalRead(BUTTON_START_PIN);
    if ((buttonSTCurrentState == PRESSED) && (buttonSTLastState == RELEASED)) {
      XInput.press(BUTTON_START);
      buttonSTLastState = PRESSED;
      buttonSTLastChange = now;
    } else if (buttonSTCurrentState == RELEASED && (buttonSTLastState == PRESSED)) {
      XInput.release(BUTTON_START);
      buttonSTLastState = RELEASED;
      buttonSTLastChange = now;
    }
  }



  if (now - buttonUPLastChange >= DEBOUCE_TIME_MS) {
    buttonUPCurrentState = digitalRead(DPAD_UP_PIN);
    if ((buttonUPCurrentState == PRESSED) && (buttonUPLastState == RELEASED)) {
      dpadUp = true;
      buttonUPLastState = PRESSED;
      buttonUPLastChange = now;
    } else if (buttonUPCurrentState == RELEASED && (buttonUPLastState == PRESSED)) {
      dpadUp = false;
      buttonUPLastState = RELEASED;
      buttonUPLastChange = now;
    }
  }
  if (now - buttonDOWNLastChange >= DEBOUCE_TIME_MS) {
    buttonDOWNCurrentState = digitalRead(DPAD_DOWN_PIN);
    if ((buttonDOWNCurrentState == PRESSED) && (buttonDOWNLastState == RELEASED)) {
      dpadDown = true;
      buttonDOWNLastState = PRESSED;
      buttonDOWNLastChange = now;
    } else if (buttonDOWNCurrentState == RELEASED && (buttonDOWNLastState == PRESSED)) {
      dpadDown = false;
      buttonDOWNLastState = RELEASED;
      buttonDOWNLastChange = now;
    }
  }
  if (now - buttonLEFTLastChange >= DEBOUCE_TIME_MS) {
    buttonLEFTCurrentState = digitalRead(DPAD_LEFT_PIN);
    if ((buttonLEFTCurrentState == PRESSED) && (buttonLEFTLastState == RELEASED)) {
      dpadLeft = true;
      buttonLEFTLastState = PRESSED;
      buttonLEFTLastChange = now;
    } else if (buttonLEFTCurrentState == RELEASED && (buttonLEFTLastState == PRESSED)) {
      dpadLeft = false;
      buttonLEFTLastState = RELEASED;
      buttonLEFTLastChange = now;
    }
  }
  if (now - buttonRIGHTLastChange >= DEBOUCE_TIME_MS) {
    buttonRIGHTCurrentState = digitalRead(DPAD_RIGHT_PIN);
    if ((buttonRIGHTCurrentState == PRESSED) && (buttonRIGHTLastState == RELEASED)) {
      dpadRight = true;
      buttonRIGHTLastState = PRESSED;
      buttonRIGHTLastChange = now;
    } else if (buttonRIGHTCurrentState == RELEASED && (buttonRIGHTLastState == PRESSED)) {
      dpadRight = false;
      buttonRIGHTLastState = RELEASED;
      buttonRIGHTLastChange = now;
    }
  }





  joyLeftXRaw = analogRead(JOY1_X_PIN);
  joyLeftYRaw = analogRead(JOY1_Y_PIN);
  joyRightXRaw = analogRead(TWIST_1_PIN);
  joyRightYRaw = analogRead(TWIST_2_PIN);
  triggerLeftRaw = analogRead(TRIGGER_LEFT_PIN);
  triggerRightRaw = analogRead(TRIGGER_RIGHT_PIN);



  if (joyLeftXRaw <= iMidLeftX)
    joyLeftXProcessed = constrain(map(joyLeftXRaw, iMin, iDZLowLeftX, oMin, oMid), oMin, oMid);
  else
    joyLeftXProcessed = constrain(map(joyLeftXRaw, iDZHighLeftX, iMax, oMid, oMax), oMid, oMax);

  if (joyLeftYRaw <= iMidLeftY)
    joyLeftYProcessed = constrain(map(joyLeftYRaw, iMin, iDZLowLeftY, oMin, oMid), oMin, oMid);
  else
    joyLeftYProcessed = constrain(map(joyLeftYRaw, iDZHighLeftY, iMax, oMid, oMax), oMid, oMax);

  if (joyRightXRaw <= iMidRightX)
    joyRightXProcessed = constrain(map(joyRightXRaw, iMin, iDZLowRightX, oMin, oMid), oMin, oMid);
  else
    joyRightXProcessed = constrain(map(joyRightXRaw, iDZHighRightX, iMax, oMid, oMax), oMid, oMax);

  if (joyRightYRaw <= iMidRightY)
    joyRightYProcessed = constrain(map(joyRightYRaw, iMin, iDZLowRightY, oMin, oMid), oMin, oMid);
  else
    joyRightYProcessed = constrain(map(joyRightYRaw, iDZHighRightY, iMax, oMid, oMax), oMid, oMax);

  if (triggerLeftRaw <= iMidLeftTrigger)
    triggerLeftProcessed = constrain(map(triggerLeftRaw & decimator, iMin, iDZLowLeftTrigger, oMin, oMid), oMin, oMid);
  else
    triggerLeftProcessed = constrain(map(triggerLeftRaw & decimator, iDZHighLeftTrigger, iMax, oMid, oMax), oMid, oMax);

  if (triggerRightRaw <= iMidRightTrigger)
    triggerRightProcessed = constrain(map(triggerRightRaw & decimator, iMin, iDZLowRightTrigger, oMin, oMid), oMin, oMid);
  else
    triggerRightProcessed = constrain(map(triggerRightRaw & decimator, iDZHighRightTrigger, iMax, oMid, oMax), oMid, oMax);

#ifdef LEFT
  XInput.setJoystickX(JOY_LEFT, joyLeftXProcessed);
  XInput.setJoystickY(JOY_LEFT, joyLeftYProcessed);
  XInput.setJoystickX(JOY_RIGHT, joyRightXProcessed);
  XInput.setJoystickY(JOY_RIGHT, oMid);  //not currently connected
  XInput.setTrigger(TRIGGER_LEFT, 0);  //not currently connected
  XInput.setTrigger(TRIGGER_RIGHT, 0);  //not currently connected
  XInput.setDpad(dpadUp, dpadDown, dpadLeft, dpadRight);
#endif

#ifdef RIGHT
  XInput.setJoystickX(JOY_LEFT, joyLeftXProcessed);
  XInput.setJoystickY(JOY_LEFT, joyLeftYProcessed);
  XInput.setJoystickX(JOY_RIGHT, joyRightXProcessed);
  XInput.setJoystickY(JOY_RIGHT, oMid);  // not currently connected, if connected should be joyRightYProcessed
  XInput.setTrigger(TRIGGER_LEFT, triggerLeftProcessed);
  XInput.setTrigger(TRIGGER_RIGHT, triggerRightProcessed);
  XInput.setDpad(0, 0, 0, 0); //not currently connected
#endif

  XInput.send();



  // for debug only


  /*

  if (triggerLeftProcessed != triggerLeftProcessedLastValue){
    triggerLeftProcessedLastValue = triggerLeftProcessed;
    Serial1.print(" - Trigger_Left_Processed: ");
    Serial1.println(triggerLeftProcessed);
  }
  if (triggerRightProcessed != triggerRightProcessedLastValue){
    triggerRightProcessedLastValue = triggerRightProcessed;
    Serial1.print(" - Trigger_Right_Processed: ");
    Serial1.println(triggerRightProcessed);
  }


  if (triggerLeftRaw != triggerLeftRawLastValue){
    triggerLeftRawLastValue = triggerLeftRaw;
    Serial1.print(" - Trigger_Left_Raw: ");
    Serial1.println(triggerLeftRaw);
  }
  if (triggerRightRaw != triggerRightRawLastValue){
    triggerRightRawLastValue = triggerRightRaw;
    Serial1.print(" - Trigger_Right_Raw: ");
    Serial1.println(triggerRightRaw);
  }

    Serial1.print("X_Left_RAW: ");
    Serial1.print(joyLeftXRaw);
    Serial1.print(" - Y_Left_RAW: ");
    Serial1.print(joyLeftYRaw);

    Serial1.print(" --- X_Left_Processed: ");
    Serial1.print(joyLeftXProcessed);
    Serial1.print(" - Y_Left_Processed: ");
    Serial1.println(joyLeftYProcessed);

*/




}
