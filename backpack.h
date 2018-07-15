#ifndef BACKPACK_H
#define BACKPACK_H

class Backpack//背包类
{
public:
	//构造函数，初始化私有数据成员
	Backpack();

	//私有数据成员的set和get函数
	int getCurePH();
	void setCurePH(int);
	int getCurePHgood();
	void setCurePHgood(int);
	int getEnhanceEXP();
	void setEnhanceEXP(int);
	int getBadge();
	void setBadge(int);

private:
	//私有数据成员
	int m_iCurePH;//加血剂数量
	int m_iCurePHgood;//加血剂数量
	int m_iEnhanceEXP;//经验丹数量
	int m_iBadge;//徽章数量
};

#endif  //BACKPACK_H