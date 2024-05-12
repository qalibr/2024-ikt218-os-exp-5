/*
 * sources: 
 *      https://web.archive.org/web/20190302142203/http://www.jamesmolloy.co.uk/tutorial_html/3.-The%20Screen.html
 *      http://www.osdever.net/bkerndev/Docs/printing.htm
 */

#include "display.h"
#include "common.h"

enum VGA_COLOR {
	VGA_BLACK = 0,
	VGA_BLUE = 1,
	VGA_GREEN = 2,
	VGA_CYAN = 3,
	VGA_RED = 4,
	VGA_MAGENTA = 5,
	VGA_BROWN = 6,
	VGA_LIGHT_GREY = 7,
	VGA_DARK_GREY = 8,
	VGA_LIGHT_BLUE = 9,
	VGA_LIGHT_GREEN = 10,
	VGA_LIGHT_CYAN = 11,
	VGA_LIGHT_RED = 12,
	VGA_LIGHT_MAGENTA = 13,
	VGA_LIGHT_BROWN = 14,
	VGA_WHITE = 15,
};

const size_t SCREEN_WIDTH = 80;
const size_t SCREEN_HEIGHT = 25;
const size_t LAST_LINE = SCREEN_HEIGHT - 1;
uint16_t *displayMemory = (uint16_t *)0xB8000;
uint16_t *displayBuffer;
size_t cursorY;
size_t cursorX;
uint8_t displayColor = (VGA_BLACK << 4) | (VGA_WHITE & 0x0F); // Default black background and white text(foreground)

void DisplayPut(char c) {
    uint8_t attributeByte = displayColor;

    uint16_t attribute = attributeByte << 8;
    uint16_t *location;

    // Handling various events and symbols, backspace, tab, return, newline, and any other character.
    if (c == 0x08 && cursorX)       { cursorX--; }
    if (c == 0x09)                  { cursorX = (cursorX + 8) & ~(8-1); }
    if (c == '\r')                  { cursorX = 0; }
    if (c == '\n')                  { cursorX = 0; cursorY++; }
    if (c >= ' ')                   { location = displayBuffer + (cursorY * SCREEN_WIDTH + cursorX); *location = c | attribute; cursorX++; }
    
    // See if we must insert a newline because we reached the end of the screen.
    if (cursorX >= SCREEN_WIDTH)    { cursorX = 0; cursorY++; }

    // cursorX and cursorY are global variables, scrolling and cursor movement will happen if it must.
    DisplayScroll();
    DisplayMoveCursor();
}

void DisplayClear() {
    uint8_t attributeByte = displayColor;
    uint16_t blank = 0x20 | (attributeByte << 8);

    size_t i;
    for (i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        displayBuffer[i] = blank; // Clear the screen by writing blank characters to it
    }

    // Also reset position of the cursor
    cursorX = 0;
    cursorY = 0;
    DisplayMoveCursor();
}

void DisplayWrite(const char *c) {
    size_t i = 0;
    
    while (c[i]) DisplayPut(c[i++]); // Write until null terminator ('\0') is encountered.
}  

void DisplayMoveCursor() {
    uint16_t cursorLocation = cursorY * SCREEN_WIDTH + cursorX;

    // Sending commands to the VGA board, to move the cursor
    OutPortByte(0x3D4, 14);                     // Set high cursor byte.
    OutPortByte(0x3D5, cursorLocation >> 8);    // Send that high byte.
    OutPortByte(0x3D4, 15);                     // Set low cursor byte.
    OutPortByte(0x3D5, cursorLocation);         // Send that low cursor byte.
}

void DisplayScroll() {
    // Setting background and foreground color;
    uint8_t attributeByte = displayColor;

    // Creating a character that is blank, this will usually fill most of the screen.
    uint16_t blank = 0x20 | (attributeByte << 8);

    // Checking if the cursor has exceeded the height of the display, if so we need to scroll...
    if (cursorY >= SCREEN_HEIGHT) {
        size_t i;

        // Move every line up one row.
        for (i = 0 * SCREEN_WIDTH; i < LAST_LINE * SCREEN_HEIGHT; i++) {
            displayBuffer[i] = displayBuffer[i + 80];
        }

        // Clear the final line of the display.
        for (i = LAST_LINE * SCREEN_WIDTH; i < SCREEN_HEIGHT * SCREEN_WIDTH; i++) {
            displayBuffer[i] = blank;
        }

        cursorY = LAST_LINE; // Set cursor to the last line.
    }
}

void DisplaySetTextColor(uint8_t fgColor, uint8_t bgColor) {
    displayColor = (bgColor << 4) | (fgColor & 0x0F);
}

void InitDisplay(void) {
    displayBuffer = displayMemory;
    DisplayClear();
}

// void displayWriteHex(uint32_t num);    

void DisplayWriteDec(uint32_t num) {
    if (num == 0) {
        DisplayPut('0');
        return;
    }

    char buffer[32];
    int i = 10;                                 // Start filling the buffer from the end
    buffer[i] = '\0';                           // Append null terminator to the end.

    // Filling the buffer beginning from the end
    while (num > 0) {
        i--;                                    // Move one position left
        buffer[i] = '0' + (num % 10);           // Calculate the last digit and add to buffer
        num /= 10;                              // Remove the last digit from the number
    }

    // Now, buffer[i] points to the first character of the string
    DisplayWrite(buffer + i);
}

void DisplayWriteHex(uint32_t hex) {
    if (hex == 0) {
        DisplayPut('0');
        return;
    }

    char buffer[32];
    int i = 31;                                 // Start from the end of the buffer
    buffer[i--] = '\0';                         // Null-terminate the buffer

    // Fill the buffer from the end
    while (hex > 0) {
        int digit = hex % 16;
        if (digit < 10) {
            buffer[i--] = '0' + digit;          // Numbers 0-9
        } else {
            buffer[i--] = 'a' + (digit - 10);   // Letters a-f
        }
        hex /= 16;
    }

    // Now, buffer[i + 1] points to the first character of the string
    DisplayWrite(&buffer[i + 1]);

}