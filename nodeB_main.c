#include <LPC21XX.H>
#include "headerB.h"
can2 r1, send;
u32 flag=0, flag1=0, flag2=0;
int main(){

	VPBDIV=1;  //for ultrasonic
	can2_init();  
	ultra_init();
	en_can2_interruptB();
	uart0_init(9600);
	while(1){

		if(flag==1){
			uart0_integer(flag);
			uart0_tx_string("Remote frame received\r\n");
			flag=0;
			if(r1.id==0x100){
				uart0_tx_string("\r\nRemote 1\r\n");
				while(1){
					u32 distance;
					uart0_tx_string("\r\nDistance: ");
					distance=get_distance();
				//	distance=10;
					uart0_integer(distance);
					if(distance>300 && distance<=400){
					distance=0x11;
				}
				else if(distance>200 && distance<=300){
					distance=0X22;
				} 
				else if(distance>100 && distance<=200){
					distance=0x33;
				}
				else if(distance>=50 && distance<=100){
					 distance=0x44;
				}
				else if(distance<50){
					distance=0x55;
				}
					send.id=0x123;
					send.rtr=0;
					send.dlc=4;
					send.byteA=distance&0x0000ffff;
					can2_tx(send);
					uart0_tx_string("\r\nData frame transmitted\r\n");
					delay_ms(10);
					if(r1.id==0x200){
						uart0_tx_string("\r\nremote 2\r\n");
						break;
				}

			}

		}

	}

}

}

