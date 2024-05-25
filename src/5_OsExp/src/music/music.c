/* Source: UiA, Per-Arne Lecture/Assignment Assets

    And,    
    UiA IKT218 2024V
    Group-5 
*/

#include "music/music.h"

/* Static Graphics Placement */
const size_t infoX = 6;
const size_t infoY = 1;

const size_t memoryInfoY = infoY + 4;

const size_t controllsInfoX = infoX;
const size_t controllsInfoY = memoryInfoY + 4;

const size_t animationX = 0;
const size_t animationY = 1;

/* Control Music Player */
bool playingMusic = true;
bool skipTune = false;
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
    DisplayClear();
    const char *descriptionLength = "->Length: ";
    const char *descriptionFreq = "->Freq: ";

    const char *controllsRow3 = "[x] - Play\n";
    const char *controllsRow4 = "[c] - Reset\n";
    const char *controllsRow5 = "[v] - Next\n";

    DisplayMoveCursorToLocAndWrite(infoX, infoY, tune->name);
    DisplayMoveCursorToLocAndWriteDec(infoX, infoY + 1, tune->length, descriptionLength);
    DisplayMoveCursorToLocAndWriteDec(infoX, infoY + 2, tune->notes[currentNoteIndex].frequency, descriptionFreq);

    DisplayMoveCursorToLocAndWrite(controllsInfoX, controllsInfoY, controllsRow3);
    DisplayMoveCursorToLocAndWrite(controllsInfoX, controllsInfoY + 1, controllsRow4);
    DisplayMoveCursorToLocAndWrite(controllsInfoX, controllsInfoY + 2, controllsRow5);

    // Print memory layout
    PrintAtCursorMemoryLayout(infoX, memoryInfoY);
}

void UpdateBusyAnimation(uint32_t step) {
    const char *animationStates[4] = { "[   ]", "[.  ]", "[.. ]", "[...]"};
    DisplayMoveCursorToLocAndWriteAnimation(animationX, animationY, animationStates[step % 4]);
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
    for (uint32_t i = 0; i < tune->length && playingMusic; i++) {
        Note *note = &tune->notes[i];
        PlaySound(note->frequency);

        uint32_t updateInterval = 50;
        uint32_t numUpdates = note->duration / updateInterval;
        for (uint32_t step = 0; step < numUpdates && playingMusic; step++) {
            if (skipTune) {
                break;
            }

            RenderMusicScreen(tune, i);
            UpdateBusyAnimation(step);
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
        printf("Music stopped.");
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