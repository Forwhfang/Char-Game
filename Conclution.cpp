/*------------------------------------------------------------------------------------------
#include "stdafx.h"
#include<WinSock2.h>//ע�����ͷ�ļ�һ��Ҫ����<Windows.h>������
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
Ŀ¼
Part1 ��Ŀ����
Part2 ��������̨API
Part3 ����������
Part4 �������õ�����
Part5 ����̨��������    ???
Part6 �߾����ַ�����ͼƬ&������
Part7 ����Socket���
------------------------------------------------------------------------------------------*/

/*----------------------------------------Part1 ��Ŀ����----------------------------------------
1.��������������
�ļ� -> �߼�����ѡ�� -> ������: ��������(GB2313-80)-����ҳ20936 -> ȷ��

2.�����ͬ��Ŀ�°汾�����ݵ�����
��Ŀ -> ���� -> �������� -> ���� -> Windows SDK�汾��ѡ����ʵļ��ɣ�

3.����ַ���ʱҪ�ı���뷽ʽ
��Ŀ -> ���� -> �������� -> ��ĿĬ��ֵ -> �ַ����� ʹ�ö��ֽ��ַ�����˫��ѡ�� 
------------------------------------------------------------------------------------------*/

/*----------------------------------------Part2 ��������̨API----------------------------------------
1.��������
��1��API�ĸ�����Լ򵥵�����API����һ��ϵͳ������һ���ӿڣ����ڵ���ϵͳ����Դ
     ϵͳ����ᶨ�����һЩ��������BOOL���ͺ�������ʹ����ʹ��
��2��HANDLE�ĸ�������HANDLE����Windows��̵�һ���ؼ��Եĸ�����Ա�ʶ��಻ͬ�Ķ������ͣ��細�ڡ��˵����ڴ桢���ʡ���ˢ�ȣ�
     һ����ÿ���̨API��Ҫ����һ�������Ϊ�����������õ��ľ��ֻ��STD_OUTPUT_HANDLE����׼��������
��3����Ҫ����ͷ�ļ�#include<Windows.h>

2.�����Ŀ���̨API�������һ�����Ƕ���װ��һ�����������Ժ�ֱ�ӵ��ã�

��1����ɫ����
��ص�ϵͳAPI��
BOOL SetConsoleTextAttribute(HANDLE hConsoleOutput, WORD wAttributes);

����˵����
hConsoleOutput���������ѡֵ��
 STD_INPUT_HANDLE ��׼����ľ��
 STD_OUTPUT_HANDLE ��׼����ľ��
 STD_ERROR_HANDLE ��׼����ľ��
wAttributes��������ɫ����ѡֵ��
 FOREGROUND_BLUE  ������ɫ����  ��Ӧ��ֵ��1
 FOREGROUND_GREEN  ������ɫ����  ��Ӧ��ֵ��2
 FOREGROUND_RED  ������ɫ����  ��Ӧ��ֵ��4
 FOREGROUND_INTENSITY  ǰ��ɫ������ʾ  ��Ӧ��ֵ��8
 BACKGROUND_BLUE  ������ɫ����  ��Ӧ��ֵ��16
 BACKGROUND_GREEN  ������ɫ����  ��Ӧ��ֵ��32
 BACKGROUND_RED  ������ɫ����  ��Ӧ��ֵ��64
 BACKGROUND_INTENSITY  ����ɫ������ʾ  ��Ӧ��ֵ��128

 ������װ��
void color(int num)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), num);
}

�÷�˵����
��������Ϊcolor
�������Ϊһ��ʮ��������������Χֵ0~15������ͬ����ɫ

����(����ֱ�Ӹ���һ�´��뵽����հ׵ĵط����в���)��
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

��2��λ�ÿ���
������װ���£�
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

�÷�˵����
��������Ϊgotoxy
�������Ϊ�������������ֱ�����ڿ���̨�ϵĺ�������

���ӣ�
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

��3��������
������װ���£�
void cursor()
{
	CONSOLE_CURSOR_INFO cci;	//��������Ϣ�ṹ��
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);	//��ȡ�����Ϣ  
	cci.dwSize = 1;	//���ù���С     
	cci.bVisible = 0;	//���ù�겻�ɼ� 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);	//Ӧ�ù����Ϣ  
}

�÷�˵����
ֱ�ӵ��ú����������ù��Ϊ���ɼ�
------------------------------------------------------------------------------------------*/

/*----------------------------------------Part3 ��������������----------------------------------------
������
_kbhit()�������������û����루ƽ�����������û������뵽�����������û�����Enter�����ٶ�ȡ�û����룬�������������ֱ�Ӷ�ȡ�û������룩
_getch()����ȡ�û������ֵ

˵����
��Ҫ����ͷ�ļ�#include<conio.h>

�÷�ģ�壺
int main()
{
	while (true)
	{
		if (_kbhit())//��ȡ�û�����
		{
			char ch = 'q';	//��������ʼ���ַ�ch
			ch = _getch();	//���û�������ַ���ֵ��ch
			switch (ch)	//��������ַ������жϲ���ȡ��Ӧ�Ľ�������(���½�Ϊ����ʹ��)
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

/*----------------------------------------Part4 �������õ�����----------------------------------------
1.�ַ��ƶ�
void color(int num)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), num);
}
void cursor()
{
	CONSOLE_CURSOR_INFO cci;	//��������Ϣ�ṹ��
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);	//��ȡ�����Ϣ  
	cci.dwSize = 1;	//���ù���С     
	cci.bVisible = 0;	//���ù�겻�ɼ� 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);	//Ӧ�ù����Ϣ  
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
				if (pos.Y > 0)//�߽���
					pos.Y--;
				break;
			case 's':
				if (pos.Y < 10)//�߽���
					pos.Y++;
				break;
			case 'a':
				if (pos.X > 0)//�߽���
					pos.X--;
				break;
			case 'd':
				if (pos.X < 30)//�߽���
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

2.�б�ѡ��
void color(int num)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), num);
}
void cursor()
{
	CONSOLE_CURSOR_INFO cci;	//��������Ϣ�ṹ��
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);	//��ȡ�����Ϣ  
	cci.dwSize = 1;	//���ù���С     
	cci.bVisible = 0;	//���ù�겻�ɼ� 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);	//Ӧ�ù����Ϣ  
}
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void Menu(string menu[], int size, int pos_x = 0, int pos_y = 0)
//menu��Ҫ��ʾ���ַ������飬size���ַ��������ѡ������pos_x��ʾ�ĺ����꣨Ĭ��Ϊ0����pos_y��ʾ�������꣨Ĭ��Ϊ0��
{
	//��ʼ���йر���
	int index = 0;
	char ch = 'q';

	//�����б�ѭ��
	while (true)
	{
		//����б�
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

		//��ȡ�������벢������Ӧ
		ch = _getch();
		switch (ch)
		{
		case 'w': 
			if (index > 0)  index -= 1;  
			break;
		case 's':
			if (index < size - 1)  index += 1;  
			break;
		case 13://����ʹ��ASCII��ʾ����ӦEnter��
			switch (index)//�����ǿɱ䲿�֣����ݲ�ͬ���������
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
				return;   //�˳�
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
	Menu(menu, 3);//W,S��������ѡ��Enterȷ��
	return 0;
}
------------------------------------------------------------------------------------------*/

/*----------------------------------------Part5 ����̨����----------------------------------------
ϵͳ���API��
BOOL PlaySound(LPCSTR pszSound, HMODULE hmod,DWORD fdwSound)

˵����
��Ҫ����ͷ�ļ�����ؿ��ļ�
#include<mmsystem.h>
#pragma comment(lib, "winmm.lib")

����˵����
LPCSTR pszSound	ָ����Ҫ�����������ַ��������ļ�·����ע���ļ��ĸ�ʽֻ����wav��
HMODULE hmod	һ������ΪNULL����
DWORD fdwSound	���Ʋ������ֵ�ģʽ ��ѡֵ��
SND_FILENAME	pszSound����ָ����WAVE�ļ���
SND_ASYNC	���첽��ʽ����������PlaySound�����ڿ�ʼ���ź���������
SND_LOOP	�ظ�����������������SND_ASYNC��־һ��ʹ��
SND_SYNC	ͬ�������������ڲ������PlaySound�����ŷ���

���ӣ�
int main()
{
	PlaySound(TEXT(".//music//Ever_Eternity.wav"), NULL, SND_FILENAME | SND_SYNC);
	return 0;
}
------------------------------------------------------------------------------------------*/


/*----------------------------------------Part6 �߾����ַ���----------------------------------------
���´�����ǽ�����룬Ҳ�ǲ��Դ���

//�ַ������������װ
void picturePainting(const std::string &filename, const int pic_width, const int pic_height, const int fontSize_X = 2, const int fontSize_Y = 2)
//filename�ļ�·������pic_width�ַ�����ȣ�pic_height�ַ����߶ȣ�fontSize_X��fontSize_Y���ص��С
{
	//����ͼ����ɫ
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	//����������Ϣ
	CONSOLE_FONT_INFOEX font = { 0 };
	font.cbSize = sizeof(font);
	font.dwFontSize.X = fontSize_X;
	font.dwFontSize.Y = fontSize_Y;
	font.FontWeight = FW_NORMAL;
	wcscpy_s(font.FaceName, L"Lucida Console");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &font);
	//���ù����Ϣ
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = 0;
	cursor.dwSize = 1;
	//������Ļ��С
	HWND hWnd = GetConsoleWindow();
	MoveWindow(hWnd, -10, -40, GetSystemMetrics(SM_CXSCREEN) + 600, GetSystemMetrics(SM_CYSCREEN) + 600, 1);
	SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, GetSystemMetrics(SM_CXSCREEN) + 600, GetSystemMetrics(SM_CYSCREEN) + 600, NULL);
	//����������
	HANDLE handle;
	handle = CreateConsoleScreenBuffer
	(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CONSOLE_TEXTMODE_BUFFER, 0);
	//���û������Ĵ�С
	COORD buffer_size = { pic_width, pic_height };
	SetConsoleScreenBufferSize(handle, buffer_size);
	//������̬����
	char** screen = new char*[pic_height];
	for (int count = 0; count < pic_height; count++)
		screen[count] = new char[pic_width];
	//��Ҫ��ʾ���ַ�����������
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
	//д�뻺���������ﻹ���Ըı�����ͼƬ��λ�ã�
	for (int i = 0; i < pic_height; i++)
	{
		COORD coord = { 0, i };
		SetConsoleCursorPosition(handle, coord);
		WriteConsole(handle, screen[i], strlen(screen[i]), NULL, NULL);
		//if (!screen[i + 1][0])
		//break;
	}
	//�������
	SetConsoleActiveScreenBuffer(handle);
	//ɾ����̬����
	delete[]screen;
}

//�ַ��������������װ
std::string str_arr[500] = { "0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","55","56","57","58","59","60","61","62","63","64","65","66","67","68","69","70","71","72","73","74","75","76","77","78","79","80","81","82","83","84","85","86","87","88","89","90","91","92","93","94","95","96","97","98","99","100","101","102","103","104","105","106","107","108","109","110","111","112","113","114","115","116","117","118","119","120","121","122","123","124","125","126","127","128","129","130","131","132","133","134","135","136","137","138","139","140","141","142","143","144","145","146","147","148","149","150","151","152","153","154","155","156","157","158","159","160","161","162","163","164","165","166","167","168","169","170","171","172","173","174","175","176","177","178","179","180","181","182","183","184","185","186","187","188","189","190","191","192","193","194","195","196","197","198","199","200","201","202","203","204","205","206","207","208","209","210","211","212","213","214","215","216","217","218","219","220","221","222","223","224","225","226","227","228","229","230","231","232","233","234","235","236","237","238","239","240","241","242","243","244","245","246","247","248","249","250","251","252","253","254","255","256","257","258","259","260","261","262","263","264","265","266","267","268","269","270","271","272","273","274","275","276","277","278","279","280","281","282","283","284","285","286","287","288","289","290","291","292","293","294","295","296","297","298","299","300","301","302","303","304","305","306","307","308","309","310","311","312","313","314","315","316","317","318","319","320","321","322","323","324","325","326","327","328","329","330","331","332","333","334","335","336","337","338","339","340","341","342","343","344","345","346","347","348","349","350","351","352","353","354","355","356","357","358","359","360","361","362","363","364","365","366","367","368","369","370","371","372","373","374","375","376","377","378","379","380","381","382","383","384","385","386","387","388","389","390","391","392","393","394","395","396","397","398","399","400","401","402","403","404","405","406","407","408","409","410","411","412","413","414","415","416","417","418","419","420","421","422","423","424","425","426","427","428","429","430","431","432","433","434","435","436","437","438","439","440","441","442","443","444","445","446","447","448","449","450","451","452","453","454","455","456","457","458","459","460","461","462","463","464","465","466","467","468","469","470","471","472","473","474","475","476","477","478","479","480","481","482","483","484","485","486","487","488","489","490","491","492","493","494","495","496","497","498","499" };

void videoPainting(std::string filePath, int fileNumber, const int pic_width, const int pic_height, const int fontSize_X, const int fontSize_Y)
//filePath�ļ�·������fileNumberͼƬ���������ܳ���500�ţ�������������С��������fileNumber��pic_height�ַ�����С��fontSize_X��fontSize_Y���ص��С
//ע������Դ����ļ�����һ����Ҫ�������洫���picturePainting�ĵ�һ��������ʽ������
{
	for (int count = 0; count < fileNumber; count++)
		picturePainting(filePath + str_arr[count] + ".txt", pic_width, pic_height, fontSize_X, fontSize_Y);
}

int main()
{
	char c;
	//����׼�������Ų���ͼƬ��һ�β�����Ƶ����Enter����
	//���ﴰ�ڵ�������ʱ����Ҫ�ֶ�������С������Enter������Զ�����
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