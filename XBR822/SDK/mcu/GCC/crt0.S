    .text
    .globl  Reset_Handler
Reset_Handler:

.option push
.option norelax
    la      gp, __global_pointer$
.option pop

    la      a0, Default_Handler
    csrw    mtvec, a0

    la      a0, __Vectors
    csrw    mtvt, a0

    la      sp, __initial_sp
    csrw    mscratch, sp

    /* Load data section */
    la      a0, __int_end
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
    addi sp, sp, -272
    sw x1, 1*4(sp)
    sw x2, 2*4(sp)
    sw x3, 3*4(sp)
    sw x4, 4*4(sp)
    sw x5, 5*4(sp)
    sw x6, 6*4(sp)
    sw x7, 7*4(sp)
    sw x8, 8*4(sp)
    sw x9, 9*4(sp)
    sw x10, 10*4(sp)
    sw x11, 11*4(sp)
    sw x12, 12*4(sp)
    sw x13, 13*4(sp)
    sw x14, 14*4(sp)
    sw x15, 15*4(sp)

    csrr a0, mcause
    csrr a1, mepc
    mv a2, sp
    jal handle_trap

    lw x1, 1*4(sp)
    lw x2, 2*4(sp)
    lw x3, 3*4(sp)
    lw x4, 4*4(sp)
    lw x5, 5*4(sp)
    lw x6, 6*4(sp)
    lw x7, 7*4(sp)
    lw x8, 8*4(sp)
    lw x9, 9*4(sp)
    lw x10, 10*4(sp)
    lw x11, 11*4(sp)
    lw x12, 12*4(sp)
    lw x13, 13*4(sp)
    lw x14, 14*4(sp)
    lw x15, 15*4(sp)
    addi sp, sp, 272
    mret


.section .vectors, "aw", @progbits
    .align  6
    .globl  __Vectors
    .type   __Vectors, @object
__Vectors:
    .long   Default_Handler
    .long   Default_Handler
    .long   Default_Handler
    .long   Default_Handler
    .long   Default_Handler
    .long   Default_Handler
    .long   Default_Handler
    .long   Default_Handler
    .long   Default_Handler
    .long   Default_Handler
    .long   Default_Handler
    .long   Default_Handler
    .long   Default_Handler
    .long   Default_Handler
    .long   Default_Handler
    .long   Default_Handler

    /* External interrupts */
    .long   0
    .long   0
    .long   0
    .long   0
    .long   0
    .long   0
    .long   0

// <<< Use Configuration Wizard in Context Menu >>>

.global __initial_sp

// <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:4>
// <i> Config the stack size for the application
#define		StackSize		0x400


.section .app_stack,"aw",@nobits
.align 2
Stack_Mem:
.space StackSize
__initial_sp:


// <o> Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
// <i> Config the heap size for the application
//#define		HeapSize		0x0
//
//.global __heap_start
//.global __heap_end
//.section .bss,"aw",@nobits
//.align 2
//Heap_Mem:
//__heap_start:
//.space HeapSize
//__heap_end:

.text
.align 2
.global delay_us
.type delay_us, @function
delay_us:
    neg a0, a0
	bgez a0, 2f
1:
    .rept 6
    nop
    .endr
    addi a0, a0, 1
    bnez a0, 1b
2:
    ret


