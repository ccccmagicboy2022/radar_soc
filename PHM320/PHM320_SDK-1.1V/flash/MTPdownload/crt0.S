
// <<< Use Configuration Wizard in Context Menu >>>

.global __initial_sp

// <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:4>
// <i> Config the stack size for the application
#define		StackSize		0x100


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



/*
 * For importing variable or functions from other c or assemble files.
 */


  .section ".text.init"
  .globl Reset_Handler
  .type Reset_Handler, %function
Reset_Handler:

    la      sp, __initial_sp
    csrw    mscratch, sp

    jal     main

__exit:
    j      __exit


.globl __continue_label
.section ".text"
.align 2
.type __continue_label, %function
__continue_label:
    mv a0, a0
    ret

.globl __bkpt_label
.section ".text"
.align 2
.type __bkpt_label, %function
__bkpt_label:
    ebreak
    ret


