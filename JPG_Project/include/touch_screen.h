#ifndef __TOUCH_SCREEN_H
#define __TOUCH_SCREEN_H

//头文件
#include <stdio.h>
#include <linux/input.h>//struct input_event
#include <sys/types.h>//open
#include <sys/stat.h>//open
#include <fcntl.h>//open
#include <unistd.h>//read

#include  "lcd_drive.h"
#include "display_jpeg.h"
#include "double_list.h"
#include "read_find.h"

//全局变量

int fd_ev0;
unsigned int Ts_x1, Ts_y1, Ts_x2, Ts_y2; 	//分别存放起点坐标和终点坐标 

//宏定义

#define UP 		0	//宏定义 上下左右滑动的值
#define DOWN 	1
#define LEFT 	2
#define RIGHT 	3

//函数声明


//int Open_Ts(void);//打开触控屏(open)
int Lcd_Init();
int Read_Ts(int *coordinate_x, int *coordinate_y);//读取触控屏的信息到结构体中。(read)
int Touch(int *x, int *y, int *z);
int Close_Ts(void);
void Get_Sxy_Exy(int Ts_fd);
int User_Sliding_screen(void);



#endif