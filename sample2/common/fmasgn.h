#ifndef FMASGN_H
#define FMASGN_H
#include <stdbool.h>
#include "fmvoice.h"

#define	MAX_FM_VOICE 16

//	public
extern void Asgn_init( void );
extern bool Asgn_chkEmpty( void );
extern Fmvoice* Asgn_getEmptyVc( void );
extern void Asgn_releaseOneVc( void );
extern void Asgn_releaseParticularVc( Fmvoice* pvc );

//	setter
extern void Asgn_setFirstEmptyVc( Fmvoice* vc );
extern void Asgn_setLastEmptyVc( Fmvoice* vc );

//	getter
extern Fmvoice* Asgn_voice( int num );
extern Fmvoice* Asgn_firstEmptyVc( void );
extern Fmvoice* Asgn_lastEmptyVc( void );

#endif