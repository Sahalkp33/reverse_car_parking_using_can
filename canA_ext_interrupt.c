#include <LPC21XX.H>
#include "headerA.h"
extern can2 v1, v2;

extern u32 count1;

void eint_handler(void)__irq

{

	static u32 count=0;

	count^=1;

	if(count){																
		IOCLR0=(1<<17);

		count1=1;																														
	}																			
	else{																		
		IOSET0=(1<<17);

		count1=2;																														
	}	

	EXTINT=1;

	VICVectAddr=0;

}

void en_eint(void){

	EXTMODE=1;

	EXTPOLAR=0;

	VICIntSelect=0;

	VICVectCntl0=14|(1<<5);

	VICVectAddr0=(u32)eint_handler;

	VICIntEnable|=(1<<14);

}
