#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "stdio.h"
char mang[20];
int dem;
void TruyenChuoi(char *str)
{
	while(*str)
	{
		UARTCharPut(UART0_BASE,*str);
		str++;
	}
}
int main(void)
{
	//Buoc 2:
	SysCtlClockSet(SYSCTL_SYSDIV_1| SYSCTL_USE_OSC|SYSCTL_XTAL_8MHZ|SYSCTL_OSC_MAIN);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	//SYSCTL_PERIPH_UART0
	//Buoc 3:
	GPIOPinConfigure(GPIO_PA0_U0RX |GPIO_PA1_U0TX);//
	GPIOPinTypeUART(GPIO_PORTA_BASE,GPIO_PIN_0|GPIO_PIN_1);
	GPIOPinTypeGPIOInput(GPIO_PORTD_BASE,GPIO_PIN_0);
	GPIOPadConfigSet(GPIO_PORTD_BASE,GPIO_PIN_0,GPIO_STRENGTH_4MA,GPIO_PIN_TYPE_STD_WPU);
	//Buoc 4:
	UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(),9600,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |UART_CONFIG_PAR_NONE));
	//UARTCharPut(UART0_BASE,'A');
	//TruyenChuoi("Chao Anh Hoa");
while(1)
{
	if(GPIOPinRead(GPIO_PORTD_BASE,GPIO_PIN_0)==0)
	{
		while(GPIOPinRead(GPIO_PORTD_BASE,GPIO_PIN_0)==0);
		dem++;
		if(dem>15) dem=0;
		sprintf(&mang[0],"So san pham:%d",dem);
		TruyenChuoi(&mang[0]);
		UARTCharPut(UART0_BASE,10);
		UARTCharPut(UART0_BASE,13);
	}
}
}