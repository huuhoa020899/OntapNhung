#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
int x;
void Timer0IntHandler(void)
{
	x= GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_0);
	x^=GPIO_PIN_0;
	GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_0,x);
  TimerIntClear(TIMER0_BASE,TIMER_A); // xóa co ng?t
}
int main(void)
{
	//Buoc3:
	SysCtlClockSet(SYSCTL_SYSDIV_1|SYSCTL_USE_OSC|SYSCTL_XTAL_8MHZ|SYSCTL_OSC_MAIN);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,GPIO_PIN_0);
	//Buoc4:
	TimerConfigure(TIMER0_BASE,TIMER_CFG_32_BIT_PER);
	TimerLoadSet(TIMER0_BASE,TIMER_A,4000);
	TimerIntEnable(TIMER0_BASE,TIMER_TIMA_TIMEOUT);
	//Buoc5:
	IntEnable(INT_TIMER0A);
	IntMasterEnable();
	//Buoc6:
	TimerEnable(TIMER0_BASE,TIMER_A);
	SysCtlDelay(5*2666666);
	TimerLoadSet(TIMER0_BASE,TIMER_A,8000);
while(1)
{
}
}