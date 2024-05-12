#include "music/music.h"

void EnableSpeaker() {
    uint8_t speakerState = InPortByte(PC_SPEAKER_PORT);
    if (speakerState != (speakerState | 0x03)) {
        OutPortByte(PC_SPEAKER_PORT, speakerState | 0x03);
    }
}

void DisableSpeaker() {
    uint8_t speakerState = InPortByte(PC_SPEAKER_PORT);
    OutPortByte(PC_SPEAKER_PORT, speakerState & ~0x03);
}

void PlaySound(uint32_t freq) {
    if (freq == 0) {
        return;
    }

    uint16_t divisor = (uint16_t)(PIT_BASE_FREQUENCY / freq);
    OutPortByte(PIT_CMD_PORT, 0b10110110);
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
        PlaySound(note->frequency);
        SleepInterrupt(note->duration);
        StopSound();
    }
    DisableSpeaker();
}

MusicPlayer* CreateMusicPlayer() {
    MusicPlayer* player = (MusicPlayer*)Malloc(sizeof(MusicPlayer));
    
    if (player) {
        printf("Player valid.\n");
        player->playTune = &PlayMusic;
    }

    return player;
}