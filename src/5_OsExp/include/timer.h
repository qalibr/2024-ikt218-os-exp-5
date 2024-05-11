#ifndef TIMER_H
#define TIMER_H

#include "libc/stdint.h"
#include "common.h"
#include "system.h"
#include "display.h"
#include "interrupt/isr.h"
#include "libc/stdio.h"

void initTimer(uint32_t freq);

#endif