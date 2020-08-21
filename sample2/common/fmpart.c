//	fmpart.c
#include	"fmtype.h"
#include	"fmpart.h"
#include	"fmsd1.h"
#include	"fmasgn.h"
#include	"fmtone.h"

//	Prototype
static Note* getNote(Part* _this);

//	getter
unsigned char Part_cc1(Part* _this){ return _this->_cc1; }
unsigned char Part_cc7(Part* _this){ return _this->_cc7; }
unsigned short Part_pb(Part* _this){ return _this->_pbvalue; }
unsigned char Part_toneNumber(Part* _this){ return _this->_toneNumber; }

void Part_init( Part* _this )
{
	int i;

	Asgn_init();
	Tone_init();

	_this->_topNt = 0;
	_this->_endNt = 0;
	_this->_cc1 = 0;
	_this->_cc7 = 100;
	_this->_cc64 = 0;
	_this->_pbvalue = 0x2000;
	_this->_toneNumber = 0;

	for ( i=0; i<MAX_NOTE_OBJECT; i++ ){
		Note_init(&_this->_note[i]);
		Note_setPart(&_this->_note[i], (void*)_this);
	}
}
void Part_note( Part* _this, unsigned char note, unsigned char velocity )
{
	if ( velocity != 0 ){
		//	keyon
		Note* newNt = getNote(_this);
		if ( Note_keyon(newNt,&_this->_tone,note,velocity) == true ){
			if ( _this->_endNt != FMNULL ){
				Note_setNextPtr( _this->_endNt,newNt );
				Note_setPrevPtr( newNt,_this->_endNt );
			}
			_this->_endNt = newNt;
			if ( _this->_topNt ==FMNULL ){
				_this->_topNt = newNt;
			}
		}
	}
	else {
		//	keyoff
		Note* nt = _this->_topNt;
		while( nt != 0 ){
			if (( Note_note(nt) == note ) &&
				( Note_isKeyOn(nt) == true ) &&
				( Note_isHeld(nt) == false )){
				if ( _this->_cc64 < 64 ){
					Note_keyoff(nt);
				}
				else {
					Note_setHold(nt,true);
				}
				break;
			}
			nt = Note_nextPtr(nt);
		}
	}
}
void Part_releaseNote( Part* _this, Note* nt )
{
	Note* prevPtr = Note_prevPtr(nt);
	if ( _this->_endNt == nt ){
		_this->_endNt = prevPtr;
	}
	if ( prevPtr != FMNULL ){
		Note_setNextPtr(prevPtr, Note_nextPtr(nt));
	}

	Note* nextPtr = Note_nextPtr(nt);
	if ( _this->_topNt == nt ){
		_this->_topNt = nextPtr;
	}
	if ( nextPtr != FMNULL ){
		Note_setPrevPtr(nextPtr, Note_prevPtr(nt));
	}
}
void Part_cc( Part* _this, unsigned char ccnum, unsigned char value )
{
	Note* nt = _this->_topNt;

	//	Limit
	if (value > 127) { value = 127; }

	switch (ccnum) {
		case 1: {
			_this->_cc1 = value;
			while ( nt != FMNULL ) {
				Note_chgVibDpt(nt);
				nt = Note_nextPtr(nt);
			}
			break;
		}
		case 7: {
			_this->_cc7 = value;
			writeSingle( REG_MASTER_VOL, (value<<1)&0xfc );
			break;
		}
		case 64: {
			_this->_cc64 = value;
			if ( value < 64 ){
				while ( nt != FMNULL ) {
					if ( Note_isHeld(nt) == true ){
						Note_keyoff(nt);
					}
					nt = Note_nextPtr(nt);
				}
			}
			break;
		}
		default: break;
	}
}
void Part_pc( Part* _this, unsigned char num )
{
	Note* nt = _this->_topNt;
	Note* nextNt;

	//	Damp
	while ( nt != FMNULL ) {
		nextNt = Note_nextPtr(nt);
		Note_damp(nt);
		nt = nextNt;
	}

	_this->_toneNumber = num;
}
void Part_pbend( Part* _this, unsigned char lsb, unsigned char msb )
{
	Note* nt = _this->_topNt;
	_this->_pbvalue = (msb<<7)|(lsb&0x7f);
	while ( nt != FMNULL ) {
		Note_chgPit(nt);
		nt = Note_nextPtr(nt);
	}
}
static Note* getNote( Part* _this )
{
	int	i;
	Note* newNt = 0;
	for ( i=0; i<MAX_NOTE_OBJECT; i++ ){
		newNt = &(_this->_note[i]);
		if ( Note_isInUse(newNt) ==  false ){
			return newNt;
		}
	}
	//	if nothing
	newNt = _this->_topNt;
	Note_damp(newNt);
	return newNt;
}
