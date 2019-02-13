/*multiplexing and 8x8 led matrix with the Max7219 LED driver and the ESP8266 NODEMCU
 * 
  CREATED BY: GIANFRANCO MACCAGNAN
  SUBMISSION BY: GIANFRANCO MACCAGNAN, Jack Hadlow, Fernando Fernandez
  CREADITS: LEDControl library by Eberhard Fahle
  DESN37900 PROJECT 1
  SHERIDAN COLLEGE
*/

//including the LEDControl library for the MAX7219
#include "LedControl.h"

/*
 Now we need a LedControl to work with.

 The following pins are for the ESP8266 
 
 pin 8 is connected to the DataIn 
 pin 9 is connected to the CLK 
 pin 10 is connected to LOAD 
 */
#define loadPin 16
#define clockPin 5
#define dataPin 4

//initiate the LedControl , using (data,clock,load, [number of Max7219])
LedControl lc=LedControl(dataPin,clockPin,loadPin,1);

/* delay time used for animation, no dealy / small delay used to provide static images */
unsigned long delaytime=100;

void setup() {
  /*Max7219 is on power saver mode from the start, we have t omake a wake up call*/
  
  /*wake up ([device number],false) */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values*/
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
}

void writeArduinoOnMatrix() {
  
  /* A multidimentional array to contain bits for both the columns and rows */
  byte pics[4][8] = {{ B11111111,B10000001,B10000001,B10000001,B10000001,B10000001,B10000001,B11111111},
                    { B00000000,B01111110,B01000010,B01000010,B01000010,B01000010,B01111110,B00000000},
                    { B00000000,B00000000,B00111100,B00100100,B00100100,B00111100,B00000000,B00000000},
                    { B00000000,B00000000,B00000000,B00011000,B00011000,B00000000,B00000000,B00000000}};

//counter for the rows
int y;
//outer loop traversses through the rows in the matrix
  for(y = 0; y<4; y++){
    //inner loop traverses through the columns
    for(int i = 0; i < 8; i++){
      //set the rows ([device number],column,[byte value from array])
      lc.setRow(0,i,pics[y][i]); 
    }
    //using delay time for animations
    delay(delaytime);
    }
}

void loop() { 
  writeArduinoOnMatrix();
}
