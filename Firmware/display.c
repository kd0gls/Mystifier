#include "mystifier.h"

#define	FADE_STEPS	14		// 98 ms (must not exceed shortest dwell)

static uint8_t curr, next, duty, step;
static uint16_t dwell, timer;
static enum { StateDwell, StateFade } state;

static const uint8_t lamp_lut[7][5+3] =
{
	{ 1, 2, 3, 4, 5, 6, 1, 2 },		// all
	{ 2, 3, 4, 5, 6, 2, 3, 4 },		// except 1
	{ 3, 4, 5, 6, 1, 3, 4, 5 },		// except 2
	{ 4, 5, 6, 1, 2, 4, 5, 6 },		// except 3
	{ 5, 6, 1, 2, 3, 5, 6, 1 },		// except 4
	{ 6, 1, 2, 3, 4, 6, 1, 2 },		// except 5
	{ 1, 2, 3, 4, 5, 1, 2, 3 },		// except 6
};

static const uint16_t dwell_lut[] =
{
	2000 / 1,		// 1000 mS
	2000 / 3 * 2,	// 666 mS
	2000 / 2,		// 500 mS
	2000 / 5 * 2,	// 400 mS
	2000 / 3,		// 333 mS
	2000 / 7 * 2,	// 284 mS
	2000 / 4,		// 250 mS
	2000 / 5,		// 200 mS
	2000 / 6,		// 166 mS
	2000 / 7,		// 142 mS
};

static void set_lamp( uint8_t lamp );

///////////////////////////////////////////////////////////////////////////////

void display_init( uint8_t rate )
{
	curr = next = 0;
	dwell = dwell_lut[rate % 10];
	timer = 1;
	state = StateDwell;
}

void display_process( void )
{
	switch( state )
	{
		case StateDwell:
			if( --timer == 0 )
			{
				next = lamp_lut[curr][random() % 8];
				duty = step = 0;
				timer = dwell;
				state = StateFade;
			}

			break;

		case StateFade:
			timer--;
			
			if( ++step == FADE_STEPS )
			{
				if( ++duty == FADE_STEPS )
				{
					curr = next;
					state = StateDwell;
				}
				else
					step = 0;
			}

			set_lamp( (step > duty) ? curr : next );
			break;
	}
}

static void set_lamp( uint8_t lamp )
{
	// warning: clear undesired lamps first, set desired lamp last!
	switch( lamp )
	{
		case 0:		// for initial fade-in only
			LAMP1 = 0;
			LAMP2 = 0;
			LAMP3 = 0;
			LAMP4 = 0;
			LAMP5 = 0;
			LAMP6 = 0;
			break;

		case 1:
			LAMP2 = 0;
			LAMP3 = 0;
			LAMP4 = 0;
			LAMP5 = 0;
			LAMP6 = 0;
			LAMP1 = 1;
			break;

		case 2:
			LAMP1 = 0;
			LAMP3 = 0;
			LAMP4 = 0;
			LAMP5 = 0;
			LAMP6 = 0;
			LAMP2 = 1;
			break;

		case 3:
			LAMP1 = 0;
			LAMP2 = 0;
			LAMP4 = 0;
			LAMP5 = 0;
			LAMP6 = 0;
			LAMP3 = 1;
			break;

		case 4:
			LAMP1 = 0;
			LAMP2 = 0;
			LAMP3 = 0;
			LAMP5 = 0;
			LAMP6 = 0;
			LAMP4 = 1;
			break;

		case 5:
			LAMP1 = 0;
			LAMP2 = 0;
			LAMP3 = 0;
			LAMP4 = 0;
			LAMP6 = 0;
			LAMP5 = 1;
			break;

		case 6:
			LAMP1 = 0;
			LAMP2 = 0;
			LAMP3 = 0;
			LAMP4 = 0;
			LAMP5 = 0;
			LAMP6 = 1;
			break;
	}
}
