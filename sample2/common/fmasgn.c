//	fmasgn.c
#include "fmtype.h"
#include "fmasgn.h"
#include "fmvoice.h"

//	Variable
static Fmvoice	_fmvc[MAX_FM_VOICE];
static Fmvoice*	_firstEmptyVc;		//	old
static Fmvoice*	_lastEmptyVc;		//	new
static Fmvoice*	_firstOccupiedVc;	//	old
static Fmvoice*	_lastOccupiedVc;	//	new

//	Prototype
static void	setToEmptyList( Fmvoice* prevVc, Fmvoice* rlsVc );

//	setter
void Asgn_setFirstEmptyVc( Fmvoice* vc ){ _firstEmptyVc = vc; }
void Asgn_setLastEmptyVc( Fmvoice* vc ){ _lastEmptyVc = vc; }

//	getter
Fmvoice* Asgn_voice( int num ){ return &(_fmvc[num]); }
Fmvoice* Asgn_firstEmptyVc( void ){ return _firstEmptyVc; }
Fmvoice* Asgn_lastEmptyVc( void ){ return _lastEmptyVc; }

void Asgn_init( void )
{
	int		i;

	for ( i=0; i<MAX_FM_VOICE; i++) {
		Fmvoice_init(&_fmvc[i]);
	}

	_firstOccupiedVc = 0;
	_lastOccupiedVc = 0;

	for ( i=0; i<MAX_FM_VOICE-1; i++ ){
		Fmvoice_setVoiceNum(&_fmvc[i], i);
		Fmvoice_setNextVc(&_fmvc[i], &_fmvc[i + 1]);
	}

	//	for No.MAX_FM_VOICE-1
	Fmvoice_setVoiceNum(&_fmvc[MAX_FM_VOICE - 1], MAX_FM_VOICE - 1);
	Fmvoice_setNextVc(&_fmvc[MAX_FM_VOICE - 1], FMNULL);

	_firstEmptyVc = &_fmvc[0];
	_lastEmptyVc = &_fmvc[MAX_FM_VOICE-1];
}
bool Asgn_chkEmpty( void )
{
	if ( _firstEmptyVc == FMNULL ){ return false; }
	else { return true; }
}
Fmvoice* Asgn_getEmptyVc( void )
{
	if ( _firstEmptyVc != FMNULL ){
		Fmvoice* ret = _firstEmptyVc;
		_firstEmptyVc = Fmvoice_nextVc(_firstEmptyVc);
		if ( _lastOccupiedVc != FMNULL ){
			Fmvoice_setNextVc(_lastOccupiedVc, ret);
		}
		_lastOccupiedVc = ret;
		if ( _firstOccupiedVc == FMNULL ){
			_firstOccupiedVc = ret;
		}
		return ret;
	}
	else {
		FMASSERT(0);
		return FMNULL;
	}
}
void Asgn_releaseOneVc( void )
{
	if ( _firstOccupiedVc == FMNULL ){
		FMASSERT(0);
		return;
	}

	//	Search keyoffed Voice
	Fmvoice* rlsVc = _firstOccupiedVc;
	Fmvoice* prevVc = FMNULL;
	while (rlsVc != FMNULL ){
		if ( Fmvoice_isKeyon(rlsVc) == false ){
			break;
		}
		prevVc = rlsVc;
		rlsVc = Fmvoice_nextVc(rlsVc);
	}

	//	if no keyoffed vc, select first one.
	if ( rlsVc == FMNULL ){
		rlsVc = _firstOccupiedVc;
	}

	setToEmptyList(prevVc,rlsVc);
}
void Asgn_releaseParticularVc( Fmvoice* pVc )
{
	//	Search pVc & its prevVc
	Fmvoice* rlsVc = _firstOccupiedVc;
	Fmvoice* prevVc = FMNULL;
	while ( rlsVc != FMNULL ){
		if ( pVc == rlsVc ){
			break;
		}
		prevVc = rlsVc;
		rlsVc = Fmvoice_nextVc(rlsVc);
	}
	setToEmptyList(prevVc,rlsVc);
}
static void setToEmptyList( Fmvoice* prevVc, Fmvoice* rlsVc )
{
	//	Release from Occupied list
	if ( rlsVc == _firstOccupiedVc ){
		_firstOccupiedVc = Fmvoice_nextVc(rlsVc);
	}
	if ( rlsVc == _lastOccupiedVc ){
		_lastOccupiedVc = prevVc;
	}
	if ( prevVc != FMNULL ){
		Fmvoice_setNextVc(prevVc, Fmvoice_nextVc(rlsVc));
	}
	Fmvoice_release(rlsVc);

	//	Set Empty list
	Fmvoice_setNextVc(_lastEmptyVc, rlsVc);
	_lastEmptyVc = rlsVc;
	if ( _firstEmptyVc == FMNULL ){
		_firstEmptyVc = rlsVc;
	}
}