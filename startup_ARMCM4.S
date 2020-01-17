/* File: startup_ARMCM4.S
 * Purpose: startup file for Cortex-M4 devices. Should use with
 *   GCC for ARM Embedded Processors
 * Version: V2.0
 * Date: 16 August 2013
 */
 
/* Copyright (c) 2011 - 2013 ARM LIMITED

   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------*/
	.syntax	unified
	.arch	armv7e-m

	.section .stack
	.align	3
#ifdef __STACK_SIZE
	.equ	Stack_Size, __STACK_SIZE
#else
	.equ	Stack_Size, 0x400
#endif
	.globl	__StackTop
	.globl	__StackLimit
__StackLimit:
	.space	Stack_Size
	.size	__StackLimit, . - __StackLimit
__StackTop:
	.size	__StackTop, . - __StackTop

	.section .heap
	.align	3
#ifdef __HEAP_SIZE
	.equ	Heap_Size, __HEAP_SIZE
#else
	.equ	Heap_Size, 0x0
#endif
	.globl	__HeapBase
	.globl	__HeapLimit
__HeapBase:
	.if	Heap_Size
	.space	Heap_Size
	.endif
	.size	__HeapBase, . - __HeapBase
__HeapLimit:
	.size	__HeapLimit, . - __HeapLimit

	.section .isr_vector
	.align	2
	.globl	__isr_vector
	.type   __isr_vector, %object
__isr_vector:
	.long	__StackTop            /* Top of Stack */
	.long	Reset_Handler         /* Reset Handler */
	.long	NMI_Handler           /* NMI Handler */
	.long	HardFault_Handler     /* Hard Fault Handler */
	.long	MemManage_Handler     /* MPU Fault Handler */
	.long	BusFault_Handler      /* Bus Fault Handler */
	.long	UsageFault_Handler    /* Usage Fault Handler */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	SVC_Handler           /* Service Call (SVCall) Handler */
	.long	DebugMon_Handler      /* Debug Monitor Handler */
	.long	0                     /* Reserved */
	.long	PendSV_Handler        /* Pendable Service (PendSV) Handler */
	.long	SysTick_Handler       /* SysTick Handler */

	@ .long default_Handler

	/* External interrupts, 139 in total, 0 -> 138 */
	.long	GPIO_Port_A_Handler				/* Interrupt 0 */
	.long	GPIO_Port_B_Handler				/* Interrupt 1 */
	.long	GPIO_Port_C_Handler				/* Interrupt 2 */
	.long	GPIO_Port_D_Handler				/* Interrupt 3 */
	.long	GPIO_Port_E_Handler				/* Interrupt 4 */
	.long	UART_0_Handler					/* Interrupt 5 */
	.long	UART_1_Handler					/* Interrupt 6 */
	.long	SSI_0_Handler					/* Interrupt 7 */
	.long	I2C_0_Handler					/* Interrupt 8 */
	.long	PWM_0_Fault_Handler				/* Interrupt 9 */
	.long	PWM_0_Generator_0_Handler		/* Interrupt 10 */
	.long	PWM_0_Generator_1_Handler		/* Interrupt 11 */
	.long	PWM_0_Generator_2_Handler		/* Interrupt 12 */
	.long	QEI_0_Handler					/* Interrupt 13 */
	.long	ADC_0_Sequence_0_Handler		/* Interrupt 14 */
	.long	ADC_0_Sequence_1_Handler		/* Interrupt 15 */
	.long	ADC_0_Sequence_2_Handler		/* Interrupt 16 */
	.long	ADC_0_Sequence_3_Handler        /* Interrupt 17 */
	.long	Watchdog_0_and_1_Handler        /* Interrupt 18 */
    .long   _16_32_Bit_Timer_0A_Handler     /* Interrupt 19 */
    .long	_16_32_Bit_Timer_0B_Handler     /* Interrupt 20 */
	.long	_16_32_Bit_Timer_1A_Handler     /* Interrupt 21 */
	.long	_16_32_Bit_Timer_1B_Handler     /* Interrupt 22 */
	.long	_16_32_Bit_Timer_2A_Handler     /* Interrupt 23 */
	.long	_16_32_Bit_Timer_2B_Handler     /* Interrupt 24 */
	.long	Analog_Comparator_0_Handler     /* Interrupt 25 */
	.long	Analog_Comparator_1_Handler     /* Interrupt 26 */
	.long	0                               /* Interrupt 27 */
	.long	System_Control_Handler          /* Interrupt 28 */
	.long	Flash_and_EEPROM_Control_Handler/* Interrupt 29 */
	.long	GPIO_Port_F_Handler             /* Interrupt 30 */
	.long	0                               /* Interrupt 31 */
	.long	0                               /* Interrupt 32 */
	.long	UART_2_Handler                  /* Interrupt 33 */
	.long	SSI_1_Handler                   /* Interrupt 34 */
	.long	_16_32_Bit_Timer_3A_Handler     /* Interrupt 35 */
	.long	_16_32_Bit_Timer_3B_Handler	    /* Interrupt 36 */
	.long	I2C_1_Handler                   /* Interrupt 37 */
	.long	QEI_1_Handler                   /* Interrupt 38 */
	.long	CAN_0_Handler                   /* Interrupt 39 */
	.long	CAN_1_Handler                   /* Interrupt 40 */
	.long	0                               /* Interrupt 41 */
	.long	0                               /* Interrupt 42 */
    .long	Hibernation_Module_Handler      /* Interrupt 43 */
	.long	USB_Handler                     /* Interrupt 44 */
	.long	PWM_Generator_3_Handler         /* Interrupt 45 */
	.long	uDMA_Software_Handler           /* Interrupt 46 */
	.long	uDMA_Error_Handler              /* Interrupt 47 */
	.long	ADC_1_Sequence_0_Handler        /* Interrupt 48 */
	.long	ADC_1_Sequence_1_Handler        /* Interrupt 49 */
	.long	ADC_1_Sequence_2_Handler        /* Interrupt 50 */
	.long	ADC_1_Sequence_3_Handler        /* Interrupt 51 */
	.long	0                               /* Interrupt 52 */
	.long	0                               /* Interrupt 53 */
	.long	0                               /* Interrupt 54 */
	.long	0                               /* Interrupt 55 */
	.long	0                               /* Interrupt 56 */
	.long	SSI_2_Handler                   /* Interrupt 57 */
	.long	SSI_3_Handler                   /* Interrupt 58 */
	.long	UART_3_Handler                  /* Interrupt 59 */
	.long	UART_4_Handler                  /* Interrupt 60 */
	.long	UART_5_Handler                  /* Interrupt 61 */
	.long	UART_6_Handler                  /* Interrupt 62 */
	.long	UART_7_Handler                  /* Interrupt 63 */
	.long	0                               /* Interrupt 64 */
	.long	0                               /* Interrupt 65 */
	.long	0                               /* Interrupt 66 */
	.long	0                               /* Interrupt 67 */
	.long	I2C_2_Handler                   /* Interrupt 68 */
	.long	I2C_3_Handler                   /* Interrupt 69 */
	.long	_16_32_Bit_Timer_4A_Handler     /* Interrupt 70 */
	.long	_16_32_Bit_Timer_4B_Handler     /* Interrupt 71 */
	.long	0                               /* Interrupt 72 */
	.long	0                               /* Interrupt 73 */
	.long	0                               /* Interrupt 74 */
	.long	0                               /* Interrupt 75*/
	.long	0                               /* Interrupt 76 */
	.long	0                               /* Interrupt 77 */
	.long	0                               /* Interrupt 78 */
	.long	0                               /* Interrupt 79 */
	.long	0                               /* Interrupt 80 */
	.long	0                               /* Interrupt 81 */
	.long	0                               /* Interrupt 82 */
	.long	0                               /* Interrupt 83 */
	.long	0                               /* Interrupt 84 */
	.long	0                               /* Interrupt 85 */
	.long	0                               /* Interrupt 86 */
	.long	0                               /* Interrupt 87 */
	.long	0                               /* Interrupt 88 */
	.long	0                               /* Interrupt 89 */
	.long	0                               /* Interrupt 90 */
	.long	0                               /* Interrupt 91 */
	.long	_16_32_Bit_Timer_5A_Handler     /* Interrupt 92 */
	.long	_16_32_Bit_Timer_5B_Handler     /* Interrupt 93 */
	.long	_32_64_Bit_Timer_0A_Handler     /* Interrupt 94 */
	.long	_32_64_Bit_Timer_0B_Handler     /* Interrupt 95 */
	.long	_32_64_Bit_Timer_1A_Handler     /* Interrupt 96 */
	.long	_32_64_Bit_Timer_1B_Handler     /* Interrupt 97 */
	.long	_32_64_Bit_Timer_2A_Handler     /* Interrupt 98 */
	.long	_32_64_Bit_Timer_2B_Handler     /* Interrupt 99 */
	.long	_32_64_Bit_Timer_3A_Handler     /* Interrupt 100 */
	.long	_32_64_Bit_Timer_3B_Handler     /* Interrupt 101 */
	.long	_32_64_Bit_Timer_4A_Handler     /* Interrupt 102 */
	.long	_32_64_Bit_Timer_4B_Handler     /* Interrupt 103 */
	.long	_32_64_Bit_Timer_5A_Handler     /* Interrupt 104 */
	.long	_32_64_Bit_Timer_5B_Handler     /* Interrupt 105 */
	.long	System_Exception_Handler        /* Interrupt 106 */
	.long	0                               /* Interrupt 107 */
	.long	0                               /* Interrupt 108 */
	.long	0                               /* Interrupt 109 */
	.long	0                               /* Interrupt 110 */
	.long	0                               /* Interrupt 111 */
	.long	0                               /* Interrupt 112 */
	.long	0                               /* Interrupt 113 */
	.long	0                               /* Interrupt 114 */
	.long	0                               /* Interrupt 115 */
	.long	0                               /* Interrupt 116 */
	.long	0                               /* Interrupt 117 */
	.long	0                               /* Interrupt 118 */
	.long	0                               /* Interrupt 119 */
	.long	0                               /* Interrupt 120 */
	.long	0                               /* Interrupt 121 */
	.long	0                               /* Interrupt 122 */
	.long	0                               /* Interrupt 123 */
	.long	0                               /* Interrupt 124 */
	.long	0                               /* Interrupt 125 */
	.long	0                               /* Interrupt 126 */
	.long	0                               /* Interrupt 127 */
	.long	0                               /* Interrupt 128 */
	.long	0                               /* Interrupt 129 */
	.long	0                               /* Interrupt 130 */
	.long	0                               /* Interrupt 131 */
	.long	0                               /* Interrupt 132 */
	.long	0                               /* Interrupt 133 */
	.long	PWM_1_Generator_0_Handler       /* Interrupt 134 */
	.long	PWM_1_Generator_1_Handler       /* Interrupt 135 */
	.long	PWM_1_Generator_2_Handler       /* Interrupt 136 */
	.long	PWM_1_Generator_3_Handler       /* Interrupt 137 */
	.long	PWM_1_Fault_Handler             /* Interrupt 138 */

	.size	__isr_vector, . - __isr_vector

	.text
	.thumb
	.thumb_func
	.align	2
	.globl	Reset_Handler
	.type	Reset_Handler, %function
Reset_Handler:
/*  Firstly it copies data from read only memory to RAM. There are two schemes
 *  to copy. One can copy more than one sections. Another can only copy
 *  one section.  The former scheme needs more instructions and read-only
 *  data to implement than the latter.
 *  Macro __STARTUP_COPY_MULTIPLE is used to choose between two schemes.  */

#ifdef __STARTUP_COPY_MULTIPLE
/*  Multiple sections scheme.
 *
 *  Between symbol address __copy_table_start__ and __copy_table_end__,
 *  there are array of triplets, each of which specify:
 *    offset 0: LMA of start of a section to copy from
 *    offset 4: VMA of start of a section to copy to
 *    offset 8: size of the section to copy. Must be multiply of 4
 *
 *  All addresses must be aligned to 4 bytes boundary.
 */
	ldr	r4, =__copy_table_start__
	ldr	r5, =__copy_table_end__

.L_loop0:
	cmp	r4, r5
	bge	.L_loop0_done
	ldr	r1, [r4]
	ldr	r2, [r4, #4]
	ldr	r3, [r4, #8]

.L_loop0_0:
	subs	r3, #4
	ittt	ge
	ldrge	r0, [r1, r3]
	strge	r0, [r2, r3]
	bge	.L_loop0_0

	adds	r4, #12
	b	.L_loop0

.L_loop0_done:
#else
/*  Single section scheme.
 *
 *  The ranges of copy from/to are specified by following symbols
 *    __etext: LMA of start of the section to copy from. Usually end of text
 *    __data_start__: VMA of start of the section to copy to
 *    __data_end__: VMA of end of the section to copy to
 *
 *  All addresses must be aligned to 4 bytes boundary.
 */
	ldr	r1, =__etext
	ldr	r2, =__data_start__
	ldr	r3, =__data_end__

.L_loop1:
	cmp	r2, r3
	ittt	lt
	ldrlt	r0, [r1], #4
	strlt	r0, [r2], #4
	blt	.L_loop1
#endif /*__STARTUP_COPY_MULTIPLE */

/*  This part of work usually is done in C library startup code. Otherwise,
 *  define this macro to enable it in this startup.
 *
 *  There are two schemes too. One can clear multiple BSS sections. Another
 *  can only clear one section. The former is more size expensive than the
 *  latter.
 *
 *  Define macro __STARTUP_CLEAR_BSS_MULTIPLE to choose the former.
 *  Otherwise efine macro __STARTUP_CLEAR_BSS to choose the later.
 */
#ifdef __STARTUP_CLEAR_BSS_MULTIPLE
/*  Multiple sections scheme.
 *
 *  Between symbol address __copy_table_start__ and __copy_table_end__,
 *  there are array of tuples specifying:
 *    offset 0: Start of a BSS section
 *    offset 4: Size of this BSS section. Must be multiply of 4
 */
	ldr	r3, =__zero_table_start__
	ldr	r4, =__zero_table_end__

.L_loop2:
	cmp	r3, r4
	bge	.L_loop2_done
	ldr	r1, [r3]
	ldr	r2, [r3, #4]
	movs	r0, 0

.L_loop2_0:
	subs	r2, #4
	itt	ge
	strge	r0, [r1, r2]
	bge	.L_loop2_0

	adds	r3, #8
	b	.L_loop2
.L_loop2_done:
#elif defined (__STARTUP_CLEAR_BSS)
/*  Single BSS section scheme.
 *
 *  The BSS section is specified by following symbols
 *    __bss_start__: start of the BSS section.
 *    __bss_end__: end of the BSS section.
 *
 *  Both addresses must be aligned to 4 bytes boundary.
 */
	ldr	r1, =__bss_start__
	ldr	r2, =__bss_end__

	movs	r0, 0
.L_loop3:
	cmp	r1, r2
	itt	lt
	strlt	r0, [r1], #4
	blt	.L_loop3
#endif /* __STARTUP_CLEAR_BSS_MULTIPLE || __STARTUP_CLEAR_BSS */

#ifndef __NO_SYSTEM_INIT
	bl	SystemInit
#endif

#ifndef __START
#define __START _start
#endif
	bl	__START

	.pool
	.size	Reset_Handler, . - Reset_Handler

	.align	1
	.thumb_func
	.weak	Default_Handler
	.type	Default_Handler, %function
Default_Handler:
	b	.
	.size	Default_Handler, . - Default_Handler

/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
	.macro	def_irq_handler	handler_name
	.weak	\handler_name
	.set	\handler_name, Default_Handler
	.endm

	def_irq_handler	NMI_Handler
	def_irq_handler	HardFault_Handler
	def_irq_handler	MemManage_Handler
	def_irq_handler	BusFault_Handler
	def_irq_handler	UsageFault_Handler
	def_irq_handler	SVC_Handler
	def_irq_handler	DebugMon_Handler
	def_irq_handler	PendSV_Handler
	def_irq_handler	SysTick_Handler
	
	@ def_irq_handler default_Handlder

	def_irq_handler	GPIO_Port_A_Handler
	def_irq_handler	GPIO_Port_B_Handler
	def_irq_handler	GPIO_Port_C_Handler
	def_irq_handler	GPIO_Port_D_Handler
	def_irq_handler	GPIO_Port_E_Handler
	def_irq_handler	UART_0_Handler
	def_irq_handler	UART_1_Handler
	def_irq_handler	SSI_0_Handler
	def_irq_handler	I2C_0_Handler
	def_irq_handler	PWM_0_Fault_Handler
	def_irq_handler	PWM_0_Generator_0_Handler
	def_irq_handler	PWM_0_Generator_1_Handler
	def_irq_handler	PWM_0_Generator_2_Handler
	def_irq_handler	QEI_0_Handler
	def_irq_handler	ADC_0_Sequence_0_Handler
	def_irq_handler	ADC_0_Sequence_1_Handler
	def_irq_handler	ADC_0_Sequence_2_Handler
	def_irq_handler	ADC_0_Sequence_3_Handler
	def_irq_handler	Watchdog_0_and_1_Handler
	def_irq_handler	_16_32_Bit_Timer_0A_Handler
	def_irq_handler	_16_32_Bit_Timer_0B_Handler
	def_irq_handler	_16_32_Bit_Timer_1A_Handler
	def_irq_handler	_16_32_Bit_Timer_1B_Handler
	def_irq_handler	_16_32_Bit_Timer_2A_Handler
	def_irq_handler	_16_32_Bit_Timer_2B_Handler
	def_irq_handler	Analog_Comparator_0_Handler
	def_irq_handler	Analog_Comparator_1_Handler
	def_irq_handler	System_Control_Handler
	def_irq_handler	Flash_and_EEPROM_Control_Handler
	def_irq_handler	GPIO_Port_F_Handler
	def_irq_handler	UART_2_Handler
	def_irq_handler	SSI_1_Handler
	def_irq_handler	_16_32_Bit_Timer_3A_Handler
	def_irq_handler	_16_32_Bit_Timer_3B_Handler	
	def_irq_handler	I2C_1_Handler
	def_irq_handler	QEI_1_Handler
	def_irq_handler	CAN_0_Handler
	def_irq_handler	CAN_1_Handler
	def_irq_handler	Hibernation_Module_Handler
	def_irq_handler	USB_Handler
	def_irq_handler	PWM_Generator_3_Handler
	def_irq_handler	uDMA_Software_Handler
	def_irq_handler	uDMA_Error_Handler
	def_irq_handler	ADC_1_Sequence_0_Handler
	def_irq_handler	ADC_1_Sequence_1_Handler
	def_irq_handler	ADC_1_Sequence_2_Handler
	def_irq_handler	ADC_1_Sequence_3_Handler
	def_irq_handler	SSI_2_Handler
	def_irq_handler	SSI_3_Handler
	def_irq_handler	UART_3_Handler
	def_irq_handler	UART_4_Handler
	def_irq_handler	UART_5_Handler
	def_irq_handler	UART_6_Handler
	def_irq_handler	UART_7_Handler
	def_irq_handler	I2C_2_Handler
	def_irq_handler	I2C_3_Handler
	def_irq_handler	_16_32_Bit_Timer_4A_Handler
	def_irq_handler	_16_32_Bit_Timer_4B_Handler
	def_irq_handler	_16_32_Bit_Timer_5A_Handler
	def_irq_handler	_16_32_Bit_Timer_5B_Handler
	def_irq_handler	_32_64_Bit_Timer_0A_Handler
	def_irq_handler	_32_64_Bit_Timer_0B_Handler
	def_irq_handler	_32_64_Bit_Timer_1A_Handler
	def_irq_handler	_32_64_Bit_Timer_1B_Handler
	def_irq_handler	_32_64_Bit_Timer_2A_Handler
	def_irq_handler	_32_64_Bit_Timer_2B_Handler
	def_irq_handler	_32_64_Bit_Timer_3A_Handler
	def_irq_handler	_32_64_Bit_Timer_3B_Handler
	def_irq_handler	_32_64_Bit_Timer_4A_Handler
	def_irq_handler	_32_64_Bit_Timer_4B_Handler
	def_irq_handler	_32_64_Bit_Timer_5A_Handler
	def_irq_handler	_32_64_Bit_Timer_5B_Handler
	def_irq_handler	System_Exception_Handler
	def_irq_handler	PWM_1_Generator_0_Handler
	def_irq_handler	PWM_1_Generator_1_Handler
	def_irq_handler	PWM_1_Generator_2_Handler
	def_irq_handler	PWM_1_Generator_3_Handler
	def_irq_handler	PWM_1_Fault_Handler

@ 	.text
@ 	//.thumb
@ 	//.thumb_func
@ 	.align	1
@ 	.globl	disableInterrupts
@ 	.type	disableInterrupts, %function
@ disableInterrupts:
@ 	mrs     r0, PRIMASK;
@     cpsid   i;
@     bx      lr
@ 	.size	disableInterrupts, . - disableInterrupts


@ 	.text
@ 	//.thumb
@ 	//.thumb_func
@ 	.align	1
@ 	.globl	enableInterrupts
@ 	.type	enableInterrupts, %function
@ enableInterrupts:
@     //
@     // Read PRIMASK and enable interrupts.
@     //
@     mrs     r0, PRIMASK;
@     cpsie   i;
@     bx      lr
@ 	.size	enableInterrupts, . - enableInterrupts

	



	.end
