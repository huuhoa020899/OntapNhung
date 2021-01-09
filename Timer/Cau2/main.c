#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
void Timer1IntHandler(void)
{
	int x;
	x=GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_0);
	x^=GPIO_PIN_0;
	GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_0,x);
	TimerIntClear(TIMER1_BASE,TIMER_A); // xóa co ng?t
}
int main(void)
{
	//Buoc3:
	SysCtlClockSet(SYSCTL_SYSDIV_1|SYSCTL_USE_OSC|SYSCTL_XTAL_8MHZ|SYSCTL_OSC_MAIN);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,GPIO_PIN_0);
	//Buoc4:
	TimerConfigure(TIMER1_BASE,TIMER_CFG_32_BIT_PER);
	TimerLoadSet(TIMER1_BASE,TIMER_A,2000);
	TimerIntEnable(TIMER1_BASE,TIMER_TIMA_TIMEOUT);
	//Buoc5:
	IntEnable(INT_TIMER1A);
	IntMasterEnable();
	//Buoc6:
	TimerEnable(TIMER1_BASE,TIMER_A);
	SysCtlDelay(4*2666666);
	TimerLoadSet(TIMER1_BASE,TIMER_A,8000);
while(1)
{
}
}