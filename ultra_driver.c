#include <LPC21XX.H>
#include "headerB.h"
#define trig (1<<8)	 //p0.2 --> trigger pin
#define echo ((IOPIN0>>9)&1)  //p0.3 --> echo pin

void ultra_init(void){

	IODIR0|=trig;  
	T1PR=59;  //set timer prescalar value to 59 (for 1us delay) --> pclk=60-1 --> T1PR=60*1
	T1TCR=0;  //disable timer1 counter
}

void trigger_pulse(void){

	T1PC=0;	 
	T1TC=0;
	T1TC=0;
	IOSET0=trig;  //SET trigger for 10us
	delay_us(10);
	IOCLR0=trig;  //CLEAR trigger
}
u32 get_distance(void){
	u32 dist=0;
	trigger_pulse();  //sending trigger pulse
	while(echo==0);	  //waiting for echp high
	T1TCR=1;   //start timer1
	while(echo==1);	 //waiting for echp low
	T1TCR=0;
	if(T1TC>30000)
	   T1TC=59;
	   //stop timer1
	dist=T1TC;  //saving time
	dist=(0.0343*dist)/2;
	//calculate distance
	return dist;

}
