#include<lpc21xx.h>
#define mo1 1<<10
#define mo2 1<<11
#define led 1<<17
typedef unsigned int u32;
typedef struct can2
{
	u32 id;
	u32 rtr;
	u32 dlc;
	u32 bytea;
	u32 byteb;
}can_msg;

void can_init(void);
void can_rx(can_msg *m1);
void delay_ms(unsigned int ms);

void motor_clock(void)
{
//	IOCLR0=led;
	IOSET0=mo1;
	IOCLR0=mo2;
}
void motor_anti(void)
{
//    IOSET0=led;
	IOSET0=mo2;
	IOCLR0=mo1;
}
void motor_off(void)
{
	IOSET0|=mo1|mo2;
}
void wiper(void)
{
	int i;
	for(i=0;i<5;i++)
	
	{	motor_clock();
		delay_ms(500);
		motor_anti();
		delay_ms(500);
	}

		motor_off();
		
}

int main()
{	
	can_msg m1;
//	int flag=0;
	IODIR0|=mo1|mo2;
	IOSET0=mo1|mo2;
	motor_off();
	IOCLR0|=mo1|mo2;
	can_init();
	while(1)
	{		
		can_rx(&m1);
			if(m1.id==0x03)
			{	
			 wiper();
			}	
	}
}
void can_init(void)
{
	
	PINSEL1|=0X00014000;
	VPBDIV=1;
	C2MOD=0X01;
	AFMR=0X02;
	C2BTR=0X001C001D;
	C2MOD=0X00;
}
void can_rx(can_msg *m1)
{
	while((C2GSR&0x1)==0);
	m1->id=C2RID;
	m1->dlc=(C2RFS>>16)&0xF;
	m1->rtr=(C2RFS>>30)&0x1;
	if(m1->rtr==0)
	{ 
		m1->bytea=C2RDA;
		m1->byteb=C2RDB;
	}
	C2CMR=(1<<2);
}

void delay_ms(unsigned int ms)
{

	T0PR=60000-1;

	T0TCR=0x01;

	while(T0TC<ms);
	T0TCR=0x03;

	T0TCR=0x00;

}
