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
    // RegisterInterruptHandler(ISR3, &InterruptThreeHandler, NULL);
    // asm volatile("int $0x03");

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

    /* Source: UiA, Per-Arne Lecture/Assignment Assets */
    /* ASSIGNMENT_3.4 Keyboard Logger */
    InitKeyboard();
    
    Tune *tunes[] = {
        new Tune( { battlefield_1942_theme, sizeof(battlefield_1942_theme) / sizeof(Note) } ),
        new Tune( { starwars_theme, sizeof(starwars_theme) / sizeof(Note) } ),
    };

    uint32_t playlistSize = sizeof(tunes) / sizeof(Tune *);

    DisplayClear();
    printf("~ MUSIC ~\n");
    MusicPlayer *boomblaster = CreateMusicPlayer();
    for (uint32_t i = 0; i < playlistSize; i++) {
        boomblaster->playTune(tunes[i]);
    }

    for (;;) ;
    return 0;
}