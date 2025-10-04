/*CAN2_NodeA_Driver*/


#include <LPC21XX.H>
#include "headerB.h"

void can2_init(void){
	PINSEL1|=0x00014000;   // CAN2 p0.24-->Tx, p0.23-->Rx
	VPBDIV=1;   //pclk=60MHz
	C2MOD=1;  //Select RESET mode
	AFMR=0x02;  //AccBP=1-->Accepting all incoming messages
	C2BTR=0x001C001D;  //Select 125kbps baudrate
	C2MOD=0;   //Cancel reset mode

}

#define TCS ((C2GSR>>3)&1) //In CGSR reg. 3rd bit is transmit complete status, SET when txmn completed
void can2_tx(can2 v){
	C2TID1=v.id;  //storing identifier into TID regr.
	C2TFI1=(v.dlc)<<16;	 //storing dlc into TFI regr.
	if(v.rtr==0){  //if data frame
		C2TDA1=v.byteA;  //storing lower bytes to data regr.
		C2TDB1=v.byteB;  //storing higher bytes to data regr.
	}
	else  //if remote frame
		C2TFI1|=(1<<30);   //setting 30th bit i.e., rtr bit in TFI regr.
	C2CMR=0x21;  //Start TXmission and selet Tx Buffer
	while(TCS==0);   //checking if data/remote frame successfully transmitted
}

#define RBS (C2GSR&1)  //In CGSR reg. 1st bit is receiver buffer status, SET when receiving completed

void can2_rx(can2 *ptr){

	while(RBS==0);   //checking if data/remote frame successfully received

	ptr->id=C2RID;	 //receive id from RID regr.

	ptr->dlc=((C2RFS>>16)&0x0f);  //dlc from 16-19 bit of RFS regr.

	ptr->rtr=((C2RFS>>30)&1);   //rtr from 30th bit of RFS regr.

	if(ptr->rtr==0){  //if data frame then only receive data value

		ptr->byteA=C2RDA;  //lower bytes from RDA regr.

		ptr->byteB=C2RDA;  //higher bytes from RDA regr.								 

	}

	C2CMR=(1<<2);   //Release Receiver Buffer

} 
