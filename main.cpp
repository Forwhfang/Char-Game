#include"backpack.h"
#include"role.h"
#include"charpic.h"
#include<Windows.h>
#include<iostream>
#include<fstream>
#include<time.h>
#include <conio.h>  
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#pragma warning(disable:4996)
using namespace std;

int flag = 0;//��ʶս��״̬
int print = 0;//��ͼ�д�ӡ����
int difficulty = 0;//�Ѷ�ѡ��
double saber_nivose_one = 1;//���ڼ���
int archer_nivose_two = 0;//���ڼ���
int characterORcharacterprinting = 0;//�ַ�ģʽ|�ַ���ģʽ

int preScore = 0;//��ǰ����
int highestScore= 0;//��ʷ��߷�

COORD pos = {6, 25};//��ʼλ��

Backpack myBackpack;//������ʼ��
Protagonist *protagonist;//����ָ���ʼ��

//�������ǳ�ʼ��
Saber saber(1);//Saber��ʼ��
Archer archer(1);//Archer��ʼ��
Lancer lancer(1);//Lancer��ʼ��

//Boss��ʼ��
Villain boss_one(1);
Villain boss_two(1);
Villain boss_three(1);
Villain boss_four(1);
Villain boss_five(1);

//�����ַ��������
string str_arr[500] = { "0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","55","56","57","58","59","60","61","62","63","64","65","66","67","68","69","70","71","72","73","74","75","76","77","78","79","80","81","82","83","84","85","86","87","88","89","90","91","92","93","94","95","96","97","98","99","100","101","102","103","104","105","106","107","108","109","110","111","112","113","114","115","116","117","118","119","120","121","122","123","124","125","126","127","128","129","130","131","132","133","134","135","136","137","138","139","140","141","142","143","144","145","146","147","148","149","150","151","152","153","154","155","156","157","158","159","160","161","162","163","164","165","166","167","168","169","170","171","172","173","174","175","176","177","178","179","180","181","182","183","184","185","186","187","188","189","190","191","192","193","194","195","196","197","198","199","200","201","202","203","204","205","206","207","208","209","210","211","212","213","214","215","216","217","218","219","220","221","222","223","224","225","226","227","228","229","230","231","232","233","234","235","236","237","238","239","240","241","242","243","244","245","246","247","248","249","250","251","252","253","254","255","256","257","258","259","260","261","262","263","264","265","266","267","268","269","270","271","272","273","274","275","276","277","278","279","280","281","282","283","284","285","286","287","288","289","290","291","292","293","294","295","296","297","298","299","300","301","302","303","304","305","306","307","308","309","310","311","312","313","314","315","316","317","318","319","320","321","322","323","324","325","326","327","328","329","330","331","332","333","334","335","336","337","338","339","340","341","342","343","344","345","346","347","348","349","350","351","352","353","354","355","356","357","358","359","360","361","362","363","364","365","366","367","368","369","370","371","372","373","374","375","376","377","378","379","380","381","382","383","384","385","386","387","388","389","390","391","392","393","394","395","396","397","398","399","400","401","402","403","404","405","406","407","408","409","410","411","412","413","414","415","416","417","418","419","420","421","422","423","424","425","426","427","428","429","430","431","432","433","434","435","436","437","438","439","440","441","442","443","444","445","446","447","448","449","450","451","452","453","454","455","456","457","458","459","460","461","462","463","464","465","466","467","468","469","470","471","472","473","474","475","476","477","478","479","480","481","482","483","484","485","486","487","488","489","490","491","492","493","494","495","496","497","498","499" };

//0�����ݵ�   1��������   2����ɭ��   3�������ݣ����ģ�   4�������ݣ��̵꣩   5~9�������ݣ����ݣ�  10����NPC  11�������͵�
int mapPartOne[27][98] = {
	{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
	{ 2,2,2,4,4,0,0,0,0,0,0,0,0,0,5,5,5,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,2,2,1,0,0,0,2,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,9,9,9,2,2 },
	{ 2,2,2,4,4,0,0,0,0,0,0,0,0,0,5,5,5,2,2,2,2,2,2,2,2,2,10,0,0,0,0,0,0,2,2,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,2,0,0,0,2,2,0,0,2,2,0,0,2,0,2,2,2,2,2,2,0,0,0,0,0,9,9,9,2,2 },
	{ 2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,0,0,0,2,2,0,0,1,2,2,0,0,0,0,2,0,0,2,2,2,2,2,2,2,2,2,2,0,0,0,2,2,0,0,10,2,0,2,2,0,0,0,0,2,2,2,0,0,0,0,0,2,2,2,0,2,0,2,2,2,0,2,2,0,0,0,0,2,2,2,2,2,2 },
	{ 2,2,2,2,2,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,2,0,0,2,2,0,0,2,2,2,2,2,2,2,2,2,2,0,0,0,2,2,0,0,2,2,0,2,0,0,0,2,2,2,2,0,0,0,0,0,0,0,2,2,0,2,0,2,2,0,2,0,2,0,0,0,0,0,10,2,2,2,2 },
	{ 2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,2,2,0,0,2,2,2,2,2,2,2,2,2,2,0,0,0,2,2,0,0,2,2,0,0,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,2,0,0,0,2,2,0,0,0,0,0,0,0,0,2,2,2,2,2,2 },
	{ 2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,2,2,2,2,0,0,2,2,0,0,2,2,2,2,2,2,2,2,2,2,0,0,0,2,2,0,0,2,0,0,0,2,0,0,0,0,2,2,2,2,2,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,2,0,0,2,2,2,2,2,2 },
	{ 2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,2,2,0,0,2,2,0,0,2,2,2,2,2,2,2,2,2,2,0,0,0,2,2,0,0,2,0,0,0,0,2,0,0,0,2,2,2,2,2,2,0,0,0,0,0,0,0,0,2,0,0,2,2,2,2,2,0,0,2,2,2,2,2,2 },
	{ 2,2,0,0,2,2,2,2,0,0,0,0,0,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,2,2,0,0,0,2,2,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,2,0,2,2,0,0,0,0,0,2,2,2,2,2,2,2,0,0,2,2,2,2,0,0,0,2,2,2,2,2,2,0,0,2,2,2,2,2,2 },
	{ 2,2,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,2,2,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,2,0,0,2,2,0,0,0,0,2,2,2,2,2,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,2,2,2,2,2,2 },
	{ 2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,2,2,0,0,0,2,2,2,2,0,0,2,2,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,0,0,2,0,0,0,0,2,0,0,0,2,2,2,2,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,2,2,2,2,2,2 },
	{ 2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,2,2,0,0,0,2,2,2,2,0,0,2,2,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,0,0,2,2,0,0,0,0,0,2,0,0,2,2,2,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,0,2,0,0,0,0,0,1,2,2,2 },
	{ 2,2,0,0,0,0,0,0,0,0,2,2,2,2,2,2,0,0,2,2,2,2,0,0,0,0,0,0,0,2,2,0,0,0,2,2,2,2,0,0,2,2,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,0,0,2,2,2,2,2,2,2,0,0,0,2,2,2,0,0,0,0,0,0,0,10,2,2,2,2,2,2,0,0,0,2,0,0,0,0,2,2,2,2 },
	{ 2,2,10,0,0,0,0,0,0,0,2,2,2,2,2,2,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,10,2,2,0,0,0,2,2,2,2,2,0,0,2,2,2,2,2,0,0,0,2,0,2,2,2,2,2,2,0,0,0,0,0,0,2,0,0,0,0,2,2,2,2 },
	{ 2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,0,0,2,2,2,2,0,0,0,0,2,2,2,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,7,7,7,2,2,2,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,10,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,2,0,0,0,2,2,2,2 },
	{ 2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,0,0,2,2,2,2,0,0,0,0,2,2,2,2,0,10,0,2,2,2,2,2,2,0,0,0,0,0,7,7,7,2,2,2,0,0,2,0,0,2,2,2,2,0,0,0,0,0,2,2,2,2,2,2,2,0,0,0,2,2,2,2,2,2,2,2,2,0,0,0,0,2,2,0,0,0,0,0,0,10,2,2 },
	{ 2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,2,0,0,2,2,2,2,2,0,0,0,0,2,2,2,2,2,0,0,0,0,0,2,2,2,2,2,2,2,2,2,0,0,0,2,0,2,0,0,0,0,0,2,0,2,2 },
	{ 2,2,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,1,2,2,2,2,0,0,0,0,2,2,2,2,2,2,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,0,0,2,0,0,2,2,2,2,2,0,0,0,0,2,2,3,3,0,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,2,0,0,0,0,0,2,0,0,2,0,0,2,2 },
	{ 2,2,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,2,2,2,10,0,0,0,0,0,0,2,2,2,2,0,0,0,10,2,2,2,0,0,2,0,0,2,2,2,2,2,0,0,0,0,2,2,3,3,0,0,0,0,0,2,2,2,2,2,2,2,2,0,0,0,2,2,0,0,0,2,0,2,2,0,2,0,2,2 },
	{ 2,2,0,0,0,0,0,0,0,0,0,0,3,3,2,2,2,2,2,2,2,2,0,0,2,2,0,0,0,1,2,2,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,2,0,0,2,2,2,2,2,2,0,0,0,2,2,2,2,0,0,0,0,0,0,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2 },
	{ 2,2,0,0,0,0,0,0,0,0,0,0,3,3,2,2,2,2,2,2,2,0,0,0,0,2,2,0,0,0,0,2,0,0,2,2,2,0,0,2,2,2,0,0,0,0,0,0,2,2,0,0,2,0,0,2,2,2,2,2,2,0,0,2,2,2,2,2,2,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,10,0,0,0,0,0,0,0,0,0,0,2,2,2 },
	{ 2,2,2,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,0,0,0,0,0,0,2,2,2,2,2,2,0,0,2,2,2,0,0,2,2,2,0,0,0,0,0,0,2,2,0,0,2,0,0,2,2,2,2,2,4,4,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,0,2,0,2,0,0,2,2,2,2,2,2,2 },
	{ 2,2,2,2,2,0,0,0,0,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,2,2,2,4,4,0,0,0,0,0,0,2,10,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,0,2,0,2,0,0,0,0,0,0,0,2,2 },
	{ 2,2,2,2,2,0,0,0,0,2,2,2,2,2,2,2,2,2,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,2,2,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,0,0,2,2,0,0,0,0,0,2,0,0,0,2,2,2,2,2,2,0,2,0,2,0,0,0,0,0,0,0,2,2 },
	{ 2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,2,2,2,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,2,2,2,2,2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,8,8,8,2,2,2,2,2,0,0,0,2,2,0,0,0,0,0,0,2,2 },
	{ 2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,10,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,3,3,2,2,2,2,2,1,0,0,0,0,10,2,2,2,0,0,0,0,0,0,8,8,8,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,11,2,2 },
	{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 }
};

//����
string str_question[]//23
{
	//������ѧ�����ڶ��¡�������������
	"���ޣ�lim(x->2) (x^2 - x - 2) / (x^3 - 3x^2 + 2x)",//3/2
	"���ޣ�lim(x->��) (x^2 + 2) / (x^2 - 6)",//1
	"���ޣ�lim(x->��) (x^2) / 2^x",//0 
	"���ޣ�lim(x->��) x��x",//1 
	"���ޣ�lim(x->��) sinx / x",//0 
	"���ޣ�lim(n->��) n!/n^n ",//0 
	"���ޣ�lim(n->��) (1 + 2 + 3 + ���� + n-1) / n^2",//1/2 
	"������y = ��(1 + x^2)�Ľ����� A.y=x+1 B.y=x-1 C.y=x+1,y=x-1",//C
	"���ޣ�lim(n->��) 1/2! + 2/3! + ���� + n/(n+1)!",//1 
	"���ޣ�lim(x->0) sinx / x",//1  
	"���ޣ�lim(x->��) (1 + 1/x)^x",//e
	"���ޣ�lim(n->��) n^(1/n)",//1
	"���ޣ�lim(x->0) (tanx - sinx) / [(sinx)^3]",//1/2
	"���ޣ�lim(n->��) 2^n / n!",//0
	"�����м��ޣ�  x_n+1 = ��(2x_n)",//2  
	"�����м��ޣ�  x_n+1 = ��(x_n + 6)",//3
	"���ޣ�lim(x->0) [(1 + x)^a - 1] / x   (a != 0)",//a 
	"���ޣ�lim(x->1) arcsin(1 - x) / lnx",//-1
	"�жϼ�ϵ����ͣ�y=lim(n->��) [1-x^(2n)]/[1+x^(2n)],��Ϊx = 1   A.��Ծ B.��ȥ C.����",//A
	"���ޣ�lim(n->��) cos(x/2) cos(x/2^2) ���� cos(x/2^n)",//sinx/x
	"���ޣ�lim(n->��) [sin��(n + 1)] - [sin��n]",//0
	"���ޣ�lim(x->4) {[��(2x + 1)] - 3} / {[��(x - 2)] - ��2}",//0
	"���ޣ�lim(a->��) sina / [1 - (a/��)^2]",//1
};

//�����
string str_answer[]//23
{
	//������ѧ�����ڶ��¡�������������
	"3/2",
	"1",
	"0",
	"1",
	"0",
	"0",
	"1/2",
	"C",
	"1",
	"1",
	"e",
	"1",
	"1/2",
	"0",
	"2",
	"3",
	"a",
	"-1",
	"A",
	"sinx/x",
	"0",
	"2��2/3",
	"��/2",
};

//�������
string str_analysis[]//24
{
	//������ѧ�����ڶ��¡�������������
	"ϰ���ƽ⼼�����ޣ�lim(x->2) (x^2 - x - 2) / (x^3 - 3x^2 + 2x)������ش﷨��0/0�ͣ�",
	"ϰ���ƽ⼼�����ޣ�lim(x->��) (x^2 + 2) / (x^2 - 6)�����߽�����С��ֻ����ߴ������жϼ���",
	"ϰ���ƽ⼼�����ޣ�lim(x->��) (x^2) / 2^x������һ����ش﷨�򣨡�/���ͣ������������ӡ���ĸͼ��۲취",
	"ϰ���ƽ⼼�����ޣ�lim(x->��) x��x�������γ��ݺ�����ʽe^[ln(x��x)]=e^(lnx/x),Ȼ��ֱ�Ӷ�ָ��λ�����޼���",
	"ϰ���ƽ⼼�����ޣ�lim(x->��) sinx / x�������γ�sinx*��1/x�������ö����н���*����С=����С�������������С",
	"ϰ���ƽ⼼�����ޣ�lim(n->��) n!/n^n �����бƶ���( 0 < n!/n^n = n/n * n-1/n * ���� * 1/n < 1/n ),Ȼ�����������޼бƼ���",
	"ϰ���ƽ⼼�����ޣ�lim(n->��) (1 + 2 + 3 + ���� + n-1) / n^2�����������õȲ�������͹�ʽ��Ȼ�����廯���(n - 1) / 2n",
	"ϰ���ƽ⼼��������y = ��(1 + x^2)�Ľ����� A.y=x+1 B.y=x-1 C.y=x+1,y=x-1�������㽥���߿��Է�����������ǣ�б�ʲ����ڣ��������ߴ�ֱ��x����������Ҫ���춨�岻���ڵ㣩��б�ʴ��ڣ����ù�ʽ�ֱ����б�ʽؾࣩ",
	"ϰ���ƽ⼼�����ޣ�lim(n->��) 1/2! + 2/3! + ���� + n/(n+1)!�����������������ʾ��n/(n+1)! = 1/n! - 1/(n+1)!",
	"ϰ���ƽ⼼�����ޣ�lim(x->0) sinx / x������Ҫ���޹�ʽ��Ҳ������ش﷨��⣨0/0�ͣ�",
	"ϰ���ƽ⼼�����ޣ�lim(x->��) (1 + 1/x)^x������Ҫ���޹�ʽ��ע����ʽ��1������η���",
	"ϰ���ƽ⼼�����ޣ�lim(n->��) n^(1/n)���������ݺ�����ʽe^(lnn/n),Ȼ��ֱ�Ӷ�ָ��λ�����޼���",
	"ϰ���ƽ⼼�����ޣ�lim(x->0) (tanx - sinx) / [(sinx)^3]�����������tanx���õȼ�����С�滻����ĸֱ���õȼ�����С�滻",
	"ϰ���ƽ⼼�����ޣ�lim(n->��) 2^n / n!�����бƶ���0 < 2^n/n! = 2/1 * 2/2 * ���� * 2/n < 2/1 * 2/2 * 2/n = 4/n,Ȼ������ȡ���޼б��м伴��",
	"ϰ���ƽ⼼�������м��ޣ�  x_n+1 = ��(2x_n)�����������ͣ������н������Զ���֤�������������ٽ�x_n+1��x_n����һ���Ԫa��ⷽ�̵�a��Ϊ��",
	"ϰ���ƽ⼼�������м��ޣ�  x_n+1 = ��(x_n + 6)�����������ͣ������н������Զ���֤�������������ٽ�x_n+1��x_n����һ���Ԫa��ⷽ�̵�a��Ϊ��",
	"ϰ���ƽ⼼�����ޣ�lim(x->0) [(1 + x)^a - 1] / x   (a != 0)������ش﷨��0/0�ͣ�",
	"ϰ���ƽ⼼�����ޣ�lim(x->1) arcsin(1 - x) / lnx������ش﷨��0/0�ͣ�",
	"ϰ���ƽ⼼���жϼ�ϵ����ͣ�y=lim(n->��) [1-x^(2n)]/[1+x^(2n)],��Ϊx = 1   A.��Ծ B.��ȥ C.����������ü��޸����ĺ����Ƚ��л��򣬶�x�������ۣ�|x|=1,|x|<1,|x|>1������֪��Ϊ�ֶκ������������жϷֶε�ͺ����޶���㼴��",
	"ϰ���ƽ⼼�����ޣ�lim(n->��) cos(x/2) cos(x / 2^2) ���� cos(x / 2^n)������շ���ԭʽ����2sin(x/2^n)���ٳ���2sin(x / 2^n)��Ȼ���ö����ǹ�ʽһֱ�����sinx/[(2^n) * sin(x / 2^n)]��Ȼ��Է�ĸ�����x*sin(x / 2^n) / (x / 2^n)������Ҫ���޹�ʽ��x",
	"ϰ���ƽ⼼�����ޣ�lim(n->��) [sin��(n + 1)] - [sin��n]�������úͲ����ʽ��Ϊ2 cos{[��(n + 1)+��n]/2} sin{[��(n + 1)-��n]/2}�������õȼ��滻�ɼ�Ϊcos{[��(n + 1)+��n]/2} [��(n + 1)-��n]�����н�����������С�����������С",
	"ϰ���ƽ⼼�����ޣ�lim(x->4) {[��(2x + 1)] - 3} / {[��(x - 2)] - ��2}������ش﷨��0/0�ͣ�",
	"ϰ���ƽ⼼�����ޣ�lim(a->��) sina / [1 - (a/��)^2]������Ԫ������t=a/�У�ע�⻻ԪҪ���ޣ���Ȼ��ʹ����ش﷨��0/0�ͣ�",
	"�����治�ã�����ʲôҲû��Ŷ��"
};

//npc�԰�
string sayings_npc[]//32
{
	"����ʲôʱ���ܹ��ı�������˶���һ��׷��������ˣ�",
	"��˵������������㼯�ɵ���?",
	"������Щ�����ˣ�ӵ�й�ȥ����ʷ�ͼ��䡣��������Щ�����ˣ���ӵ����δ֪��δ����!",
	"���Ӱ���׷��һ���ǲ��ҵĿ�ʼ�����������������ͬʱҲ�������������飬֪����һ��ǳ���Ҫ��",
	"�����������ʶ����ľ�ɫ��������Ϊ֪��������Ĺ������Լ�����С���Ż���������ϣ���أ�",
	"�ҡ���ΪʲôҪ�����أ��㻹�ǵ���̤����;��������",
	"ʲô�������Ļ��䲻��ʧ�ܣ���Ҳ����ɹ�������",
	"�ɳ�������һ�����£������˳���֮�Ĳ�������ġ�",
	"�ҵ����ӵ�ӳ��ˮ���ϣ��ǳ�����ϣ����Ц�������꣬�������ҿ��������������������",
	"��֪���𣬱��˳�Ц�����룬��Խ��ʵ�ֵļ�ֵ��",
	"��ϣ���Լ���һ�������ؾ�����⣬��Ȼ�����е���ĩ�ң��������ƺ�΢�磬���ԵĻ�ϲ����",
	"�ٺ٣����˶���ʲô��˼�����춷����������ġ�",
	"ÿһ�����������������ɳ������ҹ��Ϣ�����������У��˴˸ı��ŶԷ�����״����",
	"�������ѷ죬������յý���",
	"һ������һϪ�£�һ��ɽˮһ�껪����",
	"�㿴����Ļ��ֿ��ˣ��������ǿ�ϧ�����ж��ٷ�����֦���ͻ��ж�����Ҷ���䡣",
	"����˵����������żȻ������ÿ��������Ҫ������һ������������Ϊ���������С�",
	"����˵����������żȻ������ÿ����������������һ����������һ��磬��ǣ�޹ҡ�",
	"��������������������У������ҵ�׷�󰡣�",
	"����û����Ϣ�ĵط��������ﶼ�������ˡ�",
	"����������һֻ��Ҷ������������ĵĺ�����δ���ѣ���Ҷ����һ����Ҳֻ������һƬ���ԵĿ�Ҷ�ء�",
	"�������޻���Ǿޱ����Զ������䡭��",
	"ԭ��û���ң����û��ʲô��ͬ��",
	"�Σ���������̫����ˣ��������ѡ���",
	"ֻ�������Լ�Ը�����ŵ����������ȥ��������ˡ���",
	"���ɣ����ǲ�����ģ������䣬���ӱܣ�����û�в�ͣ���ꡣ",
	"��һֱ��Ѱ�����ܹ�����ҵ��ˡ�������˾������ģ�",
	"�������Ҫ������ʱ�򣬺�֮��ͻ���֡����ǹ��ϵ�Ԥ�ԡ�",
	"��һ����������һ������������ʱ�򣬻�������ʲô��?"
	"�����ʶ��ʶ�ҵ������ɣ���ø��Ӹ���ǿ��",
	"�Ǹ���������һ�ּ�Ӳ�ִ����Ķ�����",
	"�尡��"
};

//��װ������������
//��ת������̨�ض�λ��
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//�������������ɫ
void color(int num)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), num);
}
//���ù���ʽ
void cursor()
{
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);	//��ȡ�����Ϣ  
	cci.dwSize = 1;	//���ù���С     
	cci.bVisible = 0;	//���ù�겻�ɼ� 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);	//����(Ӧ��)�����Ϣ  
}

//��ͼ��Ϣ���ַ�ģʽ|�ַ���ģʽ
void modePrint()
{
	gotoxy(102, 3);
	cout << "                   ";

	color(15);
	gotoxy(102, 1);
	if (characterORcharacterprinting == 0)
		cout << "�ַ�ģʽ";
	else if (characterORcharacterprinting == 1)
		cout << "�ַ���ģʽ";
}

//��ͼ��Ϣ����Ϸ����
void scoreDataPrint()
{
	gotoxy(102, 3);
	cout << "                  ";
	gotoxy(102, 4);
	cout << "                  ";
	gotoxy(102, 5);
	cout << "                  ";

	color(15);
	gotoxy(102, 3);
	cout << "����";
	gotoxy(102, 4);
	cout << "��ǰ����  �� " << preScore;
	gotoxy(102, 5);
	cout << "��ʷ��߷֣� " << highestScore;
}

//��ͼ��Ϣ��������Ϣ
void roleDataPrint(Protagonist* temp_protagonist)
{
	gotoxy(102, 7);
	cout << "               ";
	gotoxy(102, 8);
	cout << "               ";
	gotoxy(102, 9);
	cout << "               ";
	gotoxy(102, 10);
	cout << "               ";
	gotoxy(102, 11);
	cout << "               ";
	gotoxy(102, 12);
	cout << "               ";
	gotoxy(102, 13);
	cout << "               ";

	color(15);
	gotoxy(102, 7);
	if (print == 0)
		cout << "Saber";
	else if (print == 1)
		cout << "Archer";
	else if (print == 2)
		cout << "Lancer";
	gotoxy(102, 8);
	cout << "PH   ��" << temp_protagonist->getPrePH() << " / " << temp_protagonist->getPH();
	gotoxy(102, 9);
	cout << "EXP  : " << temp_protagonist->getPreEXP() << " / " << temp_protagonist->getEXP();
	gotoxy(102, 10);
	cout << "LV   : " << temp_protagonist->getLV();
	gotoxy(102, 11);
	cout << "ATK  : " << temp_protagonist->getATK();
	gotoxy(102, 12);
	cout << "DEF  : " << temp_protagonist->getDEF();
	gotoxy(102, 13);
	cout << "Money: " << temp_protagonist->getMoney();
}

//��ͼ��Ϣ��������Ϣ
void backpackDataPrint()
{
	gotoxy(102, 16);
	cout << "              ";
	gotoxy(102, 17);
	cout << "              ";
	gotoxy(102, 18);
	cout << "              ";
	gotoxy(102, 19);
	cout << "              ";

	color(15);
	gotoxy(102, 15);
	cout << "����";
	gotoxy(102, 16);
	cout << "��ҩ  �� " << myBackpack.getCurePH();
	gotoxy(102, 17);
	cout << "����ҩ�� " << myBackpack.getCurePHgood();
	gotoxy(102, 18);
	cout << "���鵤�� " << myBackpack.getEnhanceEXP();
	gotoxy(102, 19);
	cout << "����  �� " << myBackpack.getBadge();
}

//��ӡ�ַ���ͼ
void mapPrint(Protagonist* temp_protagonist)
{
	for (int i = 0; i <= 27; i++)
	{
		for (int j = 0; j <= 98; j++)
		{
			//�ݵء���0
			if (mapPartOne[i][j] == 0)
				cout << " ";
			//���䡪��1
			if (mapPartOne[i][j] == 1)
			{
				color(11);
				cout << "@";
			}
			//ɭ�֡���2
			if (mapPartOne[i][j] == 2)
			{
				color(10);
				cout << "x";
			}
			//ҽԺ����3
			if (mapPartOne[i][j] == 3)
			{
				color(13);
				cout << "#";
			}
			//�̵ꡪ��4
			if (mapPartOne[i][j] == 4)
			{
				color(9);
				cout << "#";
			}
			//��ݡ���5~9
			if (mapPartOne[i][j] == 5 || mapPartOne[i][j] == 6 || mapPartOne[i][j] == 7 || mapPartOne[i][j] == 8 || mapPartOne[i][j] == 9)
			{
				color(14);
				cout << "#";
			}
			//NPC����10
			if (mapPartOne[i][j] == 10)
			{
				color(12);
				cout << "Y";
			}
			//���͵㡪��11
			if (mapPartOne[i][j] == 11)
			{
				color(12);
				cout << "@";
			}
		}
		cout << endl;
	}
	modePrint();
	scoreDataPrint();
	roleDataPrint(temp_protagonist);
	backpackDataPrint();
}

//ս��������Ϣ�����ͣ����ӳ٣�
void fightScene()
{
	color(14);

	//�߿�(99, 28)
	gotoxy(0, 0);
	for (int count = 1; count <= 50; count++)
	{
		cout << "* ";
		Sleep(20);
	}

	for (int count = 1; count <= 27; count++)
	{
		gotoxy(0, count);
		cout << "*";
		gotoxy(98, count);
		cout << "*";
		Sleep(20);
	}

	gotoxy(0, 27);
	for (int count = 0; count < 50; count++)
	{
		cout << "* ";
		Sleep(20);
	}

	gotoxy(0, 19);
	for (int count = 1; count <= 50; count++)
	{
		cout << "* ";
		Sleep(20);
	}

	for (int count = 19; count <= 27; count++)
	{
		gotoxy(40, count);
		cout << "*";
		Sleep(20);
	}

	gotoxy(0, 9);
	for (int count = 1; count <= 50; count++)
	{
		cout << "* ";
		Sleep(20);
	}
}

//ս��������Ϣ�����ͣ����ӳ٣�
void CfightScene()
{
	color(14);

	//�߿�(99, 28)
	gotoxy(0, 0);
	for (int count = 1; count <= 50; count++)
	{
		cout << "* ";
	}

	for (int count = 1; count <= 27; count++)
	{
		gotoxy(0, count);
		cout << "*";
		gotoxy(98, count);
		cout << "*";
	}

	gotoxy(0, 27);
	for (int count = 0; count < 50; count++)
	{
		cout << "* ";
	}

	gotoxy(0, 19);
	for (int count = 1; count <= 50; count++)
	{
		cout << "* ";
	}

	for (int count = 19; count <= 27; count++)
	{
		gotoxy(40, count);
		cout << "*";
	}

	gotoxy(0, 9);
	for (int count = 1; count <= 50; count++)
	{
		cout << "* ";
	}
}

//ս��������Ϣ���������
void fightData(Protagonist* role_one, Villain& role_two)
{
	color(15);

	gotoxy(17, 21);
	cout << "    ";
	gotoxy(12, 21);
	cout << "PH  ��" << role_one->getPrePH();
	gotoxy(21, 21);
	cout << " / " << role_one->getPH();

	gotoxy(12, 22);
	cout << "EXP : " << role_one->getPreEXP() << " / " << role_one->getEXP();

	gotoxy(12, 23);
	cout << "LV  : " << role_one->getLV();
	gotoxy(12, 24);
	cout << "ATK : " << role_one->getATK();
	gotoxy(12, 25);
	cout << "DEF : " << role_one->getDEF();

	gotoxy(15, 3);
	cout << "LV  ��" << role_two.getLV();
	gotoxy(20, 4);
	cout << "    ";
	gotoxy(15, 4);
	cout << "PH  ��" << role_two.getPrePH();
	gotoxy(24, 4);
	cout << " / " << role_two.getPH();
	gotoxy(15, 5);
	cout << "ATK : " << role_two.getATK();
	gotoxy(15, 6);
	cout << "DEF : " << role_two.getDEF();
}

//�˵���ӡ
void showmenu(string* menu, int size, int index, int pos_x, int pos_y)
{
	//��ʼ����ʾ������̨�ն˵ľ���λ��  
	COORD pos = { 0,0 };
	pos.X = pos_x;
	pos.Y = pos_y;

	//˵����
	color(15);
	gotoxy(pos_x, pos_y);
	cout << "��ѡ��Ҫ���еĲ�����";

	for (int i = 0; i < size; i++)
	{
		//���i==index��ʾ�ڵ�ǰѡ���λ�ã�Ĭ�ϳ�ʼ����ʾ�ǵ�һ�  
		//���������°���ѡ���ʱ�򣬹����ƶ���Ҳ�Ϳ������б�ѡ�������   
		if (i == index)
		{
			color(14);
			pos.Y += 1;
			gotoxy(pos.X, pos.Y);
			cout << *(menu + i) << endl;
		}

		//������ʾΪ��һ��ɫ   
		else
		{
			color(15);
			pos.Y += 1;
			gotoxy(pos.X, pos.Y);
			cout << *(menu + i) << endl;
		}
	}
	//ˢ�±�׼���������   
	fflush(stdout);
}
//�˵�ѡ�񣬻�ȡ�û�����
int  get_userinput(int *index, int size)
{
	int ch;
	ch = _getch();
	switch (ch)
	{
		//��   
	case 'w': if (*index > 0)  *index -= 1;  break;//���ѡ���ϣ���ô��������ƶ�   
												   //��   
	case 's':if (*index < size - 1)  *index += 1;  break;//���ѡ���£���ô��������ƶ�   
														 //�س�   
	case 13: return 13;
	}
	return 0;
}

//�ж�ս�����Ƿ���һ��Ѫ��Ϊ�㣬������Ӧ��������仯
bool check(Protagonist* role_one, Villain& role_two)
{
	flag = 0;//flag δ��ɡ���0   ʧ�ܡ���1   ʤ������2

	if (role_one->getPrePH() <= 0)
	{
		color(14);
		gotoxy(30, 12);
		cout << "ʤ �� �� �� �� �� �£��� �� �� �� �� �� ����";
		Sleep(5000);
		flag = 1;
		return true;
	}

	if (role_two.getPrePH() <= 0)
	{
		color(14);
		gotoxy(30, 12);
		cout << "ʤ �� �� �֣��� ϲ �� �� Ӯ �� �� ʤ ����";
		gotoxy(30, 13);
		cout << "�� �� �� �� �� Ǯ��";
		Sleep(5000);
		role_one->setMoney(role_one->getMoney() + role_two.getLV() * 5);
		role_one->setPreEXP_EXP_LV(role_two.getLV());
		if (difficulty == 0)
			preScore += role_two.getLV() * 10;
		else if (difficulty == 1)
			preScore += role_two.getLV() * 10 * 2;
		else if (difficulty == 2)
			preScore += role_two.getLV() * 10 * 3;
		if (preScore > highestScore)
			highestScore = preScore;
		flag = 2;
		return true;
	}

	return false;
}

//��������������
void attack(Protagonist* role_one, Villain& role_two)
{
	color(14);
	gotoxy(40, 12);
	cout << "�� �� �� �� �� ��";
	Sleep(1000);
	gotoxy(40, 12);
	cout << "                 ";

	if (role_one->getATK() > role_two.getDEF() && role_one->getATK() - role_two.getDEF() <= role_two.getPrePH())
		role_two.setPrePH(role_two.getPrePH() - role_one->getATK() + role_two.getDEF());
	else if (role_one->getATK() > role_two.getDEF() && role_one->getATK() - role_two.getDEF() > role_two.getPrePH())
		role_two.setPrePH(0);
	else if (role_one->getATK() <= role_two.getDEF() && role_two.getPH()*0.1 <= role_two.getPrePH())
		role_two.setPrePH(role_two.getPrePH() - role_two.getPH()*0.1);
	else if (role_one->getATK() <= role_two.getDEF() && role_two.getPH()*0.1 > role_two.getPrePH())
		role_two.setPrePH(0);

	fightData(role_one, role_two);
	if (check(role_one, role_two)) return;

	Sleep(2000);

	color(14);
	gotoxy(40, 12);
	cout << "�� �� �� �� �� �� ��";
	Sleep(1000);
	gotoxy(40, 12);
	cout << "                    ";

	if (role_two.getATK() > role_one->getDEF() && role_two.getATK() - role_one->getDEF() <= role_one->getPrePH())
		role_one->setPrePH(role_one->getPrePH() - role_two.getATK() + role_one->getDEF());
	else if (role_two.getATK() > role_one->getDEF() && role_two.getATK() - role_one->getDEF() > role_one->getPrePH())
		role_one->setPrePH(0);
	else if (role_two.getATK() <= role_one->getDEF() && role_one->getPH()*0.1 <= role_one->getPrePH())
		role_one->setPrePH(role_one->getPrePH() - role_one->getPH()*0.1);
	else if (role_two.getATK() <= role_one->getDEF() && role_one->getPH()*0.1 > role_one->getPrePH())
		role_one->setPrePH(0);

	fightData(role_one, role_two);
	if (check(role_one, role_two)) return;
}

//�����������˵���ӡ
void defense_attackmenuPrint(string menu[], int size, int pos_x, int pos_y, Protagonist* temp_protagonist)
{
	cursor();
	saber.m_bNivose_one = false;
	saber.m_bNivose_two = false;
	archer.m_bNivose_one = false;
	archer.m_bNivose_two = false;
	lancer.m_bNivose_one = false;
	lancer.m_bNivose_two = false;
	int ret;
	int index = 0;
	while (1)
	{
		showmenu(menu, size, index, pos_x, pos_y);
		gotoxy(pos_x, pos_y);
		color(15);
		cout << "��ѡ��Ҫʹ�õļ��ܣ�  ";
		ret = get_userinput(&index, size);
		if (ret == 13)
		{
			gotoxy(pos_x, pos_y);
			cout << "                   ";
			gotoxy(pos_x, pos_y + 1);
			cout << "          ";
			gotoxy(pos_x, pos_y + 2);
			cout << "          ";
			switch (index)
			{
			case 0://����1
				temp_protagonist->setNivose_one();
				color(14);
				gotoxy(31, 13);
				cout << "�� ʹ �� �� �� �� ���� " << temp_protagonist->getNivose_oneName();
				Sleep(1000);
				gotoxy(31, 13);
				cout << "                                 ";
				return;
			case 1://����2
				temp_protagonist->setNivose_two();
				color(14);
				gotoxy(31, 13);
				cout << "�� ʹ �� �� �� �� ���� " << temp_protagonist->getNivose_twoName();
				Sleep(1000);
				gotoxy(31, 13);
				cout << "                                 ";
				return;
			}
		}
	}
}

//�����������ַ��棩����������
void defense_attack(Protagonist* role_one, Villain& role_two)
{
	cursor();
	color(14);
	defense_attackmenuPrint(role_one->getNivosseName(), 2, 60, 21, role_one);

	//����һ����Ŀ�����û���Ժ���������ɹ��������ʧ��
	int temp = rand() % 23;
	color(14);
	gotoxy(5, 12);
	cout << str_question[temp];
	gotoxy(5, 13);
	cout << "�� �� �� �� �� �� �� ";
	cout << "                     ";
	string answer;
	cin >> answer;
	gotoxy(5, 12);
	for (unsigned int i = 0; i < str_question[temp].length(); i++)
		cout << " ";
	gotoxy(5, 13);
	cout << "                     ";
	for (int i = 0; i < answer.length(); i++)
		cout << " ";

	//�жϴ��Ƿ���ȷ����������Ӧ����
	if (answer == str_answer[temp])//����ȷ
	{
		//�ҷ�����
		gotoxy(31, 13);
		cout << "�� �� �� �� �� �� ��";
		Sleep(1000);
		gotoxy(31, 13);
		cout << "                    ";
		if (saber.m_bNivose_one == true)//�������²��������ӹ���
		{
			saber_nivose_one += 0.2;
			if (role_one->getATK() > role_two.getDEF() && (role_one->getATK() - role_two.getDEF())*saber_nivose_one <= role_two.getPrePH())
				role_two.setPrePH(role_two.getPrePH() - (role_one->getATK() - role_two.getDEF())*saber_nivose_one);
			else if (role_one->getATK() > role_two.getDEF() && (role_one->getATK() - role_two.getDEF())*saber_nivose_one > role_two.getPrePH())
				role_two.setPrePH(0);
			else if (role_one->getATK() <= role_two.getDEF() && role_two.getPH()*0.1*saber_nivose_one <= role_two.getPrePH())
				role_two.setPrePH(role_two.getPrePH() - role_two.getPH()*0.1*saber_nivose_one);
			else if (role_one->getATK() <= role_two.getDEF() && role_two.getPH()*0.1*saber_nivose_one > role_two.getPrePH())
				role_two.setPrePH(0);
			gotoxy(31, 13);
			cout << "�� �� �� �� �� �� �� �� �� �� �� �� �� �� �� 20%";
			Sleep(1000);
			gotoxy(31, 13);
			cout << "                                                ";
		}
		else if (saber.m_bNivose_two == true)//����ն�����ָ��˺���50%
		{
			if (role_one->getATK() > role_two.getDEF() && role_one->getATK() - role_two.getDEF() <= role_two.getPrePH())
			{
				role_two.setPrePH(role_two.getPrePH() - role_one->getATK() + role_two.getDEF());
				if ((role_one->getATK() - role_two.getDEF())*0.5 >= role_one->getPH() - role_one->getPrePH())
					role_one->setPrePH(role_one->getPH());
				else if ((role_one->getATK() - role_two.getDEF())*0.5 < role_one->getPH() - role_one->getPrePH())
					role_one->setPrePH(role_one->getPrePH() + (role_one->getATK() - role_two.getDEF())*0.5);
			}
			else if (role_one->getATK() > role_two.getDEF() && role_one->getATK() - role_two.getDEF() > role_two.getPrePH())
			{
				role_two.setPrePH(0);
				if (role_two.getPrePH()*0.5 >= role_one->getPH() - role_one->getPrePH())
					role_one->setPrePH(role_one->getPH());
				else if (role_two.getPrePH()*0.5 < role_one->getPH() - role_one->getPrePH())
					role_one->setPrePH(role_one->getPrePH() + role_two.getPrePH()*0.5);
			}
			else if (role_one->getATK() <= role_two.getDEF() && role_two.getPH()*0.1 <= role_two.getPrePH())
			{
				role_two.setPrePH(role_two.getPrePH() - role_two.getPH()*0.1);
				if (role_two.getPH()*0.05 >= role_one->getPH() - role_one->getPrePH())
					role_one->setPrePH(role_one->getPH());
				else if (role_two.getPH()*0.05 < role_one->getPH() - role_one->getPrePH())
					role_one->setPrePH(role_one->getPrePH() + role_two.getPH()*0.05);

			}
			else if (role_one->getATK() <= role_two.getDEF() && role_two.getPH()*0.1 > role_two.getPrePH())
			{
				role_two.setPrePH(0);
				if (role_two.getPrePH()*0.5 >= role_one->getPH() - role_one->getPrePH())
					role_one->setPrePH(role_one->getPH());
				else if (role_two.getPrePH()*0.5 < role_one->getPH() - role_one->getPrePH())
					role_one->setPrePH(role_one->getPrePH() + role_two.getPrePH()*0.5);
			}
			gotoxy(31, 13);
			cout << "Ѫ �� �� �� �� �� �� 50%";
			Sleep(2000);
			gotoxy(31, 13);
			cout << "                        ";
		}
		else if (archer.m_bNivose_one == true)//Ԫ�������������Ѫ20%
		{
			if (role_one->getPH() - role_one->getPrePH() < role_one->getPH() / 5)
				role_one->setPrePH(role_one->getPH());
			else if (role_one->getPH() - role_one->getPrePH() >= role_one->getPH() / 5)
				role_one->setPrePH(role_one->getPrePH() + role_one->getPH() / 5);
			gotoxy(31, 13);
			cout << "Ѫ �� �� �� 20%";
			Sleep(2000);
			gotoxy(31, 13);
			cout << "               ";
		}
		else if (archer.m_bNivose_two == true)//���������������β��������´ι����˺�3��
		{
			if (archer_nivose_two == 0)
			{
				archer_nivose_two = 1;
				gotoxy(31, 13);
				cout << "�� �� �� �� ������ �� �� �� �� �� �� 3 ��";
				Sleep(2000);
				gotoxy(31, 13);
				cout << "                                         ";
			}
			else if (archer_nivose_two == 1)
			{
				if (role_one->getATK() > role_two.getDEF() && (role_one->getATK() - role_two.getDEF()) * 3 <= role_two.getPrePH())
					role_two.setPrePH(role_two.getPrePH() - (role_one->getATK() - role_two.getDEF()) * 3);
				else if (role_one->getATK() > role_two.getDEF() && (role_one->getATK() - role_two.getDEF()) * 3 > role_two.getPrePH())
					role_two.setPrePH(0);
				else if (role_one->getATK() <= role_two.getDEF() && (role_one->getATK() - role_two.getDEF()) * 0.3 <= role_two.getPrePH())
					role_two.setPrePH(role_two.getPrePH() - role_two.getPH()*0.3);
				else if (role_one->getATK() <= role_two.getDEF() && (role_one->getATK() - role_two.getDEF()) * 0.3 > role_two.getPrePH())
					role_two.setPrePH(0);
				archer_nivose_two = 0;
				gotoxy(31, 13);
				cout << "�� �� �� �� �� �� �� 3 ��";
				Sleep(2000);
				gotoxy(31, 13);
				cout << "                         ";
			}
		}
		else if (lancer.m_bNivose_one == true)//����Ͷ�䡪���˺�����
		{
			if (role_one->getATK() > role_two.getDEF() && (role_one->getATK() - role_two.getDEF()) * 2 <= role_two.getPrePH())
				role_two.setPrePH(role_two.getPrePH() - (role_one->getATK() - role_two.getDEF()) * 2);
			else if (role_one->getATK() > role_two.getDEF() && (role_one->getATK() - role_two.getDEF()) * 2 > role_two.getPrePH())
				role_two.setPrePH(0);
			else if (role_one->getATK() <= role_two.getDEF() && role_two.getPH()*0.2 <= role_two.getPrePH())
				role_two.setPrePH(role_two.getPrePH() - role_two.getPH()*0.2);
			else if (role_one->getATK() <= role_two.getDEF() && role_two.getPH()*0.2 > role_two.getPrePH())
				role_two.setPrePH(0);
			gotoxy(31, 13);
			cout << "�� �� �� �� �� ��";
			Sleep(2000);
			gotoxy(31, 13);
			cout << "                 ";
		}
		else if (lancer.m_bNivose_two == true)//����˫ʽ����������������
		{
			if (role_one->getATK() > role_two.getDEF() && (role_one->getATK() - role_two.getDEF()) * 2 <= role_two.getPrePH())
				role_two.setPrePH(role_two.getPrePH() - (role_one->getATK() - role_two.getDEF()) * 2);
			else if (role_one->getATK() > role_two.getDEF() && (role_one->getATK() - role_two.getDEF()) * 2 > role_two.getPrePH())
				role_two.setPrePH(0);
			else if (role_one->getATK() <= role_two.getDEF() && role_two.getPH()*0.2 <= role_two.getPrePH())
				role_two.setPrePH(role_two.getPrePH() - role_two.getPH()*0.2);
			else if (role_one->getATK() <= role_two.getDEF() && role_two.getPH()*0.2 > role_two.getPrePH())
				role_two.setPrePH(0);
			gotoxy(31, 13);
			cout << "�� �� �� �� �� ��";
			Sleep(2000);
			gotoxy(31, 13);
			cout << "                 ";
		}
		//��ʱ����������Ϣ
		fightData(role_one, role_two);
		if (check(role_one, role_two)) return;

		//�з�����
		gotoxy(31, 13);
		cout << "�� �� �� �� �� �� ��";
		Sleep(1000);
		gotoxy(31, 13);
		cout << "                    ";
		if (role_two.getATK() > role_one->getDEF() && role_two.getATK() - role_one->getDEF() <= role_one->getPrePH())
			role_one->setPrePH(role_one->getPrePH() - role_two.getATK() + role_one->getDEF());
		else if (role_two.getATK() > role_one->getDEF() && role_two.getATK() - role_one->getDEF() > role_one->getPrePH())
			role_one->setPrePH(0);
		else if (role_two.getATK() <= role_one->getDEF() && role_one->getPH()*0.1 <= role_one->getPrePH())
			role_one->setPrePH(role_one->getPrePH() - role_one->getPH()*0.1);
		else if (role_two.getATK() <= role_one->getDEF() && role_one->getPH()*0.1 > role_one->getPrePH())
			role_one->setPrePH(0);
		//��ʱ����������Ϣ
		fightData(role_one, role_two);
		if (check(role_one, role_two)) return;
	}
	else if(answer != str_answer[temp])//�𰸴���
	{
		saber_nivose_one = 1;

		gotoxy(31, 13);
		cout << "�� �� ʹ �� ʧ �� ��";
		Sleep(1000);
		gotoxy(31, 13);
		cout << "                    ";
		gotoxy(31, 13);
		cout << "�� �� �� �� �� �� ��";
		Sleep(1000);
		gotoxy(31, 13);
		cout << "                    ";

		if (role_two.getATK() > role_one->getDEF() && role_two.getATK() - role_one->getDEF() <= role_one->getPrePH())
			role_one->setPrePH(role_one->getPrePH() - role_two.getATK() + role_one->getDEF());
		else if (role_two.getATK() > role_one->getDEF() && role_two.getATK() - role_one->getDEF() > role_one->getPrePH())
			role_one->setPrePH(0);
		else if (role_two.getATK() <= role_one->getDEF() && role_one->getPH()*0.1 <= role_one->getPrePH())
			role_one->setPrePH(role_one->getPrePH() - role_one->getPH()*0.1);
		else if (role_two.getATK() <= role_one->getDEF() && role_one->getPH()*0.1 > role_one->getPrePH())
			role_one->setPrePH(0);
		fightData(role_one, role_two);
		if (check(role_one, role_two)) return;
	}

	//��ջ�����
	char c;
	while ((c = getchar()) != EOF && c != '\n');
}

//�����������ַ����棩��������������ʵ�����ַ������ƣ�
void Cdefense_attack(Protagonist* role_one, Villain& role_two)
{
	color(14);
	cursor();
	defense_attackmenuPrint(role_one->getNivosseName(), 2, 60, 21, role_one);

	int temp = rand() % 23;
	color(14);
	gotoxy(5, 12);
	cout << str_question[temp];
	gotoxy(5, 13);
	cout << "�� �� �� �� �� �� �� ";

	string answer;
	cin >> answer;

	gotoxy(5, 12);
	for (unsigned int i = 0; i < str_question[temp].length(); i++)
		cout << " ";
	gotoxy(5, 13);
	cout << "                                                                                         ";

	if (answer == str_answer[temp])
	{
		gotoxy(31, 13);
		cout << "�� �� �� �� �� �� ��";
		Sleep(1000);
		gotoxy(31, 13);
		cout << "                    ";
		if (saber.m_bNivose_one == true)//�������²��������ӹ���
		{
			saber_nivose_one += 0.2;
			if (role_one->getATK() > role_two.getDEF() && (role_one->getATK() - role_two.getDEF())*saber_nivose_one <= role_two.getPrePH())
				role_two.setPrePH(role_two.getPrePH() - (role_one->getATK() - role_two.getDEF())*saber_nivose_one);
			else if (role_one->getATK() > role_two.getDEF() && (role_one->getATK() - role_two.getDEF())*saber_nivose_one > role_two.getPrePH())
				role_two.setPrePH(0);
			else if (role_one->getATK() <= role_two.getDEF() && role_two.getPH()*0.1*saber_nivose_one <= role_two.getPrePH())
				role_two.setPrePH(role_two.getPrePH() - role_two.getPH()*0.1*saber_nivose_one);
			else if (role_one->getATK() <= role_two.getDEF() && role_two.getPH()*0.1*saber_nivose_one > role_two.getPrePH())
				role_two.setPrePH(0);
			system("cls");
			videoPainting(".//pic//TXT//nivose//saber_nivose_one//ASCII-saber_nivose_one", 43, 601, 198, 2, 2);
			setConsoleDefault();
			CfightScene();
			fightData(role_one, role_two);
			gotoxy(31, 13);
			cout << "�� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� 20% ��";
			Sleep(3000);
			gotoxy(31, 13);
			cout << "                                                      ";
		}
		else if (saber.m_bNivose_two == true)//����ն�����ָ��˺���50%
		{
			if (role_one->getATK() > role_two.getDEF() && role_one->getATK() - role_two.getDEF() <= role_two.getPrePH())
			{
				role_two.setPrePH(role_two.getPrePH() - role_one->getATK() + role_two.getDEF());
				if ((role_one->getATK() - role_two.getDEF())*0.5 >= role_one->getPH() - role_one->getPrePH())
					role_one->setPrePH(role_one->getPH());
				else if ((role_one->getATK() - role_two.getDEF())*0.5 < role_one->getPH() - role_one->getPrePH())
					role_one->setPrePH(role_one->getPrePH() + (role_one->getATK() - role_two.getDEF())*0.5);
			}
			else if (role_one->getATK() > role_two.getDEF() && role_one->getATK() - role_two.getDEF() > role_two.getPrePH())
			{
				role_two.setPrePH(0);
				if (role_two.getPrePH()*0.5 >= role_one->getPH() - role_one->getPrePH())
					role_one->setPrePH(role_one->getPH());
				else if (role_two.getPrePH()*0.5 < role_one->getPH() - role_one->getPrePH())
					role_one->setPrePH(role_one->getPrePH() + role_two.getPrePH()*0.5);
			}
			else if (role_one->getATK() <= role_two.getDEF() && role_two.getPH()*0.1 <= role_two.getPrePH())
			{
				role_two.setPrePH(role_two.getPrePH() - role_two.getPH()*0.1);
				if (role_two.getPH()*0.05 >= role_one->getPH() - role_one->getPrePH())
					role_one->setPrePH(role_one->getPH());
				else if (role_two.getPH()*0.05 < role_one->getPH() - role_one->getPrePH())
					role_one->setPrePH(role_one->getPrePH() + role_two.getPH()*0.05);

			}
			else if (role_one->getATK() <= role_two.getDEF() && role_two.getPH()*0.1 > role_two.getPrePH())
			{
				role_two.setPrePH(0);
				if (role_two.getPrePH()*0.5 >= role_one->getPH() - role_one->getPrePH())
					role_one->setPrePH(role_one->getPH());
				else if (role_two.getPrePH()*0.5 < role_one->getPH() - role_one->getPrePH())
					role_one->setPrePH(role_one->getPrePH() + role_two.getPrePH()*0.5);
			}
			system("cls");
			videoPainting(".//pic//TXT//nivose//saber_nivose_two//ASCII-saber_nivose_two", 76, 601, 198, 2, 2);
			setConsoleDefault();
			CfightScene();
			fightData(role_one, role_two);
			gotoxy(31, 13);
			cout << "Ѫ �� �� �� �� �� �� 50%";
			Sleep(3000);
			gotoxy(31, 13);
			cout << "                        ";
		}
		else if (archer.m_bNivose_one == true)//Ԫ�������������Ѫ20%
		{
			if (role_one->getPH() - role_one->getPrePH() < role_one->getPH() / 5)
				role_one->setPrePH(role_one->getPH());
			else if (role_one->getPH() - role_one->getPrePH() >= role_one->getPH() / 5)
				role_one->setPrePH(role_one->getPrePH() + role_one->getPH() / 5);
			system("cls");
			videoPainting(".//pic//TXT//nivose//archer_nivose_one//ASCII-archer_nivose_one", 17, 601, 198, 2, 2);
			setConsoleDefault();
			CfightScene();
			fightData(role_one, role_two);
			gotoxy(31, 13);
			cout << "Ѫ �� �� �� 20%";
			Sleep(3000);
			gotoxy(31, 13);
			cout << "               ";
		}
		else if (archer.m_bNivose_two == true)//���������������β��������´ι����˺�3��
		{
			if (archer_nivose_two == 0)
			{
				archer_nivose_two = 1;
				system("cls");
				videoPainting(".//pic//TXT//nivose//archer_nivose_two//archer_nivose_two_one//ASCII-archer_nivose_two_one", 50, 601, 198, 2, 2);
				setConsoleDefault();
				CfightScene();
				fightData(role_one, role_two);
				gotoxy(31, 13);
				cout << "�� �� �� �� ������ �� �� �� �� �� �� 3 ��";
				Sleep(3000);
				gotoxy(31, 13);
				cout << "                                         ";
			}
			else if (archer_nivose_two == 1)
			{
				if (role_one->getATK() > role_two.getDEF() && (role_one->getATK() - role_two.getDEF()) * 3 <= role_two.getPrePH())
					role_two.setPrePH(role_two.getPrePH() - (role_one->getATK() - role_two.getDEF()) * 3);
				else if (role_one->getATK() > role_two.getDEF() && (role_one->getATK() - role_two.getDEF()) * 3 > role_two.getPrePH())
					role_two.setPrePH(0);
				else if (role_one->getATK() <= role_two.getDEF() && (role_one->getATK() - role_two.getDEF()) * 0.3 <= role_two.getPrePH())
					role_two.setPrePH(role_two.getPrePH() - role_two.getPH()*0.3);
				else if (role_one->getATK() <= role_two.getDEF() && (role_one->getATK() - role_two.getDEF()) * 0.3 > role_two.getPrePH())
					role_two.setPrePH(0);
				system("cls");
				videoPainting(".//pic//TXT//nivose//archer_nivose_two//archer_nivose_two_two//ASCII-archer_nivose_two_two", 57, 601, 198, 2, 2);
				setConsoleDefault();
				CfightScene();
				fightData(role_one, role_two);
				archer_nivose_two = 0;
				gotoxy(31, 13);
				cout << "�� �� �� �� �� �� �� 3 ��";
				Sleep(3000);
				gotoxy(31, 13);
				cout << "                         ";
			}		
		}
		else if (lancer.m_bNivose_one == true)//����Ͷ�䡪���˺�����
		{
			if (role_one->getATK() > role_two.getDEF() && (role_one->getATK() - role_two.getDEF()) * 2 <= role_two.getPrePH())
				role_two.setPrePH(role_two.getPrePH() - (role_one->getATK() - role_two.getDEF()) * 2);
			else if (role_one->getATK() > role_two.getDEF() && (role_one->getATK() - role_two.getDEF()) * 2 > role_two.getPrePH())
				role_two.setPrePH(0);
			else if (role_one->getATK() <= role_two.getDEF() && role_two.getPH()*0.2 <= role_two.getPrePH())
				role_two.setPrePH(role_two.getPrePH() - role_two.getPH()*0.2);
			else if (role_one->getATK() <= role_two.getDEF() && role_two.getPH()*0.2 > role_two.getPrePH())
				role_two.setPrePH(0);
			system("cls");
			videoPainting(".//pic//TXT//nivose//lancer_nivose_one//ASCII-lancer_nivose_one", 79, 601, 198, 2, 2);
			setConsoleDefault();
			CfightScene();
			fightData(role_one, role_two);
			gotoxy(31, 13);
			cout << "�� �� �� �� �� ��";
			Sleep(3000);
			gotoxy(31, 13);
			cout << "                 ";
		}
		else if (lancer.m_bNivose_two == true)//����˫ʽ����������������
		{
			if (role_one->getATK() > role_two.getDEF() && (role_one->getATK() - role_two.getDEF()) * 2 <= role_two.getPrePH())
				role_two.setPrePH(role_two.getPrePH() - (role_one->getATK() - role_two.getDEF()) * 2);
			else if (role_one->getATK() > role_two.getDEF() && (role_one->getATK() - role_two.getDEF()) * 2 > role_two.getPrePH())
				role_two.setPrePH(0);
			else if (role_one->getATK() <= role_two.getDEF() && role_two.getPH()*0.2 <= role_two.getPrePH())
				role_two.setPrePH(role_two.getPrePH() - role_two.getPH()*0.2);
			else if (role_one->getATK() <= role_two.getDEF() && role_two.getPH()*0.2 > role_two.getPrePH())
				role_two.setPrePH(0);
			system("cls");
			videoPainting(".//pic//TXT//nivose//lancer_nivose_two//ASCII-lancer_nivose_two", 78, 601, 198, 2, 2);
			setConsoleDefault();
			CfightScene();
			fightData(role_one, role_two);
			gotoxy(31, 13);
			cout << "�� �� �� �� �� ��";
			Sleep(3000);
			gotoxy(31, 13);
			cout << "                 ";
		}
		if (check(role_one, role_two)) return;

		gotoxy(31, 13);
		cout << "�� �� �� �� �� �� ��";
		Sleep(1000);
		gotoxy(31, 13);
		cout << "                    ";
		if (role_two.getATK() > role_one->getDEF() && role_two.getATK() - role_one->getDEF() <= role_one->getPrePH())
			role_one->setPrePH(role_one->getPrePH() - role_two.getATK() + role_one->getDEF());
		else if (role_two.getATK() > role_one->getDEF() && role_two.getATK() - role_one->getDEF() > role_one->getPrePH())
			role_one->setPrePH(0);
		else if (role_two.getATK() <= role_one->getDEF() && role_one->getPH()*0.1 <= role_one->getPrePH())
			role_one->setPrePH(role_one->getPrePH() - role_one->getPH()*0.1);
		else if (role_two.getATK() <= role_one->getDEF() && role_one->getPH()*0.1 > role_one->getPrePH())
			role_one->setPrePH(0);
		fightData(role_one, role_two);
		if (check(role_one, role_two)) return;
	}
	else
	{
		saber_nivose_one = 1;

		gotoxy(31, 13);
		cout << "�� �� ʹ �� ʧ �� ��";
		Sleep(1000);
		gotoxy(31, 13);
		cout << "                    ";
		gotoxy(31, 13);
		cout << "�� �� �� �� �� �� ��";
		Sleep(1000);
		gotoxy(31, 13);
		cout << "                    ";

		if (role_two.getATK() > role_one->getDEF() && role_two.getATK() - role_one->getDEF() <= role_one->getPrePH())
			role_one->setPrePH(role_one->getPrePH() - role_two.getATK() + role_one->getDEF());
		else if (role_two.getATK() > role_one->getDEF() && role_two.getATK() - role_one->getDEF() > role_one->getPrePH())
			role_one->setPrePH(0);
		else if (role_two.getATK() <= role_one->getDEF() && role_one->getPH()*0.1 <= role_one->getPrePH())
			role_one->setPrePH(role_one->getPrePH() - role_one->getPH()*0.1);
		else if (role_two.getATK() <= role_one->getDEF() && role_one->getPH()*0.1 > role_one->getPrePH())
			role_one->setPrePH(0);
		fightData(role_one, role_two);
		if (check(role_one, role_two)) return;
	}

	char c;
	while ((c = getchar()) != EOF && c != '\n');
}

//ս����ʹ����ҩ
void AfterCurePHinFight(Protagonist* role_one, Villain& role_two)
{
	cursor();
	if (myBackpack.getCurePH() > 0)//��ҩ������ʣ��
	{
		//�ҷ���Ѫ
		color(14);
		gotoxy(31, 13);
		cout << "�� ʹ �� �� �� ҩ��";
		Sleep(1000);
		gotoxy(31, 13);
		cout << "                   ";
		myBackpack.setCurePH(myBackpack.getCurePH() - 1);
		if (role_one->getPH() - role_one->getPrePH() >= 20)
			role_one->setPrePH(role_one->getPrePH() + 20);
		else if (role_one->getPH() - role_one->getPrePH() < 20)
			role_one->setPrePH(role_one->getPH());
		fightData(role_one, role_two);

		//�з�����
		color(14);
		gotoxy(31, 13);
		cout << "�� �� �� �� �� �� ��";
		Sleep(1000);
		gotoxy(31, 13);
		cout << "                    ";
		if (role_two.getATK() > role_one->getDEF())
			role_one->setPrePH(role_one->getPrePH() - role_two.getATK() + role_one->getDEF());
		if (role_two.getATK() <= role_one->getDEF())
			role_one->setPrePH(role_one->getPrePH() - 1);
		fightData(role_one, role_two);

		//���
		if (check(role_one, role_two)) return;
	}

	else if (myBackpack.getCurePH() == 0)//��ҩ����Ϊ��
	{
		color(14);
		gotoxy(31, 13);
		cout << "�� �⣡�� ҩ �� �� �ˣ�";
		Sleep(1000);
		gotoxy(31, 13);
		cout << "                       ";
	}
}

//ս����ʹ�ú���ҩ
void AfterCurePHgoodinFight(Protagonist* role_one, Villain& role_two)
{
	cursor();
	if (myBackpack.getCurePHgood() > 0)//��ҩ������ʣ��
	{
		//�ҷ���Ѫ
		color(14);
		gotoxy(31, 13);
		cout << "�� ʹ �� �� �� �� ҩ��";
		Sleep(1000);
		gotoxy(31, 13);
		cout << "                      ";
		myBackpack.setCurePHgood(myBackpack.getCurePHgood() - 1);
		if (role_one->getPH() - role_one->getPrePH() >= 50)
			role_one->setPrePH(role_one->getPrePH() + 50);
		else if (role_one->getPH() - role_one->getPrePH() < 50)
			role_one->setPrePH(role_one->getPH());
		fightData(role_one, role_two);

		//�з�����
		color(14);
		gotoxy(31, 13);
		cout << "�� �� �� �� �� �� ��";
		Sleep(1000);
		gotoxy(31, 13);
		cout << "                    ";
		if (role_two.getATK() > role_one->getDEF())
			role_one->setPrePH(role_one->getPrePH() - role_two.getATK() + role_one->getDEF());
		if (role_two.getATK() <= role_one->getDEF())
			role_one->setPrePH(role_one->getPrePH() - 1);
		fightData(role_one, role_two);

		//���
		if (check(role_one, role_two)) return;
	}

	else if (myBackpack.getCurePHgood() == 0)//��ҩ����Ϊ��
	{
		color(14);
		gotoxy(31, 13);
		cout << "�� �⣡�� �� ҩ �� �� �ˣ�";
		Sleep(1000);
		gotoxy(31, 13);
		cout << "                          ";
	}
}

//ս����ʹ�þ��鵤
void AfterEnhanceEXPinFight(Protagonist* role_one, Villain& role_two)
{
	cursor();
	if (myBackpack.getEnhanceEXP() > 0)//���鵤������ʣ��
	{
		//�ҷ��Ӿ���
		color(14);
		gotoxy(31, 13);
		cout << "�� ʹ �� �� �� �� ����";
		Sleep(1000);
		gotoxy(31, 13);
		cout << "                      ";
		myBackpack.setEnhanceEXP(myBackpack.getEnhanceEXP() - 1);
		role_one->setPreEXP_EXP_LV(20);
		fightData(role_one, role_two);

		//�з�����
		color(14);
		gotoxy(31, 13);
		cout << "�� �� �� �� �� �� ��";
		Sleep(1000);
		gotoxy(31, 13);
		cout << "                    ";
		if (role_two.getATK() > role_one->getDEF())
			role_one->setPrePH(role_one->getPrePH() - role_two.getATK() + role_one->getDEF());
		if (role_two.getATK() <= role_one->getDEF())
			role_one->setPrePH(role_one->getPrePH() - 1);
		fightData(role_one, role_two);

		//���
		if (check(role_one, role_two)) return;
	}

	else if (myBackpack.getEnhanceEXP() == 0)//���鵤����Ϊ��
	{
		color(14);
		gotoxy(31, 13);
		cout << "�� �⣡�� �� �� �� �� �ˣ�";
		Sleep(1000);
		gotoxy(31, 13);
		cout << "                          ";
	}

}

//��ͼ��ʹ����ҩ
void AfterCurePHinMap(Protagonist* temp_protagonist)
{
	if (myBackpack.getCurePH() > 0)
	{
		color(15);
		gotoxy(100, 26);
		cout << "��ʹ������ҩ��";
		Sleep(1000);
		gotoxy(100, 26);
		cout << "              ";

		myBackpack.setCurePH(myBackpack.getCurePH() - 1);
		if (temp_protagonist->getPH() - temp_protagonist->getPrePH() >= 20)
			temp_protagonist->setPrePH(temp_protagonist->getPrePH() + 20);
		else if (temp_protagonist->getPH() - temp_protagonist->getPrePH() < 20)
			temp_protagonist->setPrePH(temp_protagonist->getPH());
		roleDataPrint(temp_protagonist);
		backpackDataPrint();
	}

	else if (myBackpack.getCurePH() == 0)
	{
		color(15);
		gotoxy(100, 26);
		cout << "��⣡��ҩ�����ˣ�";
		Sleep(1000);
		gotoxy(100, 26);
		cout << "                  ";
	}
}

//��ͼ��ʹ�ú���ҩ
void AfterCurePHgoodinMap(Protagonist* temp_protagonist)
{
	if (myBackpack.getCurePHgood() > 0)
	{
		color(15);
		gotoxy(100, 26);
		cout << "��ʹ���˺���ҩ��";
		Sleep(1000);
		gotoxy(100, 26);
		cout << "                ";

		myBackpack.setCurePHgood(myBackpack.getCurePHgood() - 1);
		if (temp_protagonist->getPH() - temp_protagonist->getPrePH() >= 50)
			temp_protagonist->setPrePH(temp_protagonist->getPrePH() + 50);
		else if (temp_protagonist->getPH() - temp_protagonist->getPrePH() < 50)
			temp_protagonist->setPrePH(temp_protagonist->getPH());
		roleDataPrint(temp_protagonist);
		backpackDataPrint();
	}

	else if (myBackpack.getCurePHgood() == 0)
	{
		color(15);
		gotoxy(100, 26);
		cout << "��⣡����ҩ�����ˣ�";
		Sleep(1000);
		gotoxy(100, 26);
		cout << "                    ";
	}
}

//��ͼ��ʹ�þ��鵤
void AfterEnhanceEXPinMap(Protagonist* temp_protagonist)
{
	if (myBackpack.getEnhanceEXP() > 0)
	{
		color(15);
		gotoxy(100, 26);
		cout << "��ʹ���˾��鵤��";
		Sleep(1000);
		gotoxy(100, 26);
		cout << "                ";

		myBackpack.setEnhanceEXP(myBackpack.getEnhanceEXP() - 1);
		temp_protagonist->setPreEXP_EXP_LV(20);
		roleDataPrint(temp_protagonist);
		backpackDataPrint();
	}

	else if (myBackpack.getEnhanceEXP() == 0)
	{
		color(15);
		gotoxy(100, 26);
		cout << "��⣡���鵤�����ˣ�";
		Sleep(1000);
		gotoxy(100, 26);
		cout << "                    ";
	}
}

//�̵��й�����ҩ
void buyCurePH(Protagonist* temp_protagonist)//500
{
	if (protagonist->getMoney() >= 200)
	{
		gotoxy(100, 26);
		cout << "�ɹ���������ҩ��";
		Sleep(1000);
		gotoxy(100, 26);
		cout << "                ";

		myBackpack.setCurePH(myBackpack.getCurePH() + 1);
		protagonist->setMoney(protagonist->getMoney() - 200);
		roleDataPrint(temp_protagonist);
		backpackDataPrint();
	}
	else if (protagonist->getMoney() < 200)
	{
		gotoxy(100, 26);
		cout << "�Բ��𣬽�Ǯ������";
		Sleep(1000);
		gotoxy(100, 26);
		cout << "                  ";
	}
}

//�̵��й������ҩ
void buyCurePHgood(Protagonist* temp_protagonist)//800
{
	if (protagonist->getMoney() >= 500)
	{
		gotoxy(100, 26);
		cout << "�ɹ������˺���ҩ��";
		Sleep(1000);
		gotoxy(100, 26);
		cout << "                  ";

		myBackpack.setCurePHgood(myBackpack.getCurePHgood() + 1);
		protagonist->setMoney(protagonist->getMoney() - 500);
		roleDataPrint(temp_protagonist);
		backpackDataPrint();
	}
	else if (protagonist->getMoney() < 500)
	{
		gotoxy(100, 26);
		cout << "�Բ��𣬽�Ǯ������";
		Sleep(1000);
		gotoxy(100, 26);
		cout << "                  ";
	}
}

//�̵��й����鵤
void buyEnhanceEXP(Protagonist* temp_protagonist)//1000
{
	if (protagonist->getMoney() >= 800)
	{
		gotoxy(100, 26);
		cout << "�ɹ������˾��鵤";
		Sleep(1000);
		gotoxy(100, 26);
		cout << "                  ";

		myBackpack.setEnhanceEXP(myBackpack.getEnhanceEXP() + 1);
		protagonist->setMoney(protagonist->getMoney() - 800);
		roleDataPrint(temp_protagonist);
		backpackDataPrint();
	}
	else if (protagonist->getMoney() < 800)
	{
		gotoxy(100, 26);
		cout << "�Բ��𣬽�Ǯ������";
		Sleep(1000);
		gotoxy(100, 26);
		cout << "                  ";
	}
}

//���ֲ˵�
string fightmenu[3]
{
	"����",
	"����",
	"����"
};

string fightmenu_other[4]
{
	"����",
	"����",
	"����",
	"����"
};

string backpackmenuInFight[4]
{
	"��ҩ",
	"����ҩ",
	"���鵤",
	"�˳�"
};

string backpackmenuInMap[4]
{
	"��ҩ",
	"����ҩ",
	"���鵤",
	"�˳�"
};

string shopmenu[4]
{
	"��ҩ",
	"����ҩ",
	"���鵤",
	"�˳�"
};

//ս���б����˵���ӡ
void bakckpackmenuPrintinFight(string menu[], int size, int pos_x, int pos_y, Protagonist* role_one, Villain& role_two)
{
	int ret;
	int index = 0;
	while (1)
	{
		showmenu(menu, size, index, pos_x, pos_y);
		ret = get_userinput(&index, size);
		if (ret == 13)
		{
			gotoxy(pos_x, pos_y);
			cout << "                    ";
			gotoxy(pos_x, pos_y + 1);
			cout << "    ";
			gotoxy(pos_x, pos_y + 2);
			cout << "      ";
			gotoxy(pos_x, pos_y + 3);
			cout << "      ";
			gotoxy(pos_x, pos_y + 4);
			cout << "    ";

			switch (index)
			{
			case 0:AfterCurePHinFight(role_one, role_two);           return;   //��ҩ
			case 1:AfterCurePHgoodinFight(role_one, role_two);       return;   //����ҩ
			case 2:AfterEnhanceEXPinFight(role_one, role_two);       return;   //���鵤
			case 3:                                                  return;   //�˳�
			}
		}
	}
}

//��ͼ�б����˵���ӡ
void bakckpackmenuPrintinMap(string menu[], int size, int pos_x, int pos_y, Protagonist* temp_protagonist)
{
	int ret;
	int index = 0;

	while (1)
	{
		showmenu(menu, size, index, pos_x, pos_y);
		gotoxy(pos_x, pos_y);
		color(15);
		cout << "��ѡ��Ҫʹ�õ���Ʒ��";
		ret = get_userinput(&index, size);

		if (ret == 13)
		{
			switch (index)
			{
			case 0:AfterCurePHinMap(temp_protagonist);           break;   //��ҩ
			case 1:AfterCurePHgoodinMap(temp_protagonist);       break;   //����ҩ
			case 2:AfterEnhanceEXPinMap(temp_protagonist);       break;   //���鵤
			case 3:                                        //�˳��˵�
				gotoxy(pos_x, pos_y);
				cout << "                    ";
				gotoxy(pos_x, pos_y + 1);
				cout << "    ";
				gotoxy(pos_x, pos_y + 2);
				cout << "      ";
				gotoxy(pos_x, pos_y + 3);
				cout << "      ";
				gotoxy(pos_x, pos_y + 4);
				cout << "      ";
				return;
			}

		}

	}
}

//ս����ս�����˵���ӡ���������ܣ�
void fightmenuPrint(string menu[], int size, int pos_x, int pos_y, Protagonist* role_one, Villain& role_two)
{

	int ret;
	int index = 0;

	while (1)
	{
		showmenu(menu, size, index, pos_x, pos_y);
		ret = get_userinput(&index, size);

		if (ret == 13)
		{
			gotoxy(pos_x, pos_y);
			cout << "                    ";
			gotoxy(pos_x, pos_y + 1);
			cout << "    ";
			gotoxy(pos_x, pos_y + 2);
			cout << "    ";
			gotoxy(pos_x, pos_y + 3);
			cout << "    ";

			switch (index)
			{
			case 0://����
				attack(role_one, role_two);                          
				return;   
			case 1://����
				if(characterORcharacterprinting==0)
					defense_attack(role_one, role_two);
				else if (characterORcharacterprinting == 1)
					Cdefense_attack(role_one, role_two);
				return;   
			case 2://����
				bakckpackmenuPrintinFight(backpackmenuInFight, 4, pos_x, pos_y, role_one, role_two);       
				return;
			}

		}

	}
}

//ս����ս�����˵���ӡ�������ܣ�
void fightmenuPrint_other(string menu[], int size, int pos_x, int pos_y, Protagonist* role_one, Villain& role_two)
{

	int ret;
	int index = 0;

	while (1)
	{
		showmenu(menu, size, index, pos_x, pos_y);
		ret = get_userinput(&index, size);

		if (ret == 13)
		{
			gotoxy(pos_x, pos_y);
			cout << "                    ";
			gotoxy(pos_x, pos_y + 1);
			cout << "    ";
			gotoxy(pos_x, pos_y + 2);
			cout << "    ";
			gotoxy(pos_x, pos_y + 3);
			cout << "    ";
			gotoxy(pos_x, pos_y + 4);
			cout << "    ";

			switch (index)
			{
			case 0://����
				attack(role_one, role_two);
				return;
			case 1://����
				if (characterORcharacterprinting == 0)
					defense_attack(role_one, role_two);
				else if (characterORcharacterprinting == 1)
					Cdefense_attack(role_one, role_two);
				return;
			case 2://����
				bakckpackmenuPrintinFight(backpackmenuInFight, 4, pos_x, pos_y, role_one, role_two);
				return;
			case 3://����
				flag = 1;
				color(14);
				gotoxy(31, 13);
				cout << "�� �� �� �� �� �� ��";
				Sleep(2000);
				gotoxy(31, 13);
				cout << "                    ";
				return;
			}

		}
	}
}

//�̵�˵���ӡ
void shopmenuPrint(string menu[], int size, int pos_x, int pos_y, Protagonist* temp_protagonist)
{
	int ret;
	int index = 0;

	while (1)
	{
		showmenu(menu, size, index, pos_x, pos_y);
		gotoxy(pos_x, pos_y);
		cout << "��ѡ��Ҫ�������Ʒ��";
		ret = get_userinput(&index, size);

		if (ret == 13)
		{
			switch (index)
			{
			case 0: buyCurePH(temp_protagonist);                 break;    //����ҩ
			case 1: buyCurePHgood(temp_protagonist);             break;    //�����ҩ
			case 2: buyEnhanceEXP(temp_protagonist);             break;    //���鵤
			case 3:                                                        //�˳�����˵�
				gotoxy(pos_x, pos_y);
				cout << "                    ";
				gotoxy(pos_x, pos_y + 1);
				cout << "    ";
				gotoxy(pos_x, pos_y + 2);
				cout << "      ";
				gotoxy(pos_x, pos_y + 3);
				cout << "      ";
				gotoxy(pos_x, pos_y + 4);
				cout << "      ";
				return;
			}

		}

	}
}

//��Ϸ����
void save()
{
	ofstream fout("data_saved.txt");
	//backpack_data
	fout << myBackpack.getCurePH() << " " << myBackpack.getCurePHgood() << " " << myBackpack.getEnhanceEXP() << " " << myBackpack.getBadge() << " ";
	//protagonist_data
	fout << protagonist->getMoney() << " ";
	//saber_data
	fout << saber.getPH() << " " << saber.getPrePH() << " " << saber.getATK() << " " << saber.getDEF() << " " << saber.getLV() << " " << saber.getEXP() << " " << saber.getPreEXP() << " ";
	//archer_data
	fout << archer.getPH() << " " << archer.getPrePH() << " " << archer.getATK() << " " << archer.getDEF() << " " << archer.getLV() << " " << archer.getEXP() << " " << archer.getPreEXP() << " ";;
	//lancer_data
	fout << lancer.getPH() << " " << lancer.getPrePH() << " " << lancer.getATK() << " " << lancer.getDEF() << " " << lancer.getLV() << " " << lancer.getEXP() << " " << lancer.getPreEXP() << " ";;
	//Villain_data
	fout << boss_one.getPH() << " " << boss_one.getPrePH() << " " << boss_one.getATK() << " " << boss_one.getDEF() << " " << boss_one.getLV() << " " << boss_one.getFlag() << " ";
	fout << boss_two.getPH() << " " << boss_two.getPrePH() << " " << boss_two.getATK() << " " << boss_two.getDEF() << " " << boss_two.getLV() << " " << boss_two.getFlag() << " ";
	fout << boss_three.getPH() << " " << boss_three.getPrePH() << " " << boss_three.getATK() << " " << boss_three.getDEF() << " " << boss_three.getLV() << " " << boss_three.getFlag() << " ";
	fout << boss_four.getPH() << " " << boss_four.getPrePH() << " " << boss_four.getATK() << " " << boss_four.getDEF() << " " << boss_four.getLV() << " " << boss_four.getFlag() << " ";
	fout << boss_five.getPH() << " " << boss_five.getPrePH() << " " << boss_five.getATK() << " " << boss_five.getDEF() << " " << boss_five.getLV() << " " << boss_five.getFlag() << " ";
	//position
	fout << pos.X << " " << pos.Y << " ";
	//score
	fout << preScore << " " << highestScore << " ";
	//map
	for (int row = 0; row < 27; row++)
	{
		for (int col = 0; col < 98; col++)
		{
			fout << mapPartOne[row][col] << " ";
		}
	}
	fout.close();
}

//��Ϸ����
void load()
{
	ifstream fin("data_saved.txt");
	int temp;
	//backpack_data
	fin >> temp;
	myBackpack.setCurePH(temp);
	fin >> temp;
	myBackpack.setCurePHgood(temp);
	fin >> temp;
	myBackpack.setEnhanceEXP(temp);
	fin >> temp;
	myBackpack.setBadge(temp);
	//protagonist_data
	fin >> temp;
	protagonist->setMoney(temp);
	//saber_data
	fin >> temp;
	saber.setPH(temp);
	fin >> temp;
	saber.setPrePH(temp);
	fin >> temp;
	saber.setATK(temp);
	fin >> temp;
	saber.setDEF(temp);
	fin >> temp;
	saber.setLV(temp);
	fin >> temp;
	saber.setEXP(temp);
	fin >> temp;
	saber.setPreEXP(temp);
	//archer_data
	fin >> temp;
	archer.setPH(temp);
	fin >> temp;
	archer.setPrePH(temp);
	fin >> temp;
	archer.setATK(temp);
	fin >> temp;
	archer.setDEF(temp);
	fin >> temp;
	archer.setLV(temp);
	fin >> temp;
	archer.setEXP(temp);
	fin >> temp;
	archer.setPreEXP(temp);
	//lancer_data
	fin >> temp;
	lancer.setPH(temp);
	fin >> temp;
	lancer.setPrePH(temp);
	fin >> temp;
	lancer.setATK(temp);
	fin >> temp;
	lancer.setDEF(temp);
	fin >> temp;
	lancer.setLV(temp);
	fin >> temp;
	lancer.setEXP(temp);
	fin >> temp;
	lancer.setPreEXP(temp);
	//Villain_data
	fin >> temp;
	boss_one.setPH(temp);
	fin >> temp;
	boss_one.setPrePH(temp);
	fin >> temp;
	boss_one.setATK(temp);
	fin >> temp;
	boss_one.setDEF(temp);
	fin >> temp;
	boss_one.setLV(temp);
	fin >> temp;
	boss_one.setFlag(temp);

	fin >> temp;
	boss_two.setPH(temp);
	fin >> temp;
	boss_two.setPrePH(temp);
	fin >> temp;
	boss_two.setATK(temp);
	fin >> temp;
	boss_two.setDEF(temp);
	fin >> temp;
	boss_two.setLV(temp);
	fin >> temp;
	boss_two.setFlag(temp);

	fin >> temp;
	boss_three.setPH(temp);
	fin >> temp;
	boss_three.setPrePH(temp);
	fin >> temp;
	boss_three.setATK(temp);
	fin >> temp;
	boss_three.setDEF(temp);
	fin >> temp;
	boss_three.setLV(temp);
	fin >> temp;
	boss_three.setFlag(temp);

	fin >> temp;
	boss_four.setPH(temp);
	fin >> temp;
	boss_four.setPrePH(temp);
	fin >> temp;
	boss_four.setATK(temp);
	fin >> temp;
	boss_four.setDEF(temp);
	fin >> temp;
	boss_four.setLV(temp);
	fin >> temp;
	boss_four.setFlag(temp);

	fin >> temp;
	boss_five.setPH(temp);
	fin >> temp;
	boss_five.setPrePH(temp);
	fin >> temp;
	boss_five.setATK(temp);
	fin >> temp;
	boss_five.setDEF(temp);
	fin >> temp;
	boss_five.setLV(temp);
	fin >> temp;
	boss_five.setFlag(temp);

	//position
	fin >> pos.X;
	fin >> pos.Y;

	//score
	fin >> preScore;
	fin >> highestScore;

	//map
	for (int row = 0; row < 27; row++)
	{
		for (int col = 0; col < 98; col++)
		{
			fin >> mapPartOne[row][col];
		}
	}
	fin.close();

	if (mapPartOne[0][0] != 2)
	{
		cerr << "��ȡ�浵ʧ��" << endl;
		exit(1);
	}
	system("cls");
}

//�������
void saveScore()
{
	if (preScore >= highestScore)
	{
		ofstream fout("score_saved.txt");
		fout << preScore;
		fout.close();
	}
}

//���ط���
void loadScore()
{
	ifstream fin("score_saved.txt");
	fin >> highestScore;
	fin.close();
}

//ս�����֣�������ţ�
void fightmusic()
{
	int i = rand() % 4;
	if (i == 0)
		PlaySound(TEXT(".//music//fight0.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	else if (i == 1)
		PlaySound(TEXT(".//music//fight1.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	else if (i == 2)
		PlaySound(TEXT(".//music//fight2.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	else if (i == 3)
		PlaySound(TEXT(".//music//fight3.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

//��ͼ����Ϊ1������
void map_1()
{
	int temp = rand() % 22;
	gotoxy(0, 27);
	cout << str_analysis[temp];

	string str;
	getline(cin, str);

	gotoxy(0, 27);
	for (unsigned int i = 0; i < str_analysis[temp].length(); i++)
		cout << " ";
	for (unsigned int i = 0; i < str.length(); i++)
		cout << " ";
}

//��ͼ����Ϊ3��ҽ��
void map_3()
{
	color(15);

	gotoxy(102, 21);
	cout << "����������Ҳ���ˣ�";
	gotoxy(102, 22);
	cout << "�ú���Ϣ�ɣ�";
	Sleep(1000);
	gotoxy(102, 21);
	cout << "                   ";
	gotoxy(102, 22);
	cout << "            ";

	gotoxy(102, 21);
	cout << "������������";
	Sleep(1000);
	gotoxy(102, 21);
	cout << "            ";

	saber.setPrePH(saber.getPH());
	archer.setPrePH(archer.getPH());
	lancer.setPrePH(lancer.getPH());
	roleDataPrint(protagonist);

	gotoxy(102, 21);
	cout << "��������Ϣ�ò����أ�";
	gotoxy(102, 22);
	cout << "����������!";
	Sleep(1000);
	gotoxy(102, 21);
	cout << "                    ";
	gotoxy(102, 22);
	cout << "           ";
}

//��ͼ����Ϊ4���̵�
void map_4()
{
	if (characterORcharacterprinting == 0)
	{
		shopmenuPrint(shopmenu, 4, 102, 21, protagonist);
	}
	else if (characterORcharacterprinting == 1)
	{
		char c;
		int ret;
		int index = 0;
		system("cls");
		picturePainting(".//pic//TXT//shop//ASCII-shop.txt", 601, 198);
		while ((c = getchar()) != EOF && c != '\n');
		picturePainting(".//pic//TXT//shop//ASCII-shopmenu_item0.txt", 601, 198);
		while (1)
		{
			ret = _getch();
			switch (ret)
			{
			case 'w':
				if (index == 1 || index == 2 || index == 3)
				{
					index--;
					picturePainting(".//pic//TXT//shop//ASCII-shopmenu_item" + str_arr[index] + ".txt", 601, 198);
				}
				break;
			case 's':
				if (index == 0 || index == 1 || index == 2)
				{
					index++;
					picturePainting(".//pic//TXT//shop//ASCII-shopmenu_item" + str_arr[index] + ".txt", 601, 198);
				}
				break;
			case 13://Enter
			case 32://Space
				switch (index)
				{
				case 0://��ҩ
					if (protagonist->getMoney() >= 200)
					{
						myBackpack.setCurePH(myBackpack.getCurePH() + 1);
						protagonist->setMoney(protagonist->getMoney() - 200);
						picturePainting(".//pic//TXT//shop//ASCII-shopmenu_true.txt", 601, 198);
						while ((c = getchar()) != EOF && c != '\n');
						picturePainting(".//pic//TXT//shop//ASCII-shopmenu_item" + str_arr[index] + ".txt", 601, 198);
					}
					else if (protagonist->getMoney() < 200)
					{
						picturePainting(".//pic//TXT//shop//ASCII-shopmenu_false.txt", 601, 198);
						while ((c = getchar()) != EOF && c != '\n');
						picturePainting(".//pic//TXT//shop//ASCII-shopmenu_item" + str_arr[index] + ".txt", 601, 198);
					}
					break;
				case 1://����ҩ
					if (protagonist->getMoney() >= 500)
					{
						myBackpack.setCurePHgood(myBackpack.getCurePHgood() + 1);
						protagonist->setMoney(protagonist->getMoney() - 500);
						picturePainting(".//pic//TXT//shop//ASCII-shopmenu_true.txt", 601, 198);
						while ((c = getchar()) != EOF && c != '\n');
						picturePainting(".//pic//TXT//shop//ASCII-shopmenu_item" + str_arr[index] + ".txt", 601, 198);
					}
					else if (protagonist->getMoney() < 500)
					{
						picturePainting(".//pic//TXT//shop//ASCII-shopmenu_false.txt", 601, 198);
						while ((c = getchar()) != EOF && c != '\n');
						picturePainting(".//pic//TXT//shop//ASCII-shopmenu_item" + str_arr[index] + ".txt", 601, 198);
					}
					break;
				case 2://���鵤
					if (protagonist->getMoney() >= 800)
					{
						myBackpack.setEnhanceEXP(myBackpack.getEnhanceEXP() + 1);
						protagonist->setMoney(protagonist->getMoney() - 800);
						picturePainting(".//pic//TXT//shop//ASCII-shopmenu_true.txt", 601, 198);
						while ((c = getchar()) != EOF && c != '\n');
						picturePainting(".//pic//TXT//shop//ASCII-shopmenu_item" + str_arr[index] + ".txt", 601, 198);
					}
					else if (protagonist->getMoney() < 800)
					{
						picturePainting(".//pic//TXT//shop//ASCII-shopmenu_false.txt", 601, 198);
						while ((c = getchar()) != EOF && c != '\n');
						picturePainting(".//pic//TXT//shop//ASCII-shopmenu_item" + str_arr[index] + ".txt", 601, 198);
					}
					break;
				case 3://�˳�
					setConsoleDefault();
					mapPrint(protagonist);
					return;
				}
			}
		}
	}
}

//��ͼ����Ϊ5������Boss1
void map_5()
{
	saber_nivose_one = 1;
	boss_one.setPrePH(boss_one.getPH());

	char c;

	color(14);
	gotoxy(0, 28);
	cout << "��������������ս�ĵ�һ������أ���ս��Ҫ����Ŷ��" << endl;
	while ((c = getchar()) != EOF && c != '\n');
	cout << "��  ���ǵ��أ���һ���ᾡ����" << endl;
	while ((c = getchar()) != EOF && c != '\n');
	cout << "����������Ķ�ʿ�ǲ�����ʤ��֮����ҫ��Ҳ������ʧ��֮���ɥ��ֻ��׷Ѱ��һ��ʤ����" << endl;
	cout << "      ���Բ����ⳡս����Σ�ϣ���㶼�ܴ��ⳡս���еõ��ջ������ս����ð�յ��������ڡ�" << endl;
	while ((c = getchar()) != EOF && c != '\n');
	system("cls");

	fightmusic();
	if (characterORcharacterprinting == 0)
	{
		picturePainting(".//pic//TXT//role//ASCII-boss0.txt", 601, 198);
		while ((c = getchar()) != EOF && c != '\n');
		setConsoleDefault();
		CfightScene();
		fightData(protagonist, boss_one);
	}
	else if (characterORcharacterprinting == 1)
	{
		fightScene();
		fightData(protagonist, boss_one);
	}

	flag = 0;
	while (flag == 0)
	{
		fightmenuPrint(fightmenu, 3, 60, 21, protagonist, boss_one);
	}
	if (flag == 1)
		boss_one.setFlag(1);
	else if (flag == 2)
	{
		boss_one.setFlag(2);
		myBackpack.setBadge(myBackpack.getBadge() + 1);
	}

	setConsoleDefault();
	mapPrint(protagonist);
	PlaySound(TEXT(".//music//map.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

//��ͼ����Ϊ6������Boss2
void map_6()
{
	saber_nivose_one = 1;
	boss_two.setPrePH(boss_two.getPH());

	char c;

	color(14);
	gotoxy(0, 28);
	cout << "��  ��������ã���������ս���ݵ�" << endl;
	while ((c = getchar()) != EOF && c != '\n');
	cout << "�������ޣ����������ˣ�����ܾ���Ŷ���Ѿ��þ�û�м�������һ���г������������ˡ�" << endl;
	cout << "      �����˰�������Ӧ��Ҫ����ôһ������ġ����Ͱɣ�" << endl;
	while ((c = getchar()) != EOF && c != '\n');
	cout << "��  ��лл�����Ŀ佱��" << endl;
	while ((c = getchar()) != EOF && c != '\n');
	system("cls");

	fightmusic();
	if (characterORcharacterprinting == 0)
	{
		picturePainting(".//pic//TXT//role//ASCII-boss1.txt", 601, 198);
		while ((c = getchar()) != EOF && c != '\n');
		setConsoleDefault();
		CfightScene();
		fightData(protagonist, boss_two);
	}
	else if (characterORcharacterprinting == 1)
	{
		fightScene();
		fightData(protagonist, boss_two);
	}

	flag = 0;
	while (flag == 0)
	{
		fightmenuPrint(fightmenu, 3, 60, 21, protagonist, boss_two);
	}
	if (flag == 1)
		boss_two.setFlag(1);
	else if (flag == 2)
	{
		boss_two.setFlag(2);
		myBackpack.setBadge(myBackpack.getBadge() + 1);
	}

	setConsoleDefault();
	mapPrint(protagonist);
	PlaySound(TEXT(".//music//map.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

//��ͼ����Ϊ7������Boss3
void map_7()
{
	saber_nivose_one = 1;
	boss_three.setPrePH(boss_three.getPH());

	char c;

	color(14);
	gotoxy(0, 28);
	cout << "����������������ս�߰ɣ��Ѿ��þ�û�п�����ս���ˣ�ϣ������һ�����ʵ�ս����" << endl;
	cout << "      ������ʱ������ã�����������ж�����������ʧ����Ҳ�ܴ���ѧ����ʲô���������ɣ����ǿ�ʼ�ɡ�" << endl;
	while ((c = getchar()) != EOF && c != '\n');
	cout << "��  ���ţ��õģ����ǿ�ʼ�ɡ�" << endl;
	while ((c = getchar()) != EOF && c != '\n');
	system("cls");

	fightmusic();
	if (characterORcharacterprinting == 0)
	{
		picturePainting(".//pic//TXT//role//ASCII-boss2.txt", 601, 198);
		while ((c = getchar()) != EOF && c != '\n');
		setConsoleDefault();
		CfightScene();
		fightData(protagonist, boss_three);
	}
	else if (characterORcharacterprinting == 1)
	{
		fightScene();
		fightData(protagonist, boss_three);
	}

	flag = 0;
	while (flag == 0)
	{
		fightmenuPrint(fightmenu, 3, 60, 21, protagonist, boss_three);
	}
	if (flag == 1)
		boss_three.setFlag(1);
	else if (flag == 2)
	{
		boss_three.setFlag(2);
		myBackpack.setBadge(myBackpack.getBadge() + 1);
	}

	setConsoleDefault();
	mapPrint(protagonist);
	PlaySound(TEXT(".//music//map.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

//��ͼ����Ϊ8������Boss4
void map_8()
{
	saber_nivose_one = 1;
	boss_four.setPrePH(boss_four.getPH());

	char c;

	color(14);
	gotoxy(0, 28);
	cout << "��  �����������ǵ�������������ս�ġ�" << endl;
	while ((c = getchar()) != EOF && c != '\n');
	cout << "������������һ���Ͽ��ս��������Ҫ���ǰ��պ��Լ������ơ�ֻ��ǿ�߲Ż���ʤ�������Ͱɣ����ӡ�" << endl;
	while ((c = getchar()) != EOF && c != '\n');
	cout << "��  ���õġ�";
	while ((c = getchar()) != EOF && c != '\n');
	system("cls");

	fightmusic();
	if (characterORcharacterprinting == 0)
	{
		picturePainting(".//pic//TXT//role//ASCII-boss3.txt", 601, 198);
		while ((c = getchar()) != EOF && c != '\n');
		setConsoleDefault();
		CfightScene();
		fightData(protagonist, boss_four);
	}
	else if (characterORcharacterprinting == 1)
	{
		fightScene();
		fightData(protagonist, boss_four);
	}

	flag = 0;
	while (flag == 0)
	{
		fightmenuPrint(fightmenu, 3, 60, 21, protagonist, boss_four);
	}
	if (flag == 1)
		boss_four.setFlag(1);
	else if (flag == 2)
	{
		boss_four.setFlag(2);
		myBackpack.setBadge(myBackpack.getBadge() + 1);
	}

	setConsoleDefault();
	mapPrint(protagonist);
	PlaySound(TEXT(".//music//map.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

//��ͼ����Ϊ9������Boss5
void map_9()
{
	saber_nivose_one = 1;
	boss_five.setPrePH(boss_five.getPH());

	char c;

	color(14);
	gotoxy(0, 28);
	cout << "��������������ս�����һ������ˣ���ֵ������治���װ���" << endl;
	while ((c = getchar()) != EOF && c != '\n');
	cout << "��  ���ǵģ�������������һϵ�е����������������Ѿ����������ֵ�����������֣��ٵ�������ϲ����������" << endl;
	cout << "      ���������ⳡս���Ҹ��Ӳ���ս�ܣ�Ϊ����֤��������֮�佨�������ꡣ" << endl;
	while ((c = getchar()) != EOF && c != '\n');
	cout << "�����������Ǳ��ֱ����ֳٶۣ�ֻҪ������̤ʵ�ص�ǰ�����վ�����ʵ������ġ����Ͱɣ����ӡ�";
	while ((c = getchar()) != EOF && c != '\n');
	system("cls");

	fightmusic();
	if (characterORcharacterprinting == 0)
	{
		picturePainting(".//pic//TXT//role//ASCII-boss4.txt", 601, 198);
		while ((c = getchar()) != EOF && c != '\n');
		setConsoleDefault();
		CfightScene();
		fightData(protagonist, boss_five);
	}
	else if (characterORcharacterprinting == 1)
	{
		fightScene();
		fightData(protagonist, boss_five);
	}

	flag = 0;
	while (flag == 0)
	{
		fightmenuPrint(fightmenu, 3, 60, 21, protagonist, boss_five);
	}
	if (flag == 1)
		boss_five.setFlag(1);
	else if (flag == 2)
	{
		boss_five.setFlag(2);
		myBackpack.setBadge(myBackpack.getBadge() + 1);
	}

	setConsoleDefault();
	mapPrint(protagonist);
	PlaySound(TEXT(".//music//map.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}
 
//��ͼ����Ϊ10��NPC
void map_10()
{
	saber_nivose_one = 1;
	char c;

	int ci = rand() % 32;
	color(14);
	gotoxy(0, 28);
	cout << sayings_npc[ci];
	while ((c = getchar()) != EOF && c != '\n');
	system("cls");

	fightmusic();
	if (characterORcharacterprinting == 0)
	{
		picturePainting(".//pic//TXT//fightScene//ASCII-fightScene_npc.txt", 601, 198);
		while ((c = getchar()) != EOF && c != '\n');
		setConsoleDefault();
	}
	int bi = (*protagonist).getLV() + rand() % (difficulty + 1);
	Villain npc(bi);
	fightScene();
	fightData(protagonist, npc);

	flag = 0;
	while (flag == 0)
	{
		fightmenuPrint(fightmenu, 3, 60, 21, protagonist, npc);
	}
	if (flag == 1)
	{
		(*protagonist).setMoney((*protagonist).getMoney() / 2);
	}
	if (flag == 2)
	{
		(*protagonist).setPreEXP_EXP_LV(2);
	}

	setConsoleDefault();
	mapPrint(protagonist);
	PlaySound(TEXT(".//music//map.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
} 

//��ͼ����Ϊ5~9���ѳɹ���ս����
void map_false()
{
	char c;
	color(15);
	gotoxy(0, 27);
	cout << "�õ�������ս�ɹ���������˻���";
	while ((c = getchar()) != EOF && c != '\n');
	gotoxy(0, 27);
	cout << "                                                                                          ";
}

//��ͼ����11�����͵㣨���ռ����л��£�
void map_11_1()
{
	saveScore();

	char c;
	system("cls");
	picturePainting(".//pic//TXT//end//ASCII-end.txt", 601, 198);
	while ((c = getchar()) != EOF && c != '\n');
}

//��ͼ����11�����͵㣨δ�ռ����л��£�
void map_11_2()
{
	color(15);
	gotoxy(0, 27);
	cout << "��δ���ȫ�����£������Ŭ����";
	Sleep(2000);
	gotoxy(0, 27);
	cout << "                              ";
}

//��ͼ����Ϊ0���ݵأ��������
void map_0()
{
	char c;
	int r = rand() % (7 - difficulty);
	if (r == 0 && (*protagonist).getPrePH() > 0)
	{
		saber_nivose_one = 1;

		fightmusic();
		if (characterORcharacterprinting == 0)
		{
			system("cls");
			fightScene();
			color(14);
			gotoxy(31, 13);
			cout << "Ұ �� �� �� �� �� �� �� �ˣ�";
			Sleep(1000);
			gotoxy(31, 13);
			cout << "                            ";
			gotoxy(31, 13);
			cout << "׼ �� �� ս �ɣ�";
			Sleep(1000);
			gotoxy(31, 13);
			cout << "                ";
		}
		else if (characterORcharacterprinting == 1)
		{
			gotoxy(0, 27);
			cout << "Ұ���Ĺ����������ˣ�׼����ս��";
			Sleep(2000);

			system("cls");
			picturePainting(".//pic//TXT//fightScene//ASCII-fightScene_monster.txt", 601, 198);
			while ((c = getchar()) != EOF && c != '\n');
			setConsoleDefault();
			CfightScene();
		}

		int b;
		if ((*protagonist).getLV() < 3)
			b = 1;
		else if ((*protagonist).getLV() >= 3)
			b = (*protagonist).getLV() - rand() % (difficulty + 1);
		Villain comprimario(b);
		fightData(protagonist, comprimario);

		flag = 0;
		while (flag == 0)
		{
			fightmenuPrint_other(fightmenu_other, 4, 60, 21, protagonist, comprimario);
		}

		setConsoleDefault();
		mapPrint(protagonist);
		PlaySound(TEXT(".//music//map.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	}
}

//��Ϸ������������
void backgroundPrint()
{
	videoPainting(".//pic//TXT//background//ASCII-background", 447, 601, 198, 2, 2);
}

//��Ϸ����ͼƬչʾ
void introductionPrint()
{
	char c;
	picturePainting(".//pic//TXT//introduction//ASCII-introduction_map.txt", 601, 198);
	while ((c = getchar()) != EOF && c != '\n');
	picturePainting(".//pic//TXT//introduction//ASCII-introduction_key.txt", 601, 198);
	while ((c = getchar()) != EOF && c != '\n');
}

//�Ѷ�ѡ��
void difficultyPrint()
{
	int ret;
	int index = 0;
	picturePainting(".//pic//TXT//difficulty//ASCII-difficulty0.txt", 601, 198);
	while (1)
	{
		ret = _getch();
		switch (ret)
		{
		case 'w':
			if (index == 1 || index == 2)
			{
				index--;
				picturePainting(".//pic//TXT//difficulty//ASCII-difficulty" + str_arr[index] + ".txt", 601, 198);
			}
			break;
		case 's':
			if (index == 0 || index == 1)
			{
				index++;
				picturePainting(".//pic//TXT//difficulty//ASCII-difficulty" + str_arr[index] + ".txt", 601, 198);
			}
			break;
		case 13:
		case 32:
			switch (index)
			{
			case 0:
				difficulty = 0;
				break;
			case 1:
				difficulty = 1;
				break;
			case 2:
				difficulty = 2;
				break;
			}
			if (difficulty == 0)
			{
				boss_one.setPreEXP_EXP_LV(3);
				boss_two.setPreEXP_EXP_LV(5);
				boss_three.setPreEXP_EXP_LV(8);
				boss_four.setPreEXP_EXP_LV(10);
				boss_five.setPreEXP_EXP_LV(12);
			}
			else if (difficulty == 1)
			{
				boss_one.setPreEXP_EXP_LV(5);
				boss_two.setPreEXP_EXP_LV(8);
				boss_three.setPreEXP_EXP_LV(10);
				boss_four.setPreEXP_EXP_LV(12);
				boss_five.setPreEXP_EXP_LV(15);
			}
			else if (difficulty == 2)
			{
				boss_one.setPreEXP_EXP_LV(5);
				boss_two.setPreEXP_EXP_LV(10);
				boss_three.setPreEXP_EXP_LV(14);
				boss_four.setPreEXP_EXP_LV(18);
				boss_five.setPreEXP_EXP_LV(20);
			}
			return;
		}
	}
}

//��Ϸ��ʼ�����ӡ
void coverPrint()
{
	int ret;
	int index = 0;
	picturePainting(".//pic//TXT//cover//ASCII-cover0.txt", 601, 198);
	while (1)
	{
		ret = _getch();
		switch (ret)
		{
		case 'w':
			if (index == 1 || index == 2)
			{
				index--;
				picturePainting(".//pic//TXT//cover//ASCII-cover" + str_arr[index] + ".txt", 601, 198);
			}
			break;
		case 's':
			if (index == 0 || index == 1)
			{
				index++;
				picturePainting(".//pic//TXT//cover//ASCII-cover" + str_arr[index] + ".txt", 601, 198);
			}
			break;
		case 13://Enter
		case 32://Space
			switch (index)
			{
			case 0://��ʼ��Ϸ
				difficultyPrint();
				system("cls");
				return;

			case 1://��ȡ�浵
				load();
				system("cls");
				return;

			case 2:
				char c;

				backgroundPrint();       //��Ϸ����
				while ((c = getchar()) != EOF && c != '\n');
				system("cls");

				introductionPrint();   	//����˵��
				system("cls");
				return;
			}
		}
	}
}

//char����ת����int����
void myCharToInt(int& num, char* ch, int n)
{
	num = 0;
	for (int count = 0, count_another = n - 1; count < n; count++, count_another--)
	{
		num += (ch[count_another] - '0')*pow(10, count);
	}

}

//���������
int main()
{
	//��ʼ��
	srand(time(NULL));
	system("mode con cols=1500 lines=1000");
	PlaySound(TEXT(".//music//cover.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	coverPrint();

	//��ʼ��
	setConsoleDefault();
	loadScore();
	protagonist = &saber;
	mapPrint(protagonist);
	gotoxy(pos.X, pos.Y);
	color(14);
	cout << "S";
	PlaySound(TEXT(".//music//map.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	//������Ϣѭ��
	while (1)
	{
		if (_kbhit())//���յ��û����루���������룩
		{
			//���ԭλ�÷���
			gotoxy(pos.X, pos.Y);
			color(14);
			cout << " ";

			char ch = 'q';
			ch = _getch();
			//�ַ�˵��
			//w  ����
			//s  ����
			//a  ����
			//d  ����
			//t  �л��ַ�|�ַ���ģʽ
			//b  ��ͼ�д򿪱���
			//q  ����
			//Esc �˳���Ϸ
			//1  �л�����ΪSabre
			//2  �л�����ΪArcher
			//3  �л�����ΪLancer
			switch (ch)
			{
			case 'w':
				if (mapPartOne[pos.Y - 1][pos.X] == 1)
				{
					map_1();
					mapPartOne[pos.Y - 1][pos.X] = 0;
				}
				if (mapPartOne[pos.Y - 1][pos.X] == 3)
				{
					map_3();
				}
				if (mapPartOne[pos.Y - 1][pos.X] == 4)
				{
					map_4();
				}
				if (mapPartOne[pos.Y - 1][pos.X] == 5 && (*protagonist).getPrePH() > 0 && (boss_one.getFlag() == 0 || boss_one.getFlag() == 1))
				{
					map_5();
				}
				if (mapPartOne[pos.Y - 1][pos.X] == 5 && boss_one.getFlag() == 2)
				{
					map_false();
				}
				if (mapPartOne[pos.Y - 1][pos.X] == 6 && (*protagonist).getPrePH() > 0 && (boss_two.getFlag() == 0 || boss_two.getFlag() == 1))
				{
					map_6();
				}
				if (mapPartOne[pos.Y - 1][pos.X] == 6 && boss_two.getFlag() == 2)
				{
					map_false();
				}
				if (mapPartOne[pos.Y - 1][pos.X] == 7 && (*protagonist).getPrePH() > 0 && (boss_three.getFlag() == 0 || boss_three.getFlag() == 1))
				{
					map_7();
				}
				if (mapPartOne[pos.Y - 1][pos.X] == 7 && boss_three.getFlag() == 2)
				{
					map_false();
				}
				if (mapPartOne[pos.Y - 1][pos.X] == 8 && (*protagonist).getPrePH() > 0 && (boss_four.getFlag() == 0 || boss_four.getFlag() == 1))
				{
					map_8();
				}
				if (mapPartOne[pos.Y - 1][pos.X] == 8 && boss_four.getFlag() == 2)
				{
					map_false();
				}
				if (mapPartOne[pos.Y - 1][pos.X] == 9 && (*protagonist).getPrePH() > 0 && (boss_five.getFlag() == 0 || boss_five.getFlag() == 1))
				{
					map_9();
				}
				if (mapPartOne[pos.Y - 1][pos.X] == 9 && boss_five.getFlag() == 2)
				{
					map_false();
				}
				if (mapPartOne[pos.Y - 1][pos.X] == 10 && (*protagonist).getPrePH() > 0)
				{
					map_10();
					mapPartOne[pos.Y - 1][pos.X] = 0;
				}
				if (mapPartOne[pos.Y - 1][pos.X] == 11 && myBackpack.getBadge() == 5)
				{
					map_11_1();
					return 0;
				}
				if (mapPartOne[pos.Y - 1][pos.X] == 11 && myBackpack.getBadge() != 5)
				{
					map_11_2();
				}
				if (mapPartOne[pos.Y - 1][pos.X] == 0)
				{
					pos.Y--;
					map_0();
				}
				break;

			case 's':
				if (mapPartOne[pos.Y + 1][pos.X] == 1)
				{
					map_1();
					mapPartOne[pos.Y + 1][pos.X] = 0;
				}
				if (mapPartOne[pos.Y + 1][pos.X] == 3)
				{
					map_3();
				}
				if (mapPartOne[pos.Y + 1][pos.X] == 4)
				{
					map_4();
				}
				if (mapPartOne[pos.Y + 1][pos.X] == 5 && (*protagonist).getPrePH() > 0 && (boss_one.getFlag() == 0 || boss_one.getFlag() == 1))
				{
					map_5();
				}
				if (mapPartOne[pos.Y + 1][pos.X] == 5 && boss_one.getFlag() == 2)
				{
					map_false();
				}
				if (mapPartOne[pos.Y + 1][pos.X] == 6 && (*protagonist).getPrePH() > 0 && (boss_two.getFlag() == 0 || boss_two.getFlag() == 1))
				{
					map_6();
				}
				if (mapPartOne[pos.Y + 1][pos.X] == 6 && boss_two.getFlag() == 2)
				{
					map_false();
				}
				if (mapPartOne[pos.Y + 1][pos.X] == 7 && (*protagonist).getPrePH() > 0 && (boss_three.getFlag() == 0 || boss_three.getFlag() == 1))
				{
					map_7();
				}
				if (mapPartOne[pos.Y + 1][pos.X] == 7 && boss_three.getFlag() == 2)
				{
					map_false();
				}
				if (mapPartOne[pos.Y + 1][pos.X] == 8 && (*protagonist).getPrePH() > 0 && (boss_four.getFlag() == 0 || boss_four.getFlag() == 1))
				{
					map_8();
				}
				if (mapPartOne[pos.Y + 1][pos.X] == 8 && boss_four.getFlag() == 2)
				{
					map_false();
				}
				if (mapPartOne[pos.Y + 1][pos.X] == 9 && (*protagonist).getPrePH() > 0 && (boss_five.getFlag() == 0 || boss_five.getFlag() == 1))
				{
					map_9();
				}
				if (mapPartOne[pos.Y + 1][pos.X] == 9 && boss_five.getFlag() == 2)
				{
					map_false();
				}
				if (mapPartOne[pos.Y + 1][pos.X] == 10 && (*protagonist).getPrePH() > 0)
				{
					map_10();
					mapPartOne[pos.Y + 1][pos.X] = 0;
				}
				if (mapPartOne[pos.Y + 1][pos.X] == 11 && myBackpack.getBadge() == 5)
				{
					map_11_1();
					return 0;
				}
				if (mapPartOne[pos.Y + 1][pos.X] == 11 && myBackpack.getBadge() != 5)
				{
					map_11_2();
				}
				if (mapPartOne[pos.Y + 1][pos.X] == 0)
				{
					pos.Y++;
					map_0();
				}
				break;

			case 'a':
				if (mapPartOne[pos.Y][pos.X - 1] == 1)
				{
					map_1();
					mapPartOne[pos.Y][pos.X - 1] = 0;
				}
				if (mapPartOne[pos.Y][pos.X - 1] == 3)
				{
					map_3();
				}
				if (mapPartOne[pos.Y][pos.X - 1] == 4)
				{
					map_4();
				}
				if (mapPartOne[pos.Y][pos.X - 1] == 5 && (*protagonist).getPrePH() > 0 && (boss_one.getFlag() == 0 || boss_one.getFlag() == 1))
				{
					map_5();
				}
				if (mapPartOne[pos.Y][pos.X - 1] == 5 && boss_one.getFlag() == 2)
				{
					map_false();
				}
				if (mapPartOne[pos.Y][pos.X - 1] == 6 && (*protagonist).getPrePH() > 0 && (boss_two.getFlag() == 0 || boss_two.getFlag() == 1))
				{
					map_6();
				}
				if (mapPartOne[pos.Y][pos.X - 1] == 6 && boss_two.getFlag() == 2)
				{
					map_false();
				}
				if (mapPartOne[pos.Y][pos.X - 1] == 7 && (*protagonist).getPrePH() > 0 && (boss_three.getFlag() == 0 || boss_three.getFlag() == 1))
				{
					map_7();
				}
				if (mapPartOne[pos.Y][pos.X - 1] == 7 && boss_three.getFlag() == 2)
				{
					map_false();
				}
				if (mapPartOne[pos.Y][pos.X - 1] == 8 && (*protagonist).getPrePH() > 0 && (boss_four.getFlag() == 0 || boss_four.getFlag() == 1))
				{
					map_8();
				}
				if (mapPartOne[pos.Y][pos.X - 1] == 8 && boss_four.getFlag() == 2)
				{
					map_false();
				}
				if (mapPartOne[pos.Y][pos.X - 1] == 9 && (*protagonist).getPrePH() > 0 && (boss_five.getFlag() == 0 || boss_five.getFlag() == 1))
				{
					map_9();
				}
				if (mapPartOne[pos.Y][pos.X - 1] == 9 && boss_five.getFlag() == 2)
				{
					map_false();
				}
				if (mapPartOne[pos.Y][pos.X - 1] == 10 && (*protagonist).getPrePH() > 0)
				{
					map_10();
					mapPartOne[pos.Y][pos.X - 1] = 0;
				}
				if (mapPartOne[pos.Y][pos.X - 1] == 11 && myBackpack.getBadge() == 5)
				{
					map_11_1();
					return 0;
				}
				if (mapPartOne[pos.Y][pos.X - 1] == 11 && myBackpack.getBadge() != 5)
				{
					map_11_2();
				}
				if (mapPartOne[pos.Y][pos.X - 1] == 0)
				{
					pos.X--;
					map_0();
				}
				break;

			case 'd':
				if (mapPartOne[pos.Y][pos.X + 1] == 1)
				{
					map_1();
					mapPartOne[pos.Y][pos.X + 1] = 0;
				}
				if (mapPartOne[pos.Y][pos.X + 1] == 3)
				{
					map_3();
				}
				if (mapPartOne[pos.Y][pos.X + 1] == 4)
				{
					map_4();
				}
				if (mapPartOne[pos.Y][pos.X + 1] == 5 && (*protagonist).getPrePH() > 0 && (boss_one.getFlag() == 0 || boss_one.getFlag() == 1))
				{
					map_5();
				}
				if (mapPartOne[pos.Y][pos.X + 1] == 5 && boss_one.getFlag() == 2)
				{
					map_false();
				}
				if (mapPartOne[pos.Y][pos.X + 1] == 6 && (*protagonist).getPrePH() > 0 && (boss_two.getFlag() == 0 || boss_two.getFlag() == 1))
				{
					map_6();
				}
				if (mapPartOne[pos.Y][pos.X + 1] == 6 && boss_two.getFlag() == 2)
				{
					map_false();
				}
				if (mapPartOne[pos.Y][pos.X + 1] == 7 && (*protagonist).getPrePH() > 0 && (boss_three.getFlag() == 0 || boss_three.getFlag() == 1))
				{
					map_7();
				}
				if (mapPartOne[pos.Y][pos.X + 1] == 7 && boss_three.getFlag() == 2)
				{
					map_false();
				}
				if (mapPartOne[pos.Y][pos.X + 1] == 8 && (*protagonist).getPrePH() > 0 && (boss_four.getFlag() == 0 || boss_four.getFlag() == 1))
				{
					map_8();
				}
				if (mapPartOne[pos.Y][pos.X + 1] == 8 && boss_four.getFlag() == 2)
				{
					map_false();
				}
				if (mapPartOne[pos.Y][pos.X + 1] == 9 && (*protagonist).getPrePH() > 0 && (boss_five.getFlag() == 0 || boss_five.getFlag() == 1))
				{
					map_9();
				}
				if (mapPartOne[pos.Y][pos.X + 1] == 9 && boss_five.getFlag() == 2)
				{
					map_false();
				}
				if (mapPartOne[pos.Y][pos.X + 1] == 10 && (*protagonist).getPrePH() > 0)
				{
					map_10();
					mapPartOne[pos.Y][pos.X + 1] = 0;
				}
				if (mapPartOne[pos.Y][pos.X + 1] == 11 && myBackpack.getBadge() == 5)
				{
					map_11_1();
					return 0;
				}
				if (mapPartOne[pos.Y][pos.X + 1] == 11 && myBackpack.getBadge() != 5)
				{
					map_11_2();
				}
				if (mapPartOne[pos.Y][pos.X + 1] == 0)
				{
					pos.X++;
					map_0();
				}
				break;

			case 't':
				if (characterORcharacterprinting == 0)
				{
					characterORcharacterprinting = 1;
					gotoxy(102, 1);
					cout << "          ";
					gotoxy(102, 1);
					color(15);
					cout << "�ַ���ģʽ";
				}
				else if (characterORcharacterprinting == 1)
				{
					characterORcharacterprinting = 0;
					gotoxy(102, 1);
					cout << "          ";
					gotoxy(102, 1);
					color(15);
					cout << "�ַ�ģʽ";
				}
				break;

			case 'b':
				bakckpackmenuPrintinMap(backpackmenuInMap, 4, 102, 21, protagonist);
				break;

			case 'q':
				color(15);
				gotoxy(0, 27);
				cout << "��Ϸ�ѱ���";
				Sleep(2000);
				gotoxy(0, 27);
				cout << "          ";
				save();
				break;

			case 27://Esc
			{
				gotoxy(0, 27);
				cout << "�˳���Ϸ" << endl;
				Sleep(2000);
				saveScore();
				return 0;
			}

			case '1':
			{
				print = 0;
				protagonist = &saber;
				roleDataPrint(protagonist);
				break;
			}

			case '2':
			{
				print = 1;
				protagonist = &archer;
				roleDataPrint(protagonist);
				break;
			}

			case '3':
			{
				print = 2;
				protagonist = &lancer;
				roleDataPrint(protagonist);
				break;
			}

			default:
				break;
			}

			//��ӡ��λ�÷���
			gotoxy(pos.X, pos.Y);
			color(14);
			if (print == 0)
				cout << "S" << endl;
			else if (print == 1)
				cout << "A" << endl;
			else if (print == 2)
				cout << "L" << endl;
		}
	}
}
