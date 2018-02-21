//******************************************************************************************//
// Circuit Playground - 4 simple examples                                                   //
// Author: Julia Nilsson (julia.nilsson@saabgroup.com or julia.anna.nilsson.92@gmail.com)   //
//         Caroline Strandberg (caroline.strandberg@saabgroup.com)                          //
//******************************************************************************************//

#include <Adafruit_CircuitPlayground.h>

// put your setup code here, to run once:
void setup() {
  CircuitPlayground.begin();

  /*------------------
  Choose a program 1-4:"
  1: Play with colors
  2: Show temperature
  3: Roll dice  
  4: Play Piano
  --------------------*/

  //////////SELECT PROGRAM HERE://///////
  int programChoice = 1;

  //1: Play with colors
  if(programChoice == 1){
    playWithColors();
  }
  
  //2: Show temperature
  if(programChoice == 2){
    showTemperature();
  }
  
  //3: Roll dice
  if(programChoice == 3){
    rollDice();
  }

  //4: Piano
  if(programChoice == 4){
    playPiano();
  }

}

//%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%//%/%/%/%/%/
//%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/ PLAY WITH COLORS /%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/
bool leftButtonPressed;
bool rightButtonPressed;
bool slideSwitch;

void playWithColors() {
  while (true) {
    CircuitPlayground.clearPixels();
        
    leftButtonPressed = CircuitPlayground.leftButton();
    rightButtonPressed = CircuitPlayground.rightButton();
    slideSwitch = CircuitPlayground.slideSwitch();

    //Switch (+, true, left)
    if (slideSwitch) {
      if (leftButtonPressed) {
           CircuitPlayground.setPixelColor(0, 255,   0,   0);
           CircuitPlayground.setPixelColor(1, 255,   0,   0);
           CircuitPlayground.setPixelColor(2, 255,   0,   0);
           CircuitPlayground.setPixelColor(3, 255,   0,   0);
           CircuitPlayground.setPixelColor(4, 255,   0,   0);
      } 
      if (rightButtonPressed) {
            CircuitPlayground.setPixelColor(5, 0,   255,   0);
            CircuitPlayground.setPixelColor(6, 0,   255,   0);
            CircuitPlayground.setPixelColor(7, 0,   255,   0);
            CircuitPlayground.setPixelColor(8, 0,   255,   0);
            CircuitPlayground.setPixelColor(9, 0,   255,   0);
      } 
    } 
    //Switch (-, false, right)
    else {
       if (leftButtonPressed) {
           CircuitPlayground.setPixelColor(0, 0x0000FF);
           CircuitPlayground.setPixelColor(1, 0x0000FF);
           CircuitPlayground.setPixelColor(2, 0x0000FF);
           CircuitPlayground.setPixelColor(3, 0x0000FF);
           CircuitPlayground.setPixelColor(4, 0x0000FF);
       } 
       if (rightButtonPressed) {
            CircuitPlayground.setPixelColor(5, 0x808000);
            CircuitPlayground.setPixelColor(6, 0x808000);
            CircuitPlayground.setPixelColor(7, 0x808000);
            CircuitPlayground.setPixelColor(8, 0x808000);
            CircuitPlayground.setPixelColor(9, 0x808000);
       } 
    }
  }
}

//%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%//%/%/%/%/%/
//%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/ SHOW TEMPERATURE /%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/
const float temperatureAlertLimit = 30.0;
float temperatureC;

void showTemperature() {
  while (true) {
    temperatureC = CircuitPlayground.temperature();

    //Open "Tools" --> "Serial Monitor" to see current temperature
    Serial.print("Temperature: ");
    Serial.print(temperatureC);
    Serial.println(" C");

    //When temperature is above temperatureAlertLimit, the circuit playground will make a noise 
    if (temperatureC > temperatureAlertLimit) {
      CircuitPlayground.playTone(2000, 1000);
    }
    
    delay(100);
  }
}

//%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%//%/%/%/%/%/
//%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/ ROLL DICE /%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/

#define ROLL_THRESHOLD      30          // Total acceleration threshold for roll 
#define DICE_COLOR         0xEA6292    // Dice digits color

float X, Y, Z, totalAccel;

uint8_t dicePixels[6][6] = {  // Pixel pattern for dice roll
  { 2, 0, 0, 0, 0, 0 } ,      // Roll = 1
  { 4, 9, 0, 0, 0, 0 } ,      //        2
  { 0, 4, 7, 0, 0, 0 } ,      //        3
  { 1, 3, 6, 8, 0, 0 } ,      //        4
  { 0, 2, 4, 5, 9, 0 } ,      //        5
  { 0, 2, 4, 5, 7, 9 } ,      //        6
};

void rollDice() {
  CircuitPlayground.setAccelRange(LIS3DH_RANGE_8_G);
  
  while (true) {
    uint8_t rollNumber;
  
    X = 0;
    Y = 0;
    Z = 0;
    for (int i=0; i<10; i++) {
      X += CircuitPlayground.motionX();
      Y += CircuitPlayground.motionY();
      Z += CircuitPlayground.motionZ();
      delay(1);
    }
    X /= 10;
    Y /= 10;
    Z /= 10;
   
    totalAccel = sqrt(X*X + Y*Y + Z*Z);
  
    // Check for rolling
    if ((totalAccel > ROLL_THRESHOLD)) {
      rollNumber = random(1,7);
      CircuitPlayground.clearPixels();
      delay(200);
      for (int p=0; p<rollNumber; p++) {
        CircuitPlayground.setPixelColor(dicePixels[rollNumber-1][p], DICE_COLOR);
      }
      CircuitPlayground.playTone(400, 100);
    }
  }
}

//%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%//%/%/%/%/%/
//%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/ PLAY PIANO /%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/%/
#define CAP_THRESHOLD   50

uint8_t pads[] = {3, 2, 0, 1, 12, 6, 9, 10};
uint8_t numberOfPads = sizeof(pads)/sizeof(uint8_t);

void playPiano() {
  while(true){
    for (int i=0; i<numberOfPads; i++) {
    
      // Check if pad is touched.
      if (captureButton(pads[i])) {
        
        //Play sound of the touched pad
        playSound(pads[i]);
  
        delay(250);
      }
    }
  }
}

void playSound(uint8_t pad) {
    switch (pad) {
    case 3:
      CircuitPlayground.playTone(800, 100);
      break;
    case 2:
      CircuitPlayground.playTone(700, 100);
      break;
    case 0:
      CircuitPlayground.playTone(600, 100);
      break;
    case 1:
      CircuitPlayground.playTone(500, 100);
      break;
    case 12:
      CircuitPlayground.playTone(400, 100);
      break;
    case 6:
      CircuitPlayground.playTone(300, 100);
      break;
    case 9:
      CircuitPlayground.playTone(200, 100);
      break;
    case 10:
      CircuitPlayground.playTone(100, 100);
      break;
    default:
      CircuitPlayground.playTone(1000, 100);
   }
}

boolean captureButton(uint8_t pad) {
  // Check if capacitive touch exceeds threshold.
  if (CircuitPlayground.readCap(pad) > CAP_THRESHOLD) {
    return true;  
  } else {
    return false;
  }
}
