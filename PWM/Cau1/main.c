#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "inc/hw_pwm.h"
#include "driverlib/pwm.h"
long x;
int main(void)
{//Buoc2:
	SysCtlClockSet( SYSCTL_SYSDIV_1|SYSCTL_USE_OSC|SYSCTL_XTAL_8MHZ|SYSCTL_OSC_MAIN);
	SysCtlPWMClockSet( SYSCTL_PWMDIV_1);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM);
 //Buoc3:
	GPIOPinTypePWM(GPIO_PORTD_BASE,GPIO_PIN_0);
	GPIOPinTypeGPIOInput(GPIO_PORTA_BASE,GPIO_PIN_0);
	GPIOPinTypeGPIOInput(GPIO_PORTA_BASE,GPIO_PIN_1);
	GPIOPadConfigSet(GPIO_PORTA_BASE,GPIO_PIN_0|GPIO_PIN_1,GPIO_STRENGTH_4MA,GPIO_PIN_TYPE_STD_WPU);
 //Buoc4:
	PWMGenConfigure(PWM_BASE, PWM_GEN_0,PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
	PWMGenPeriodSet(PWM_BASE, PWM_GEN_0, 40);
	PWMPulseWidthSet(PWM_BASE, PWM_OUT_0, 20);
	PWMOutputState(PWM_BASE, (PWM_OUT_0_BIT | PWM_OUT_1_BIT), true);
	PWMGenEnable(PWM_BASE, PWM_GEN_0);
while(1)
{  x=GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_0|GPIO_PIN_1); 
	if((GPIO_PIN_0&x)==0)
	{
		PWMPulseWidthSet(PWM_BASE, PWM_OUT_0, 16);
	}
	else if((GPIO_PIN_1&x)==0)
	{
		PWMPulseWidthSet(PWM_BASE, PWM_OUT_0, 24);
	}
}
}