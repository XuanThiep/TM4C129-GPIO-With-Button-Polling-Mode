#include <stdbool.h>
#include <stdint.h>
#include "driverlib/inc/hw_memmap.h"
#include "driverlib/inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"



int main(void)
{
	/* Configure system clock using external clock and PLL */
	SysCtlClockFreqSet(SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480,
			120000000);

	/* Enable GPIO Peripheral Clock */
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);

	/* Configure Led as gpio output */
	GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1);

	/* Turn off all led */
	GPIOPinWrite(GPIO_PORTN_BASE,GPIO_PIN_0 | GPIO_PIN_1 ,0x00);

	/* Configure Butoon as gpio input with pull up resistor */
	GPIODirModeSet(GPIO_PORTJ_BASE, GPIO_PIN_0 | GPIO_PIN_1,GPIO_DIR_MODE_IN);
	GPIOPadConfigSet(GPIO_PORTJ_BASE, GPIO_PIN_0 | GPIO_PIN_1,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);

	while(1)
	{
		/* Check button 1 */
		if(GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_0) == 0x00)
		{
			GPIOPinWrite(GPIO_PORTN_BASE,GPIO_PIN_0 ,0xff);
		}
		else
		{
			GPIOPinWrite(GPIO_PORTN_BASE,GPIO_PIN_0 ,0x00);
		}

		/* Check button 2 */
		if(GPIOPinRead(GPIO_PORTJ_BASE,GPIO_PIN_1) == 0x00)
		{
			GPIOPinWrite(GPIO_PORTN_BASE,GPIO_PIN_1 ,0xff);
		}
		else
		{
			GPIOPinWrite(GPIO_PORTN_BASE,GPIO_PIN_1 ,0x00);
		}
	}
}
