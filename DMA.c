/*
 * DMA.c
 *
 *  Created on: Oct 5, 2018
 *      Author: LuisFernando
 */

#include "DMA.h"

void DMA_enable(dma_enable_t enableOrDisable, dma_source_t dmaSource)
{
	if(DMA_DISABLE == enableOrDisable)
		DMAMUX->CHCFG[0] &= ~(DMAMUX_CHCFG_ENBL_MASK);
	else if(DMA_ENABLE == enableOrDisable)
		DMAMUX->CHCFG[0] |= (DMAMUX_CHCFG_ENBL_MASK) | DMAMUX_CHCFG_SOURCE(dmaSource);

}
//DMAMUX_CHCFG_TRIG_MASK
/*MAscara para habilitar el trigger
 * capitulo 24.1*/
