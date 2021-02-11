// fmsd1_raspi.c
#include <bcm2835.h>
#include <stdio.h>
#include <time.h>

#define PIN_OUT RPI_V2_GPIO_P1_22
#define RST	RPI_V2_GPIO_P1_36

void ss(int en)
{
	if (en == HIGH){ bcm2835_gpio_write(PIN_OUT, HIGH);}
	else { bcm2835_gpio_write(PIN_OUT, LOW);}
}
void writeSingle( unsigned char adrs, unsigned char data )
{
	ss(LOW);
	bcm2835_spi_transfer(adrs);
	bcm2835_spi_transfer(data);
	ss(HIGH);
}
void writeBurst( unsigned char adrs, unsigned char* data, int count )
{
	int i;
	ss(LOW);
	bcm2835_spi_transfer(adrs);
	for (i = 0; i<count; i++) {
		bcm2835_spi_transfer(*(data + i));
	}
	ss(HIGH);
}
void delayMs( int ms )
{
	struct timespec ts;
	ts.tv_sec = 0;
	ts.tv_nsec = 1000000 * ms;
	nanosleep(&ts, 0);
}
void initSPI(void)
{
	if (!bcm2835_init())
	{
		printf("bcm2835_spi_begin failed. Are you running as root??\n");
		return;
	}

	bcm2835_spi_begin();
	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_256); // The default

	bcm2835_gpio_fsel(PIN_OUT, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(RST , BCM2835_GPIO_FSEL_OUTP);

	ss(HIGH);
	// change to 3.3V for reading value
	writeSingle(0x1d, 1);
}
void initSD1( void )
{
	//	1.	powerOnReset( void );
	bcm2835_gpio_write(RST, LOW);

	//	2. wait 100usec
	delayMs(1);

	//	3.	RST_N : high
	bcm2835_gpio_write(RST, HIGH);

	//	4.	DRV_SEL	: low
	writeSingle(29, 1);  //  3.3v

							 //	5.	AP0 : 0
	writeSingle(2, 0x0e);

	//	6.	wait for Quarz stability
	delayMs(1);

	//	7.	CLKE : "1"
	writeSingle(0, 0x01);

	//	8.	ALRST : low
	writeSingle(1, 0x00);

	//	9.	SFTRST	:	0xa3
	writeSingle(26, 0xa3);
	delayMs(1);

	//	10.	SFTRST	:	0x00
	writeSingle(26, 0x00);

	//	11.	wait 30msec
	delayMs(30);

	//	12.	AP1 AP3: "0"
	writeSingle(2, 0x04);

	//	13.	wait 10usec
	delayMicroseconds(10);

	//	14.	AP2: "0"
	writeSingle(2, 0x00);

	writeSingle(25, 0x81);	//	-18[dB]
	writeSingle(27, 0x3f);	//	set itp max
	writeSingle(20, 0x00);	//	set itp on
	writeSingle(3, 0x01);	//	amp gain(6.5[dB])
	writeSingle(9, 0xcc);	//	0[dB] Sequencer Volume
}
void powerDown( void )
{
	//	1.	damp

	//	2.	mute

	//	3.	AP3,2,1: "0"
    writeSingle(2,0x01);

	//	4.	ALRST: "1"
    writeSingle(1,0x80);

	//	5.	CLKE: "0"
    writeSingle(0,0x00);
}