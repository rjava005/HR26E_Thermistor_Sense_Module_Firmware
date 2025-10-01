.syntax unified
.cpu cortex-m4
.thumb

.global Reset_Handler

/* Vector table */
.section .isr_vector, "a", %progbits
.word  0x20020000     /* Initial stack pointer (128KB RAM end) */
.word  Reset_Handler  /* Reset vector */

.text
Reset_Handler:
    bl main
    b .