/* Source: UiA, Per-Arne Lecture/Assignment Assets

    And,    
    UiA IKT218 2024V
    Group-5 
*/

#include "music/music.h"

const size_t infoX = 5;
const size_t infoY = 1;
const size_t animationX = 0;
const size_t animationY = 1;

void RenderMusicScreen(const Tune *tune, uint32_t currentNoteIndex) {
    DisplayClear();
    char info[75]; // Screen width - 5
    DisplayMoveCursorToLocAndWriteInfo(infoX, infoY, tune->length, tune->notes[currentNoteIndex].frequency);
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
    for (uint32_t i = 0; i < tune->length; i++) {
        Note *note = &tune->notes[i];
        PlaySound(note->frequency);

        uint32_t updateInterval = 50;
        uint32_t numUpdates = note->duration / updateInterval;
        for (uint32_t step = 0; step < numUpdates; step++) {
            RenderMusicScreen(tune, i);
            UpdateBusyAnimation(step);
            SleepInterrupt(updateInterval);
        }
        StopSound();
    }
    DisableSpeaker();
}

MusicPlayer* CreateMusicPlayer() {
    // Allocate memory for a new music player
    MusicPlayer* player = (MusicPlayer*)Malloc(sizeof(MusicPlayer));
    
    if (player) {
        printf("Player valid.\n");
        player->playTune = &PlayMusic; // Pointer to music player
    }

    return player;
}

