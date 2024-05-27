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
}

#define SLEEP_INTERRUPT_DELIVERABLES 100

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
    /* Assignment 2 */
    DisplayClear();
    printf("Assignment 2 Deliverables: \n\n");
    printf("Hello, World!\n");
    SleepInterrupt(SLEEP_INTERRUPT_DELIVERABLES);

    /* Assignment 3.1/3.2 */
    DisplayClear();
    printf("Assignment 3 Deliverables: \n\n");
    RegisterInterruptHandler(ISR3, &InterruptThreeHandler, NULL);
    RegisterInterruptHandler(ISR4, &InterruptFourHandler, NULL);
    RegisterInterruptHandler(ISR5, &InterruptFiveHandler, NULL);
    asm volatile("int $0x03");
    asm volatile("int $0x04");
    asm volatile("int $0x05");
    SleepInterrupt(SLEEP_INTERRUPT_DELIVERABLES);

    /* Assignment 4 */
    DisplayClear();
    printf("Assignment 4 Deliverables (1/3): Allocate memory using Malloc\n\n");
    void* some_memory = Malloc(12345);
    void* memory2 = Malloc(54321);
    void* memory3 = Malloc(13331);
    char* memory4 = new char[1000]();
    SleepInterrupt(SLEEP_INTERRUPT_DELIVERABLES);
    DisplayClear();
    printf("Assignment 4 Deliverables (2/3): Allocate memory using new\n\n");
    void *some_new_memory = new uint32_t[1000];
    printf("\n");
    SleepInterrupt(SLEEP_INTERRUPT_DELIVERABLES);
    Free(some_new_memory);
    printf("\n");
    SleepInterrupt(SLEEP_INTERRUPT_DELIVERABLES);
    void *new_memory2 = new uint32_t[500];
    delete[] (uint32_t *)new_memory2;
    SleepInterrupt(SLEEP_INTERRUPT_DELIVERABLES);
    DisplayClear();
    printf("Assignment 4 Deliverables(3/3): Print memory layout\n\n");
    PrintMemoryLayout();
    SleepInterrupt(SLEEP_INTERRUPT_DELIVERABLES);

    /* Assignment 5 */
    DisplayClear();
    printf("Assignment 5 Deliverables:\n\n");
    printf("Starting Music Player");
    SleepInterrupt(SLEEP_INTERRUPT_DELIVERABLES);
    
    Tune *tunes[] = {
        new Tune( { "music_1", music_1, sizeof(music_1) / sizeof(Note)}),
        new Tune( { "music_2", music_2, sizeof(music_2) / sizeof(Note)}),
        new Tune( { "music_3", music_3, sizeof(music_3) / sizeof(Note)}),
        new Tune( { "music_4", music_4, sizeof(music_4) / sizeof(Note)}),
        new Tune( { "music_5", music_5, sizeof(music_5) / sizeof(Note)}),
        new Tune( { "music_6", music_6, sizeof(music_6) / sizeof(Note)}),
        new Tune( { "starwars_theme", starwars_theme, sizeof(starwars_theme) / sizeof(Note) } ),
        new Tune( { "battlefield_1942_theme", battlefield_1942_theme, sizeof(battlefield_1942_theme) / sizeof(Note) } ),
    };

    /* Assignment 3.3/3.4
        Keyboard logger:
        The keyboard does not print characters to the screen, instead
        The music player is interactable, can restart, play, and go to next
        song if certain keybinds are pressed. */
    uint32_t playlistSize = sizeof(tunes) / sizeof(Tune *);
    MusicPlayer *boomblaster = CreateMusicPlayer();
    while (true) {
        // IsMusicPlaying function returns value from boolean music control variable 'playingMusic' from music.c
        for (uint32_t i = 0; i < playlistSize && IsMusicPlaying(); i++) {
            // Pass Tune object from the 'tunes' array of Tune objects. Index indicates which song is playing.
            boomblaster->playTune(tunes[i]); 
        }
    }

    for (;;) ;
    return 0;
}