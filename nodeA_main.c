/*main_NodeA.c*/
#include <LPC21xx.H>
#include "headerA.h"
#define led (1<<17)
#define buzz (1<<21)

//#define sw ((IOPIN0>>14)&1)
u8 flag=0;
u32 count1;	  
can2 v1, v2, r1; 	  

int main(){	
	IODIR0|=led|buzz;
	IOSET0=led;	  
	IOCLR0=buzz;
	PINSEL1|=1;		  
	can2_init();
	uart0_init(9600);
	en_eint();
	en_can2_interruptA();
	uart0_tx_string("WELCOME\r\n");
//	uart0_integer(10);	  	   
	/*Configure remote frame*/	

	v1.id=0x100;   //id for sending dataframe from receiver node at every 50ms 
	v2.id=0x200;   //id for stop sending dataframe from receiver node at every 50ms	
	v1.rtr=v2.rtr=1;  //rtr=1														
	v1.dlc=v2.dlc=4;  //dlc=4														
	while(1){
		if(count1==1){
			IOCLR0=led;
			count1=0;
			can2_tx(v1);
			uart0_tx_string("\r\nRemote frame 1 transmitted\r\n");										

		}
		else if(count1==2){	
			IOSET0=led;
			count1=0;
			can2_tx(v2);
			uart0_tx_string("\r\nRemote frame 2 transmitted\r\n");	
		}																
		if(flag==1){																

			flag=0;																	
			/*when flag=1 data frame receieved from node B. We have to process data and beep the buzzer*/ 
			if(r1.id==0x123){
				int distance;
				distance=r1.byteA;
				//uart0_tx_string("\r\n Distance:");
				//uart0_integer(distance);		
				
				if(distance==0x11){
				    uart0_tx_string("recieved 0x11 \r\n");
					IOSET0=buzz;
					delay_sec(2);
					IOCLR0=buzz;
					
				}
				else if(distance==0x22){
				    uart0_tx_string("recieved 0x22\r\n");
					IOSET0=buzz;
					delay_ms(1);
					IOCLR0=buzz;
					
				} 
				else if(distance==0x33){
				    uart0_tx_string("recieved 0x33\r\n");
					IOSET0=buzz;
					delay_ms(700);
					IOCLR0=buzz;
				
				}
				else if(distance==0x44){
				    uart0_tx_string("recieved 0x44\r\n");
					IOSET0=buzz;
					delay_ms(100);
					IOCLR0=buzz;

				}
				else if(distance==0x55){
				    uart0_tx_string("recieved 0x55\r\n");
					IOSET0=buzz;
					delay_ms(10);
					//while(distance<50);
					IOCLR0=buzz;
				}

			}

		}										   

}	}											   

