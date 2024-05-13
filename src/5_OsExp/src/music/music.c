/* Source: UiA, Per-Arne Lecture/Assignment Assets */

#include "music/music.h"

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
        printf("Note: %d, Freq=%d, Sleep=%d\n", i, note->frequency, note->duration);
        PlaySound(note->frequency);         // Take current note's frequency and play sound
        SleepInterrupt(note->duration);     // Play the note for it's duration
        StopSound();                        // Stop sound
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