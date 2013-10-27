#ifndef _SD_H
#define _SD_H

#include "integer.h"

#define	CMDREAD		17
#define	CMDWRITE	24
#define	CMDREADCSD	9

CHAR sdInit(void);
CHAR sdState(void);
void sdCommand(BYTE cmd, WORD paramx, WORD paramy);

BYTE sdResp8b(void);
void sdResp8bError(BYTE value);
WORD sdResp16b(void);

#endif //_SD_H
