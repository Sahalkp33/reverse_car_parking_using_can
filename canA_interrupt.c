/*CAN2_interrupt_nodeA.c*/
#include <LPC21XX.H>
#include "headerA.h"
extern can2 r1;
extern u8 flag;
void can2_rx_handlerA(void)__irq
{
	flag=1;
	r1.id=C2RID;  //get the identifier of the data/remote frame sent by node B
	r1.dlc=(C2RFS>>16)&0x0f;  //get the dlc of the data/remote frame sent by node B
	r1.rtr=(C2RFS>>30)&1;  //get rtr value sent by node B
	if(r1.rtr==0){  //if data frame
		r1.byteA=C2RDA;  //lower 4 bytes
		r1.byteB=C2RDB;  //higher 4 bytes
	}
	C2CMR=(1<<2);  //release reveiver buffer
	VICVectAddr=0;
}
void en_can2_interruptA(void){
	/*init_vic*/
	VICIntSelect=0;
	VICVectCntl2=27|(1<<5);
	VICVectAddr2=(u32)can2_rx_handlerA;
	VICIntEnable|=(1<<27);
	/*Enable can2 interrupt*/
	C2IER=1;  //enable rx interrupt
}
