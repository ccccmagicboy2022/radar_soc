.section .start, "ax", @progbits
    .globl  Reset_Handler
Reset_Handler:

.option push
.option norelax
    la      gp, __global_pointer
.option pop

    la      a0, Default_Handler
    csrw    mtvec, a0

    la      a0, __Vectors
    csrw    mtvt, a0

    la      sp, __initial_sp
    csrw    mscratch, sp

    /* Load data section */
    la      a0, __erodata
    la      a1, __data_start
    la      a2, __data_end
    bgeu    a1, a2, 2f
1:
    lw      t0, (a0)
    sw      t0, (a1)
    addi    a0, a0, 4
    addi    a1, a1, 4
    bltu    a1, a2, 1b
2:

    /* Clear bss section */
    la      a0, __bss_start__
    la      a1, __bss_end__
    bgeu    a0, a1, 2f
1:
    sw      zero, (a0)
    addi    a0, a0, 4
    bltu    a0, a1, 1b
2:

    jal     main

__exit:
    j      __exit

    .align 6
Default_Handler:
    jal handle_trap


.section .vectors, "aw", @progbits
    .align  6
    .globl  __Vectors
    .type   __Vectors, @object
__Vectors:
    .rept 16
    .long   Default_Handler
    .endr

    /* External interrupts */
    .long   IRQ000_Handler
    .long   IRQ001_Handler
    .long   IRQ002_Handler
    .long   IRQ003_Handler
    .long   IRQ004_Handler
    .long   IRQ005_Handler
    .long   IRQ006_Handler


.global __initial_sp

#define		StackSize		0x400

.section .app_stack, "aw", @nobits
.align 2
Stack_Mem:
.space StackSize
__initial_sp:

.text
.align 2
.global delay_us
.type delay_us, @function
delay_us:
    neg a0, a0
	bgez a0, 2f
1:
    .rept 5
    nop
    .endr
    addi a0, a0, 1
    bnez a0, 1b
2:
    ret


