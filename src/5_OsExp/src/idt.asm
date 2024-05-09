; Source:
; https://web.archive.org/web/20190309070619/http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html

global _idtFlush

_idtFlush:
    mov eax, [esp+4]          ; Getting pointer to the IDT
    lidt [eax]                  ; loading the poitner
    ret                         ; Returning to C code
    
;global _isr0
;_isr0:
;    cli                         ; disable interrupts
;    push byte 0                 ; Dummy error code. 
;    push byte 0                 ; Interrupt number
;    jmp _isrCommonHandler        ; Jump to common handler for interrupts

; Using macro to make the 32 routines

; The macro takes one parameter, accessed through %1
%macro ISR_NOERRCODE 1
  global isr%1
  isr%1:
    ;cli                
    push byte 0         
    push  %1            
    jmp _isrCommonHandler
%endmacro

; Macro for when there is an error code
%macro ISR_ERRCODE 1
  global isr%1
  isr%1:
    ;cli                     
    push %1                 
    jmp _isrCommonHandler
%endmacro

ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE 8
ISR_NOERRCODE 9
ISR_ERRCODE 10 ; Double Fault
ISR_ERRCODE 11 ; Invalid TSS (Text Segment Selector)
ISR_ERRCODE 12 ; Segment not present
ISR_ERRCODE 13 ; General protection fault
ISR_ERRCODE 14 ; Page fault
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_ERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_ERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

extern isrHandler

_isrCommonHandler:
    pusha                   ; "all" registers

    mov ax, ds
    push eax                ; Save data segment descriptor

    mov ax, 0x10            ; Load kernel data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call isrHandler

    pop ebx                 ; Reload original data segment descriptor
    mov ds, ax              ; Segment registers
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa                    ; Restore remaining registers
    add esp, 8              ; Clean up the pushed error code and pushed ISR number
    sti
    iret                    ; Returning from interrupt and pop CS, EIP, EFLAGS, SS, and ESP simultaneously.