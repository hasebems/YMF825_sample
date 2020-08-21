// fmnote.c
#include	"fmtype.h"
#include	"fmnote.h"
#include	"fmpart.h"
#include	"fmtone.h"
#include	"fmasgn.h"

//	Prototype
static void		obtainNecessaryVoice(Note* _this);

//	setter
void Note_setPrevPtr( Note* _this, Note* pn ){ _this->_prevPtr = pn; }
void Note_setNextPtr( Note* _this, Note* nn ){ _this->_nextPtr = nn; }
void Note_setPart( Note* _this, void* pt ){ _this->_parent = pt; }
void Note_setHold( Note* _this, bool hold ){ _this->_hold = hold; }
//	getter
bool Note_isInUse( Note* _this ){ return _this->_inUse; }
bool Note_isKeyOn( Note* _this ){ return _this->_keyon; }
bool Note_isHeld( Note* _this ){ return _this->_hold; }
Note* Note_prevPtr( Note* _this ){ return _this->_prevPtr;}
Note* Note_nextPtr( Note* _this ){ return _this->_nextPtr;}
unsigned char Note_note(Note* _this){ return _this->_note; }
unsigned char Note_velocity(Note* _this){ return _this->_velocity; }

void Note_init( Note* _this )
{
	_this->_prevPtr = 0;
	_this->_nextPtr = 0;
	_this->_inUse = false;
	_this->_keyon = false;
	_this->_hold = false;
	_this->_note = 0;
	_this->_parent = 0;
	_this->_velocity = 0;
}

bool Note_keyon( Note* _this, ToneData* newTone, unsigned char newNote, unsigned char newVelocity )
{
	if ( _this->_parent == FMNULL){ return false; }

	_this->_note = newNote;
	_this->_velocity = newVelocity;

	//	obtain necessary voices
	obtainNecessaryVoice( _this);

	Fmvoice_keyon(_this->_vc, _this, _this->_parent, newTone, newNote, newVelocity);

	//	set variables
	_this->_keyon = true;
	_this->_inUse = true;
	_this->_hold = false;
	return true;
}
void Note_keyoff( Note* _this )
{
	Fmvoice_keyoff( _this->_vc );
	_this->_keyon = false;
	_this->_hold = false;
}
void Note_damp( Note* _this )
{
	if (_this->_vc != FMNULL) {
		Asgn_releaseParticularVc(_this->_vc);
	}
}
void Note_releaseVc( Note* _this, Fmvoice* rlsVc )
{
	if ( rlsVc == _this->_vc ) {
		_this->_vc = FMNULL;
	}
	Note_release(_this);
}
void Note_release( Note* _this )
{
	if (_this->_parent == FMNULL){ return; }
	Part_releaseNote((Part*)_this->_parent,_this);
	_this->_prevPtr = _this->_nextPtr = FMNULL;
	_this->_keyon = false;
	_this->_inUse = false;
	_this->_hold = false;
}
void Note_chgVibDpt( Note* _this )
{
	if (_this->_parent == FMNULL){ return; }
	Part* pt = (Part*)_this->_parent;
	if (pt == FMNULL) { return; }
	Fmvoice_chgVibDpt(_this->_vc, Part_cc1(pt));
}
void Note_chgPit( Note* _this )
{
	if (_this->_parent == FMNULL) { return; }
	Part* pt = (Part*)_this->_parent;
	if (pt == FMNULL) { return; }
	Fmvoice_chgPit(_this->_vc, Part_pb(pt));
}
static void obtainNecessaryVoice(Note* _this)
{
	while (Asgn_chkEmpty() != true) {
		Asgn_releaseOneVc();
	} 
	_this->_vc = Asgn_getEmptyVc();
}