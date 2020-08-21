#ifndef FMTONE_H
#define FMTONE_H

#define MAX_FM_OPERATOR		4
#define MAX_OPERATOR_PRM 	10

//	ToneData Class
typedef struct {
	unsigned char		voiceCommon;				// BO(2) | LFO(2) | ALG(3)
	unsigned char		opPrm[MAX_FM_OPERATOR][MAX_OPERATOR_PRM];
} ToneData;

//	public
extern void Tone_init( void );
extern void Tone_setToneExc( unsigned char data, int excNum );
extern void Tone_sendTone( void );
#endif
