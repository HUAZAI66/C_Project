#ifndef _DISPLAY_JPEG_H
#define _DISPLAY_JPEG_H


//头文件

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <linux/input.h>
#include <sys/mman.h>
#include <stdlib.h>
#include "jpeglib.h"
#include "jconfig.h"
#include  "lcd_drive.h"
#include  "touch_screen.h"

//宏定义
#define FB_SIZE 800*480*4


//函数声明
int  Lcd_Draw_JpG(unsigned int x,unsigned int y,const char *pjpg_path,char *pjpg_buf,unsigned int jpg_buf_size,unsigned int jpg_half);
void Show_JpeG(const char *pathname);

int  Display();






#endif