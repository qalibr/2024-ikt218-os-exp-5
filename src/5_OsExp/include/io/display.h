/* Source: 
- http://www.osdever.net/bkerndev/Docs/printing.htm
- https://web.archive.org/web/20190302142203/http://www.jamesmolloy.co.uk/tutorial_html/3.-The%20Screen.html
- UiA, Per-Arne Lecture/Assignment Assets
    
    And,    
    UiA IKT218 2024V
    Group-5 
 */


#ifndef DISPLAY_H
#define DISPLAY_H

#include "libc/stdint.h"
#include "io/display.h"

void DisplayClear();                                                            // Clear the screen
void DisplayClearLeftHalf();
void DisplayPut(char c);                                                        // Put single char to screen
void DisplayWrite(const char *c);                                               // Write null-terminated ASCII string to monitor
void DisplayMoveCursor();                                                       // Function to move the cursor 
void DisplayMoveCursorToLocAndWrite(size_t x, size_t y, const char *content);
void DisplayMoveCursorToLocAndWriteAnimation(size_t x, size_t y, const char *state);     // Function to move the cursor to a specific location
void DisplayMoveCursorToLocAndWriteDec(size_t x, size_t y, uint32_t dec, const char *descr);
void DisplayMoveCursorToLocAndWriteHex(size_t x, size_t y, uint32_t hex, const char *descr);
void DisplayScroll();                                                           // Function to scroll the display as more input is received
void DisplaySetTextColor(uint8_t fgColor, uint8_t bgColor);                     // Function to set the color of the background and foreground
void InitDisplay();                                                             // Initialize display
void DisplayWriteDec(uint32_t num);                                             // Represent decimal number
void DisplayWriteHex(uint32_t num);                                             // Represent hex number
void DisplayHideCursor();

#endif


/*
void UpdateHeatAnimation(uint32_t step) {
    int frameIndex = step % 3;
    for (int i = 0; i < 6; i++) {
        DisplayMoveCursorToLocAndWrite(heatAnimationX, heatAnimationY + i, animationFrame[frameIndex][i]);
    }
}

const char *animationFrame[3][6] = {
    {
        " (                   ",  // Frame 1
        " )\\ )    (           ", 
        "(()/(    )(    (     ",
        " /(_))_ (()\\   )\\   ",
        "(_))     ((_) ((_))  ",
        "(__\\        _     __",
    },
    {
        "  (                  ",  // Frame 2 (Offset)
        ")\\ )    (           ",
        "(()/(    )(    (     ",
        "/(_))_ (()\\   )\\    ",
        "(_))     ((_) ((_))  ",
        "(__ )\\   /()_     __",
    },
    {
        "   (                 ",  // Frame 3 (Further Offset)
        "\\ )    (            ",
        "(()/(    )(    (     ",
        " (_))_ (()\\   )\\    ",
        " )     ((_) ((_))    ",
        "(__\\        _     __",
    }
};

*/