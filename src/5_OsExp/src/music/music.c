/* Source: UiA, Per-Arne Lecture/Assignment Assets

    And,    
    UiA IKT218 2024V
    Group-5 
*/

#include "music/music.h"

#define MARGIN_X 3
#define MARGIN_Y 3

/* Static Graphics Placement */
const size_t INFO_X = MARGIN_X + 5;
const size_t INFO_Y = MARGIN_Y;

const size_t MUSIC_STOPPED_X = MARGIN_X;
const size_t MUSIC_STOPPED_Y = INFO_Y + 3;

const size_t CONTROLLS_INFO_X = MARGIN_X;
const size_t CONTROLLS_INFO_Y = INFO_Y + 4;  // Row: 5

const size_t MEMORY_INFO_X = MARGIN_X;
const size_t MEMORY_INFO_Y = CONTROLLS_INFO_Y + 4;  // Row: 9

const size_t ANIMATION_X = MARGIN_X;
const size_t ANIMATION_Y = INFO_Y;

const size_t LOGO_X = 80 - 1 - 28;
const size_t LOGO_Y = 21 - 3;
const size_t HEAT_ANIMATION_X = 39;
const size_t HEAT_ANIMATION_Y = LOGO_Y - 4;

/* Control Music Player */
bool playingMusic = true;
bool skipTune = false;

/* src: https://www.asciiart.eu/text-to-ascii-art */
// Animation frames for group logo
const char *animationFrames[3][7] = {
    {
        " (    `                     `    (  (`  ",
        " )\\ )    (      `   (            )\\))(  ",
        "(()/(  ` )(    (    ))\\  `  )   ((_)()\\ ",
        " /(_))_ (()\\   )\\  /((_) /(/(    (()((_)",
        "(_)) __| ((_) ((_)(_))( ((_)_\\    | __| ",
        "  | (_ || '_|/ _ \\| || || '_ \\)   |__ \\ ",
        "   \\___||_|  \\___/ \\_,_|| .__/    |___/ ",
        //"~~~~~~~~~~~~~~~~~~~~~~~~|_|~~~~~~~~~~~~~",
    },
    {
        " (           `                   (  (   ",
        " )\\ )  `  (         (       `    )\\))(  ",
        "(()/(   )(     (    ))\\     )   ((_)()\\ ",
        " /(_))_ (()\\   )\\  /((_) /(/(    (()((_)",
        "(_)) __| ((_) ((_)(_))( ((_)_\\    | __| ",
        "  | (_ || '_|/ _ \\| || || '_ \\)   |__ \\ ",
        "   \\___||_|  \\___/ \\_,_|| .__/    |___/ ",
       //"~~~~~~~~~~~~~~~~~~~~~~~~|_|~~~~~~~~~~~~~",
    },
    {
        " (  `       `                `   ( `(   ",
        " )\\ )     (       ` (        `   )\\))(  ",
        "(()/(  `)(     (    ))\\     )   ((_)()\\ ",
        " /(_))_ (()\\   )\\  /((_) /(/(    (()((_)",
        "(_)) __| ((_) ((_)(_))( ((_)_\\    | __| ",
        "  | (_ || '_|/ _ \\| || || '_ \\)   |__ \\ ",
        "   \\___||_|  \\___/ \\_,_|| .__/    |___/ ",
        //"~~~~~~~~~~~~~~~~~~~~~~~~|_|~~~~~~~~~~~~~",
    }
};

void MusicRestart() {
    playingMusic = false;
}
void MusicContinue() {
    playingMusic = true;
}
void MusicNext() {
    skipTune = true;
}
bool IsMusicPlaying() {
    return playingMusic;
}

void RenderMusicScreen(const Tune *tune, uint32_t currentNoteIndex) {
    // Hacky solution to the animation problems posed by the heat animation
    // Clear the left half of the screen only
    DisplayClearLeftHalf();

    const char *descriptionLength = "->Length: ";
    const char *descriptionFreq = "->Freq: ";

    const char *controllsRow3 = "[x] - Play\n";
    const char *controllsRow4 = "[c] - Reset\n";
    const char *controllsRow5 = "[v] - Next\n";

    DisplayMoveCursorToLocAndWrite(INFO_X, INFO_Y, tune->name);
    DisplayMoveCursorToLocAndWriteDec(INFO_X, INFO_Y + 1, tune->length, descriptionLength);
    DisplayMoveCursorToLocAndWriteDec(INFO_X, INFO_Y + 2, tune->notes[currentNoteIndex].frequency, descriptionFreq);

    DisplayMoveCursorToLocAndWrite(CONTROLLS_INFO_X, CONTROLLS_INFO_Y, controllsRow3);
    DisplayMoveCursorToLocAndWrite(CONTROLLS_INFO_X, CONTROLLS_INFO_Y + 1, controllsRow4);
    DisplayMoveCursorToLocAndWrite(CONTROLLS_INFO_X, CONTROLLS_INFO_Y + 2, controllsRow5);

    // Print memory layout
    PrintMemoryLayoutAtCursor(MEMORY_INFO_X, MEMORY_INFO_Y);

    /* Border */
    const char *border = "~";
    const char *special1 = "|";
    const char *special2 = "_";
    // Top/Bottom borders
    for (int i = 0; i < 80; i++) {
        DisplayMoveCursorToLocAndWrite(i, 0, border);

        // Putting lower part of 'P' from the logo into the border.
        if (i == 63) {
            DisplayMoveCursorToLocAndWrite(i++, 21, special1);
            DisplayMoveCursorToLocAndWrite(i, 0, border);

            DisplayMoveCursorToLocAndWrite(i++, 21, special2);
            DisplayMoveCursorToLocAndWrite(i, 0, border);

            DisplayMoveCursorToLocAndWrite(i, 21, special1);
            DisplayMoveCursorToLocAndWrite(i, 0, border);
        } else {
            DisplayMoveCursorToLocAndWrite(i, 21, border);
        }        
    }

    // Left/Right borders
    for (int i = 0; i < 21; i++) {
        DisplayMoveCursorToLocAndWrite(0, i, border);
        DisplayMoveCursorToLocAndWrite(79, i, border);
    }

    /* LOGO: W: 40, H: 8 */
    // const char *row1 = " (                               (  (   ";
    // const char *row2 = " )\ )    (           (           )\))(  ";
    // const char *row3 = "(()/(    )(    (    ))\  `  )   ((_)()\ ";
    // const char *row4 = " /(_))_ (()\   )\  /((_) /(/(    (()((_)";
    // const char *row5 = "(_)) __| ((_) ((_)(_))( ((_)_\    | __| ";
    // const char *row6 = "  | (_ || '_|/ _ \| || || '_ \)   |__ \ ";
    // const char *row7 = "   \___||_|  \___/ \_,_|| .__/    |___/ ";
    // const char *row8 = "                        |_|             ";

    // DisplayMoveCursorToLocAndWrite(logoX, logoY, row1);
    // DisplayMoveCursorToLocAndWrite(logoX, logoY + 1, row2);
    // DisplayMoveCursorToLocAndWrite(logoX, logoY + 2, row3);
    // DisplayMoveCursorToLocAndWrite(logoX, logoY + 3, row4);
    // DisplayMoveCursorToLocAndWrite(logoX, logoY + 4, row5);
    // DisplayMoveCursorToLocAndWrite(logoX, logoY + 5, row6);
    // DisplayMoveCursorToLocAndWrite(logoX, logoY + 6, row7);
    // DisplayMoveCursorToLocAndWrite(logoX, logoY + 7, row8);
}

void UpdateHeatAnimation(uint32_t step) {
    int frameIndex = step % 3;
    for (int i = 0; i < 7; i++) {
        DisplayMoveCursorToLocAndWrite(HEAT_ANIMATION_X, HEAT_ANIMATION_Y + i, animationFrames[frameIndex][i]);
    }
}

void UpdateBusyAnimation(uint32_t step) {
    const char *animationStates[4] = { "[   ]", "[.  ]", "[.. ]", "[...]"};
    DisplayMoveCursorToLocAndWriteAnimation(ANIMATION_X, ANIMATION_Y, animationStates[step % 4]);
}

void EnableSpeaker() {
    uint8_t speakerState = InPortByte(PC_SPEAKER_PORT);
    if (speakerState != (speakerState | 0x03)) {
        OutPortByte(PC_SPEAKER_PORT, speakerState | 0x03); // Or bits to enable speaker
    }
}

void DisableSpeaker() {
    uint8_t speakerState = InPortByte(PC_SPEAKER_PORT);
    OutPortByte(PC_SPEAKER_PORT, speakerState & ~0x03); // Invert bits to disable speaker
}

void PlaySound(uint32_t freq) {
    if (freq == 0) {
        return;
    }

    uint16_t divisor = (uint16_t)(PIT_BASE_FREQUENCY / freq);
    OutPortByte(PIT_CMD_PORT, 0b10110110); // Setting square wave mode on channel 2
    
    // Sending low and high bytes of the divisor
    OutPortByte(PIT_CHANNEL2_PORT, divisor & 0xFF);
    OutPortByte(PIT_CHANNEL2_PORT, divisor >> 8);

    EnableSpeaker();
}

void StopSound() {
    DisableSpeaker();
}

void PlayMusic(Tune *tune) {
    EnableSpeaker();
    DisplayClear(); // Get rid of strange artefacts that remain when using the 50% displayclear.
    for (uint32_t i = 0; i < tune->length && playingMusic; i++) {
        Note *note = &tune->notes[i];
        PlaySound(note->frequency);

        uint32_t animationIterator = 0;
        uint32_t updateInterval = 50;
        uint32_t numUpdates = note->duration / updateInterval;
        for (uint32_t step = 0; step < numUpdates && playingMusic; step++) {
            if (skipTune) {
                break;
            }

            RenderMusicScreen(tune, i);
            UpdateBusyAnimation(step);
            UpdateHeatAnimation(step);
            SleepInterrupt(updateInterval);
        }
        StopSound();
        if (skipTune) {
            skipTune = false;
            break;
        }
    }
    DisableSpeaker();

    if (!playingMusic) {
        const char *descr = ">> Music Stopped <<";
        DisplayMoveCursorToLocAndWrite(MUSIC_STOPPED_X, MUSIC_STOPPED_Y, descr);
    }
}

MusicPlayer* CreateMusicPlayer() {
    // Allocate memory for a new music player
    MusicPlayer* player = (MusicPlayer*)Malloc(sizeof(MusicPlayer));
    
    if (player) {
        printf("Player valid.\n");
        if (!playingMusic) { printf("Press 'x' to play music.\n"); }
        player->playTune = &PlayMusic; // Pointer to music player
    }

    return player;
}