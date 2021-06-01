#include "mystifier.h"

nonvol_t nonvol;

void nonvol_load( void )
{
	NVMREGS = 0;
	
	NVMADR         = (uint16_t) &saf.rate;
	NVMCON1bits.RD = 1;
	nonvol.rate    = NVMDAT;
	
	NVMADR         = (uint16_t) &saf.seed;
	NVMCON1bits.RD = 1;
	nonvol.seed    = NVMDAT;
}

void nonvol_store( void )
{
	NVMREGS = 0;

	NVMADR           = (uint16_t) &saf;
	NVMCON1bits.FREE = 1;		// erasing
	NVMCON1bits.WREN = 1;
	NVMCON2          = 0x55;
	NVMCON2          = 0xAA;
	NVMCON1bits.WR   = 1;

	NVMADR           = (uint16_t) &saf.rate;
	NVMDAT           = nonvol.rate;
	NVMCON1bits.FREE = 0;		// writing
	NVMCON1bits.LWLO = 1;		// to latch only
	NVMCON1bits.WREN = 1;
	NVMCON2          = 0x55;
	NVMCON2          = 0xAA;
	NVMCON1bits.WR   = 1;
	
	NVMADR           = (uint16_t) &saf.seed;
	NVMDAT           = nonvol.seed;
	NVMCON1bits.FREE = 0;		// writing
	NVMCON1bits.LWLO = 0;		// to latch and flash
	NVMCON1bits.WREN = 1;
	NVMCON2          = 0x55;
	NVMCON2          = 0xAA;
	NVMCON1bits.WR   = 1;
	
	NVMCON1bits.WREN = 0;
}
