//#define sw1 14
//#define sw2 15
int br_cnt=0,bis_cnt=0,ch_cnt=0,total=0,bread=40,biscut=10,chips=15;
char rx_bytes[12],i;
void TOTAL(void)__irq
{
	delay_ms(250);
	total=((bread*br_cnt)+(biscut*bis_cnt)+(chips*ch_cnt));
	EXTINT=0X01;
	LCD_COMMAND(0X01);
	LCD_COMMAND(0X80);
	LCD_STR("TOTAL :");
	LCD_INTEGER(total);
	LCD_COMMAND(0XC0);
	LCD_STR("**THANK YOU**");
	bread=0,biscut=0,chips=0,br_cnt=0,bis_cnt=0,ch_cnt=0,total=0;
	VICVectAddr=0;
}
void REMOVE(void)__irq
{
	delay_ms(250);
	
	LCD_COMMAND(0X01);
	LCD_COMMAND(0X80);
	LCD_STR("REMOVING MODE");
	LCD_COMMAND(0XC0);
	LCD_STR("SCAN THE ITEM");
	 EXTINT=0X02;
	while(1)
	{
		for(i=0;i<12;i++)
	{
		rx_bytes[i]=UART_RX();
		UART_TX(rx_bytes[i]);
	}
		if((strcmp(rx_bytes,"0600670ECFA0")==0)&&(br_cnt!=0))
		{
			br_cnt--;
			LCD_COMMAND(0X01);
			LCD_COMMAND(0X80);
 			LCD_STR("BREAD QTY:");
			LCD_INTEGER(br_cnt);
			LCD_COMMAND(0XC0);
			LCD_STR("PRICE: ");
			LCD_INTEGER(br_cnt*bread);break;
		}
		if((strcmp(rx_bytes,"0600031D948C")==0)&&(bis_cnt!=0))
		{
			bis_cnt--;
			LCD_COMMAND(0X01);
			LCD_COMMAND(0X80);
			LCD_STR("BISCUTS QTY:");
			LCD_INTEGER(bis_cnt);
			LCD_COMMAND(0XC0);
			LCD_STR("PRICE: ");
			LCD_INTEGER(bis_cnt*biscut);break;
		}
		if((strcmp(rx_bytes,"26001EE8ED3D")==0)&&(ch_cnt!=0))
		{
			ch_cnt--;
			LCD_COMMAND(0X01);
			LCD_COMMAND(0X80);
			LCD_STR("CHIPES QTY:");
			LCD_INTEGER(ch_cnt);
			LCD_COMMAND(0XC0);
			LCD_STR("PRICE: ");
			LCD_INTEGER(ch_cnt*chips);break;
		}
	
	}
		LCD_STR("PRODUCT IS REMOVED");
		VICVectAddr=0;	
}


