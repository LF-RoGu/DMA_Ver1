/*
 * DMA.h
 *
 *  Created on: Oct 5, 2018
 *      Author: LuisFernando
 */

#ifndef DMA_H_
#define DMA_H_

#include "MK64F12.h"
#include "NVIC.h"
#include "GPIO.h"
#include "Bits.h"

typedef enum{
	SOURCE0,/*Reserved*/
	SOURCE1,/*UART0*/
	SOURCE2,/*UART0*/
	SOURCE3,/*UART1*/
	SOURCE4,/*UART1*/
	SOURCE5,/*UART2*/
	SOURCE6,/*UART2*/
	SOURCE7,/*UART3*/
	SOURCE8,/*UART3*/
	SOURCE9,/*SPI0*/
	SOURCE10,/*SPI0*/
	SOURCE11,/*SPI0*/
	SOURCE12,/*SPI1*/
	SOURCE13,/*SPI1*/
	SOURCE14,/*I2C0*/
	SOURCE15,/*I2C1*/
	SOURCE16,/*Reserved*/
	SOURCE17,/*Reserved*/
	SOURCE18,/*FTM0*/
	SOURCE19,/*FTM0*/
	SOURCE20,/*FTM0*/
	SOURCE21,/*FTM0*/
	SOURCE22,/*FTM0*/
	SOURCE23,/*FTM0*/
	SOURCE24,/*FMT3*/
	SOURCE25,/*FMT3*/
	SOURCE26,/*FMT3*/
	SOURCE27,/*FMT3*/
	SOURCE28,/*FMT3*/
	SOURCE29,/*FMT3*/
	SOURCE30,
	SOURCE31,
	SOURCE32,
	SOURCE33,
	SOURCE34,
	SOURCE35,
	SOURCE36,
	SOURCE37,
	SOURCE38,
	SOURCE39,
	SOURCE40,/*ADC1*/
	SOURCE41,/*ADC2*/
	SOURCE42,/*ADC3*/
	SOURCE43,/*CMP0*/
	SOURCE44,/*CMP1*/
	SOURCE45,/*CMP2*/
	SOURCE46,/*CMP3*/
	SOURCE47,/*RTC*/
	SOURCE48,/*CMT*/
	SOURCE49,/*Port Control Module*/
	SOURCE50,/*Port Control Module*/
	SOURCE51,/*Port Control Module*/
	SOURCE52,/*Port Control Module*/
	SOURCE53,/*Port Control Module*/
	SOURCE54,/*DMA MUX*/
	SOURCE55,/*DMA MUX*/
	SOURCE56,/*DMA MUX*/
	SOURCE57,/*DMA MUX*/
	SOURCE58,/*DMA MUX*/
	SOURCE59,/*DMA MUX*/
	SOURCE60,/*DMA MUX*/
	SOURCE61,/*DMA MUX*/
	SOURCE62,/*DMA MUX*/
	SOURCE63/*DMA MUX*/

}dma_source_t;
typedef enum{DMA_DISABLE,DMA_ENABLE}dma_enable_t;

void DMA_enable(dma_enable_t enableOrDisable, dma_source_t dmaSource);

#endif /* DMA_H_ */
