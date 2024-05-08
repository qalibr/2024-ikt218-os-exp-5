/*
 * SOURCE https://web.archive.org/web/20190302142203/http://www.jamesmolloy.co.uk/tutorial_html/3.-The%20Screen.html
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include "libc/stdint.h"

void displayPut(char c);                // Put single char to screen
void displayClear();                    // Clear the screen 
void displayWrite(char *c);             // Write null-terminated ASCII string to monitor
static void displayMoveCursor();        // Function to move the cursor
static void displayScroll();            // Function to scroll the display as more input is received
void displayPut(char c);                // Function to place a single character to the screen.
void displayWriteHex(uint32_t num);     // Represent hex number
void displayWriteDec(uint32_t num);     // Represent decimal number

#endif
