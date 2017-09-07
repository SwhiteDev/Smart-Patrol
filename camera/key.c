/*
 * this is a program check the key_io to take a picture and send it to server
 * it's lib is bcm2385 of raspberry, so you must run it at raspberry
 */

#include <bcm2835.h>

#define PIN0 RPI_GPIO_P1_11

int main(int argc, char **argv)
{
	if(!bcm2835_init()){
		return 1;
	}
	bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);

	while(1){
		bcm2835_gpio_write(PIN, HIGH);
	}
	bcm2835_close();
	return 0;
	
}
