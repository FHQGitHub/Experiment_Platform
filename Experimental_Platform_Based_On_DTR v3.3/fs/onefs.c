#include "onefs.h"

static char	*onefs_init(void);
static void	onefs_open(void);
static void	onefs_close(void);
static char	*onefs_create(const char *file_name, onefs_type onefs_t);
static void	onefs_remove(WM_HWIN hElement);
static void	onefs_remove_exclusive(onefs_node_struct_type *pIndex);
static char *onefs_enter(WM_HWIN hElement);
static char *onefs_exit(void);
static void onefs_distruct(void);

onefs_struct_type onefs = {
	
	NULL,
	NULL,
	0,
	{0},
	
	onefs_init,
	onefs_open,
	onefs_close,
	onefs_create,
	onefs_remove,
	onefs_remove_exclusive,
	onefs_enter,
	onefs_exit,
	onefs_distruct
	
	
};

static int alloc_id()
{
	int id = 0;
	int probe 			= 1;
	int pool_index 	= 0;
	int bit_index 	= 0;
	
	while(id < 320) {
		
		if(0 == (onefs.id_pool[pool_index] & probe)) {
			onefs.id_pool[pool_index] |= probe;
			return ID_WIDGET_FS_USER + id * 2;
		}
		else {
			probe <<= 1;
			id ++;
			if(bit_index == 31)	{
				bit_index = 0;
				pool_index ++;
			}
			else bit_index ++;
		}
	}
		
	return -1;		
				
}

static void ultilize_id(int id)
{
	int probe 			= 1;
	int pool_index 	= 0;
	int bit_index 	= 0;
	
	pool_index = (id - ID_WIDGET_FS_USER) >> 5;
	bit_index = (id - ID_WIDGET_FS_USER) - pool_index * 32;
	probe <<= bit_index;
	
	
	onefs.id_pool[pool_index] &= ~probe;
				
			
}

static FRESULT scan_files (char* path)
{
	char scan_path[80] = {0};
    FRESULT res;
    DIR dir;
    UINT i;
    static FILINFO fno;
	static u8 scan_flag = 0;
	onefs_node_struct_type *pIndex = NULL;
	u8	exist_flag = 0;
	
    res = f_opendir(&dir, path);                       /* Open the directory */
    if (res == FR_OK) {
        for (;;) {
			exist_flag = 0;
            res = f_readdir(&dir, &fno);                   /* Read a directory item */
            if (res != FR_OK || fno.fname[0] == 0) break;  /* Break on error or end of dir */	
			pIndex = onefs.index->child;
				/*遍历至需要进入的路径节点*/
			while(NULL != pIndex) {
				if(!strcmp((const char *)pIndex->name, fno.fname)) {
					exist_flag = 1;
					break;
				}
				pIndex = pIndex->next;
			}
			
			if(exist_flag)
				break;
			else {				
				if (fno.fattrib & AM_DIR) 
					onefs.create(fno.fname, onefs_directory);	
				else
					onefs.create(fno.fname, onefs_file);
			}				
        }
        f_closedir(&dir);
    }

    return res;
}

static char	*onefs_init()
{
	onefs.hWin = FsWinOnCreate();
	onefs.root = (onefs_node_struct_type *)calloc(sizeof(onefs_node_struct_type), 1);
	if(NULL == onefs.root)
		return NULL;
	onefs.root->path = "0:";
	onefs.index = onefs.root;
	onefs.index->element_id = GUI_ID_USER + 7;
	return onefs.root->path;

}

static void onefs_open()
{
	WM_BringToTop(onefs.hWin);
	WM_ShowWin(onefs.hWin);
}

static void onefs_close()
{
	WM_HideWin(onefs.hWin);
}


static char	*onefs_create(const char *file_name, onefs_type onefs_t)
{
	onefs_node_struct_type *pIndex = onefs.index;
	
	if(NULL == pIndex) 
		return NULL;
	
	if(NULL == pIndex->child) {
		
		pIndex->child = (onefs_node_struct_type *)calloc(sizeof(onefs_node_struct_type), 1);
		if(NULL == pIndex->child)
			return NULL;
		
		pIndex->child->name = (char *)calloc(sizeof(char), 10);
		if(NULL == pIndex->child->name)
			return NULL;
		
		pIndex->child->path = (char *)calloc(sizeof(char), 80);
		if(NULL == pIndex->child->path)
			return NULL;
		
		pIndex->child->parent = onefs.index;
		pIndex->child->type = onefs_others;
		pIndex->element_number ++;
		pIndex->child->rank = pIndex->element_number;
		pIndex->child->element_id = alloc_id();
		strcpy(pIndex->child->name, file_name);
		sprintf(pIndex->child->path, "%s%s/",pIndex->path, file_name);
		pIndex = pIndex->child;
	}
	
	else {
		pIndex = pIndex->child;
		while(pIndex->next != NULL)
			pIndex = pIndex->next;
		
		pIndex->next = (onefs_node_struct_type *)calloc(sizeof(onefs_node_struct_type), 1);
		if(NULL == pIndex->next)
			return NULL;
		
		pIndex->next->name = (char *)calloc(sizeof(char), 10);
		if(NULL == pIndex->next->name)
			return NULL;
		
		
		pIndex->next->path = (char *)calloc(sizeof(char), 40);
		if(NULL == pIndex->next->path)
			return NULL;
		
		pIndex->next->parent = onefs.index;
		pIndex->next->type = onefs_others;
		pIndex->next->priv = pIndex;
		onefs.index->element_number ++;
		pIndex->next->rank = onefs.index->element_number;
		pIndex->next->element_id = alloc_id();
		strcpy(pIndex->next->name, file_name);
		sprintf(pIndex->next->path, "%s%s/",onefs.index->path, file_name);
		pIndex = pIndex->next;
	}
	
	pIndex->type = onefs_t;
	pIndex->handler = gui.fs->draw(70+125*((pIndex->rank-1)%6), 50+105*((pIndex->rank-1)/6), onefs.hWin, file_name, pIndex->element_id, pIndex->element_id + 1, pIndex->type);

	return pIndex->path;
	
}
		

static void onefs_remove(WM_HWIN hElement)
{
	onefs_node_struct_type *pIndex = onefs.index;
	onefs_node_struct_type *pNode = NULL;
	
	if(NULL == pIndex)
		return;
	
	pIndex = pIndex->child;
	if(NULL == pIndex)
		return;
	
	while(pIndex->handler->hImg != hElement && NULL != pIndex)
		pIndex = pIndex->next;
	
	if(NULL == pIndex)
		return;
	
	pNode = pIndex;
	
	/*擦除图标*/
	gui.fs->wipe(pIndex->handler);
	
	/*清空数据*/
	free(pIndex->handler);
	free(pIndex->name);
	free(pIndex->path);
	if(NULL != pIndex->content)
		free(pIndex->content);
	
	/*从文件树中卸载节点*/
	
	/*是第一个子表项*/
	if(NULL == pIndex->priv) {
		
		/*将父子关系转移到下一个节点*/
		pIndex->parent->child = pIndex->next;
		pIndex->next->priv = NULL;
	}
	
	/*是后续表项*/
	else {
		
		/*从链表中移除节点*/
		if(NULL != pIndex->next)
			pIndex->next->priv = pIndex->priv;
		pIndex->priv->next = pIndex->next;
	}
	
	pIndex->parent->element_number --;
	
	
	while(NULL != pIndex) {
		pIndex->rank --;
		pIndex = pIndex->next;
		
	}
	 
	ultilize_id(pNode->element_id);
	free(pNode);
	
}

static void onefs_remove_exclusive(onefs_node_struct_type *pIndex)
{
	if(NULL != pIndex->child)
        onefs_remove_exclusive(pIndex->child);
    
    if(NULL != pIndex->next)
        onefs_remove_exclusive(pIndex->next);
	
	gui.fs->wipe(pIndex->handler);
	
	free(pIndex->handler);
	free(pIndex->name);
	free(pIndex->parent);
	free(pIndex->child);
	free(pIndex->next);
	free(pIndex->priv);
	free(pIndex->content);
	
	memset(pIndex, 0, sizeof(onefs_node_struct_type));
	
}

static char *onefs_enter(WM_HWIN hElement)
{
	onefs_node_struct_type *pIndex = NULL;
	onefs_node_struct_type *pElement = NULL;
	char scan_path[80] = {0};
	
	if(NULL == onefs.index)
		return NULL;

	pIndex = onefs.index->child;
	pElement = pIndex;
	/*遍历至需要进入的路径节点*/
	while(pIndex->handler->hImg != hElement && NULL != pIndex)
		pIndex = pIndex->next;
	
	/*进入选中节点*/
	if(NULL != pIndex) {
		
		/*如果选中的是路径*/
		if(onefs_directory == pIndex->type) {
			onefs.index = pIndex;
			
			/*修改路径显示*/
			TEXT_SetText(WM_GetDialogItem(onefs.hWin, ID_WIDGET_FS_TEXT_PATH), pIndex->path);
			
			/*隐藏当前路径中的图标*/
			while(NULL != pElement) {
				WM_HideWin(pElement->handler->hImg);
				WM_HideWin(pElement->handler->hText);
				pElement = pElement->next;
			}
			
			/*绘制选中节点的子图标*/
			
			sprintf(scan_path, "%s", pIndex->path);
			scan_path[strlen(scan_path)-1] = 0;
			scan_files(scan_path);
			pIndex = onefs.index->child;
			while(NULL != pIndex) {
				WM_ShowWin(pIndex->handler->hImg);
				WM_ShowWin(pIndex->handler->hText);
				pIndex = pIndex->next;
			}
		}
		
		else if(onefs_file == pIndex->type) {
		}
	}
	
	
	return onefs.index->path;
	
}

static char *onefs_exit()
{
	onefs_node_struct_type *pIndex = onefs.index;
	if(NULL == pIndex->parent)
		return pIndex->path;
	
	pIndex = pIndex->child;
	
	while(NULL != pIndex) {
		WM_HideWin(pIndex->handler->hImg);
		WM_HideWin(pIndex->handler->hText);
		pIndex = pIndex->next;
	}
	
	onefs.index = onefs.index->parent;
	TEXT_SetText(WM_GetDialogItem(onefs.hWin, ID_WIDGET_FS_TEXT_PATH), onefs.index->path);
	
	pIndex = onefs.index->child;
	while(NULL != pIndex) {
		WM_ShowWin(pIndex->handler->hImg);
		WM_ShowWin(pIndex->handler->hText);
		pIndex = pIndex->next;
	}
	
	return onefs.index->path;
}

static void onefs_distruct()
{
	onefs_remove_exclusive(onefs.root->child);
	onefs.root->child = NULL;
	onefs.root->element_number = 0;
	onefs.index = onefs.root;
	
}

