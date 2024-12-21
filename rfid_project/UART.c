void UART_CONFIG(void)
{
	PINSEL0|=0x05; //p0.8tx p0.9rx
	U0LCR=0X83;
	U0DLL=97;
	U0DLM=0;
	U0LCR=0X03;
}
void UART_TX(unsigned char ch)
{
	U0THR=ch;
	while((U0LSR>>5&1)==0);
}
unsigned char UART_RX(void)
{
	while((U0LSR&1)==0);
	return U0RBR;
}
void UART_STR(unsigned char *s)
{
while(*s)
UART_TX(*s++);
//unsigned char *rx_bytes;
//int i;
//	for(i=0;i<15;i++)
//		{
//		rx_bytes[i]=UART_RX();
//		UART_TX(rx_bytes[i]);
//		}
}
