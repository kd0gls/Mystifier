
// PIC16F15224 Configuration Bit Settings

// CONFIG1
#pragma config FEXTOSC = OFF			// External Oscillator Mode Selection bits (Oscillator not enabled)
#pragma config RSTOSC = HFINTOSC_1MHZ	// Power-up Default Value for COSC bits (HFINTOSC (1 MHz))
#pragma config CLKOUTEN = OFF			// Clock Out Enable bit (CLKOUT function is disabled; I/O function on RA4)
#pragma config VDDAR = HI				// VDD Range Analog Calibration Selection bit (Internal analog systems are calibrated for operation between VDD = 2.3V - 5.5V)

// CONFIG2
#pragma config MCLRE = EXTMCLR			// Master Clear Enable bit (If LVP = 0, MCLR pin is MCLR; If LVP = 1, RA3 pin function is MCLR)
#pragma config PWRTS = PWRT_64			// Power-up Timer Selection bits (PWRT set at 64 ms)
#pragma config WDTE = OFF				// WDT Operating Mode bits (WDT disabled; SEN is ignored)
#pragma config BOREN = OFF				// Brown-out Reset Enable bits (Brown-out Reset disabled)
#pragma config BORV = LO				// Brown-out Reset Voltage Selection bit (Brown-out Reset Voltage (VBOR) set to 1.9V)
#pragma config PPS1WAY = OFF			// PPSLOCKED One-Way Set Enable bit (The PPSLOCKED bit can be set and cleared as needed (unlocking sequence is required))
#pragma config STVREN = OFF				// Stack Overflow/Underflow Reset Enable bit (Stack Overflow or Underflow will not cause a reset)

// CONFIG3

// CONFIG4
#pragma config BBSIZE = BB512			// Boot Block Size Selection bits (512 words boot block size)
#pragma config BBEN = OFF				// Boot Block Enable bit (Boot Block is disabled)
#pragma config SAFEN = ON				// SAF Enable bit (SAF is enabled)
#pragma config WRTAPP = OFF				// Application Block Write Protection bit (Application Block is not write-protected)
#pragma config WRTB = OFF				// Boot Block Write Protection bit (Boot Block is not write-protected)
#pragma config WRTC = OFF				// Configuration Registers Write Protection bit (Configuration Registers are not write-protected)
#pragma config WRTSAF = OFF				// Storage Area Flash (SAF) Write Protection bit (SAF is not write-protected)
#pragma config LVP = OFF				// Low Voltage Programming Enable bit (High Voltage on MCLR/Vpp must be used for programming)

// CONFIG5
#pragma config CP = OFF					// User Program Flash Memory Code Protection bit (User Program Flash Memory code protection is disabled)
