#ifndef FMSD1_H
#define FMSD1_H

//	public
void initSPI( void );
void initSD1( void );
void delayMs( int ms );
void writeSingle( unsigned char adrs, unsigned char data );
void writeBurst( unsigned char adrs, unsigned char* data, int count );

static const unsigned char REG_TOP_ADRS = 12;
static const unsigned char REG_VOL = 0;
static const unsigned char REG_BLK = 1;
static const unsigned char REG_FNUM = 2;
static const unsigned char REG_CTRL = 3;
static const unsigned char REG_CH_VOL = 4;
static const unsigned char REG_XVB = 5;
static const unsigned char REG_INT = 6;
static const unsigned char REG_FRC = 7;
static const unsigned char REG_MASTER_VOL = 25;
#endif
