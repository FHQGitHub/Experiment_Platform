#ifndef __ONEFS_H
#define	__ONEFS_H

#include "bsp.h"
#include "oneGUI.h"

#define ID_WIDGET_FS_MAINWIN   							(GUI_ID_USER + 0x00)
#define ID_WIDGET_FS_MAINLIST   						(GUI_ID_USER + 0x01)
#define ID_WIDGET_FS_SUBLIST   							(GUI_ID_USER + 0x02)
#define ID_WIDGET_FS_BUTTON_EXIT   						(GUI_ID_USER + 0x03)
#define ID_WIDGET_FS_BUTTON_DEL   						(GUI_ID_USER + 0x04)
#define ID_WIDGET_FS_BUTTON_RENAME   					(GUI_ID_USER + 0x05)
#define ID_WIDGET_FS_TEXT_PATH   						(GUI_ID_USER + 0x06)
#define	ID_WIDGET_FS_USER								(GUI_ID_USER + 0x10)

typedef struct onefs_node_struct {
	
	WIDEGT_fs_handlerInfoStructTypedef				*handler;
	char 																			*name;
	char 																			*path;
	char 																			*content;
	onefs_type																type;
	
	int																				rank;
	int 																			element_number;
	int																				element_id;
	struct onefs_node_struct									*parent;
	struct onefs_node_struct									*child;
	struct onefs_node_struct									*next;
	struct onefs_node_struct									*priv;
	
}onefs_node_struct_type;


typedef struct onefs_struct {

	onefs_node_struct_type													*root;
	onefs_node_struct_type													*index;
	WM_HWIN 																hWin;
	int																		id_pool[10];
	
	char	 																*(*init)(void);
	void	 																(*open)(void);
	void	 																(*close)(void);
	char																	*(*create)(const char *file_name, onefs_type onefs_t);
	void 																	(*remove)(WM_HWIN hElement);
	void 																	(*remove_exclusive)(onefs_node_struct_type *pIndex);
	char 																	*(*enter)(WM_HWIN hElement);
	char 																	*(*exit)(void);
	void 																	(*distruct)(void);
	
}onefs_struct_type;

extern onefs_struct_type onefs;

WM_HWIN FsWinOnCreate(void);

#endif
