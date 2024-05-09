/*
 * sources: 
 *      https://web.archive.org/web/20190302142203/http://www.jamesmolloy.co.uk/tutorial_html/3.-The%20Screen.html
 *      http://www.osdever.net/bkerndev/Docs/printing.htm
 */


#ifndef DISPLAY_H
#define DISPLAY_H

#include "libc/stdint.h"

void displayPut(char c);                                        // Put single char to screen
void displayClear();                                            // Clear the screen 
void displayWrite(char *c);                                     // Write null-terminated ASCII string to monitor
void displayMoveCursor();                                       // Function to move the cursor
void displayScroll();                                           // Function to scroll the display as more input is received
void displayPut(char c);                                        // Function to place a single character to the screen.
void displaySetTextColor(uint8_t fgColor, uint8_t bgColor);     // Function to set the color of the background and foreground
void displayInit();
// void displayWriteHex(uint32_t num);                          // Represent hex number
// void displayWriteDec(uint32_t num);                          // Represent decimal number

#endif
