#include "fsl_device_registers.h"
#include <stdint.h>

void software_delay(unsigned long delay)
{
	while (delay > 0) delay--;
}

void main(){
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;

	PORTB_GPCLR = 0x000C0100;
	PORTC_GPCLR = 0x00010100; //portC 0

	GPIOB_PDDR = 0x00000000;
	GPIOC_PDDR = 0x00000001; //output 0

	uint32_t outvalC = 0x00, inval = 0;
	unsigned long Delay = 0x100000;

	while(1){
		software_delay(Delay);
		inval = GPIOB_PDIR & 0x0C; //instant input
		if(inval == 0x04){
			GPIOC_PDOR = 0x00;
		}else{
			GPIOC_PDOR = 0x01;
		}

}
}
