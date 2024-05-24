/* Source: UiA, Per-Arne Lecture/Assignment Assets

    And,    
    UiA IKT218 2024V
    Group-5 
*/

extern "C" {
    #include "memory/memory.h"
    #include "interrupt/isr.h"
    #include "libc/stdio.h"
    #include "libc/stdbool.h"
    #include "libc/stddef.h"
    #include "io/pit.h"
    #include "io/keyboard.h"
    #include "io/display.h"
    #include "music/music.h"
    #include "io/musicScreen.h"
}

/* Source: UiA, Per-Arne Lecture/Assignment Assets */
/* ASSIGNMENT_4.1 Memory Management */
void *operator new(size_t size) {
    return Malloc(size);
}
void *operator new[](size_t size) {
    return Malloc(size);
}
void operator delete(void *ptr) noexcept {
    Free(ptr);
}
void operator delete[](void *ptr) noexcept {
    Free(ptr);
}
void operator delete(void *ptr, size_t size) noexcept {
    (void)size;
    Free(ptr);
}
void operator delete[](void *ptr, size_t size) noexcept {
    (void)size;
    Free(ptr);
}

void InterruptThreeHandler(Registers_t *r, void *context) {
    printf("Interrupt 3 - OK\n");
}

void InterruptFourHandler(Registers_t *r, void *context) {
    printf("Interrupt 4 - OK\n");
}

void InterruptFiveHandler(Registers_t *r, void *context) {
    printf("Interrupt 5 - OK\n");
}

extern "C" int kernel_main(void);
int kernel_main(){

    /* ASSIGNMENT_3.2 Induce interrupt */
    // Upon return from this interrupt, the program immediately
    //  raises error code 13 (general protection fault) and "crashes". 
    // The ISR handler likely mangles the return address.
    // We don't experience this with the IRQ handler. Not sure how to handle
    //  this error. We have tried looking for problems with the ISR handler,
    //  but that has proven extremely difficult.The music player works well,
    //  and so does the keyboard logger..
    // UPDATE. Changed ebx to eax in interrupt.asm (ISR handler).
    RegisterInterruptHandler(ISR3, &InterruptThreeHandler, NULL);
    RegisterInterruptHandler(ISR4, &InterruptFourHandler, NULL);
    RegisterInterruptHandler(ISR5, &InterruptFiveHandler, NULL);
    asm volatile("int $0x03");
    asm volatile("int $0x04");
    asm volatile("int $0x05");

    /* ASSIGNMENT_4.1 Memory Management */
    // DisplayClear();
    // // 1.
    // SleepInterrupt(3000);
    // void *evenMoreMemory = new uint32_t[1000];
    // printf("\n");
    // SleepInterrupt(3000);
    // Free(evenMoreMemory);
    // printf("\n");
    // // 2.
    // SleepInterrupt(3000);
    // void *deleteThisMemory = new uint32_t[500];
    // printf("\n");
    // SleepInterrupt(3000);
    // delete[] (uint32_t *)deleteThisMemory;
    // printf("\n");
    // // 3.
    // SleepInterrupt(3000);
    // void *absurdMemory = new uint32_t[100000000];
    // printf("\n");
    // SleepInterrupt(3000);

    // Cannot have this fancy stuff, because if someone pushes 'c' or 'x'
    // during this timer the controlls will not work.
    // bool pauseOneMoment = true;
    // while (pauseOneMoment) {
    //     for (int i = 1; i <= 3; i++) {
    //         printf("Starting Music Player: %ds\n", i);
    //         SleepInterrupt(1000);
    //     }
    //     pauseOneMoment = false;
    //     SleepInterrupt(200);
    // }

    /* Source: UiA, Per-Arne Lecture/Assignment Assets */
    /* ASSIGNMENT_3.4 Keyboard Logger */
    InitKeyboard();
    
    Tune *tunes[] = {
        new Tune( { "starwars_theme", starwars_theme, sizeof(starwars_theme) / sizeof(Note) } ),
        new Tune( { "music_1", music_1, sizeof(music_1) / sizeof(Note)}),
        new Tune( { "music_2", music_2, sizeof(music_2) / sizeof(Note)}),
        new Tune( { "music_3", music_3, sizeof(music_3) / sizeof(Note)}),
        new Tune( { "music_4", music_4, sizeof(music_4) / sizeof(Note)}),
        new Tune( { "music_5", music_5, sizeof(music_5) / sizeof(Note)}),
        new Tune( { "music_6", music_6, sizeof(music_6) / sizeof(Note)}),
        new Tune( { "battlefield_1942_theme", battlefield_1942_theme, sizeof(battlefield_1942_theme) / sizeof(Note) } ),
    };

    uint32_t playlistSize = sizeof(tunes) / sizeof(Tune *);
    MusicPlayer *boomblaster = CreateMusicPlayer();
    while (true) {
        for (uint32_t i = 0; i < playlistSize && IsMusicPlaying(); i++) {
            boomblaster->playTune(tunes[i]);
        }
    }


    for (;;) ;
    return 0;
}