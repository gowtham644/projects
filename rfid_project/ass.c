#include<lpc21xx.h>
#include<string.h>
#include"LCD.c"
#include"UART.c"
char rx_bytes[12];
int i; 
int main()
{
	LCD_INIT();
	UART_CONFIG();
	LCD_STR("SCAN THE CARD");
	while(1)

	{
		for(i=0;i<12;i++)
	{
		rx_bytes[i]=UART_RX();
		UART_TX(rx_bytes[i]);
	}
		if(strstr(rx_bytes,"0600670ECFA0"))

		{
			LCD_COMMAND(0X01);
			LCD_COMMAND(0X80);
			LCD_STR("HI GOWTHAM");
			LCD_COMMAND(0XC0);
			LCD_STR(rx_bytes);
		}
}
}
