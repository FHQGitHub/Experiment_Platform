#ifndef __WIDEGT_FS
#define __WIDEGT_FS

#include "WM.h"
#include "GUI.h"
#include "oneSpecializedSkin.h"


#define WIDGET_FOLDER_DEFAULT_SIZE												60u


typedef enum onefs_type {
	onefs_directory,
	onefs_file,
	onefs_others
}onefs_type;

typedef struct WIDEGT_fs_element {
	SpecializedSkinTypedef			img;
	char												text[10];
	
}WIDEGT_fs_elementInfoStructTypedef;

typedef struct  WIDEGT_fs_handler
{
	WM_HWIN							hImg;
	WM_HWIN							hText;
	
}WIDEGT_fs_handlerInfoStructTypedef;


typedef struct WIDEGT_fs{
	
	WIDEGT_fs_handlerInfoStructTypedef					*(*draw)(int x0, int y0, WM_HWIN hParent, const char *pText, int img_id, int text_id, onefs_type element_type);
	void																				(*wipe)(WIDEGT_fs_handlerInfoStructTypedef * hFs);

	int																					size_x;
	int																					size_y;
	
	WIDEGT_fs_elementInfoStructTypedef					*element;				
	WIDEGT_fs_handlerInfoStructTypedef					*hWin;
	
}WIDEGT_fsInfoStructTypedef;

extern WIDEGT_fsInfoStructTypedef fs;


#endif
