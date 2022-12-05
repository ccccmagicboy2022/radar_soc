
.global __initial_sp

#define		StackSize		0x400

.section .app_stack,"aw",@nobits
.align 2
Stack_Mem:
.space StackSize
__initial_sp:

.global __main
.global handle_trap

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
