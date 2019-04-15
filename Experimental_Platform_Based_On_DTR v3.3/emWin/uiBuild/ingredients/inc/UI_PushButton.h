#ifndef __PUSHBUTTON_H
#define __PUSHBUTTON_H

#include "WM.h"

/* alpha混合背景色 */
#define PUSHBUTTON_BKCOLOR_UNSEL GUI_BLACK
#define PUSHBUTTON_BKCOLOR_SEL (0X007C7782)

void _cbPushButtonText(WM_MESSAGE *pMsg);
void _cbPushButtonBitmap(WM_MESSAGE *pMsg);

#endif


