; Source:
; https://web.archive.org/web/20190309070619/http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html
   
;global _isr0
;_isr0:
;    cli                         ; disable interrupts
;    push byte 0                 ; Dummy error code. 
;    push byte 0                 ; Interrupt number
;    jmp isrCommonHandler        ; Jump to common handler for interrupts

; Using macro to make the 32 routines

; The macro takes one parameter, accessed through %1
%macro ISR_NOERRCODE 1
  global isr%1
  isr%1:
    ;cli                
    push byte 0         
    push  %1            
    jmp isrCommonHandler
%endmacro

; Macro for when there is an error code
%macro ISR_ERRCODE 1
  global isr%1
  isr%1:
    ;cli                     
    push %1                 
    jmp isrCommonHandler
%endmacro

%macro IRQ 2
  global irq%1
  irq%1:
    cli
    push byte 0
    push byte %2
    jmp irqCommonHandler
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
isrCommonHandler:
    pusha                   ; "all" registers

    mov ax, ds              ; Moving current DS into AX
    push eax                ; Save original DS

    mov ax, 0x10            ; Load kernel data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call isrHandler

    pop ebx
    mov ds, ax              ; Segment registers
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa                    ; Restore remaining registers
    add esp, 8              ; Clean up the pushed error code and pushed ISR number
    sti
    iret                    ; Returning from interrupt and pop CS, EIP, EFLAGS, SS, and ESP simultaneously.


global idtFlush
idtFlush:
    mov eax, [esp+4]            ; Getting pointer to the IDT
    lidt [eax]                  ; loading the poitner
    ret                         ; Returning to C code

IRQ 0, 32
IRQ 1, 33
IRQ 2, 34
IRQ 3, 35
IRQ 4, 36
IRQ 5, 37
IRQ 6, 38
IRQ 7, 39
IRQ 8, 40
IRQ 9, 41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47

extern irqHandler
irqCommonHandler:
  pusha

  mov ax, ds
  push eax

  mov ax, 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  call irqHandler

  pop ebx
  mov ds, bx
  mov es, bx
  mov fs, bx
  mov gs, bx

  popa    
  add esp, 8    
  sti
  iret     
