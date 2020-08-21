// fmsd1_ino.cpp
#include	<SPI.h>

void writeSingleCPP( unsigned char adrs, unsigned char data )
{
	digitalWrite(10, LOW);	//	select slave
	SPI.transfer(adrs);
	SPI.transfer(data);
	digitalWrite(10, HIGH);
	delay(1);
}
extern "C" void writeSingle( unsigned char adrs, unsigned char data ){ writeSingleCPP(adrs,data);}
extern "C" void writeBurst( unsigned char adrs, unsigned char* data, int count )
{
	digitalWrite(10, LOW);
	SPI.transfer(adrs);
	for (int i = 0; i<count; i++) {
		SPI.transfer(*(data + i));
	}
	digitalWrite(10, HIGH);
	delay(1);
}
extern "C" void delayMs( int ms ){	delay(ms);}

void initSPI(void)
{
	//	init SPI
	/*
	* Conditions only for Arduino UNO
	*  SPI master
	*  RST_N- Pin9
	*  SS   - Pin10
	*  MOSI - Pin11
	*  MISO - Pin12
	*  SCK  - Pin13
	*/
	pinMode(10, OUTPUT);
	digitalWrite(10, HIGH);
	SPI.setBitOrder(MSBFIRST);
	SPI.setClockDivider(SPI_CLOCK_DIV4);	//	4MHz
	SPI.setDataMode(SPI_MODE0);
	SPI.begin();
}
void initSD1( void )
{
	//	1.	powerOnReset( void );
	pinMode(9, OUTPUT);
	digitalWrite(9, LOW);

	//	2. wait 100usec
	delay(1);

	//	3.	RST_N : high
	digitalWrite(9, HIGH);

	//	4.	DRV_SEL	: low
	writeSingleCPP(29, 0);  //  5v

	//	5.	AP0 : 0
	writeSingleCPP(2, 0x0e);

	//	6.	wait for Quarz stability
	delay(1);

	//	7.	CLKE : "1"
	writeSingleCPP(0, 0x01);

	//	8.	ALRST : low
	writeSingleCPP(1, 0x00);

	//	9.	SFTRST	:	0xa3
	writeSingleCPP(26, 0xa3);
	delay(1);

	//	10.	SFTRST	:	0x00
	writeSingleCPP(26, 0x00);

	//	11.	wait 30msec
	delay(30);

	//	12.	AP1 AP3: "0"
	writeSingleCPP(2, 0x04);

	//	13.	wait 10usec
	delayMicroseconds(10);

	//	14.	AP2: "0"
	writeSingleCPP(2, 0x00);

	writeSingleCPP(25, 0xcc);	//	0[dB]
	writeSingleCPP(27, 0x3f);	//	set itp max
	writeSingleCPP(20, 0x00);	//	set itp on
	writeSingleCPP(3, 0x01);	//	amp gain(6.5[dB])
	writeSingleCPP(9, 0xf8);	//	Sequencer Volume
}