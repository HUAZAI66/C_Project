#ifndef _LCD_DRIVE_H
#define _LCD_DRIVE_H


//头文件

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <syslog.h>
#include <errno.h>
#include <linux/input.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdbool.h>

#include <jpeglib.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>



//宏定义

//函数声明
void Lcd_DraW_Point(unsigned int x,unsigned int y,unsigned int color,unsigned int *lcd_fd_ptr);
int  Open_Lcd_Device();
int  Close_Lcd_Device(int lcd_fd, unsigned int *lcd_fb_ptr);






#endif