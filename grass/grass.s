/*
 * (C) 2024, Cornell University
 * All rights reserved.
 *
 * Description: grass layer entry
 */
    .section .text
    .global grass_entry

grass_entry:
    li sp,0x80003f80
    call main
