#ifndef FMNOTE_H
#define FMNOTE_H
#include "fmtone.h"
#include "fmvoice.h"

//	Note Class
typedef struct _Note Note;
struct _Note {
	unsigned char	_note;
	unsigned char	_velocity;
	bool			_inUse;
	bool			_keyon;
	bool			_hold;

	Note*			_prevPtr;
	Note*			_nextPtr;
	void*			_parent;
	Fmvoice*		_vc;
};

//	public
extern void Note_init( Note* _this );
extern bool Note_keyon( Note* _this, ToneData* newTone, unsigned char note, unsigned char velocity );
extern void Note_keyoff( Note* _this );
extern void Note_releaseVc( Note* _this, Fmvoice* rlsVc );
extern void Note_release( Note* _this );
extern void Note_damp( Note* _this );
extern void Note_chgVibDpt( Note* _this );
extern void Note_chgPit( Note* _this );

//	setter
extern void Note_setPrevPtr( Note* _this, Note* pn );
extern void Note_setNextPtr( Note* _this, Note* nn );
extern void Note_setPart( Note* _this, void* pt );
extern void Note_setHold( Note* _this, bool hold );
//	getter
extern bool Note_isInUse( Note* _this );
extern bool Note_isKeyOn( Note* _this );
extern bool Note_isHeld( Note* _this );
extern Note* Note_prevPtr( Note* _this );
extern Note* Note_nextPtr( Note* _this );
extern unsigned char Note_note(Note* _this);
extern unsigned char Note_velocity(Note* _this);
#endif