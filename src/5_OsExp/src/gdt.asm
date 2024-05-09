; Source
; https://web.archive.org/web/20190309070619/http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html
; http://www.osdever.net/bkerndev/Docs/gdt.htm

global _gdtFlush

_gdtFlush:
    mov eax, [esp+4]
    lgdt [eax]          ; Loading our pointer into the GDT

    mov ax, 0x10        ; 0x10 is the offset to the data segment
    mov ds, ax          ; Moving the data segment selectors
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    jmp 0x08:flush_new     ; Far jump to refresh code segment selector

flush_new:
    ret                 ; Return to C code