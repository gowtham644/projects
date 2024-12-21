#include<lpc21xx.h>
#include<string.h>
#include"LCD.c"
#include"UART.c"
#include"INTR.c"
#define EINT0 0X01
#define EINT1 0X20000000


int main()
{
	PINSEL1|=EINT0;
	PINSEL0|=EINT1;
	LCD_INIT();
	LCD_COMMAND(0X01);
	LCD_STR("!<<HELLO>>!");
	LCD_COMMAND(0XC0);
	LCD_STR("<<TROLLY_N0_1>>");

	VICIntSelect=0;//all intrrupts are irq
	VICVectCntl0=(0x20)|14;
	VICVectAddr0=(int)TOTAL;
	VICVectCntl1=(0x20)|15;
	VICVectAddr1=(int)REMOVE;

	EXTMODE=0X00;
	EXTPOLAR=0X00;

	VICIntEnable=1<<14|1<<15;
	UART_CONFIG();
	while(1)

	{

		for(i=0;i<12;i++)
	{
		rx_bytes[i]=UART_RX();
		UART_TX(rx_bytes[i]);
	}
		if(strstr(rx_bytes,"0600670ECFA0"))

		{

			br_cnt++;
			LCD_COMMAND(0X01);
			LCD_COMMAND(0X80);
			LCD_STR("BREAD QTY:");
			LCD_INTEGER(br_cnt);
			LCD_COMMAND(0XC0);
			LCD_STR("PRICE: ");
			LCD_INTEGER(br_cnt*bread);

		}
		if(strstr(rx_bytes,"0600031D948C"))
		{
			bis_cnt++;
			LCD_COMMAND(0X01);
			LCD_COMMAND(0X80);
			LCD_STR("BISCUT QTY:");
			LCD_INTEGER(bis_cnt);
			LCD_COMMAND(0XC0);
			LCD_STR("PRICE: ");
			LCD_INTEGER(bis_cnt*biscut);
		}
		if(strstr(rx_bytes,"26001EE8ED3D"))
		{
			ch_cnt++;
			LCD_COMMAND(0X01);
			LCD_COMMAND(0X80);
			LCD_STR("CHIPES QTY:");
			LCD_INTEGER(ch_cnt);
			LCD_COMMAND(0XC0);
			LCD_STR("PRICE: ");
			LCD_INTEGER(ch_cnt*chips);
		}
	}
}
