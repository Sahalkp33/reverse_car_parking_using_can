#include<LPC21XX.H>
#include<stdio.h>
#include "headerB.h"

void uart0_init(unsigned int baud)
{
 int a[6]={15,60,30,0,15};
  unsigned int result,pclk;
  pclk=a[VPBDIV]*1000000;
  result=(pclk/(16*baud));
  PINSEL0|=5;
  U0LCR=0X83;
  U0DLL=result&0xff;
  U0DLM=(result>>8)&0xff;
  U0LCR^=(1<<7);
}
#define THRE ((U0LSR>>5)&1)
void uart0_tx(unsigned char data)
{
 U0THR=data;
 while(THRE==0);
}
#define RDR (U0LSR&1)
 unsigned char uart0_rx(void)
{
 while(RDR==0);
 return U0RBR;
}
void uart0_tx_string(char *ptr)
{
 while(*ptr)
 {
  U0THR=*ptr;
  while(THRE==0);
  ptr++;
 }
}
void uart0_rx_string(char *ptr,int len)
{	
 unsigned char i;
 for(i=0;i<len;i++)
 {
   	while(RDR==0);
	ptr[i]=U0RBR;
	if(*ptr=='\r')
	 break;
 }
 ptr[i]='\0';
}
void uart0_integer(int num)
{
  int p[10],i=0;
  while(num>0)
  {
    p[i]=num%10;
	num=num/10;
	i++;
  }
  for(--i;i>=0;i--)
  {
    uart0_tx(p[i]+48);

  }
}
