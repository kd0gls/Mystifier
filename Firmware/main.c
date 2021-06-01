#include "mystifier.h"

#define	RATE_ADJUST_TIME	(15 * 2000)		// in 500 us increments

static uint16_t timer;
static enum { StateAdjust, StateRun } state;

///////////////////////////////////////////////////////////////////////////////

void main( void )
{
	OSCFRQ	 = 0b00000100;			// HFINTOSC to 16 MHz
	OSCCON	 = 0b00100000;			// HFINTOSC

	ANSELA	 = 0b00010000;			// ANA4 to analog, all other pins to digital
	SLRCONA	 = 0b00000000;			// normal slew rate
	LATA	 = 0b00000000;			// all pins negated
	TRISA	 = 0b00010000;			// ANA4 to input, all other pins to outputs

	ANSELC	 = 0b00000000;			// all pins to digital
	SLRCONC	 = 0b00000000;			// normal slew rate
	LATC	 = 0b00000000;			// all pins negated
	TRISC	 = 0b00000000;			// all pins to outputs

	//	16 MHz (Fosc) / 4 (Fcyc) / 200 (PR2 + 1) = 20 KHz PWM / 10 (postscaler) = 2 KHz
	T2PR	 = 199;
	T2CLKCON = 0b00000001;			// clock to Fosc/4
	T2CON	 = 0b10001001;			// timer on, 1:1 prescaler, 1:10 postscaler

	PWM3DC	 = 0;
	PWM3CON	 = 0b10000000;
	RA2PPS	 = 3;					// RA2 to PWM3 output

	FVRCON	 = 0b10000011;			// FVR enabled, 4.096V
	ADCON0	 = 0b00010001;			// channel ANA4, ADC enabled
	ADCON1	 = 0b00100011;			// left justified result, conversion clock to Fosc/32 (2 uS), Vref- to Vss, Vref+ to FVR
	
	///////////////////////////////////

	nonvol_load();
	
	display_init( nonvol.rate );
	nonvol.rate++;
	
	random_init( 0xA5A5 ^ nonvol.seed );
	nonvol.seed += 101;
	
	power_init();
	
	nonvol_store();

	///////////////////////////////////
	
	timer = RATE_ADJUST_TIME;
	state = StateAdjust;
	
	for( ;; )
	{
		power_process();
		
		if( TMR2IF )
		{
			TMR2IF = 0;
			
			TP = 1;
			
			switch( state )
			{
				case StateAdjust:
					if( --timer == 0 )
					{
						nonvol.rate--;		// undo rate change
						nonvol_store();
						state = StateRun;
					}

					display_process();
					break;

				case StateRun:
					display_process();
					break;
			}
			
			TP = 0;
		}
	}
}
