/* Source: UiA, Per-Arne Lecture/Assignment Assets */

#ifndef KEYBOARD_H
#define KEYBOARD_H

#pragma once

#include "libc/stdint.h"
#include "libc/stdbool.h"
#include "port.h"
#include "libc/stdio.h"
#include "system.h"
#include "interrupt/isr.h"

char ScancodeToAscii(uint8_t *scanCode);

void KeyboardIrqHandler(Registers_t *r, void *context);

void InitKeyboard();

#endif