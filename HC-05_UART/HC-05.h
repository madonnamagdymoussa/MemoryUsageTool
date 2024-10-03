
#ifndef HC_05_H_
#define HC_05_H_

#include "lstd.h"
void HC05_Initialization(void);
void HC05_ReadChar(u8_t *CharacterRead);
void HC05_WriteChar(u8_t *pTxBuffer);
void HC05_WriteString(u8_t* String  );
#endif /* HC_05_H_ */
