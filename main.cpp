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

int flag = 0;//标识战斗状态
int print = 0;//地图中打印人物
int difficulty = 0;//难度选择
double saber_nivose_one = 1;//用于技能
int archer_nivose_two = 0;//用于技能
int characterORcharacterprinting = 0;//字符模式|字符画模式

int preScore = 0;//当前分数
int highestScore= 0;//历史最高分

COORD pos = {6, 25};//初始位置

Backpack myBackpack;//背包初始化
Protagonist *protagonist;//基类指针初始化

//三大主角初始化
Saber saber(1);//Saber初始化
Archer archer(1);//Archer初始化
Lancer lancer(1);//Lancer初始化

//Boss初始化
Villain boss_one(1);
Villain boss_two(1);
Villain boss_three(1);
Villain boss_four(1);
Villain boss_five(1);

//用于字符动画输出
string str_arr[500] = { "0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","55","56","57","58","59","60","61","62","63","64","65","66","67","68","69","70","71","72","73","74","75","76","77","78","79","80","81","82","83","84","85","86","87","88","89","90","91","92","93","94","95","96","97","98","99","100","101","102","103","104","105","106","107","108","109","110","111","112","113","114","115","116","117","118","119","120","121","122","123","124","125","126","127","128","129","130","131","132","133","134","135","136","137","138","139","140","141","142","143","144","145","146","147","148","149","150","151","152","153","154","155","156","157","158","159","160","161","162","163","164","165","166","167","168","169","170","171","172","173","174","175","176","177","178","179","180","181","182","183","184","185","186","187","188","189","190","191","192","193","194","195","196","197","198","199","200","201","202","203","204","205","206","207","208","209","210","211","212","213","214","215","216","217","218","219","220","221","222","223","224","225","226","227","228","229","230","231","232","233","234","235","236","237","238","239","240","241","242","243","244","245","246","247","248","249","250","251","252","253","254","255","256","257","258","259","260","261","262","263","264","265","266","267","268","269","270","271","272","273","274","275","276","277","278","279","280","281","282","283","284","285","286","287","288","289","290","291","292","293","294","295","296","297","298","299","300","301","302","303","304","305","306","307","308","309","310","311","312","313","314","315","316","317","318","319","320","321","322","323","324","325","326","327","328","329","330","331","332","333","334","335","336","337","338","339","340","341","342","343","344","345","346","347","348","349","350","351","352","353","354","355","356","357","358","359","360","361","362","363","364","365","366","367","368","369","370","371","372","373","374","375","376","377","378","379","380","381","382","383","384","385","386","387","388","389","390","391","392","393","394","395","396","397","398","399","400","401","402","403","404","405","406","407","408","409","410","411","412","413","414","415","416","417","418","419","420","421","422","423","424","425","426","427","428","429","430","431","432","433","434","435","436","437","438","439","440","441","442","443","444","445","446","447","448","449","450","451","452","453","454","455","456","457","458","459","460","461","462","463","464","465","466","467","468","469","470","471","472","473","474","475","476","477","478","479","480","481","482","483","484","485","486","487","488","489","490","491","492","493","494","495","496","497","498","499" };

//0——草地   1——宝箱   2——森林   3——房屋（中心）   4——房屋（商店）   5~9——房屋（道馆）  10——NPC  11——传送点
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

//问题
string str_question[]//23
{
	//工科数学分析第二章——极限与连续
	"求极限：lim(x->2) (x^2 - x - 2) / (x^3 - 3x^2 + 2x)",//3/2
	"求极限：lim(x->∞) (x^2 + 2) / (x^2 - 6)",//1
	"求极限：lim(x->∞) (x^2) / 2^x",//0 
	"求极限：lim(x->∞) x√x",//1 
	"求极限：lim(x->∞) sinx / x",//0 
	"求极限：lim(n->∞) n!/n^n ",//0 
	"求极限：lim(n->∞) (1 + 2 + 3 + …… + n-1) / n^2",//1/2 
	"求曲线y = √(1 + x^2)的渐近线 A.y=x+1 B.y=x-1 C.y=x+1,y=x-1",//C
	"求极限：lim(n->∞) 1/2! + 2/3! + …… + n/(n+1)!",//1 
	"求极限：lim(x->0) sinx / x",//1  
	"求极限：lim(x->∞) (1 + 1/x)^x",//e
	"求极限：lim(n->∞) n^(1/n)",//1
	"求极限：lim(x->0) (tanx - sinx) / [(sinx)^3]",//1/2
	"求极限：lim(n->∞) 2^n / n!",//0
	"求数列极限：  x_n+1 = √(2x_n)",//2  
	"求数列极限：  x_n+1 = √(x_n + 6)",//3
	"求极限：lim(x->0) [(1 + x)^a - 1] / x   (a != 0)",//a 
	"求极限：lim(x->1) arcsin(1 - x) / lnx",//-1
	"判断间断点类型：y=lim(n->∞) [1-x^(2n)]/[1+x^(2n)],点为x = 1   A.跳跃 B.可去 C.无穷",//A
	"求极限：lim(n->∞) cos(x/2) cos(x/2^2) …… cos(x/2^n)",//sinx/x
	"求极限：lim(n->∞) [sin√(n + 1)] - [sin√n]",//0
	"求极限：lim(x->4) {[√(2x + 1)] - 3} / {[√(x - 2)] - √2}",//0
	"求极限：lim(a->π) sina / [1 - (a/π)^2]",//1
};

//问题答案
string str_answer[]//23
{
	//工科数学分析第二章——极限与连续
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
	"2√2/3",
	"π/2",
};

//问题分析
string str_analysis[]//24
{
	//工科数学分析第二章——极限与连续
	"习得破解技：求极限：lim(x->2) (x^2 - x - 2) / (x^3 - 3x^2 + 2x)——洛必达法则（0/0型）",
	"习得破解技：求极限：lim(x->∞) (x^2 + 2) / (x^2 - 6)——高阶无穷小，只看最高次幂项判断即可",
	"习得破解技：求极限：lim(x->∞) (x^2) / 2^x——法一：洛必达法则（∞/∞型）；法二：分子、分母图像观察法",
	"习得破解技：求极限：lim(x->∞) x√x——变形成幂函数形式e^[ln(x√x)]=e^(lnx/x),然后直接对指数位置求极限即可",
	"习得破解技：求极限：lim(x->∞) sinx / x——变形成sinx*（1/x），运用定理：有界量*无穷小=无穷小，结果还是无穷小",
	"习得破解技：求极限：lim(n->∞) n!/n^n ——夹逼定理( 0 < n!/n^n = n/n * n-1/n * …… * 1/n < 1/n ),然后再两边求极限夹逼即可",
	"习得破解技：求极限：lim(n->∞) (1 + 2 + 3 + …… + n-1) / n^2——分子先用等差数列求和公式，然后整体化简得(n - 1) / 2n",
	"习得破解技：求曲线y = √(1 + x^2)的渐近线 A.y=x+1 B.y=x-1 C.y=x+1,y=x-1——计算渐近线可以分两种情况考虑，斜率不存在（即渐近线垂直于x轴的情况，主要考察定义不存在点），斜率存在（套用公式分别算出斜率截距）",
	"习得破解技：求极限：lim(n->∞) 1/2! + 2/3! + …… + n/(n+1)!——裂项相减法，提示：n/(n+1)! = 1/n! - 1/(n+1)!",
	"习得破解技：求极限：lim(x->0) sinx / x——重要极限公式，也可用洛必达法则解（0/0型）",
	"习得破解技：求极限：lim(x->∞) (1 + 1/x)^x——重要极限公式，注意形式是1的无穷次方型",
	"习得破解技：求极限：lim(n->∞) n^(1/n)——化成幂函数形式e^(lnn/n),然后直接对指数位置求极限即可",
	"习得破解技：求极限：lim(x->0) (tanx - sinx) / [(sinx)^3]——分子提出tanx后用等价无穷小替换，分母直接用等价无穷小替换",
	"习得破解技：求极限：lim(n->∞) 2^n / n!——夹逼定理：0 < 2^n/n! = 2/1 * 2/2 * …… * 2/n < 2/1 * 2/2 * 2/n = 4/n,然后两边取极限夹逼中间即可",
	"习得破解技：求数列极限：  x_n+1 = √(2x_n)——经典题型，单调有界收敛性定理证明数列收敛，再将x_n+1和x_n换成一般变元a后解方程得a即为答案",
	"习得破解技：求数列极限：  x_n+1 = √(x_n + 6)——经典题型，单调有界收敛性定理证明数列收敛，再将x_n+1和x_n换成一般变元a后解方程得a即为答案",
	"习得破解技：求极限：lim(x->0) [(1 + x)^a - 1] / x   (a != 0)——洛必达法则（0/0型）",
	"习得破解技：求极限：lim(x->1) arcsin(1 - x) / lnx——洛必达法则（0/0型）",
	"习得破解技：判断间断点类型：y=lim(n->∞) [1-x^(2n)]/[1+x^(2n)],点为x = 1   A.跳跃 B.可去 C.无穷——对于用极限给出的函数先进行化简，对x分类讨论（|x|=1,|x|<1,|x|>1），可知其为分段函数，再着重判断分段点和函数无定义点即可",
	"习得破解技：求极限：lim(n->∞) cos(x/2) cos(x / 2^2) …… cos(x / 2^n)——配凑法，原式乘以2sin(x/2^n)，再除以2sin(x / 2^n)，然后用二倍角公式一直化简得sinx/[(2^n) * sin(x / 2^n)]，然后对分母化简得x*sin(x / 2^n) / (x / 2^n)后用重要极限公式得x",
	"习得破解技：求极限：lim(n->∞) [sin√(n + 1)] - [sin√n]——利用和差化积公式化为2 cos{[√(n + 1)+√n]/2} sin{[√(n + 1)-√n]/2}，而利用等价替换可简化为cos{[√(n + 1)+√n]/2} [√(n + 1)-√n]，是有界量乘以无穷小结果还是无穷小",
	"习得破解技：求极限：lim(x->4) {[√(2x + 1)] - 3} / {[√(x - 2)] - √2}——洛必达法则（0/0型）",
	"习得破解技：求极限：lim(a->π) sina / [1 - (a/π)^2]——换元法，令t=a/π（注意换元要换限），然后使用洛必达法则（0/0型）",
	"运气真不好，里面什么也没有哦！"
};

//npc对白
string sayings_npc[]//32
{
	"不管什么时候，能够改变世界的人都是一心追逐梦想的人！",
	"你说，海洋是眼泪汇集成的吗?",
	"我们这些老年人，拥有过去的历史和记忆。而你们这些年轻人，则拥有那未知的未来啊!",
	"孩子啊，追逐一切是不幸的开始，有做不到的事情的同时也有能做到的事情，知道这一点非常重要。",
	"哈哈，真想见识更多的景色啊。正因为知道了世界的广阔和自己的渺小，才会对明天充满希望呢！",
	"我……为什么要旅行呢？你还记得你踏上旅途的理由吗？",
	"什么都不做的话虽不会失败，但也不会成功，对吗？",
	"成长并不是一件坏事，忘记了赤子之心才是最糟的。",
	"我的面庞倒映在水面上，是充满了希望的笑脸。少年，可以让我看看你的面庞是怎样的吗？",
	"你知道吗，被人嘲笑的梦想，就越有实现的价值。",
	"很希望自己是一棵树，守静，向光，安然，敏感的神经末梢，触着流云和微风，窃窃的欢喜……",
	"嘿嘿，与人斗有什么意思，与天斗才其乐无穷的。",
	"每一段相遇都像河流与泥沙，在昼夜不息地流淌与冲击中，彼此改变着对方的形状……",
	"生命有裂缝，阳光才照得进来",
	"一剪闲云一溪月，一程山水一年华……",
	"你看春天的花又开了，唉，但是可惜啊，有多少繁花满枝，就会有多少秋叶零落。",
	"有人说，生命纯属偶然，所以每个生命都要依恋另一个生命，相依为命，结伴而行。",
	"有人说，生命纯属偶然，所以每个生命都不属于另一个生命，像一阵风，无牵无挂。",
	"哈，逆命而生，背光而行，这是我的追求啊！",
	"心若没有栖息的地方，到哪里都是在流浪。",
	"看啊，那有一只枯叶蝶啊。如果内心的蝴蝶从未苏醒，枯叶蝶的一生，也只不过是一片无言的枯叶呢。",
	"记忆是无花的蔷薇，永远不会败落……",
	"原来没有我，真的没有什么不同。",
	"梦，不能做得太深，深了，难以清醒……",
	"只会相信自己愿意相信的事物而活下去，这就是人……",
	"来吧，我是不会输的！不认输，不逃避，世上没有不停的雨。",
	"我一直在寻找着能够打败我的人……这个人究竟在哪？",
	"当世界快要灭亡的时候，海之神就会出现。这是古老的预言。",
	"当一个生命与另一个生命相遇的时候，会孕育出什么呢?"
	"让你见识见识我的力量吧，变得更加更加强大！",
	"那个啊，冰是一种坚硬又脆弱的东西。",
	"冲啊！"
};

//封装几个基本函数
//跳转到控制台特定位置
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//控制输出字体颜色
void color(int num)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), num);
}
//设置光标格式
void cursor()
{
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);	//获取光标信息  
	cci.dwSize = 1;	//设置光标大小     
	cci.bVisible = 0;	//设置光标不可见 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);	//设置(应用)光标信息  
}

//地图信息，字符模式|字符画模式
void modePrint()
{
	gotoxy(102, 3);
	cout << "                   ";

	color(15);
	gotoxy(102, 1);
	if (characterORcharacterprinting == 0)
		cout << "字符模式";
	else if (characterORcharacterprinting == 1)
		cout << "字符画模式";
}

//地图信息：游戏分数
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
	cout << "分数";
	gotoxy(102, 4);
	cout << "当前分数  ： " << preScore;
	gotoxy(102, 5);
	cout << "历史最高分： " << highestScore;
}

//地图信息：人物信息
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
	cout << "PH   ：" << temp_protagonist->getPrePH() << " / " << temp_protagonist->getPH();
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

//地图信息：背包信息
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
	cout << "背包";
	gotoxy(102, 16);
	cout << "伤药  ： " << myBackpack.getCurePH();
	gotoxy(102, 17);
	cout << "好伤药： " << myBackpack.getCurePHgood();
	gotoxy(102, 18);
	cout << "经验丹： " << myBackpack.getEnhanceEXP();
	gotoxy(102, 19);
	cout << "徽章  ： " << myBackpack.getBadge();
}

//打印字符地图
void mapPrint(Protagonist* temp_protagonist)
{
	for (int i = 0; i <= 27; i++)
	{
		for (int j = 0; j <= 98; j++)
		{
			//草地——0
			if (mapPartOne[i][j] == 0)
				cout << " ";
			//宝箱——1
			if (mapPartOne[i][j] == 1)
			{
				color(11);
				cout << "@";
			}
			//森林——2
			if (mapPartOne[i][j] == 2)
			{
				color(10);
				cout << "x";
			}
			//医院——3
			if (mapPartOne[i][j] == 3)
			{
				color(13);
				cout << "#";
			}
			//商店——4
			if (mapPartOne[i][j] == 4)
			{
				color(9);
				cout << "#";
			}
			//武馆——5~9
			if (mapPartOne[i][j] == 5 || mapPartOne[i][j] == 6 || mapPartOne[i][j] == 7 || mapPartOne[i][j] == 8 || mapPartOne[i][j] == 9)
			{
				color(14);
				cout << "#";
			}
			//NPC——10
			if (mapPartOne[i][j] == 10)
			{
				color(12);
				cout << "Y";
			}
			//传送点——11
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

//战斗场景信息：外型（有延迟）
void fightScene()
{
	color(14);

	//边框(99, 28)
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

//战斗场景信息：外型（无延迟）
void CfightScene()
{
	color(14);

	//边框(99, 28)
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

//战斗场景信息：人物参数
void fightData(Protagonist* role_one, Villain& role_two)
{
	color(15);

	gotoxy(17, 21);
	cout << "    ";
	gotoxy(12, 21);
	cout << "PH  ：" << role_one->getPrePH();
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
	cout << "LV  ：" << role_two.getLV();
	gotoxy(20, 4);
	cout << "    ";
	gotoxy(15, 4);
	cout << "PH  ：" << role_two.getPrePH();
	gotoxy(24, 4);
	cout << " / " << role_two.getPH();
	gotoxy(15, 5);
	cout << "ATK : " << role_two.getATK();
	gotoxy(15, 6);
	cout << "DEF : " << role_two.getDEF();
}

//菜单打印
void showmenu(string* menu, int size, int index, int pos_x, int pos_y)
{
	//初始化显示到控制台终端的具体位置  
	COORD pos = { 0,0 };
	pos.X = pos_x;
	pos.Y = pos_y;

	//说明语
	color(15);
	gotoxy(pos_x, pos_y);
	cout << "请选择要进行的操作：";

	for (int i = 0; i < size; i++)
	{
		//如果i==index表示在当前选项的位置，默认初始化显示是第一项，  
		//当按下上下按键选择的时候，光标会移动，也就看到了列表选择的现象   
		if (i == index)
		{
			color(14);
			pos.Y += 1;
			gotoxy(pos.X, pos.Y);
			cout << *(menu + i) << endl;
		}

		//否则显示为另一颜色   
		else
		{
			color(15);
			pos.Y += 1;
			gotoxy(pos.X, pos.Y);
			cout << *(menu + i) << endl;
		}
	}
	//刷新标准输出缓冲区   
	fflush(stdout);
}
//菜单选择，获取用户输入
int  get_userinput(int *index, int size)
{
	int ch;
	ch = _getch();
	switch (ch)
	{
		//上   
	case 'w': if (*index > 0)  *index -= 1;  break;//如果选择上，那么光标向上移动   
												   //下   
	case 's':if (*index < size - 1)  *index += 1;  break;//如果选择下，那么光标向下移动   
														 //回车   
	case 13: return 13;
	}
	return 0;
}

//判断战斗中是否有一方血量为零，并有相应人物参数变化
bool check(Protagonist* role_one, Villain& role_two)
{
	flag = 0;//flag 未完成——0   失败——1   胜利——2

	if (role_one->getPrePH() <= 0)
	{
		color(14);
		gotoxy(30, 12);
		cout << "胜 负 乃 兵 家 常 事，请 大 侠 重 新 再 来！";
		Sleep(5000);
		flag = 1;
		return true;
	}

	if (role_two.getPrePH() <= 0)
	{
		color(14);
		gotoxy(30, 12);
		cout << "胜 负 已 分！恭 喜 大 侠 赢 得 了 胜 利！";
		gotoxy(30, 13);
		cout << "获 得 大 量 金 钱！";
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

//攻击，参数处理
void attack(Protagonist* role_one, Villain& role_two)
{
	color(14);
	gotoxy(40, 12);
	cout << "你 发 动 了 攻 击";
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
	cout << "敌 人 发 动 了 攻 击";
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

//防御反击，菜单打印
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
		cout << "请选择要使用的技能：  ";
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
			case 0://技能1
				temp_protagonist->setNivose_one();
				color(14);
				gotoxy(31, 13);
				cout << "你 使 用 了 技 能 —— " << temp_protagonist->getNivose_oneName();
				Sleep(1000);
				gotoxy(31, 13);
				cout << "                                 ";
				return;
			case 1://技能2
				temp_protagonist->setNivose_two();
				color(14);
				gotoxy(31, 13);
				cout << "你 使 用 了 技 能 —— " << temp_protagonist->getNivose_twoName();
				Sleep(1000);
				gotoxy(31, 13);
				cout << "                                 ";
				return;
			}
		}
	}
}

//防御反击（字符版），参数处理
void defense_attack(Protagonist* role_one, Villain& role_two)
{
	cursor();
	color(14);
	defense_attackmenuPrint(role_one->getNivosseName(), 2, 60, 21, role_one);

	//跳出一道题目，当用户答对后防御反击成功，答错则失败
	int temp = rand() % 23;
	color(14);
	gotoxy(5, 12);
	cout << str_question[temp];
	gotoxy(5, 13);
	cout << "请 输 入 您 的 答 案 ";
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

	//判断答案是否正确，并做出相应处理
	if (answer == str_answer[temp])//答案正确
	{
		//我方攻击
		gotoxy(31, 13);
		cout << "技 能 发 挥 作 用 了";
		Sleep(1000);
		gotoxy(31, 13);
		cout << "                    ";
		if (saber.m_bNivose_one == true)//醉仙望月步——叠加攻击
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
			cout << "连 续 答 对 本 次 伤 害 比 上 次 伤 害 增 加 20%";
			Sleep(1000);
			gotoxy(31, 13);
			cout << "                                                ";
		}
		else if (saber.m_bNivose_two == true)//弦月斩——恢复伤害的50%
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
			cout << "血 量 恢 复 伤 害 的 50%";
			Sleep(2000);
			gotoxy(31, 13);
			cout << "                        ";
		}
		else if (archer.m_bNivose_one == true)//元灵归心术——加血20%
		{
			if (role_one->getPH() - role_one->getPrePH() < role_one->getPH() / 5)
				role_one->setPrePH(role_one->getPH());
			else if (role_one->getPH() - role_one->getPrePH() >= role_one->getPH() / 5)
				role_one->setPrePH(role_one->getPrePH() + role_one->getPH() / 5);
			gotoxy(31, 13);
			cout << "血 量 恢 复 20%";
			Sleep(2000);
			gotoxy(31, 13);
			cout << "               ";
		}
		else if (archer.m_bNivose_two == true)//蓄力攻击——本次不攻击，下次攻击伤害3倍
		{
			if (archer_nivose_two == 0)
			{
				archer_nivose_two = 1;
				gotoxy(31, 13);
				cout << "本 次 不 攻 击，下 次 攻 击 伤 害 乘 3 倍";
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
				cout << "本 次 攻 击 伤 害 乘 3 倍";
				Sleep(2000);
				gotoxy(31, 13);
				cout << "                         ";
			}
		}
		else if (lancer.m_bNivose_one == true)//落日投射——伤害翻倍
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
			cout << "攻 击 伤 害 翻 倍";
			Sleep(2000);
			gotoxy(31, 13);
			cout << "                 ";
		}
		else if (lancer.m_bNivose_two == true)//风雷双式——连续攻击两次
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
			cout << "连 续 攻 击 两 次";
			Sleep(2000);
			gotoxy(31, 13);
			cout << "                 ";
		}
		//及时更新人物信息
		fightData(role_one, role_two);
		if (check(role_one, role_two)) return;

		//敌方攻击
		gotoxy(31, 13);
		cout << "敌 人 发 动 了 攻 击";
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
		//及时更新人物信息
		fightData(role_one, role_two);
		if (check(role_one, role_two)) return;
	}
	else if(answer != str_answer[temp])//答案错误
	{
		saber_nivose_one = 1;

		gotoxy(31, 13);
		cout << "技 能 使 用 失 败 了";
		Sleep(1000);
		gotoxy(31, 13);
		cout << "                    ";
		gotoxy(31, 13);
		cout << "敌 人 发 动 了 攻 击";
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

	//清空缓冲区
	char c;
	while ((c = getchar()) != EOF && c != '\n');
}

//防御反击（字符画版），参数处理（具体实现与字符版类似）
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
	cout << "请 输 入 你 的 答 案 ";

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
		cout << "技 能 发 挥 作 用 了";
		Sleep(1000);
		gotoxy(31, 13);
		cout << "                    ";
		if (saber.m_bNivose_one == true)//醉仙望月步——叠加攻击
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
			cout << "连 续 答 对 本 次 伤 害 比 上 次 伤 害 的 增 加 20% 倍";
			Sleep(3000);
			gotoxy(31, 13);
			cout << "                                                      ";
		}
		else if (saber.m_bNivose_two == true)//弦月斩——恢复伤害的50%
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
			cout << "血 量 恢 复 伤 害 的 50%";
			Sleep(3000);
			gotoxy(31, 13);
			cout << "                        ";
		}
		else if (archer.m_bNivose_one == true)//元灵归心术——加血20%
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
			cout << "血 量 恢 复 20%";
			Sleep(3000);
			gotoxy(31, 13);
			cout << "               ";
		}
		else if (archer.m_bNivose_two == true)//蓄力攻击——本次不攻击，下次攻击伤害3倍
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
				cout << "本 次 不 攻 击，下 次 攻 击 伤 害 乘 3 倍";
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
				cout << "本 次 攻 击 伤 害 乘 3 倍";
				Sleep(3000);
				gotoxy(31, 13);
				cout << "                         ";
			}		
		}
		else if (lancer.m_bNivose_one == true)//落日投射——伤害翻倍
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
			cout << "攻 击 伤 害 翻 倍";
			Sleep(3000);
			gotoxy(31, 13);
			cout << "                 ";
		}
		else if (lancer.m_bNivose_two == true)//风雷双式——连续攻击两次
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
			cout << "连 续 攻 击 两 次";
			Sleep(3000);
			gotoxy(31, 13);
			cout << "                 ";
		}
		if (check(role_one, role_two)) return;

		gotoxy(31, 13);
		cout << "敌 人 发 动 了 攻 击";
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
		cout << "技 能 使 用 失 败 了";
		Sleep(1000);
		gotoxy(31, 13);
		cout << "                    ";
		gotoxy(31, 13);
		cout << "敌 人 发 动 了 攻 击";
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

//战斗中使用伤药
void AfterCurePHinFight(Protagonist* role_one, Villain& role_two)
{
	cursor();
	if (myBackpack.getCurePH() > 0)//伤药数量有剩余
	{
		//我方加血
		color(14);
		gotoxy(31, 13);
		cout << "你 使 用 了 伤 药！";
		Sleep(1000);
		gotoxy(31, 13);
		cout << "                   ";
		myBackpack.setCurePH(myBackpack.getCurePH() - 1);
		if (role_one->getPH() - role_one->getPrePH() >= 20)
			role_one->setPrePH(role_one->getPrePH() + 20);
		else if (role_one->getPH() - role_one->getPrePH() < 20)
			role_one->setPrePH(role_one->getPH());
		fightData(role_one, role_two);

		//敌方攻击
		color(14);
		gotoxy(31, 13);
		cout << "敌 人 发 动 了 攻 击";
		Sleep(1000);
		gotoxy(31, 13);
		cout << "                    ";
		if (role_two.getATK() > role_one->getDEF())
			role_one->setPrePH(role_one->getPrePH() - role_two.getATK() + role_one->getDEF());
		if (role_two.getATK() <= role_one->getDEF())
			role_one->setPrePH(role_one->getPrePH() - 1);
		fightData(role_one, role_two);

		//检查
		if (check(role_one, role_two)) return;
	}

	else if (myBackpack.getCurePH() == 0)//伤药数量为零
	{
		color(14);
		gotoxy(31, 13);
		cout << "糟 糕！伤 药 用 完 了！";
		Sleep(1000);
		gotoxy(31, 13);
		cout << "                       ";
	}
}

//战斗中使用好伤药
void AfterCurePHgoodinFight(Protagonist* role_one, Villain& role_two)
{
	cursor();
	if (myBackpack.getCurePHgood() > 0)//伤药数量有剩余
	{
		//我方加血
		color(14);
		gotoxy(31, 13);
		cout << "你 使 用 了 好 伤 药！";
		Sleep(1000);
		gotoxy(31, 13);
		cout << "                      ";
		myBackpack.setCurePHgood(myBackpack.getCurePHgood() - 1);
		if (role_one->getPH() - role_one->getPrePH() >= 50)
			role_one->setPrePH(role_one->getPrePH() + 50);
		else if (role_one->getPH() - role_one->getPrePH() < 50)
			role_one->setPrePH(role_one->getPH());
		fightData(role_one, role_two);

		//敌方攻击
		color(14);
		gotoxy(31, 13);
		cout << "敌 人 发 动 了 攻 击";
		Sleep(1000);
		gotoxy(31, 13);
		cout << "                    ";
		if (role_two.getATK() > role_one->getDEF())
			role_one->setPrePH(role_one->getPrePH() - role_two.getATK() + role_one->getDEF());
		if (role_two.getATK() <= role_one->getDEF())
			role_one->setPrePH(role_one->getPrePH() - 1);
		fightData(role_one, role_two);

		//检查
		if (check(role_one, role_two)) return;
	}

	else if (myBackpack.getCurePHgood() == 0)//伤药数量为零
	{
		color(14);
		gotoxy(31, 13);
		cout << "糟 糕！好 伤 药 用 完 了！";
		Sleep(1000);
		gotoxy(31, 13);
		cout << "                          ";
	}
}

//战斗中使用经验丹
void AfterEnhanceEXPinFight(Protagonist* role_one, Villain& role_two)
{
	cursor();
	if (myBackpack.getEnhanceEXP() > 0)//经验丹数量有剩余
	{
		//我方加经验
		color(14);
		gotoxy(31, 13);
		cout << "你 使 用 了 经 验 丹！";
		Sleep(1000);
		gotoxy(31, 13);
		cout << "                      ";
		myBackpack.setEnhanceEXP(myBackpack.getEnhanceEXP() - 1);
		role_one->setPreEXP_EXP_LV(20);
		fightData(role_one, role_two);

		//敌方攻击
		color(14);
		gotoxy(31, 13);
		cout << "敌 人 发 动 了 攻 击";
		Sleep(1000);
		gotoxy(31, 13);
		cout << "                    ";
		if (role_two.getATK() > role_one->getDEF())
			role_one->setPrePH(role_one->getPrePH() - role_two.getATK() + role_one->getDEF());
		if (role_two.getATK() <= role_one->getDEF())
			role_one->setPrePH(role_one->getPrePH() - 1);
		fightData(role_one, role_two);

		//检查
		if (check(role_one, role_two)) return;
	}

	else if (myBackpack.getEnhanceEXP() == 0)//经验丹数量为零
	{
		color(14);
		gotoxy(31, 13);
		cout << "糟 糕！经 验 丹 用 完 了！";
		Sleep(1000);
		gotoxy(31, 13);
		cout << "                          ";
	}

}

//地图中使用伤药
void AfterCurePHinMap(Protagonist* temp_protagonist)
{
	if (myBackpack.getCurePH() > 0)
	{
		color(15);
		gotoxy(100, 26);
		cout << "你使用了伤药！";
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
		cout << "糟糕！伤药用完了！";
		Sleep(1000);
		gotoxy(100, 26);
		cout << "                  ";
	}
}

//地图中使用好伤药
void AfterCurePHgoodinMap(Protagonist* temp_protagonist)
{
	if (myBackpack.getCurePHgood() > 0)
	{
		color(15);
		gotoxy(100, 26);
		cout << "你使用了好伤药！";
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
		cout << "糟糕！好伤药用完了！";
		Sleep(1000);
		gotoxy(100, 26);
		cout << "                    ";
	}
}

//地图中使用经验丹
void AfterEnhanceEXPinMap(Protagonist* temp_protagonist)
{
	if (myBackpack.getEnhanceEXP() > 0)
	{
		color(15);
		gotoxy(100, 26);
		cout << "你使用了经验丹！";
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
		cout << "糟糕！经验丹用完了！";
		Sleep(1000);
		gotoxy(100, 26);
		cout << "                    ";
	}
}

//商店中购买伤药
void buyCurePH(Protagonist* temp_protagonist)//500
{
	if (protagonist->getMoney() >= 200)
	{
		gotoxy(100, 26);
		cout << "成功购买了伤药！";
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
		cout << "对不起，金钱不够！";
		Sleep(1000);
		gotoxy(100, 26);
		cout << "                  ";
	}
}

//商店中购买好伤药
void buyCurePHgood(Protagonist* temp_protagonist)//800
{
	if (protagonist->getMoney() >= 500)
	{
		gotoxy(100, 26);
		cout << "成功购买了好伤药！";
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
		cout << "对不起，金钱不够！";
		Sleep(1000);
		gotoxy(100, 26);
		cout << "                  ";
	}
}

//商店中购买经验丹
void buyEnhanceEXP(Protagonist* temp_protagonist)//1000
{
	if (protagonist->getMoney() >= 800)
	{
		gotoxy(100, 26);
		cout << "成功购买了经验丹";
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
		cout << "对不起，金钱不够！";
		Sleep(1000);
		gotoxy(100, 26);
		cout << "                  ";
	}
}

//各种菜单
string fightmenu[3]
{
	"攻击",
	"技能",
	"背包"
};

string fightmenu_other[4]
{
	"攻击",
	"技能",
	"背包",
	"逃跑"
};

string backpackmenuInFight[4]
{
	"伤药",
	"好伤药",
	"经验丹",
	"退出"
};

string backpackmenuInMap[4]
{
	"伤药",
	"好伤药",
	"经验丹",
	"退出"
};

string shopmenu[4]
{
	"伤药",
	"好伤药",
	"经验丹",
	"退出"
};

//战斗中背包菜单打印
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
			case 0:AfterCurePHinFight(role_one, role_two);           return;   //伤药
			case 1:AfterCurePHgoodinFight(role_one, role_two);       return;   //好伤药
			case 2:AfterEnhanceEXPinFight(role_one, role_two);       return;   //经验丹
			case 3:                                                  return;   //退出
			}
		}
	}
}

//地图中背包菜单打印
void bakckpackmenuPrintinMap(string menu[], int size, int pos_x, int pos_y, Protagonist* temp_protagonist)
{
	int ret;
	int index = 0;

	while (1)
	{
		showmenu(menu, size, index, pos_x, pos_y);
		gotoxy(pos_x, pos_y);
		color(15);
		cout << "请选择要使用的物品：";
		ret = get_userinput(&index, size);

		if (ret == 13)
		{
			switch (index)
			{
			case 0:AfterCurePHinMap(temp_protagonist);           break;   //伤药
			case 1:AfterCurePHgoodinMap(temp_protagonist);       break;   //好伤药
			case 2:AfterEnhanceEXPinMap(temp_protagonist);       break;   //经验丹
			case 3:                                        //退出菜单
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

//战斗中战斗主菜单打印（不可逃跑）
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
			case 0://攻击
				attack(role_one, role_two);                          
				return;   
			case 1://技能
				if(characterORcharacterprinting==0)
					defense_attack(role_one, role_two);
				else if (characterORcharacterprinting == 1)
					Cdefense_attack(role_one, role_two);
				return;   
			case 2://背包
				bakckpackmenuPrintinFight(backpackmenuInFight, 4, pos_x, pos_y, role_one, role_two);       
				return;
			}

		}

	}
}

//战斗中战斗主菜单打印（可逃跑）
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
			case 0://攻击
				attack(role_one, role_two);
				return;
			case 1://技能
				if (characterORcharacterprinting == 0)
					defense_attack(role_one, role_two);
				else if (characterORcharacterprinting == 1)
					Cdefense_attack(role_one, role_two);
				return;
			case 2://背包
				bakckpackmenuPrintinFight(backpackmenuInFight, 4, pos_x, pos_y, role_one, role_two);
				return;
			case 3://逃跑
				flag = 1;
				color(14);
				gotoxy(31, 13);
				cout << "你 成 功 逃 跑 了 ！";
				Sleep(2000);
				gotoxy(31, 13);
				cout << "                    ";
				return;
			}

		}
	}
}

//商店菜单打印
void shopmenuPrint(string menu[], int size, int pos_x, int pos_y, Protagonist* temp_protagonist)
{
	int ret;
	int index = 0;

	while (1)
	{
		showmenu(menu, size, index, pos_x, pos_y);
		gotoxy(pos_x, pos_y);
		cout << "请选择要购买的物品：";
		ret = get_userinput(&index, size);

		if (ret == 13)
		{
			switch (index)
			{
			case 0: buyCurePH(temp_protagonist);                 break;    //买伤药
			case 1: buyCurePHgood(temp_protagonist);             break;    //买好伤药
			case 2: buyEnhanceEXP(temp_protagonist);             break;    //买经验丹
			case 3:                                                        //退出购物菜单
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

//游戏保存
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

//游戏读档
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
		cerr << "读取存档失败" << endl;
		exit(1);
	}
	system("cls");
}

//保存分数
void saveScore()
{
	if (preScore >= highestScore)
	{
		ofstream fout("score_saved.txt");
		fout << preScore;
		fout.close();
	}
}

//加载分数
void loadScore()
{
	ifstream fin("score_saved.txt");
	fin >> highestScore;
	fin.close();
}

//战斗音乐（随机播放）
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

//地图数组为1，宝箱
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

//地图数组为3，医馆
void map_3()
{
	color(15);

	gotoxy(102, 21);
	cout << "大侠看起来也累了，";
	gotoxy(102, 22);
	cout << "好好休息吧！";
	Sleep(1000);
	gotoxy(102, 21);
	cout << "                   ";
	gotoxy(102, 22);
	cout << "            ";

	gotoxy(102, 21);
	cout << "………………";
	Sleep(1000);
	gotoxy(102, 21);
	cout << "            ";

	saber.setPrePH(saber.getPH());
	archer.setPrePH(archer.getPH());
	lancer.setPrePH(lancer.getPH());
	roleDataPrint(protagonist);

	gotoxy(102, 21);
	cout << "看起来休息得不错呢，";
	gotoxy(102, 22);
	cout << "继续出发吧!";
	Sleep(1000);
	gotoxy(102, 21);
	cout << "                    ";
	gotoxy(102, 22);
	cout << "           ";
}

//地图数组为4，商店
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
				case 0://伤药
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
				case 1://好伤药
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
				case 2://经验丹
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
				case 3://退出
					setConsoleDefault();
					mapPrint(protagonist);
					return;
				}
			}
		}
	}
}

//地图数组为5，道馆Boss1
void map_5()
{
	saber_nivose_one = 1;
	boss_one.setPrePH(boss_one.getPH());

	char c;

	color(14);
	gotoxy(0, 28);
	cout << "馆主：这是你挑战的第一间道馆呢，挑战者要加油哦！" << endl;
	while ((c = getchar()) != EOF && c != '\n');
	cout << "我  ：是的呢，我一定会尽力的" << endl;
	while ((c = getchar()) != EOF && c != '\n');
	cout << "馆主：优秀的斗士是不会在胜利之后后夸耀，也不会在失败之后沮丧，只会追寻下一场胜利。" << endl;
	cout << "      所以不管这场战斗如何，希望你都能从这场战斗中得到收获，这才是战斗与冒险的意义所在。" << endl;
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

//地图数组为6，道馆Boss2
void map_6()
{
	saber_nivose_one = 1;
	boss_two.setPrePH(boss_two.getPH());

	char c;

	color(14);
	gotoxy(0, 28);
	cout << "我  ：馆主你好，我是来挑战道馆的" << endl;
	while ((c = getchar()) != EOF && c != '\n');
	cout << "馆主：噢，你终于来了，等你很久了哦。已经好久没有见过像你一样有朝气的年轻人了。" << endl;
	cout << "      年轻人啊，就是应该要有那么一点傲气的。加油吧！" << endl;
	while ((c = getchar()) != EOF && c != '\n');
	cout << "我  ：谢谢馆主的夸奖了" << endl;
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

//地图数组为7，道馆Boss3
void map_7()
{
	saber_nivose_one = 1;
	boss_three.setPrePH(boss_three.getPH());

	char c;

	color(14);
	gotoxy(0, 28);
	cout << "馆主：啊，你是挑战者吧，已经好久没有看到挑战者了，希望能有一场精彩的战斗。" << endl;
	cout << "      与其有时间在迷茫，倒不如先行动看看，就算失败了也能从中学到点什么，来吧来吧，我们开始吧。" << endl;
	while ((c = getchar()) != EOF && c != '\n');
	cout << "我  ：嗯，好的，我们开始吧。" << endl;
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

//地图数组为8，道馆Boss4
void map_8()
{
	saber_nivose_one = 1;
	boss_four.setPrePH(boss_four.getPH());

	char c;

	color(14);
	gotoxy(0, 28);
	cout << "我  ：请问这里是道馆吗？我是来挑战的。" << endl;
	while ((c = getchar()) != EOF && c != '\n');
	cout << "馆主：生活是一场严酷的战斗，最重要的是把握好自己的手牌。只有强者才会获得胜利！加油吧，孩子。" << endl;
	while ((c = getchar()) != EOF && c != '\n');
	cout << "我  ：好的。";
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

//地图数组为9，道馆Boss5
void map_9()
{
	saber_nivose_one = 1;
	boss_five.setPrePH(boss_five.getPH());

	char c;

	color(14);
	gotoxy(0, 28);
	cout << "馆主：这是你挑战的最后一间道馆了，坚持到这里真不容易啊。" << endl;
	while ((c = getchar()) != EOF && c != '\n');
	cout << "我  ：是的，经过了与数分一系列的邂逅与相遇，我已经从讨厌数分到慢慢理解数分，再到后来逐渐喜欢上数分了" << endl;
	cout << "      所以最后的这场战斗我更加不可战败，为了验证我与数分之间建立的友谊。" << endl;
	while ((c = getchar()) != EOF && c != '\n');
	cout << "馆主：就算是笨手笨脚又迟钝，只要步步脚踏实地的前进，终究可以实现梦想的。加油吧，孩子。";
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
 
//地图数组为10，NPC
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

//地图数组为5~9但已成功挑战道馆
void map_false()
{
	char c;
	color(15);
	gotoxy(0, 27);
	cout << "该道馆已挑战成功，并获得了徽章";
	while ((c = getchar()) != EOF && c != '\n');
	gotoxy(0, 27);
	cout << "                                                                                          ";
}

//地图数组11，传送点（已收集所有徽章）
void map_11_1()
{
	saveScore();

	char c;
	system("cls");
	picturePainting(".//pic//TXT//end//ASCII-end.txt", 601, 198);
	while ((c = getchar()) != EOF && c != '\n');
}

//地图数组11，传送点（未收集所有徽章）
void map_11_2()
{
	color(15);
	gotoxy(0, 27);
	cout << "尚未获得全部徽章，请继续努力！";
	Sleep(2000);
	gotoxy(0, 27);
	cout << "                              ";
}

//地图数组为0，草地，随机遇怪
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
			cout << "野 生 的 怪 兽 跳 出 来 了！";
			Sleep(1000);
			gotoxy(31, 13);
			cout << "                            ";
			gotoxy(31, 13);
			cout << "准 备 出 战 吧！";
			Sleep(1000);
			gotoxy(31, 13);
			cout << "                ";
		}
		else if (characterORcharacterprinting == 1)
		{
			gotoxy(0, 27);
			cout << "野生的怪物跳出来了，准备出战吧";
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

//游戏背景视屏播放
void backgroundPrint()
{
	videoPainting(".//pic//TXT//background//ASCII-background", 447, 601, 198, 2, 2);
}

//游戏操作图片展示
void introductionPrint()
{
	char c;
	picturePainting(".//pic//TXT//introduction//ASCII-introduction_map.txt", 601, 198);
	while ((c = getchar()) != EOF && c != '\n');
	picturePainting(".//pic//TXT//introduction//ASCII-introduction_key.txt", 601, 198);
	while ((c = getchar()) != EOF && c != '\n');
}

//难度选择
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

//游戏开始封面打印
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
			case 0://开始游戏
				difficultyPrint();
				system("cls");
				return;

			case 1://读取存档
				load();
				system("cls");
				return;

			case 2:
				char c;

				backgroundPrint();       //游戏背景
				while ((c = getchar()) != EOF && c != '\n');
				system("cls");

				introductionPrint();   	//操作说明
				system("cls");
				return;
			}
		}
	}
}

//char类型转换成int类型
void myCharToInt(int& num, char* ch, int n)
{
	num = 0;
	for (int count = 0, count_another = n - 1; count < n; count++, count_another--)
	{
		num += (ch[count_another] - '0')*pow(10, count);
	}

}

//主函数入口
int main()
{
	//初始化
	srand(time(NULL));
	system("mode con cols=1500 lines=1000");
	PlaySound(TEXT(".//music//cover.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	coverPrint();

	//初始化
	setConsoleDefault();
	loadScore();
	protagonist = &saber;
	mapPrint(protagonist);
	gotoxy(pos.X, pos.Y);
	color(14);
	cout << "S";
	PlaySound(TEXT(".//music//map.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	//进入消息循环
	while (1)
	{
		if (_kbhit())//接收到用户输入（无阻塞输入）
		{
			//清除原位置符号
			gotoxy(pos.X, pos.Y);
			color(14);
			cout << " ";

			char ch = 'q';
			ch = _getch();
			//字符说明
			//w  上移
			//s  下移
			//a  左移
			//d  右移
			//t  切换字符|字符画模式
			//b  地图中打开背包
			//q  保存
			//Esc 退出游戏
			//1  切换人物为Sabre
			//2  切换人物为Archer
			//3  切换人物为Lancer
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
					cout << "字符画模式";
				}
				else if (characterORcharacterprinting == 1)
				{
					characterORcharacterprinting = 0;
					gotoxy(102, 1);
					cout << "          ";
					gotoxy(102, 1);
					color(15);
					cout << "字符模式";
				}
				break;

			case 'b':
				bakckpackmenuPrintinMap(backpackmenuInMap, 4, 102, 21, protagonist);
				break;

			case 'q':
				color(15);
				gotoxy(0, 27);
				cout << "游戏已保存";
				Sleep(2000);
				gotoxy(0, 27);
				cout << "          ";
				save();
				break;

			case 27://Esc
			{
				gotoxy(0, 27);
				cout << "退出游戏" << endl;
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

			//打印新位置符号
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
