#include <LedControl.h>

/*
========================================================
PROJECT TITLE:
Arduino MAX7219 8x8 Dot Matrix – Arrow Direction Switch Animation

DESCRIPTION:
This project creates a smooth diagonal arrow animation 
on an 8x8 LED matrix using the MAX7219 module.

Animation behavior:
- Arrow flows to the right ( > )
- Instantly switches direction to left ( < )
- Smooth continuous loop

The MAX7219 handles multiplexing internally, making the 
implementation simple and stable.

COMPONENTS:
- Arduino Uno / Nano
- MAX7219 8x8 Dot Matrix Module
- Jumper wires

WIRING:
- VCC → 5V
- GND → GND
- DIN → D11
- CS  → D10
- CLK → D13
========================================================
*/


// DIN, CLK, CS, number of modules
LedControl lc = LedControl(11, 13, 10, 1);

// ==========================
// FRAMES (Arrow Right >)
// ==========================

int f1[8][8] = {
  {1,0,0,0,0,0,0,0},
  {0,1,0,0,0,0,0,0},
  {0,0,1,0,0,0,0,0},
  {0,0,0,1,0,0,0,0},
  {0,0,0,1,0,0,0,0},
  {0,0,1,0,0,0,0,0},
  {0,1,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0}
};

int f2[8][8] = {
  {1,1,0,0,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {0,0,1,1,0,0,0,0},
  {0,0,0,1,1,0,0,0},
  {0,0,0,1,1,0,0,0},
  {0,0,1,1,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {1,1,0,0,0,0,0,0}
};

int f3[8][8] = {
  {1,1,1,0,0,0,0,0},
  {0,1,1,1,0,0,0,0},
  {0,0,1,1,1,0,0,0},
  {0,0,0,1,1,1,0,0},
  {0,0,0,1,1,1,0,0},
  {0,0,1,1,1,0,0,0},
  {0,1,1,1,0,0,0,0},
  {1,1,1,0,0,0,0,0}
};

int f4[8][8] = {
  {1,1,1,1,0,0,0,0},
  {0,1,1,1,1,0,0,0},
  {0,0,1,1,1,1,0,0},
  {0,0,0,1,1,1,1,0},
  {0,0,0,1,1,1,1,0},
  {0,0,1,1,1,1,0,0},
  {0,1,1,1,1,0,0,0},
  {1,1,1,1,0,0,0,0}
};

int f5[8][8] = {
  {1,1,1,1,1,0,0,0},
  {0,1,1,1,1,1,0,0},
  {0,0,1,1,1,1,1,0},
  {0,0,0,1,1,1,1,1},
  {0,0,0,1,1,1,1,1},
  {0,0,1,1,1,1,1,0},
  {0,1,1,1,1,1,0,0},
  {1,1,1,1,1,0,0,0}
};

int f6[8][8] = {
  {0,1,1,1,1,0,0,0},
  {0,0,1,1,1,1,0,0},
  {0,0,0,1,1,1,1,0},
  {0,0,0,0,1,1,1,1},
  {0,0,0,0,1,1,1,1},
  {0,0,0,1,1,1,1,0},
  {0,0,1,1,1,1,0,0},
  {0,1,1,1,1,0,0,0}
};

int f7[8][8] = {
  {0,0,1,1,1,0,0,0},
  {0,0,0,1,1,1,0,0},
  {0,0,0,0,1,1,1,0},
  {0,0,0,0,0,1,1,1},
  {0,0,0,0,0,1,1,1},
  {0,0,0,0,1,1,1,0},
  {0,0,0,1,1,1,0,0},
  {0,0,1,1,1,0,0,0}
};

int f8[8][8] = {
  {0,0,0,1,1,0,0,0},
  {0,0,0,0,1,1,0,0},
  {0,0,0,0,0,1,1,0},
  {0,0,0,0,0,0,1,1},
  {0,0,0,0,0,0,1,1},
  {0,0,0,0,0,1,1,0},
  {0,0,0,0,1,1,0,0},
  {0,0,0,1,1,0,0,0}
};

int f9[8][8] = {
  {0,0,0,0,1,0,0,0},
  {0,0,0,0,0,1,0,0},
  {0,0,0,0,0,0,1,0},
  {0,0,0,0,0,0,0,1},
  {0,0,0,0,0,0,0,1},
  {0,0,0,0,0,0,1,0},
  {0,0,0,0,0,1,0,0},
  {0,0,0,0,1,0,0,0}
};

int f10[8][8] = {
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
};

// ==========================
int temp[8][8];

// ==========================
void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
}

// ==========================
void loop() {

  // RIGHT →
  for(int i=1;i<=10;i++){
    playFrame(i);
  }

  delay(300); // pause arah

  // LEFT ←
  for(int i=1;i<=10;i++){
    playFrameMirror(i);
  }

  delay(300); // pause arah
}

// ==========================
void playFrame(int index){
  int (*frame)[8];

  switch(index){
    case 1: frame=f1; break;
    case 2: frame=f2; break;
    case 3: frame=f3; break;
    case 4: frame=f4; break;
    case 5: frame=f5; break;
    case 6: frame=f6; break;
    case 7: frame=f7; break;
    case 8: frame=f8; break;
    case 9: frame=f9; break;
    case 10: frame=f10; break;
  }

  showFrame(frame, 90);
}

// ==========================
void playFrameMirror(int index){
  int (*frame)[8];

  switch(index){
    case 1: frame=f1; break;
    case 2: frame=f2; break;
    case 3: frame=f3; break;
    case 4: frame=f4; break;
    case 5: frame=f5; break;
    case 6: frame=f6; break;
    case 7: frame=f7; break;
    case 8: frame=f8; break;
    case 9: frame=f9; break;
    case 10: frame=f10; break;
  }

  mirrorFrame(frame, temp);
  showFrame(temp, 90);
}

// ==========================
void mirrorFrame(int src[8][8], int dst[8][8]) {
  for(int r=0; r<8; r++){
    for(int c=0; c<8; c++){
      dst[r][c] = src[r][7 - c];
    }
  }
}

// ==========================
void showFrame(int frame[8][8], int duration) {
  long start = millis();

  while (millis() - start < duration) {
    for (int r = 0; r < 8; r++) {
      for (int c = 0; c < 8; c++) {
        lc.setLed(0, r, c, frame[r][c]);
      }
    }
  }
}