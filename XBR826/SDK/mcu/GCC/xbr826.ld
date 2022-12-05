ENTRY(Reset_Handler)

MEMORY
{
	ROM :
	ORIGIN = 0x0 ,
	LENGTH = 0x1000

	RAM :
	ORIGIN = 0x1000 ,
	LENGTH = 0x800
}

SECTIONS
{
    .text : {
		. = ALIGN(0x4) ;
		__stext = . ;
		KEEP(*crt0.o(*.start*))
		KEEP(*(.vectors))
		*(.text*)
		. = ALIGN(0x10) ;
		__etext = . ;
    } > ROM

    .rodata : {
		. = ALIGN(0x4) ;
		__srodata = .;
		*(.rdata*)
		*(.rodata*)
		. = ALIGN(0x10) ;
		__erodata = .;
    } > ROM

    .data : {
		. = ALIGN(0x4) ;
		__data_start = . ;
		*(.data*)
		__global_pointer = .;
		*(.sdata)
		*(.sdata.*)
		. = ALIGN(0x10) ;
		__data_end = . ;
	} > RAM AT > ROM

    .bss : {
		. = ALIGN(0x4) ;
		__bss_start__ = . ;
		*(.bss*)
		*(COMMON)
		. = ALIGN(0x10) ;
		KEEP(*crt0.o(.app_heap))
		KEEP(*crt0.o(.app_stack))
		__bss_end__ = . ;
	} > RAM
}
