#include "bsp.h"
#include "uiBuild.h"

#if (__USE_WIDGET_FS)

static WIDEGT_fs_handlerInfoStructTypedef 	*fs_draw(int x0, int y0, WM_HWIN hParent, const char *pText, int img_id, int text_id, onefs_type element_type);
static void	 																fs_wipe(WIDEGT_fs_handlerInfoStructTypedef * hElement);

WIDEGT_fsInfoStructTypedef fs = {
	
	fs_draw,
	fs_wipe,
	
};

static WIDEGT_fs_handlerInfoStructTypedef *fs_draw(int x0, int y0, WM_HWIN hParent, const char *pText, int img_id, int text_id, onefs_type element_type)
{
	
	WM_HWIN hButton;
	WM_HWIN hText;
	SpecializedSkinTypedef *button_fs;
	int 	img_size = 0;
	GUI_RECT 		pRect;
	
	if(NULL == hParent) 
		return NULL;
	
	fs.element = (WIDEGT_fs_elementInfoStructTypedef*)calloc(sizeof(WIDEGT_fs_elementInfoStructTypedef), 1);
	if(NULL == fs.element)
		return NULL;
	
	fs.hWin = (WIDEGT_fs_handlerInfoStructTypedef*)calloc(sizeof(WIDEGT_fs_handlerInfoStructTypedef), 1);
	if(NULL == fs.hWin)
		return NULL;
	
	if(NULL == pText)
		pText = "new folder";
	
	WM_GetClientRectEx(hParent, &pRect);
	img_size = 60;
	
	if(element_type == onefs_directory) {
		fs.element->img.normal = &bmfolder;
		fs.element->img.mark = &bmfolder;
	}
	
	else {
		fs.element->img.normal = &bmfile;
		fs.element->img.mark = &bmfile;
	}

	button_fs = &fs.element->img;
	strcpy(fs.element->text, pText);
	
	hButton = BUTTON_CreateEx(x0, y0, img_size, img_size, hParent, WM_CF_SHOW, 0, img_id);
	BUTTON_SetSkin(hButton, SKIN_button2C);
	WM_SetUserData(hButton, (const void *)&button_fs, sizeof(button_fs));
	
	hText = TEXT_CreateEx(x0-15, y0+60, 90, 24, hParent, WM_CF_SHOW, GUI_TA_HCENTER | GUI_TA_VCENTER, text_id, fs.element->text);
	TEXT_SetFont(hText, GUI_FONT_20_ASCII);
	
	fs.hWin->hImg = hButton;
	fs.hWin->hText = hText;

	return fs.hWin;
	
}

static void fs_wipe(WIDEGT_fs_handlerInfoStructTypedef * hFs)
{
	WM_DeleteWindow(hFs->hImg);
	WM_DeleteWindow(hFs->hText);
}


#endif
