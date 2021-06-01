#include	"xc.inc"

        psect	saf,class=CODE,delta=2

	global	_saf
_saf:	dw	0	// rate
	dw	0	// seed

	end
