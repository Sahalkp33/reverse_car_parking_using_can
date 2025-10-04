/*can2_receiver_interrupt_nodeB*/
#include <LPC21XX.H>
#include "headerB.h"
extern can2 r1;
extern u32 flag, flag1, flag2;
void can2_rx_handlerB(void)__irq

{

	flag=1;   //set flag if remote frame
	r1.id=C2RID;   //get the identifier of the data/remote frame sent by node B
	r1.dlc=(C2RFS>>16)&0x0f;   //get the dlc of the data/remote frame sent by node B
	r1.rtr=(C2RFS>>30)&1;   //get the rtr bit of the data/remote frame sent by node B
//	if(r1.rtr==1){

//		if(r1.id==0x100) { 

//			flag1=1;  //ID for sending df --> 100 so set flag

//		}

//		if(r1.id==0x200)   {

//			flag2=1;  //ID for stop sending df --> 200 so set flag2

//		}

//	}

	C2CMR=(1<<2);  //Release receiver buffer

	VICVectAddr=0;

}

void en_can2_interruptB(void){

	//VICIntSelect=0;
	VICVectAddr4=(u32)can2_rx_handlerB;
	VICVectCntl4=27|(1<<5);
	VICIntEnable=(1<<27);
	C2IER=1;  //Enable CAN2 Interrupt --> rx interrupt
}
