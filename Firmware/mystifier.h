#include <xc.h>

// Mystifier v3 PIC16F15224

// ICSP connections: 1=yellow, 4=blue, 12=black, 13=red, 14=green

//		PWMOUT		RA2			// pin 11
//		FEEDBACK	RA4			// pin 3

#define	LAMP1		LATC3		// pin 7
#define	LAMP2		LATC4		// pin 6
#define	LAMP3		LATC5		// pin 5
#define	LAMP4		LATC0		// pin 10
#define	LAMP5		LATC1		// pin 9
#define	LAMP6		LATC2		// pin 8

#define	TP			LATA5		// pin 2

#define ELEMENTSOF( a )		(sizeof( a ) / sizeof( (a)[0] ))

typedef struct
{
	uint8_t rate;
	uint8_t seed;
} nonvol_t;

void display_init( uint8_t rate );
void display_process( void );

void nonvol_load( void );
void nonvol_store( void );

void power_init( void );
void power_process( void );

uint16_t random( void );
void random_init( uint16_t seed );

extern const nonvol_t saf;
extern nonvol_t nonvol;

// Required linker options
// -mreserve=rom@0xF80:0xFFF -Wl,-ASAF=F80h-FFFh -Wl,-DSAF=2 -Wl,-Psaf=SAF
