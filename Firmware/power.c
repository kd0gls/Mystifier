#include "mystifier.h"

#define V80		125		// 2.000V
#define V85		132		// 2.125V
#define V90		140		// 2.250V
#define V95		148		// 2.375V
#define V100	156		// 2.500V
#define V105	164		// 2.625V
#define V110	171		// 2.750V
#define V115	179		// 2.875V
#define V120	187		// 3.000V

#define	VREG	V100

#define DC_MAX	((uint16_t) 150 << 6)
#define DC_MIN	((uint16_t) 1 << 6)
#define DC_STEP	(1 << 6)

void power_init( void )
{
	GO = 1;
}

void power_process( void )
{
	if( GO == 0 )
	{
		if( ADRESH < VREG )
		{
			if( PWM3DC < DC_MAX )
				PWM3DC += DC_STEP;
		}
		else if( ADRESH > VREG )
		{
			if( PWM3DC > DC_MIN )
				PWM3DC -= DC_STEP;
		}

		GO = 1;
	}
}
