#include "uiBuild.h"

#define ID_WINDOW_0   					(GUI_ID_USER + 0x00)
#define ID_WIDGET_KEYBOARD_BUTTON_Q   			(GUI_ID_USER + 0x01)
#define ID_WIDGET_KEYBOARD_BUTTON_W   			(GUI_ID_USER + 0x02)
#define ID_WIDGET_KEYBOARD_BUTTON_E   			(GUI_ID_USER + 0x03)
#define ID_WIDGET_KEYBOARD_BUTTON_R  			(GUI_ID_USER + 0x04)
#define ID_WIDGET_KEYBOARD_BUTTON_T   			(GUI_ID_USER + 0x05)
#define ID_WIDGET_KEYBOARD_BUTTON_Y   			(GUI_ID_USER + 0x06)
#define ID_WIDGET_KEYBOARD_BUTTON_U   			(GUI_ID_USER + 0x07)
#define ID_WIDGET_KEYBOARD_BUTTON_I   			(GUI_ID_USER + 0x08)
#define ID_WIDGET_KEYBOARD_BUTTON_O   			(GUI_ID_USER + 0x09)
#define ID_WIDGET_KEYBOARD_BUTTON_P   			(GUI_ID_USER + 0x0A)
#define ID_WIDGET_KEYBOARD_BUTTON_A   			(GUI_ID_USER + 0x0B)
#define ID_WIDGET_KEYBOARD_BUTTON_S   			(GUI_ID_USER + 0x0C)
#define ID_WIDGET_KEYBOARD_BUTTON_D   			(GUI_ID_USER + 0x0D)
#define ID_WIDGET_KEYBOARD_BUTTON_F   			(GUI_ID_USER + 0x0E)
#define ID_WIDGET_KEYBOARD_BUTTON_G   			(GUI_ID_USER + 0x0F)
#define ID_WIDGET_KEYBOARD_BUTTON_H   			(GUI_ID_USER + 0x10)
#define ID_WIDGET_KEYBOARD_BUTTON_J   			(GUI_ID_USER + 0x11)
#define ID_WIDGET_KEYBOARD_BUTTON_K   			(GUI_ID_USER + 0x12)
#define ID_WIDGET_KEYBOARD_BUTTON_L   			(GUI_ID_USER + 0x13)
#define ID_WIDGET_KEYBOARD_BUTTON_Z   			(GUI_ID_USER + 0x14)
#define ID_WIDGET_KEYBOARD_BUTTON_X   			(GUI_ID_USER + 0x15)
#define ID_WIDGET_KEYBOARD_BUTTON_C   			(GUI_ID_USER + 0x16)
#define ID_WIDGET_KEYBOARD_BUTTON_V   			(GUI_ID_USER + 0x17)
#define ID_WIDGET_KEYBOARD_BUTTON_B   			(GUI_ID_USER + 0x18)
#define ID_WIDGET_KEYBOARD_BUTTON_N   			(GUI_ID_USER + 0x19)
#define ID_WIDGET_KEYBOARD_BUTTON_M   			(GUI_ID_USER + 0x1A)
#define ID_WIDGET_KEYBOARD_BUTTON_CAPS   		(GUI_ID_USER + 0x1B)
#define ID_WIDGET_KEYBOARD_BUTTON_DEL   		(GUI_ID_USER + 0x1C)
#define ID_WIDGET_KEYBOARD_BUTTON_NUM   		(GUI_ID_USER + 0x1D)
#define ID_WIDGET_KEYBOARD_BUTTON_SYM   		(GUI_ID_USER + 0x1E)
#define ID_WIDGET_KEYBOARD_BUTTON_COMMA   	        (GUI_ID_USER + 0x1F)
#define ID_WIDGET_KEYBOARD_BUTTON_SPACE   	        (GUI_ID_USER + 0x20)
#define ID_WIDGET_KEYBOARD_BUTTON_DOT   		(GUI_ID_USER + 0x21)
#define ID_WIDGET_KEYBOARD_BUTTON_CE   			(GUI_ID_USER + 0x22)
#define ID_WIDGET_KEYBOARD_BUTTON_ENTER   	        (GUI_ID_USER + 0x23)
#define ID_WIDGET_KEYBOARD_BUTTON_0   			(GUI_ID_USER + 0x24)
#define ID_WIDGET_KEYBOARD_BUTTON_1   			(GUI_ID_USER + 0x25)
#define ID_WIDGET_KEYBOARD_BUTTON_2   			(GUI_ID_USER + 0x26)
#define ID_WIDGET_KEYBOARD_BUTTON_3  			(GUI_ID_USER + 0x27)
#define ID_WIDGET_KEYBOARD_BUTTON_4   			(GUI_ID_USER + 0x28)
#define ID_WIDGET_KEYBOARD_BUTTON_5   			(GUI_ID_USER + 0x29)
#define ID_WIDGET_KEYBOARD_BUTTON_6   			(GUI_ID_USER + 0x2A)
#define ID_WIDGET_KEYBOARD_BUTTON_7   			(GUI_ID_USER + 0x2B)
#define ID_WIDGET_KEYBOARD_BUTTON_8   			(GUI_ID_USER + 0x2C)
#define ID_WIDGET_KEYBOARD_BUTTON_9   			(GUI_ID_USER + 0x2D)

extern SpecializedSkinTypedef _button_info[45];
extern unsigned char _keyboard_Data[45][3][6];

static void _cbDialog(WM_MESSAGE * pMsg) 
{
        WM_HWIN hItem;
	SpecializedSkinTypedef *button;
        int     NCode;
        int     Id;
	int  i;
	
          switch (pMsg->MsgId) {
          case WM_INIT_DIALOG:
                        hItem = pMsg->hWin;
                        WINDOW_SetBkColor(hItem, 0x00FFFCF9);
                        for(i=0; i<45; i++) {
                                
                                hItem = WM_GetDialogItem(pMsg->hWin, ID_WIDGET_KEYBOARD_BUTTON_Q + i);
                                BUTTON_SetFocussable(hItem, 0);  
                                BUTTON_SetText(hItem, "");
                                BUTTON_SetSkin(hItem, SKIN_button2C);
                                //BUTTON_SetText(hItem, (const char *)_keyboard_Data[i][0]);
                                                
                        }
                
            break;
                        
          case WM_NOTIFY_PARENT:
            Id    = WM_GetId(pMsg->hWinSrc);
            NCode = pMsg->Data.v;
                        switch(Id) {
                                case ID_WIDGET_KEYBOARD_BUTTON_Q: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN) {
                                                                if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                        EDIT_AddKey(hConnectEdit, 'q');
                                                                        else EDIT_AddKey(hConnectEdit, 'Q');
                                                        }
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_W: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
							if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN) {
                                                                if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                        EDIT_AddKey(hConnectEdit, 'r');
                                                                        else EDIT_AddKey(hConnectEdit, 'R');
                                                        }
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_E: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN) {
                                                                if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                        EDIT_AddKey(hConnectEdit, 'r');
                                                                        else EDIT_AddKey(hConnectEdit, 'R');
                                                        }
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_R: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN) {
                                                                if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                        EDIT_AddKey(hConnectEdit, 'r');
                                                                        else EDIT_AddKey(hConnectEdit, 'R');
                                                        }
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_T: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN) {
                                                                if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                        EDIT_AddKey(hConnectEdit, 't');
                                                                        else EDIT_AddKey(hConnectEdit, 'T');
                                                        }
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_Y: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN) {
                                                                if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                        EDIT_AddKey(hConnectEdit, 'y');
                                                                        else EDIT_AddKey(hConnectEdit, 'Y');
                                                        }
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_U: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN) {
                                                                if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                        EDIT_AddKey(hConnectEdit, 'u');
                                                                        else EDIT_AddKey(hConnectEdit, 'U');
                                                        }
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_I: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN) {
                                                                if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                        EDIT_AddKey(hConnectEdit, 'i');
                                                                        else EDIT_AddKey(hConnectEdit, 'I');
                                                        }
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_O: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN) {
                                                                if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                        EDIT_AddKey(hConnectEdit, 'o');
                                                                        else EDIT_AddKey(hConnectEdit, 'O');
                                                        }
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_P: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN) {
                                                                if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                        EDIT_AddKey(hConnectEdit, 'p');
                                                                        else EDIT_AddKey(hConnectEdit, 'P');
                                                        }
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_A: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN) {
                                                                if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                        EDIT_AddKey(hConnectEdit, 'a');
                                                                        else EDIT_AddKey(hConnectEdit, 'A');
                                                        }
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_S: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN) {
                                                                if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                        EDIT_AddKey(hConnectEdit, 's');
                                                                        else EDIT_AddKey(hConnectEdit, 'S');
                                                        }
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_D: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN) {
                                                                if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                        EDIT_AddKey(hConnectEdit, 'd');
                                                                        else EDIT_AddKey(hConnectEdit, 'D');
                                                        }
                                                        break;
                                                }
                                        break;	
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_F: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN) {
                                                                if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                        EDIT_AddKey(hConnectEdit, 'f');
                                                                        else EDIT_AddKey(hConnectEdit, 'F');
                                                        }
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_G: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN) {
                                                                if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                        EDIT_AddKey(hConnectEdit, 'g');
                                                                        else EDIT_AddKey(hConnectEdit, 'G');
                                                        }
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_H: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN) {
                                                                if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                        EDIT_AddKey(hConnectEdit, 'h');
                                                                        else EDIT_AddKey(hConnectEdit, 'H');
                                                        }
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_J: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN) {
                                                                if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                        EDIT_AddKey(hConnectEdit, 'j');
                                                                        else EDIT_AddKey(hConnectEdit, 'J');
                                                        }
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_K: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN) {
                                                                if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                        EDIT_AddKey(hConnectEdit, 'k');
                                                                        else EDIT_AddKey(hConnectEdit, 'K');
                                                        }
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_L: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN) {
                                                                if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                        EDIT_AddKey(hConnectEdit, 'l');
                                                                        else EDIT_AddKey(hConnectEdit, 'L');
                                                        }
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_Z: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN) {
                                                                if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                        EDIT_AddKey(hConnectEdit, 'z');
                                                                        else EDIT_AddKey(hConnectEdit, 'Z');
                                                        }
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_X: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN) {
                                                                if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                        EDIT_AddKey(hConnectEdit, 'x');
                                                                        else EDIT_AddKey(hConnectEdit, 'X');
                                                        }
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_C: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN) {
                                                                if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                        EDIT_AddKey(hConnectEdit, 'c');
                                                                        else EDIT_AddKey(hConnectEdit, 'C');
                                                        }
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_V: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN) {
                                                                if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                        EDIT_AddKey(hConnectEdit, 'v');
                                                                        else EDIT_AddKey(hConnectEdit, 'V');
                                                        }
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_B: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN) {
                                                                if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                        EDIT_AddKey(hConnectEdit, 'b');
                                                                        else EDIT_AddKey(hConnectEdit, 'B');
                                                        }
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_N: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN) {
                                                                if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                        EDIT_AddKey(hConnectEdit, 'n');
                                                                        else EDIT_AddKey(hConnectEdit, 'N');
                                                        }
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_M: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN) {
                                                                if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                        EDIT_AddKey(hConnectEdit, 'm');
                                                                        else EDIT_AddKey(hConnectEdit, 'M');
                                                        }
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_CAPS: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                keyboard.status = WIDGET_KEYBOARD_STA_CAPS; 
                                                        else if(WIDGET_KEYBOARD_STA_CAPS == keyboard.status)
                                                                keyboard.status = WIDGET_KEYBOARD_STA_LITTLE; 
                                                        
                                                        for(i=0; i<45; i++) {
                                                                _button_info[i].content = _keyboard_Data[i][(WIDGET_KEYBOARD_STA_CAPS == keyboard.status)?1:0];
                                                                button = &_button_info[i];
                                                                WM_SetUserData(WM_GetDialogItem(keyboard.hWin, (GUI_ID_USER + i + 1)), (const void *)&button, sizeof(button));
                                                        }
                                                        WM_Paint(keyboard.hWin);
                                                        
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_DEL: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        EDIT_AddKey(hConnectEdit, '\b');
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_NUM: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type != WIDGET_KEYBOARD_TYPE_NUMBER) 
                                                                        keyboard.type= WIDGET_KEYBOARD_TYPE_NUMBER; 
                                                        else keyboard.type = WIDGET_KEYBOARD_TYPE_STANDARD_EN; 
                                                                        
                                                                WM_Paint(keyboard.hWin);
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_SYM: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type != WIDGET_KEYBOARD_TYPE_SYMBLE) 
                                                                        keyboard.type= WIDGET_KEYBOARD_TYPE_SYMBLE; 
                                                        else keyboard.type = WIDGET_KEYBOARD_TYPE_STANDARD_EN; 
                                                                        
                                                                WM_Paint(keyboard.hWin);
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_COMMA: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN)
                                                                EDIT_AddKey(hConnectEdit, ',');

                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_SPACE: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN)
                                                                EDIT_AddKey(hConnectEdit, ' ');

                                                        break;
                                                }
                                        break;
                                                
					case ID_WIDGET_KEYBOARD_BUTTON_DOT:
					switch(NCode) {
						case WM_NOTIFICATION_CLICKED:
							
						break;
						case WM_NOTIFICATION_RELEASED:
							if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN)
								EDIT_AddKey(hConnectEdit, '.');

							break;
						}
                                        break;
						
                                        case ID_WIDGET_KEYBOARD_BUTTON_CE: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN)
                                                                keyboard.type = WIDGET_KEYBOARD_TYPE_STANDARD_CH;
                                                        else if (keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_CH)
                                                                keyboard.type = WIDGET_KEYBOARD_TYPE_STANDARD_EN;
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_ENTER: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_0: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN) {
                                                                if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                        EDIT_AddKey(hConnectEdit, '0');
                                                                        else EDIT_AddKey(hConnectEdit, '0');
                                                        }
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_1: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN) {
                                                                if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                        EDIT_AddKey(hConnectEdit, '1');
                                                                        else EDIT_AddKey(hConnectEdit, '1');
                                                        }
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_2: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN) {
                                                                if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                        EDIT_AddKey(hConnectEdit, '2');
                                                                        else EDIT_AddKey(hConnectEdit, '2');
                                                        }
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_3: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN) {
                                                                if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                        EDIT_AddKey(hConnectEdit, '3');
                                                                        else EDIT_AddKey(hConnectEdit, '3');
                                                        }
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_4: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN) {
                                                                if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                        EDIT_AddKey(hConnectEdit, '4');
                                                                        else EDIT_AddKey(hConnectEdit, '4');
                                                        }
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_5: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN) {
                                                                if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                        EDIT_AddKey(hConnectEdit, '5');
                                                                        else EDIT_AddKey(hConnectEdit, '5');
                                                        }
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_6: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN) {
                                                                if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                        EDIT_AddKey(hConnectEdit, '6');
                                                                        else EDIT_AddKey(hConnectEdit, '6');
                                                        }
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_7: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN) {
                                                                if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                        EDIT_AddKey(hConnectEdit, '7');
                                                                        else EDIT_AddKey(hConnectEdit, '7');
                                                        }
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_8:
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN) {
                                                                if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                        EDIT_AddKey(hConnectEdit, '8');
                                                                        else EDIT_AddKey(hConnectEdit, '8');
                                                        }
                                                        break;
                                                }
                                        break;
                                                
                                        case ID_WIDGET_KEYBOARD_BUTTON_9: 
                                        switch(NCode) {
                                                case WM_NOTIFICATION_CLICKED:
                                                        
                                                break;
                                                case WM_NOTIFICATION_RELEASED:
                                                        if(keyboard.type == WIDGET_KEYBOARD_TYPE_STANDARD_EN) {
                                                                if(WIDGET_KEYBOARD_STA_LITTLE == keyboard.status)
                                                                        EDIT_AddKey(hConnectEdit, '9');
                                                                        else EDIT_AddKey(hConnectEdit, '9');
                                                        }
                                                        break;
                                                }
                                        break;
                        }
            break;
                        
          default:
                WM_DefaultProc(pMsg);
          break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       createFramewin
*/
WM_HWIN fullKeyboardPageOnCreate(void);
WM_HWIN fullKeyboardPageOnCreate(void) {
	
  GUI_WIDGET_CREATE_INFO _aDialogcreate[] = {
  { WINDOW_CreateIndirect, "Window", ID_WINDOW_0, keyboard.axis_x, keyboard.axis_y, keyboard.size_x, keyboard.size_y, 0, 0x0, 0 },
	//{ WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 0, 0, 800, 480, 0, 0x0, 0 },	
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_0, keyboard.key_interval, 																																	keyboard.key_interval, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_1, keyboard.key_interval  * 2 			+ 	keyboard.key_size, 																	keyboard.key_interval, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_2, (keyboard.key_interval * 2 			+ 	keyboard.key_size)*2, 															keyboard.key_interval, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_3, (keyboard.key_interval * 2 			+ 	keyboard.key_size)*3, 															keyboard.key_interval, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_4, (keyboard.key_interval * 2 			+	keyboard.key_size)*4, 															keyboard.key_interval, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_5, (keyboard.key_interval * 2 			+ 	keyboard.key_size)*5, 															keyboard.key_interval, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_6, (keyboard.key_interval * 2 			+ 	keyboard.key_size)*6, 															keyboard.key_interval, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_7, (keyboard.key_interval * 2 			+ 	keyboard.key_size)*7, 															keyboard.key_interval, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_8, (keyboard.key_interval * 2 			+ 	keyboard.key_size)*8, 															keyboard.key_interval, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_9, (keyboard.key_interval * 2 			+ 	keyboard.key_size)*9, 															keyboard.key_interval, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
        { BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_Q,  keyboard.key_interval,			 																														keyboard.key_interval * 2 + keyboard.key_size, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_W,  keyboard.key_interval * 2 			+ 	keyboard.key_size, 	 																keyboard.key_interval * 2 + keyboard.key_size, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_E, (keyboard.key_interval * 2 			+ 	keyboard.key_size)*2, 															keyboard.key_interval * 2 + keyboard.key_size, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_R, (keyboard.key_interval * 2 			+ 	keyboard.key_size)*3, 															keyboard.key_interval * 2 + keyboard.key_size, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_T, (keyboard.key_interval * 2 			+ 	keyboard.key_size)*4, 															keyboard.key_interval * 2 + keyboard.key_size, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_Y, (keyboard.key_interval * 2 			+ 	keyboard.key_size)*5, 															keyboard.key_interval * 2 + keyboard.key_size, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_U, (keyboard.key_interval * 2 			+ 	keyboard.key_size)*6, 															keyboard.key_interval * 2 + keyboard.key_size, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_I, (keyboard.key_interval * 2 			+ 	keyboard.key_size)*7, 															keyboard.key_interval * 2 + keyboard.key_size, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_O, (keyboard.key_interval * 2 			+ 	keyboard.key_size)*8, 															keyboard.key_interval * 2 + keyboard.key_size, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_P, (keyboard.key_interval * 2 			+ 	keyboard.key_size)*9, 															keyboard.key_interval * 2 + keyboard.key_size, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_A, keyboard.key_interval 				+ 	keyboard.key_size/2,																(keyboard.key_interval * 2 + keyboard.key_size)*2, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_S, keyboard.key_interval  * 2 			+	keyboard.key_size 		+ keyboard.key_size/2 ,			(keyboard.key_interval * 2 + keyboard.key_size)*2, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_D, (keyboard.key_interval * 2 			+	keyboard.key_size)*2 		+ keyboard.key_size/2 ,			(keyboard.key_interval * 2 + keyboard.key_size)*2, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_F, (keyboard.key_interval * 2 			+ 	keyboard.key_size)*3 		+ keyboard.key_size/2 ,			(keyboard.key_interval * 2 + keyboard.key_size)*2, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_G, (keyboard.key_interval * 2 			+ 	keyboard.key_size)*4 		+ keyboard.key_size/2 ,			(keyboard.key_interval * 2 + keyboard.key_size)*2, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_H, (keyboard.key_interval * 2 			+ 	keyboard.key_size)*5 		+ keyboard.key_size/2 ,			(keyboard.key_interval * 2 + keyboard.key_size)*2, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_J, (keyboard.key_interval * 2 			+ 	keyboard.key_size)*6 		+ keyboard.key_size/2 ,			(keyboard.key_interval * 2 + keyboard.key_size)*2, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_K, (keyboard.key_interval * 2 			+ 	keyboard.key_size)*7 		+ keyboard.key_size/2 ,			(keyboard.key_interval * 2 + keyboard.key_size)*2, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_L, (keyboard.key_interval * 2 			+ 	keyboard.key_size)*8		+ keyboard.key_size/2 ,			(keyboard.key_interval * 2 + keyboard.key_size)*2, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_Z, keyboard.key_interval  * 2 			+ 	keyboard.key_size 		+ keyboard.key_size/2 ,			(keyboard.key_interval * 2 + keyboard.key_size)*3, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_X, (keyboard.key_interval * 2 			+ 	keyboard.key_size)*2 		+ keyboard.key_size/2 ,			(keyboard.key_interval * 2 + keyboard.key_size)*3, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_C, (keyboard.key_interval * 2 			+ 	keyboard.key_size)*3 		+ keyboard.key_size/2 ,			(keyboard.key_interval * 2 + keyboard.key_size)*3, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_V, (keyboard.key_interval * 2 			+ 	keyboard.key_size)*4 		+ keyboard.key_size/2 ,			(keyboard.key_interval * 2 + keyboard.key_size)*3, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_B, (keyboard.key_interval * 2 			+ 	keyboard.key_size)*5 		+ keyboard.key_size/2 ,			(keyboard.key_interval * 2 + keyboard.key_size)*3, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_N, (keyboard.key_interval * 2 			+ 	keyboard.key_size)*6 		+ keyboard.key_size/2 ,			(keyboard.key_interval * 2 + keyboard.key_size)*3, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_M, (keyboard.key_interval * 2 			+ 	keyboard.key_size)*7 		+ keyboard.key_size/2 ,			(keyboard.key_interval * 2 + keyboard.key_size)*3, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_CAPS, 	keyboard.key_interval, 																															(keyboard.key_interval * 2 + keyboard.key_size)*3, (keyboard.key_size * 3) >> 1, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_DEL, 	(keyboard.key_interval * 2 + keyboard.key_size)*8       + keyboard.key_size/2, 	(keyboard.key_interval * 2 + keyboard.key_size)*3, (keyboard.key_size * 3) >> 1, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_NUM, 	keyboard.key_interval, 																															(keyboard.key_interval * 2 	+ keyboard.key_size)*4, 	(keyboard.key_size * 3) >> 1, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_SYM, 	keyboard.key_interval  * 2 + keyboard.key_size 	        + keyboard.key_size/2, (keyboard.key_interval * 2 + keyboard.key_size)*4, (keyboard.key_size * 3) >> 1, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_COMMA,     (keyboard.key_interval * 2 + keyboard.key_size)*3, 															(keyboard.key_interval * 2 + keyboard.key_size)*4, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_SPACE,     (keyboard.key_interval * 2 + keyboard.key_size)*4 	+ (keyboard.key_size>>3)*3 ,(keyboard.key_interval * 2 + keyboard.key_size)*4, (keyboard.key_size * 3) >> 1, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_DOT, 	(keyboard.key_interval * 2 + keyboard.key_size)*6, 															(keyboard.key_interval * 2 + keyboard.key_size)*4, keyboard.key_size, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_CE, 	(keyboard.key_interval * 2 + keyboard.key_size)*7, 															(keyboard.key_interval * 2 + keyboard.key_size)*4, (keyboard.key_size * 3) >> 1, keyboard.key_size, 0, 0x0, 0 },
	{ BUTTON_CreateIndirect, "Button", ID_WIDGET_KEYBOARD_BUTTON_ENTER,     (keyboard.key_interval * 2 + keyboard.key_size)*8 	+ keyboard.key_size/2, 	(keyboard.key_interval * 2 + keyboard.key_size)*4, (keyboard.key_size * 3) >> 1, keyboard.key_size, 0, 0x0, 0 },
};
	
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogcreate, GUI_COUNTOF(_aDialogcreate), _cbDialog, WM_HBKWIN, 0, 0);
  WM_HideWindow(hWin);
  return hWin;

}


/*************************** End of file ****************************/

