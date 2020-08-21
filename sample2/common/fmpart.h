#ifndef FMPART_H
#define FMPART_H
#include	"fmnote.h"
#include	"fmtone.h"
#include	"fmasgn.h"

#define MAX_NOTE_OBJECT 20

//	Part Class
typedef struct _Part Part;
struct _Part{

	ToneData	_tone;
	Note		_note[MAX_NOTE_OBJECT];

	Note*		_topNt;	//	old
	Note*		_endNt;	//	latest

	unsigned char _cc1;
	unsigned char _cc7;
	unsigned char _cc64;
	unsigned short  _pbvalue;	//	0 - 16383
	unsigned char _toneNumber;
};

//	public
extern void Part_init( Part* _this );
extern void Part_note( Part* _this, unsigned char note, unsigned char velocity );
extern void Part_cc( Part* _this, unsigned char ccnum, unsigned char value );
extern void Part_pbend( Part* _this, unsigned char lsb, unsigned char msb );
extern void Part_pc( Part* _this, unsigned char num );
extern void Part_releaseNote( Part* _this, Note* nt);

//	getter
extern unsigned char Part_cc1( Part* _this );
extern unsigned char Part_cc7( Part* _this );
extern unsigned short Part_pb( Part* _this );
extern unsigned char Part_toneNumber( Part* _this );
#endif