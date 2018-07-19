/*------------------------------------------------------------------------------------------
#include "stdafx.h"
#include<WinSock2.h>//注意这个头文件一定要放在<Windows.h>的上面
#include<Windows.h>
#include<conio.h>
#include<string>
#include<iostream>
#include<fstream>
#include<mmsystem.h>
#pragma comment(lib,"WS2_32")
#pragma comment(lib, "winmm.lib")
#pragma warning(disable:4996)
using namespace std;
------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------
目录
Part1 项目设置
Part2 基本控制台API
Part3 无阻塞输入
Part4 两个有用的例子
Part5 控制台播放音乐    ???
Part6 高精度字符画（图片&动画）
Part7 网络Socket编程
------------------------------------------------------------------------------------------*/

/*----------------------------------------Part1 项目设置----------------------------------------
1.解决输出中文乱码
文件 -> 高级保存选项 -> 编码栏: 简体中文(GB2313-80)-代码页20936 -> 确定

2.解决不同项目下版本不兼容的问题
项目 -> 属性 -> 配置属性 -> 常规 -> Windows SDK版本（选择合适的即可）

3.输出字符画时要改变编码方式
项目 -> 属性 -> 配置属性 -> 项目默认值 -> 字符集： 使用多字节字符集（双击选择） 
------------------------------------------------------------------------------------------*/

/*----------------------------------------Part2 基本控制台API----------------------------------------
1.基本概念
（1）API的概念：可以简单的理解成API就是一个系统函数的一个接口，便于调用系统的资源
     系统本身会定义好了一些参数（如BOOL）和函数便于使用者使用
（2）HANDLE的概念：句柄（HANDLE）是Windows编程的一个关键性的概念，用以标识许多不同的对象类型，如窗口、菜单、内存、画笔、画刷等，
     一般调用控制台API需要传入一个句柄作为参数，这里用到的句柄只有STD_OUTPUT_HANDLE（标准输出句柄）
（3）需要包含头文件#include<Windows.h>

2.基本的控制台API（下面我会把他们都封装成一个函数方便以后直接调用）

（1）颜色控制
相关的系统API：
BOOL SetConsoleTextAttribute(HANDLE hConsoleOutput, WORD wAttributes);

参数说明：
hConsoleOutput（句柄）可选值：
 STD_INPUT_HANDLE 标准输入的句柄
 STD_OUTPUT_HANDLE 标准输出的句柄
 STD_ERROR_HANDLE 标准错误的句柄
wAttributes（设置颜色）可选值：
 FOREGROUND_BLUE  字体颜色：蓝  对应的值：1
 FOREGROUND_GREEN  字体颜色：绿  对应的值：2
 FOREGROUND_RED  字体颜色：红  对应的值：4
 FOREGROUND_INTENSITY  前景色高亮显示  对应的值：8
 BACKGROUND_BLUE  背景颜色：蓝  对应的值：16
 BACKGROUND_GREEN  背景颜色：绿  对应的值：32
 BACKGROUND_RED  背景颜色：红  对应的值：64
 BACKGROUND_INTENSITY  背景色高亮显示  对应的值：128

 函数封装：
void color(int num)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), num);
}

用法说明：
函数名字为color
传入参数为一个十进制整形数（范围值0~15）代表不同的颜色

例子(可以直接复制一下代码到下面空白的地方进行测试)：
void color(int num)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), num);
}
int main()
{
	color(15);
	cout << "Hello World" << endl;
	return 0;
}

（2）位置控制
函数封装如下：
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

用法说明：
函数名字为gotoxy
传入参数为两个整型数，分别代表在控制台上的横纵坐标

例子：
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
int main()
{
	gotoxy(50,10);
	cout << "Hello World";
	return 0;
}

（3）光标控制
函数封装如下：
void cursor()
{
	CONSOLE_CURSOR_INFO cci;	//定义光标信息结构体
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);	//获取光标信息  
	cci.dwSize = 1;	//设置光标大小     
	cci.bVisible = 0;	//设置光标不可见 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);	//应用光标信息  
}

用法说明：
直接调用函数即可设置光标为不可见
------------------------------------------------------------------------------------------*/

/*----------------------------------------Part3 无阻塞接收输入----------------------------------------
函数：
_kbhit()：无阻塞接收用户输入（平常的输入是用户先输入到缓冲区，等用户按下Enter键后再读取用户输入，而这个函数可以直接读取用户的输入）
_getch()：获取用户输入的值

说明：
需要包含头文件#include<conio.h>

用法模板：
int main()
{
	while (true)
	{
		if (_kbhit())//获取用户输入
		{
			char ch = 'q';	//创建并初始化字符ch
			ch = _getch();	//将用户输入的字符赋值给ch
			switch (ch)	//对输入的字符做出判断并采取相应的交互动作(以下仅为测试使用)
			{
			case 'w':
				cout << "For test up" << endl;
				break;
			case 's':
				cout << "For test down" << endl;
				break;
			case 'a':
				cout << "For test left" << endl;
				break;
			case 'd':
				cout << "For test right" << endl;
				break;
			default:
				break;
			}
		}
	}
	return 0;
}
------------------------------------------------------------------------------------------*/

/*----------------------------------------Part4 两个有用的例子----------------------------------------
1.字符移动
void color(int num)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), num);
}
void cursor()
{
	CONSOLE_CURSOR_INFO cci;	//定义光标信息结构体
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);	//获取光标信息  
	cci.dwSize = 1;	//设置光标大小     
	cci.bVisible = 0;	//设置光标不可见 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);	//应用光标信息  
}
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
int main()
{
	color(14);
	cursor(); 
	COORD pos = { 0,0 };
	gotoxy(pos.X, pos.Y);
	cout << "T";
	char ch = 'q';
	while (true)
	{
		if (_kbhit())
		{
			gotoxy(pos.X, pos.Y);
			cout << " ";
			ch = _getch();
			switch (ch)
			{
			case 'w':
				if (pos.Y > 0)//边界检查
					pos.Y--;
				break;
			case 's':
				if (pos.Y < 10)//边界检查
					pos.Y++;
				break;
			case 'a':
				if (pos.X > 0)//边界检查
					pos.X--;
				break;
			case 'd':
				if (pos.X < 30)//边界检查
					pos.X++;
				break;
			default:
				break;
			}
			gotoxy(pos.X, pos.Y);
			cout << "T";
		}
	}
	return 0;
}

2.列表选择
void color(int num)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), num);
}
void cursor()
{
	CONSOLE_CURSOR_INFO cci;	//定义光标信息结构体
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);	//获取光标信息  
	cci.dwSize = 1;	//设置光标大小     
	cci.bVisible = 0;	//设置光标不可见 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);	//应用光标信息  
}
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void Menu(string menu[], int size, int pos_x = 0, int pos_y = 0)
//menu是要显示的字符串数组，size是字符串数组的选项数，pos_x显示的横坐标（默认为0），pos_y显示的纵坐标（默认为0）
{
	//初始化有关变量
	int index = 0;
	char ch = 'q';

	//进入列表循环
	while (true)
	{
		//输出列表
		for (int i = 0; i < size; i++)
		{  
			if (i == index)
			{
				color(14);
				gotoxy(pos_x, pos_y + i);
				cout << *(menu + i);
			}
			else
			{
				color(15);
				gotoxy(pos_x, pos_y + i);
				cout << *(menu + i);
			}
		}

		//读取键盘输入并做出反应
		ch = _getch();
		switch (ch)
		{
		case 'w': 
			if (index > 0)  index -= 1;  
			break;
		case 's':
			if (index < size - 1)  index += 1;  
			break;
		case 13://这里使用ASCII表示，对应Enter键
			switch (index)//这里是可变部分，根据不同的需求调整
			{
			case 0:
				gotoxy(pos_x, pos_y + size);
				cout << "Choice one";
				break;
			case 1:
				gotoxy(pos_x, pos_y + size);
				cout << "Choice two";
				break;
			case 2: 
				return;   //退出
			default:
				break;
			}
		}		
	}
}
int main()
{
	cursor();
	string menu[]=
	{
		"one",
		"two",
		"quit"
	};
	Menu(menu, 3);//W,S控制上下选择，Enter确认
	return 0;
}
------------------------------------------------------------------------------------------*/

/*----------------------------------------Part5 控制台音乐----------------------------------------
系统相关API：
BOOL PlaySound(LPCSTR pszSound, HMODULE hmod,DWORD fdwSound)

说明：
需要包含头文件与相关库文件
#include<mmsystem.h>
#pragma comment(lib, "winmm.lib")

参数说明：
LPCSTR pszSound	指定了要播放声音的字符串，即文件路径（注意文件的格式只能是wav）
HMODULE hmod	一般设置为NULL即可
DWORD fdwSound	控制播放音乐的模式 可选值：
SND_FILENAME	pszSound参数指定了WAVE文件名
SND_ASYNC	用异步方式播放声音，PlaySound函数在开始播放后立即返回
SND_LOOP	重复播放声音，必须与SND_ASYNC标志一块使用
SND_SYNC	同步播放声音，在播放完后PlaySound函数才返回

例子：
int main()
{
	PlaySound(TEXT(".//music//Ever_Eternity.wav"), NULL, SND_FILENAME | SND_SYNC);
	return 0;
}
------------------------------------------------------------------------------------------*/


/*----------------------------------------Part6 高精度字符画----------------------------------------
以下代码既是讲解代码，也是测试代码

//字符画输出函数封装
void picturePainting(const std::string &filename, const int pic_width, const int pic_height, const int fontSize_X = 2, const int fontSize_Y = 2)
//filename文件路径名，pic_width字符画宽度，pic_height字符画高度，fontSize_X、fontSize_Y像素点大小
{
	//设置图画颜色
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	//设置字体信息
	CONSOLE_FONT_INFOEX font = { 0 };
	font.cbSize = sizeof(font);
	font.dwFontSize.X = fontSize_X;
	font.dwFontSize.Y = fontSize_Y;
	font.FontWeight = FW_NORMAL;
	wcscpy_s(font.FaceName, L"Lucida Console");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &font);
	//设置光标信息
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = 0;
	cursor.dwSize = 1;
	//设置屏幕大小
	HWND hWnd = GetConsoleWindow();
	MoveWindow(hWnd, -10, -40, GetSystemMetrics(SM_CXSCREEN) + 600, GetSystemMetrics(SM_CYSCREEN) + 600, 1);
	SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, GetSystemMetrics(SM_CXSCREEN) + 600, GetSystemMetrics(SM_CYSCREEN) + 600, NULL);
	//创建缓冲区
	HANDLE handle;
	handle = CreateConsoleScreenBuffer
	(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CONSOLE_TEXTMODE_BUFFER, 0);
	//设置缓冲区的大小
	COORD buffer_size = { pic_width, pic_height };
	SetConsoleScreenBufferSize(handle, buffer_size);
	//创建动态数组
	char** screen = new char*[pic_height];
	for (int count = 0; count < pic_height; count++)
		screen[count] = new char[pic_width];
	//把要显示的字符画存入数组
	std::ifstream get;
	get.open(filename);
	if (!get.good())
		exit(0);
	for (int i = 0; i < pic_height; i++)
	{
		get.getline(screen[i], pic_width);
		if (!screen[i][0])
			break;
	}
	get.close();
	//写入缓冲区（这里还可以改变输入图片的位置）
	for (int i = 0; i < pic_height; i++)
	{
		COORD coord = { 0, i };
		SetConsoleCursorPosition(handle, coord);
		WriteConsole(handle, screen[i], strlen(screen[i]), NULL, NULL);
		//if (!screen[i + 1][0])
		//break;
	}
	//激活缓冲区
	SetConsoleActiveScreenBuffer(handle);
	//删除动态数组
	delete[]screen;
}

//字符动画输出函数封装
std::string str_arr[500] = { "0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","55","56","57","58","59","60","61","62","63","64","65","66","67","68","69","70","71","72","73","74","75","76","77","78","79","80","81","82","83","84","85","86","87","88","89","90","91","92","93","94","95","96","97","98","99","100","101","102","103","104","105","106","107","108","109","110","111","112","113","114","115","116","117","118","119","120","121","122","123","124","125","126","127","128","129","130","131","132","133","134","135","136","137","138","139","140","141","142","143","144","145","146","147","148","149","150","151","152","153","154","155","156","157","158","159","160","161","162","163","164","165","166","167","168","169","170","171","172","173","174","175","176","177","178","179","180","181","182","183","184","185","186","187","188","189","190","191","192","193","194","195","196","197","198","199","200","201","202","203","204","205","206","207","208","209","210","211","212","213","214","215","216","217","218","219","220","221","222","223","224","225","226","227","228","229","230","231","232","233","234","235","236","237","238","239","240","241","242","243","244","245","246","247","248","249","250","251","252","253","254","255","256","257","258","259","260","261","262","263","264","265","266","267","268","269","270","271","272","273","274","275","276","277","278","279","280","281","282","283","284","285","286","287","288","289","290","291","292","293","294","295","296","297","298","299","300","301","302","303","304","305","306","307","308","309","310","311","312","313","314","315","316","317","318","319","320","321","322","323","324","325","326","327","328","329","330","331","332","333","334","335","336","337","338","339","340","341","342","343","344","345","346","347","348","349","350","351","352","353","354","355","356","357","358","359","360","361","362","363","364","365","366","367","368","369","370","371","372","373","374","375","376","377","378","379","380","381","382","383","384","385","386","387","388","389","390","391","392","393","394","395","396","397","398","399","400","401","402","403","404","405","406","407","408","409","410","411","412","413","414","415","416","417","418","419","420","421","422","423","424","425","426","427","428","429","430","431","432","433","434","435","436","437","438","439","440","441","442","443","444","445","446","447","448","449","450","451","452","453","454","455","456","457","458","459","460","461","462","463","464","465","466","467","468","469","470","471","472","473","474","475","476","477","478","479","480","481","482","483","484","485","486","487","488","489","490","491","492","493","494","495","496","497","498","499" };

void videoPainting(std::string filePath, int fileNumber, const int pic_width, const int pic_height, const int fontSize_X, const int fontSize_Y)
//filePath文件路径名，fileNumber图片数量（不能超过500张，由上面的数组大小决定），fileNumber、pic_height字符画大小，fontSize_X、fontSize_Y像素点大小
//注意这里对传入文件名有一定的要求（由下面传入给picturePainting的第一个参数格式决定）
{
	for (int count = 0; count < fileNumber; count++)
		picturePainting(filePath + str_arr[count] + ".txt", pic_width, pic_height, fontSize_X, fontSize_Y);
}

int main()
{
	char c;
	//下面准备了五张测试图片和一段测试视频，按Enter继续
	//这里窗口弹出来的时候不需要手动调整大小，按下Enter键后会自动调整
	picturePainting(".//picture//ASCII-test1.txt", 601, 198);
	while ((c = getchar()) != EOF && c != '\n');
	picturePainting(".//picture//ASCII-test2.txt", 601, 198);
	while ((c = getchar()) != EOF && c != '\n');
	picturePainting(".//picture//ASCII-test3.txt", 601, 198);
	while ((c = getchar()) != EOF && c != '\n');
	picturePainting(".//picture//ASCII-test4.txt", 601, 198);
	while ((c = getchar()) != EOF && c != '\n');
	picturePainting(".//picture//ASCII-test5.txt", 601, 198);
	while ((c = getchar()) != EOF && c != '\n');
	videoPainting(".//video//test", 107, 601, 198, 2, 2);
	Sleep(5000);
	return 0;
}
------------------------------------------------------------------------------------------*/