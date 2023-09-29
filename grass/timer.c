/*
 * (C) 2023, Cornell University
 * All rights reserved.
 */

/* Author: Yunhao Zhang
 * Description: timer reset
 * mtime is at 0x200bff8 and mtimecmp is at 0x2004000 in the memory map
 * see section 3.1.15 of references/riscv-privileged-v1.10.pdf
 * and section 9.1, 9.3 of references/sifive-fe310-v19p04.pdf
 */

#include "egos.h"

static unsigned long long mtime_get() {
    unsigned int low, high;
    do {
        high = REGW(0x200BFF8, 4);
        low  = REGW(0x200BFF8, 0);
    }  while ( REGW(0x200BFF8, 4) != high );

    return (((unsigned long long)high) << 32) | low;
}

static void mtimecmp_set(unsigned long long time) {
    REGW(0x2004000, 4) = 0xFFFFFFFF;
    REGW(0x2004000, 0) = (unsigned int)time;
    REGW(0x2004000, 4) = (unsigned int)(time >> 32);
}

#define QUANTUM_SMALL 5000
#define QUANTUM_LARGE 50000

int timer_reset() {
    mtimecmp_set(mtime_get() + QUANTUM_LARGE);
    return 0;
}
