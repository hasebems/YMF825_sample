#ifndef FMVOICE_H
#define FMVOICE_H
#include	<stdbool.h>

//	Fmvoice Class
typedef struct _Fmvoice Fmvoice;
struct _Fmvoice {
	unsigned char	_vnum;
	unsigned char	_tone;
	bool			_keyon;
	Fmvoice*		_nextVc;
	void*			_parent;
};

//	public
extern void Fmvoice_init( Fmvoice* _this );
extern void Fmvoice_keyon( Fmvoice* _this, void* nt, void* pt, void* tn, unsigned char note, unsigned char vel );
extern void Fmvoice_keyoff( Fmvoice* _this );
extern void Fmvoice_release( Fmvoice* _this );
extern void Fmvoice_chgVibDpt( Fmvoice* _this, unsigned char vibDpt );
extern void Fmvoice_chgPit( Fmvoice* _this, unsigned short pb );
extern void Fmvoice_setBasicPit( Fmvoice* _this, unsigned char note );

//	setter
extern void Fmvoice_setVoiceNum( Fmvoice* _this, unsigned char vn );
extern void Fmvoice_setNextVc( Fmvoice* _this, Fmvoice* vc );

//	getter
extern unsigned char Fmvoice_vnum( Fmvoice* _this );
extern bool Fmvoice_isKeyon( Fmvoice* _this );
extern Fmvoice* Fmvoice_nextVc( Fmvoice* _this );
#endif