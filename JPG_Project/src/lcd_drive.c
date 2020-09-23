#include  "lcd_drive.h"

#define FB_SIZE	800*480*4 //LCD的映射大小

/*
 * 功能：LCD画点
 * 参数：
 * 		x,y,颜色		--->
 * 返回值
 * 		成功		--->无
 * 		失败		--->无
 */

void Lcd_DraW_Point(unsigned int x,unsigned int y,unsigned int color,unsigned int *lcd_fd_ptr)
{

	*(lcd_fd_ptr+800*y+x) = color;

}

/*
 * 功能：打开LCD设备
 * 参数：
 * 		pathname		--->你要打开LCD的文件的路径名
 * 返回值
 * 		成功		--->成功打开的文件对应的文件描述符
 * 		失败		--->-1
 */


int Open_Lcd_Device()
{
	int lcd_fd;
	lcd_fd = open("/dev/fb0",O_RDWR);
	if(-1 == lcd_fd)
	{
		perror("open lcd device failed\n");
		return-1;
	}

	return lcd_fd;
}


/*	
 * 功能：关闭文件释放映射内存
 * 参数：文件描述符
 * 		
 * 返回值
 * 		成功		--->
 * 		失败		--->
 */
int Close_Lcd_Device(int lcd_fd, unsigned int *lcd_fb_ptr)
{
	munmap(lcd_fb_ptr, FB_SIZE);

	return close(lcd_fd);
}











