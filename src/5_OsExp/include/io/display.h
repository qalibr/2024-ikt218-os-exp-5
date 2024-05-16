/* Source: 
- http://www.osdever.net/bkerndev/Docs/printing.htm
- https://web.archive.org/web/20190302142203/http://www.jamesmolloy.co.uk/tutorial_html/3.-The%20Screen.html
- UiA, Per-Arne Lecture/Assignment Assets */


#ifndef DISPLAY_H
#define DISPLAY_H

#include "libc/stdint.h"

void DisplayClear();                                        // Clear the screen
void DisplayPut(char c);                                    // Put single char to screen                                   
void DisplayWrite(const char *c);                           // Write null-terminated ASCII string to monitor                           
void DisplayMoveCursor();                                   // Function to move the cursor                              
void DisplayScroll();                                       // Function to scroll the display as more input is received                                      
void DisplaySetTextColor(uint8_t fgColor, uint8_t bgColor); // Function to set the color of the background and foreground
void InitDisplay();                                         // Initialize display
void DisplayWriteDec(uint32_t num);                         // Represent decimal number
void DisplayWriteHex(uint32_t num);                         // Represent hex number


#endif
