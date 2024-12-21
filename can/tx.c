#include<lpc21xx.h>
#include"LCD.c"
#define sw1 14
#define sw2 15
#define sw3 16
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
void can_tx(can_msg m1);
//int flag=0;
int main()
{
	can_msg m1;
	LCD_INIT();
	can_init();
	m1.rtr=0;
	m1.dlc=4;
	LCD_COMMAND(0X80);
	LCD_STR("BODY CONTROL");
	while(1)
	{
		if(((IOPIN0>>sw1)&1)==0)
		{
			LCD_COMMAND(0X01);
			delay_ms(300);
			LCD_COMMAND(0X80);
			LCD_STR("BODY CONTROL");
			LCD_COMMAND(0XC0);
	        LCD_STR("LEFT INDICATOR");
			m1.id=0x01;
			can_tx(m1);
		}
		if(((IOPIN0>>sw2)&1)==0)
		{
			LCD_COMMAND(0X01);
			delay_ms(300);
			LCD_COMMAND(0X80);
			LCD_STR("BODY CONTROL");
			LCD_COMMAND(0XC0);
	        LCD_STR("RIGHT INDICATOR");
			m1.id=0x02;
			can_tx(m1);
		}
		if(((IOPIN0>>sw3)&1)==0)
		{
			LCD_COMMAND(0X01);
			delay_ms(300);
			LCD_COMMAND(0X80);
			LCD_STR("BODY CONTROL");
			LCD_COMMAND(0XC0);
	        LCD_STR("WIPER ON");
			m1.id=0x03;
			can_tx(m1);
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
void can_tx(can_msg m1)
{
	C2TID1=m1.id;
		C2TFI1=(m1.dlc<<16);
		if(m1.rtr==0)
		{
			C2TFI1&=~(1<<30);
			C2TDA1=m1.bytea;
			C2TDB1=m1.byteb;
		}
		else
		{
			C2TFI1|=(1<<30);
		}
		C2CMR=(1<<0)|(1<<5);
		while((C2GSR&(1<<3))==0);
}




