/* Source: 
- http://www.osdever.net/bkerndev/Docs/printing.htm
- https://web.archive.org/web/20190302142203/http://www.jamesmolloy.co.uk/tutorial_html/3.-The%20Screen.html
- UiA, Per-Arne Lecture/Assignment Assets */


#ifndef DISPLAY_H
#define DISPLAY_H

#include "libc/stdint.h"

// Put single char to screen
void DisplayPut(char c);                                        

// Clear the screen 
void DisplayClear();                                            

// Write null-terminated ASCII string to monitor
void DisplayWrite(const char *c);                                     

// Function to move the cursor
void DisplayMoveCursor();                                       

// Function to scroll the display as more input is received
void DisplayScroll();                                           

// Function to place a single character to the screen.
void DisplayPut(char c);                                        

// Function to set the color of the background and foreground
void DisplaySetTextColor(uint8_t fgColor, uint8_t bgColor);     
void InitDisplay();

// Represent decimal number
void DisplayWriteDec(uint32_t num);

// Represent hex number
void DisplayWriteHex(uint32_t num);


#endif
