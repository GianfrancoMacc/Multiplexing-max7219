//Max7219 control library
#include "LedControl.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 8 is connected to the DataIn 
 pin 9 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
#define loadPin 16
#define clockPin 5
#define dataPin 4

 
LedControl lc=LedControl(dataPin,clockPin,loadPin,2);

/* we always wait a bit between updates of the display */
unsigned long delaytime=100;

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */

   /*Wake up call, it turns off sleep mode, sets intensity and clears the display */
   /*NOTE ---- displays are numbered starting at 0 ----*/
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);

  /*Display #2*/
  lc.shutdown(1,false);
  lc.setIntensity(1,8);
  lc.clearDisplay(1);
  
}
void writeArduinoOnMatrix() {
  
  /* A multidimentional array to contain bits for both the columns and rows */
  byte dots[][8] = {{ B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B11111111},
                    { B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B11111111,B00000000},
                    { B00000000,B00000000,B00000000,B00000000,B00000000,B11111111,B00000000,B00000000},
                    { B00000000,B00000000,B00000000,B00000000,B11111111,B00000000,B00000000,B00000000},
                    { B00000000,B00000000,B00000000,B11111111,B00000000,B00000000,B00000000,B00000000},
                    { B00000000,B00000000,B11111111,B00000000,B00000000,B00000000,B00000000,B00000000},
                    { B00000000,B11111111,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
                    { B11111111,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000}};

int y;
  for(y = 0; y<8; y++){
    for(int i = 0; i < 8; i++){
      lc.setRow(0,i,dots[y][i]);  
      lc.setRow(1,i,dots[y][i]);
        }
        delay(delaytime);
      }
    
    
    
    
    }
  
/*This section of code can be used to reset the 8x8 matrix
  lc.setRow(0,0,0);
  lc.setRow(0,1,0);
  lc.setRow(0,2,0);
  lc.setRow(0,3,0);
  lc.setRow(0,4,0);
  delay(delaytime);
 }*/


void loop() { 
  writeArduinoOnMatrix();
}
