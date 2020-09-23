#include "touch_screen.h"

/*
 *
 * 功能：打开LCD触摸屏设备
 * 参数：
 * 		pathname		--->你要打开LCD的文件的路径名
 * 返回值
 * 		成功		--->成功打开的文件对应的文件描述符
 * 		失败		--->-1
 */
/*int Open_Ts(void)
{	
	fd_ev0 = open("/dev/input/event0", O_RDWR);
	if( -1 == fd_ev0 )
	{
			perror("open event0 failed\n");
	}		
	return 0;
}
*/

/*
 * 功能：打开文件
 * 参数：
 * 		pathname		--->你要打开的文件的路径名
 * 返回值
 * 		成功		--->成功打开的文件对应的文件描述符
 * 		失败		--->-1
 */

 int OpenLcd(const char *pathname)
{
	
	//1，打开LCD设备文件  --
	int lcd_fd = open(pathname,O_RDWR);
	if(-1 == lcd_fd)
	{
		perror("open lcd failed\n");
		exit(0);
	}
	else
	{
		printf("open lcd success\n");
	}
	return lcd_fd;
}

/*
 * 功能：LCD初始化
 * 参数：
 * 		
 * 返回值
 * 		成功		--->
 * 		失败		--->退出程序
 */
int Lcd_Init()
{
	int fd;
	//打开LCD设备文件
	fd = OpenLcd("/dev/input/event0");
	return fd;	
}




/*
 *
 * 功能：读取触摸屏
 * 参数：
 * 		x,y		---> x坐标,y 坐标
 * 返回值
 * 		成功		--->
 * 		失败		--->
 */

int Read_Ts(int *coordinate_x, int *coordinate_y)//2，读取触控屏的信息到结构体中。(read)
{
	int ret;	
	struct input_event coordinate;
	while(1)
	{
		read(fd_ev0, &coordinate, sizeof(struct input_event));//读取触摸屏的结构体
				
		
		if(coordinate.type==3 && coordinate.code==0 && coordinate.value>0 && coordinate.value<800)//判断触摸屏状态
		{
			*coordinate_x =  coordinate.value;
		}
		if(coordinate.type==3 && coordinate.code==1 && coordinate.value>0 && coordinate.value<480)
		{
			*coordinate_y =  coordinate.value;
		}
		if(coordinate.type==1 && coordinate.code==330 && coordinate.value==0)
		{
			break;
		}			
	}
	
	return 0;
}


/*
 *
 * 功能：获取触摸屏
 * 参数：
 * 		x,y	z	---> x坐标,y 坐标
 * 返回值
 * 		成功		--->
 * 		失败		--->
 */

int Touch(int *x, int *y, int *z)
{
	int tmp_x,tmp_y;
	//打开触摸屏的设备文件
	int ts_fd = open("/dev/input/event0", O_RDWR);
	//读取触摸屏数据
	struct input_event ts;
	
	while(1)
	{
		read(ts_fd, &ts, sizeof(ts));//读取触摸屏的数据
		
		//触摸屏数据
		if(ts.type == EV_ABS &&  ts.code == ABS_X)  //事件为触摸屏的x坐标
		{
			tmp_x = ts.value;
			if (tmp_x<800&&tmp_x>60)
			{
				if(tmp_x<=500)
				*z=tmp_x; 
				else *z=500;
			}

		}
		
		if(ts.type == EV_ABS &&  ts.code == ABS_Y)  //事件为触摸屏的y坐标
			tmp_y = ts.value;
		
			printf("ts.value:%d\n", ts.value);
			printf("x:%d   y:%d\n", *x, *y);
		
			if(ts.value == 0)
			{
				*x = tmp_x;
				*y = tmp_y;
				break;
			}
	}
	//关闭触摸屏
	close(ts_fd);
	
	return 0;
}



/*
*	函数功能：获取一次滑动的起点坐标和终点坐标
*	函数参数：触摸屏文件描述符
*   返回值：无
*	
*/
void Get_Sxy_Exy(int Ts_fd)
{
	struct input_event xy;
	int flag = 0;
	while(1)    //获取第一个点的坐标
	{
		read(Ts_fd, &xy, sizeof(xy));
		if(xy.type == EV_ABS && xy.code == ABS_X && flag == 0)
		{
			Ts_x1 = xy.value;
			flag = 1;
		}
		else if(xy.type == EV_ABS && xy.code == ABS_Y && flag == 1)
		{
			Ts_y1 = xy.value;
			flag = 2;
		}
		
		if(flag == 2)
		{
			printf("get START xy:(%d,%d)\n", Ts_x1, Ts_y1);
			flag = 0;
			break;	//跳出循环 ，此时 （Ts_x1, Ts_y1）是滑动轨迹的第一个坐标
		}			
	}		
	
	while(1)	//获取最后一个点的坐标 ： 最后一个点？ 压力值为0的点
	{
		read(Ts_fd, &xy, sizeof(xy));
		if(xy.type == EV_ABS && xy.code == ABS_X)
		{
			Ts_x2 = xy.value;
		}
		else if(xy.type == EV_ABS && xy.code == ABS_Y)
		{
			Ts_y2 = xy.value;
		}
		
		if(xy.type == EV_KEY && xy.code == BTN_TOUCH && xy.value == 0)	//压力值为0，代表手指离开屏幕，代表此时 是滑动的最后一个点
		{
			printf("get END xy:(%d,%d)\n", Ts_x2, Ts_y2);
			break;	//跳出循环 ，此时 （Ts_x1, Ts_y1）是滑动轨迹的第一个坐标
		}			
	}		
		
}


/*
*	函数功能：判断一次滑动的方向
*	函数参数：无
*   返回值：滑动的方向
*	
*/
int Get_slide(void)
{
	/*上滑的情况：1，y1>y2(由于触摸屏坐标轴是左上角是远点)，2，|y1-y2|> |x2-x1| 在45度角的上方*/
	if(Ts_y1>Ts_y2 && (Ts_y1-Ts_y2)*(Ts_y1-Ts_y2) > (Ts_x1-Ts_x2)*(Ts_x1-Ts_x2))	//如果 y1-y2的平方大于 x1-x2的平方
	{
		return UP;	//上滑
	}
	/*下滑的情况：1，y2>y1(由于触摸屏坐标轴是左上角是远点)，2，|y2-y1| > |x2-x1| 在45度角的下方*/
	else if(Ts_y1<Ts_y2 && (Ts_y1-Ts_y2)*(Ts_y1-Ts_y2) > (Ts_x1-Ts_x2)*(Ts_x1-Ts_x2))
	{
		return DOWN;
	}
	
	/*左滑的情况：1，x1>x2，2，|y2-y1| < |x2-x1| 在45度角的下方*/
	else if(Ts_x1>Ts_x2 &&(Ts_y1-Ts_y2)*(Ts_y1-Ts_y2) < (Ts_x1-Ts_x2)*(Ts_x1-Ts_x2))
	{
		return LEFT;
	}
	
	/*右滑的情况：1，x1<x2，2，|y2-y1| < |x2-x1| 在45度角的下方*/
	else if(Ts_x1<Ts_x2 && (Ts_y1-Ts_y2)*(Ts_y1-Ts_y2) < (Ts_x1-Ts_x2)*(Ts_x1-Ts_x2))
	{
		return RIGHT;
	}
	
}


/*
 *
 * 功能：用户滑屏图片切换
 * 参数：
 * 		
 * 返回值
 * 		成功		
 * 		失败		
 */

int User_Sliding_screen(void)
{
	int ret;
	int ts_fd = Lcd_Init();
	Show_JpeG("pic/4.jpg");

	while(1)
	{
		 Get_Sxy_Exy(ts_fd);//获取触摸屏
		 ret = Get_slide();//识别触摸屏滑屏方向
		 printf("==================\n");
		if(ret == UP)//上滑
		{
			Show_JpeG("image/exit.jpg");
			printf("UP \n");
			break;
		}
		if(ret == DOWN)//下滑
		{
			Show_JpeG("./image/ha.jpg");
			sleep(1);
			Show_JpeG("./image/hh.jpg");
			sleep(1);
			Show_JpeG("./image/ke.jpg");
			sleep(1);
			Show_JpeG("./image/lm.jpg");
			sleep(1);
			Show_JpeG("./image/ok.jpg");
			sleep(1);
			printf("DOWN \n");
		}
		if(ret == LEFT)//左滑
		{
			p = p->prev;
			if(p == d_list)
			{
				p = p->prev;
			}
			Show_JpeG( p->pic_path );
			printf("LEFT \n");

		}
		if(ret == RIGHT)
		{
			p =p->next;

			if(p == d_list)
			{
				p = p->next;
				
			}
			Show_JpeG(p->pic_path );
			printf("RIGHT \n");
		
		}
	}

	return 0;
}






/*	
 * 功能：关闭触摸屏
 * 参数：无
 * 		
 * 返回值
 * 		成功		---> 0
 * 		失败		--->
 */

int Close_Ts(void)
{
	close(fd_ev0);
	
	return 0;
}