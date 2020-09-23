#include "main.h"

int main(int argc, char const *argv[])
{

	if(argc < 2)
    {
        printf("Parameter is wrong\n");
        printf("%s path filename", argv[0]);
        return -1;
    }
	
	//检索目录所有的jpg
	find(argv[1]);
	//初始化界面
	Display();
	//滑屏刷图操作
	//User_Sliding_screen();
	
	//关闭触摸屏
	Close_Ts();

	return 0;
}

		

