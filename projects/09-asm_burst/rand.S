;* ---------------------------------------------------------------------
;*
;* Assembly implementation of 4- and 8--bit LFSR-based (Linear Feedback
;* Shift Register) pseudo-random generators.
;* ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
;*
;* Copyright (c) 2017-2019 Tomas Fryza
;* Dept. of Radio Electronics, Brno University of Technology, Czechia
;* This work is licensed under the terms of the MIT license.
;*
;* https://www.xilinx.com/support/documentation/application_notes/xapp052.pdf
;* http://courses.cse.tamu.edu/walker/csce680/lfsr_table.pdf
;*
;* ---------------------------------------------------------------------

;* Includes ------------------------------------------------------------
; Set offset for control register addresses (NEEDED FOR I/O REGISTERS)
#define __SFR_OFFSET    0
#include <avr/io.h>

;* Define --------------------------------------------------------------
#define input   r24

;*----------------------------------------------------------------------
;* Burst generator.
;* Input:  r24 - count of pulses
.global burst_asm
burst_asm:
    sbi PORTB, 5            ; set pin
    cbi PORTB, 5            ; clear pin
    dec input               ; Decrement  
    brne burst_asm          ; End if "input" is ZERO (Z=1)
    ret