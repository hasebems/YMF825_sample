//	fmvoice.c
#include	"fmtype.h"
#include	"fmvoice.h"
#include	"fmtone.h"
#include	"fmnote.h"
#include	"fmsd1.h"
#include	"fmpart.h"
#include 	"fmboard.h"

//	setter
void Fmvoice_setVoiceNum( Fmvoice* _this, unsigned char vn ){ _this->_vnum = vn; }
void Fmvoice_setNextVc( Fmvoice* _this, Fmvoice* vc ){ _this->_nextVc = vc; }

//	getter
unsigned char Fmvoice_vnum( Fmvoice* _this ){ return _this->_vnum; }
bool Fmvoice_isKeyon( Fmvoice* _this ){ return _this->_keyon;}
Fmvoice* Fmvoice_nextVc( Fmvoice* _this ){ return _this->_nextVc; }

#ifdef ARDUINO
static const unsigned short PROGMEM tPitTbl[256] = {
#else
static const unsigned short tPitTbl[256] = {
#endif
	256,257,259,260,262,263,264,266,267,269,270,272,273,275,276,278,
	279,281,282,284,285,287,288,290,292,293,295,296,298,300,301,303,
	304,306,308,309,311,313,314,316,318,320,321,323,325,327,328,330,
	332,334,336,337,339,341,343,345,347,349,350,352,354,356,358,360,
	362,364,366,368,370,372,374,376,378,380,382,384,386,388,391,393,
	395,397,399,401,403,406,408,410,412,415,417,419,421,424,426,428,
	431,433,435,438,440,442,445,447,450,452,454,457,459,462,464,467,
	470,472,475,477,480,482,485,488,490,493,496,498,501,504,506,509,
	512,515,518,520,523,526,529,532,535,538,540,543,546,549,552,555,
	558,561,564,567,571,574,577,580,583,586,589,593,596,599,602,606,
	609,612,616,619,622,626,629,632,636,639,643,646,650,653,657,660,
	664,668,671,675,679,682,686,690,693,697,701,705,709,712,716,720,
	724,728,732,736,740,744,748,752,756,760,764,769,773,777,781,785,
	790,794,798,803,807,811,816,820,825,829,834,838,843,847,852,856,
	861,866,870,875,880,885,890,894,899,904,909,914,919,924,929,934,
	939,944,949,954,960,965,970,975,981,986,991,997,1002,1007,1013,1023
};
#ifdef ARDUINO
static const unsigned short PROGMEM tFreq[240] = {
#else
static const unsigned short tFreq[240] = {
#endif
	347,348,349,350,351,352,353,354,355,356,	357,358,359,360,361,362,363,365,366,367,
	368,369,370,371,372,373,374,375,376,377,	378,380,381,382,383,384,385,386,387,388,
	390,391,392,393,394,395,396,397,399,400,	401,402,403,404,406,407,408,409,410,412,
	413,414,415,416,417,419,420,421,422,424,	425,426,427,428,430,431,432,433,435,436,
	437,439,440,441,442,444,445,446,447,449,	450,451,453,454,455,457,458,459,461,462,
	463,465,466,467,469,470,471,473,474,475,	477,478,480,481,482,484,485,487,488,489,
	491,492,494,495,496,498,499,501,502,504,	505,507,508,510,511,513,514,515,517,518,
	520,521,523,524,526,528,529,531,532,534,	535,537,538,540,541,543,545,546,548,549,
	551,552,554,556,557,559,561,562,564,565,	567,569,570,572,574,575,577,579,580,582,
	584,585,587,589,590,592,594,596,597,599,	601,602,604,606,608,609,611,613,615,617,
	618,620,622,624,626,627,629,631,633,635,	636,638,640,642,644,646,648,649,651,653,
	655,657,659,661,663,665,667,668,670,672,	674,676,678,680,682,684,686,688,690,692
};
void Fmvoice_init( Fmvoice* _this )
{
	_this->_keyon = (false);
	_this->_nextVc = FMNULL;
}
void Fmvoice_keyon( Fmvoice* _this, void* nt, void* pt, void* tn, unsigned char note, unsigned char vel )
{
	Part* ptp = (Part*)pt;

	_this->_parent = nt;
	_this->_keyon = true;
	_this->_nextVc = FMNULL;
	_this->_tone = Part_toneNumber(ptp);

	//	set voice number
	writeSingle( 11, _this->_vnum );

	//	Damp
	writeSingle( REG_TOP_ADRS+REG_CTRL, 0x30 );

	//	FNUM,BLOCK
	Fmvoice_setBasicPit( _this, note );

	//	Vol
	writeSingle( REG_TOP_ADRS+REG_VOL, vel&0xfc );

	//	ChVol
	writeSingle( REG_TOP_ADRS+REG_CH_VOL, 0x71 );

	//	XVB
	Fmvoice_chgVibDpt(_this, Part_cc1(ptp));

	//	INT, FRAC
	Fmvoice_chgPit(_this, Part_pb(ptp));

	//	KeyOn, ToneNum
	writeSingle( REG_TOP_ADRS+REG_CTRL, 0x40 + _this->_tone );
}
void Fmvoice_keyoff( Fmvoice* _this )
{
	_this->_keyon = false;
	writeSingle( 11, _this->_vnum );
	writeSingle( REG_TOP_ADRS+REG_CTRL, _this->_tone );
}
void Fmvoice_release( Fmvoice* _this )
{
	_this->_keyon = false;
	if ( _this->_parent != FMNULL ){
		Note* nt = (Note*)_this->_parent;
		Note_releaseVc(nt,_this);
	}
	_this->_nextVc = FMNULL;

	writeSingle( 11, _this->_vnum );
	writeSingle( REG_TOP_ADRS+REG_CTRL, 0x30 );
}
void Fmvoice_chgPit( Fmvoice* _this, unsigned short pb )
{
	unsigned char reg[2];
	unsigned char pit = pb/64;
#ifdef ARDUINO
	unsigned short pitTableData = pgm_read_word_near(tPitTbl + pit);
	reg[1] = (unsigned char)((pitTableData<<1) & 0x007e);
	reg[0] = (unsigned char)(((pitTableData<<2) & 0x1f00)>>8);
#else
	reg[1] = (unsigned char)((tPitTbl[pit]<<1) & 0x007e);
	reg[0] = (unsigned char)(((tPitTbl[pit]<<2) & 0x1f00)>>8);
#endif

	writeSingle( 11, _this->_vnum );
	writeSingle( REG_TOP_ADRS+REG_INT, reg[0] );
	writeSingle( REG_TOP_ADRS+REG_FRC, reg[1] );
}
void Fmvoice_chgVibDpt( Fmvoice* _this, unsigned char vibDpt )
{
	vibDpt = vibDpt >>4;
	if ( vibDpt == 0 ){ vibDpt = 1;}
	writeSingle( 11, _this->_vnum );
	writeSingle( REG_TOP_ADRS+REG_XVB, vibDpt );
}
void Fmvoice_setBasicPit( Fmvoice* _this, unsigned char note )
{
	signed short realNote = note;
	while ( realNote > 128 ){ realNote -= 12;}
	while ( realNote < 0 ){ realNote += 12;}

	int tblIndex = (realNote % 12) * 20;

	unsigned char reg[2];
#ifdef ARDUINO
	unsigned short fr = pgm_read_word_near(tFreq + tblIndex);
#else
	unsigned short fr = tFreq[tblIndex];
#endif
	unsigned char oct = realNote/12 - 1;
	reg[0] = (unsigned char)(((fr & 0x0380)>>4) | oct);
	reg[1] = (unsigned char)(fr & 0x007f);

	writeSingle( 11, _this->_vnum );
	writeSingle( REG_TOP_ADRS+REG_BLK, reg[0] );
	writeSingle( REG_TOP_ADRS+REG_FNUM, reg[1] );
}