#include "read_find.h"

/*
 * 功能：把指定目录下的所有.bmp结尾的文件路径保存在一个 双向循环链表中
 * 参数：路径名
 * 		
 * 返回值:无
 * 		 
 */


void find(const char *dirpath)
{
	//打开目录argv[1]
	DIR *dp = opendir(dirpath);
  	if(!dp)
  	{
        perror("opendir");
        return ;
    }

    d_list = Create_List();//创建双向链表
    struct dirent *read;
    unsigned char file_path[256];//存储文件完整路径

    //循环读取目录
	while(read = readdir(dp))
	{	
		bzero(file_path,sizeof(file_path));
		if ((strcmp(read->d_name,".") != 0) && (strcmp(read->d_name,"..") != 0))
		{
			if (strcmp(".jpg",read->d_name + (strlen(read->d_name) - 4)) == 0)/*筛选.bmp文件*/		
			{
				if(dirpath[strlen(dirpath)-1] == '/')
				{
					sprintf(file_path, "%s%s", dirpath, read->d_name);
				}
				else
				{
					sprintf(file_path, "%s/%s", dirpath, read->d_name);
				}
			}
				puts(file_path);	
				p = Create_Node(file_path);
				Insert_Node(d_list,p);	
		}		
	}

	p = d_list->next;
	
	//关闭目录
	closedir(dp);
}



