/*
 * sources: 
 *      https://web.archive.org/web/20190302142203/http://www.jamesmolloy.co.uk/tutorial_html/3.-The%20Screen.html
 *      http://www.osdever.net/bkerndev/Docs/printing.htm
 */


#ifndef DISPLAY_H
#define DISPLAY_H

#include "libc/stdint.h"

// Put single char to screen
void displayPut(char c);                                        

// Clear the screen 
void displayClear();                                            

// Write null-terminated ASCII string to monitor
void displayWrite(char *c);                                     

// Function to move the cursor
void displayMoveCursor();                                       

// Function to scroll the display as more input is received
void displayScroll();                                           

// Function to place a single character to the screen.
void displayPut(char c);                                        

// Function to set the color of the background and foreground
void displaySetTextColor(uint8_t fgColor, uint8_t bgColor);     
void initDisplay();

// Represent decimal number
void displayWriteDec(uint32_t num);                             

// Represent hex number
// void displayWriteHex(uint32_t num);                          


#endif
