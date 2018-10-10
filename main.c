

#include "MK64F12.h"
#include "NVIC.h"
#include "GPIO.h"
#include "Bits.h"
#include <stdio.h>

#define NUM_STEPS (1u)
#define SYSTEM_CLOCK (21000000u)
#define DELAY (0.01F)

#define NBYTES_16b 2

#define ARRAY_SIZE (16u)

#define DMA_CH0 (0x01u)
#define DMA_SOURCE_GPIO (51u)
#define MAGIC_NUMBER 0X101
/*
uint8_t g_data_source[ARRAY_SIZE] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};//defines source data space
uint8_t g_data_desti[ARRAY_SIZE]; //defines destination data space
*/
uint16_t g_data_source[ARRAY_SIZE] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};//defines source data space
uint16_t g_data_desti[ARRAY_SIZE]; //defines destination data space

/*size of the array*/
#define SIZEWAVE 101

uint16 sineWave[SIZEWAVE] = { 2047, 2176, 2304, 2431, 2556, 2680, 2801, 2919,
		3033, 3144, 3250, 3352, 3448, 3539, 3624, 3703, 3775, 3841, 3899, 3950,
		3994, 4030, 4058, 4078, 4090, 4094, 4090, 4078, 4058, 4030, 3994, 3950,
		3899, 3841, 3775, 3703, 3624, 3539, 3448, 3352, 3250, 3144, 3033, 2919,
		2801, 2680, 2556, 2431, 2304, 2176, 2047, 1918, 1790, 1663, 1538, 1414,
		1293, 1175, 1061, 950, 844, 742, 646, 555, 470, 391, 319, 253, 195, 144,
		100, 64, 36, 16, 4, 0, 4, 16, 36, 64, 100, 144, 195, 253, 319, 391, 470,
		555, 646, 742, 844, 950, 1061, 1175, 1293, 1414, 1538, 1663, 1790, 1918,
		2047 };
uint16 triangularWave[SIZEWAVE] = { 0, 82, 164, 246, 328, 409, 491, 573, 655,
		737, 819, 901, 983, 1064, 1146, 1228, 1310, 1392, 1474, 1556, 1638,
		1719, 1801, 1883, 1965, 2047, 2129, 2211, 2293, 2375, 2456, 2538, 2620,
		2702, 2784, 2866, 2948, 3030, 3111, 3193, 3275, 3357, 3439, 3521, 3603,
		3685, 3766, 3848, 3930, 4012, 4094, 4012, 3930, 3848, 3766, 3685, 3603,
		3521, 3439, 3357, 3275, 3193, 3111, 3030, 2948, 2866, 2784, 2702, 2620,
		2538, 2456, 2375, 2293, 2211, 2129, 2047, 1965, 1883, 1801, 1719, 1638,
		1556, 1474, 1392, 1310, 1228, 1146, 1064, 983, 901, 819, 737, 655, 573,
		491, 409, 328, 246, 164, 82, 0 };
uint16 squareWave[SIZEWAVE] = { 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094,
		4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094,
		4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094,
		4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094, 4094,
		4094, 4094, 4094, 4094, 4094, 4094, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4094 };


void DMA0_IRQHandler(void)
{

	uint8_t i;

	DMA0->INT = DMA_CH0;

	for ( i = 0; i < ARRAY_SIZE; ++i)
	{
		printf("%d,",g_data_desti[i]);
	}
	printf("\n");
}


void DMA_clock_gating(void)
{
	SIM->SCGC7 |= SIM_SCGC7_DMA_MASK;
	SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
}


void DMA_init(void)
{

	DMAMUX->CHCFG[0] = 0;
	DMAMUX->CHCFG[0] = DMAMUX_CHCFG_ENBL_MASK | /*enables DMA MUX channel*/
					   DMAMUX_CHCFG_SOURCE(DMA_SOURCE_GPIO);/*source is FTM0 channel 0*/

	DMA0->ERQ = 0x01;//enables DMA0 request

	DMA0->TCD[0].SADDR = (uint32_t)(&g_data_source[4]);/*defines source data address*/
	DMA0->TCD[0].SOFF = 2;/*2 Source address signed offset;it is expressed in number of bytes*/
	/*este uno quiere decir que se mueve en un byte el valor del apuntador, de a donde apunta la siguente transferencia*/

	DMA0->TCD[0].DADDR = (uint32_t)(&g_data_desti[0]);/*defines destination data address*//*a donde quieres mandar los datos*/
	DMA0->TCD[0].DOFF = 2;/*escribir el destino*//*destination address signed offset;it is expressed in number of bytes*//*cuantos espacios quiero brincar entre transferencias*/

	/*para poder transferir correctamente, citer y biter, deben tener el mismo valor*/

	DMA0->TCD[0].CITER_ELINKNO = DMA_CITER_ELINKNO_CITER(NUM_STEPS);// NUM_STEPS;/*CITER = 1*//*cuantos paquetes de bytes quiero transferir?*/
	DMA0->TCD[0].BITER_ELINKNO = DMA_BITER_ELINKNO_BITER(NUM_STEPS);/*BITER = 1*/
	/*NBytes para 16 bits, tenemos que enviar empaquetado el doble del tamaño*/
	DMA0->TCD[0].NBYTES_MLNO = 16*NBYTES_16b;/*byte number*/ /*cuantos bytes quiero transferir*/

	DMA0->TCD[0].ATTR = 0x101;/*16 bit transfer size, in order to transfer see Kinetis user manual*//*0 es de 8 en 8, para lo demás, ver el manual*/

/*	DMA0->TCD[0].ATTR = 0;*//*8 bit transfer size, in order to transfer see Kinetis user manual*//*0 es de 8 en 8, para lo demás, ver el manual*/

	DMA0->TCD[0].SLAST = 0;//restores the source address to the initial value, which is expressed in the amount of bytes to restore*/
/*registro para reestablecer direcciones*/
	DMA0->TCD[0].DLAST_SGA = 0;/*restores the destination address to the initial value, which is expressed in the amount of bytes to restore*/

	/*DMA0->TCD[0].CSR = 0x4u;*/
	DMA0->TCD[0].CSR = DMA_CSR_INTMAJOR_MASK;/*The end-of-major loop interrupt is enabled*/


}

int main(void)
{
	gpio_pin_control_register_t sw2 = GPIO_MUX1 | GPIO_PE | GPIO_PS | DMA_FALLING_EDGE; /* GPIO configured to trigger the DMA*/

	GPIO_clock_gating(GPIO_C);
	GPIO_pin_control_register(GPIO_C, bit_6, &sw2);
	DMA_clock_gating();
	DMA_init(); /* Configure the T*/
	NVIC_enable_interrupt_and_priotity(DMA_CH0_IRQ, PRIORITY_5);
	NVIC_global_enable_interrupts;
    for (;;) {

    }
    /* Never leave main */
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
