/*
Copyright (c) 2018 Intrepid Control Systems, Inc.
All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
extern void *_estack;

#define NULL ((void *)0)

void Reset_HandlerSys();
void Default_Handler();

void NMI_Handler()             __attribute__ ((weak, alias ("Default_Handler")));
void HardFault_Handler()       __attribute__ ((weak, alias ("Default_Handler")));
void SVC_Handler()             __attribute__ ((weak, alias ("Default_Handler")));
void PendSV_Handler()          __attribute__ ((weak, alias ("Default_Handler")));
void SysTick_Handler()         __attribute__ ((weak, alias ("Default_Handler")));
void POWER_CLOCK_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void RADIO_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void UART0_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void GPIOTE_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void ADC_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void TIMER0_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void TIMER1_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void TIMER2_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void RTC0_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void TEMP_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void RNG_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void ECB_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void CCM_AAR_IRQHandler()      __attribute__ ((weak, alias ("Default_Handler")));
void WDT_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void RTC1_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void QDEC_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void LPCOMP_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void SWI0_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void SWI1_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void SWI2_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void SWI3_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void SWI4_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void SWI5_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void SPI0_TWI0_IRQHandler()    __attribute__((weak, alias("Default_Handler")));
void SPI1_TWI1_IRQHandler()    __attribute__((weak, alias("Default_Handler")));

void * g_pfnVectors[0x30] __attribute__ ((section (".isr_vector"), used)) = 
{
	&_estack,
	&Reset_HandlerSys,
	&NMI_Handler,
	&HardFault_Handler,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&SVC_Handler,
	NULL,
	NULL,
	&PendSV_Handler,
	&SysTick_Handler,
	&POWER_CLOCK_IRQHandler,
	&RADIO_IRQHandler,
	&UART0_IRQHandler,
	&SPI0_TWI0_IRQHandler,
	&SPI1_TWI1_IRQHandler,
	NULL,
	&GPIOTE_IRQHandler,
	&ADC_IRQHandler,
	&TIMER0_IRQHandler,
	&TIMER1_IRQHandler,
	&TIMER2_IRQHandler,
	&RTC0_IRQHandler,
	&TEMP_IRQHandler,
	&RNG_IRQHandler,
	&ECB_IRQHandler,
	&CCM_AAR_IRQHandler,
	&WDT_IRQHandler,
	&RTC1_IRQHandler,
	&QDEC_IRQHandler,
	&LPCOMP_IRQHandler,
	&SWI0_IRQHandler,
	&SWI1_IRQHandler,
	&SWI2_IRQHandler,
	&SWI3_IRQHandler,
	&SWI4_IRQHandler,
	&SWI5_IRQHandler,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
};

void SystemInit();
void __libc_init_array();
int main();

extern void *_sidata, *_sdata, *_edata;
extern void *_sbss, *_ebss;
extern void *_sstack;

void __attribute__((naked, noreturn)) Reset_HandlerSys()
{
	asm volatile(".equ NRF_POWER_RAMON_ADDRESS,0x40000524");
	asm volatile(".equ NRF_POWER_RAMON_RAMxON_ONMODE_Msk,3");
	asm volatile("LDR     R0, =NRF_POWER_RAMON_ADDRESS");
	asm volatile("LDR     R2, [R0]");
	asm volatile("MOVS    R1, #NRF_POWER_RAMON_RAMxON_ONMODE_Msk");
	asm volatile("ORR     R2, R2, R1");
	asm volatile("STR     R2, [R0]");
	
	#ifdef sram_layout
	asm ("ldr sp, =_estack");
	#endif

	// Copy data
	void **pSource, **pDest;
	for (pSource = &_sidata, pDest = &_sdata; pDest != &_edata; pSource++, pDest++)
		*pDest = *pSource;

	// Zero-out the BSS
	for (pDest = &_sbss; pDest != &_ebss; pDest++)
		*pDest = 0;
	
	// Watermark the stack so we can track usage when debugging
	for (pDest = &_sstack; pDest != &_estack; pDest++)
		*pDest = (void*)0xAA;

	SystemInit();
	__libc_init_array();
	(void)main();
	for (;;) ;
}

void __attribute__((naked, noreturn)) Default_Handler()
{
	for (;;) ;
}
