#ifndef ROLE_H
#define ROLE_H

#include<string>

class Role//人物类（抽象基类）
{
public:
	//初始化人物（传入参数为人物等级）
	Role(int lv);

	//数据成员的set函数
	void setPH(int);
	void setPrePH(int);
	void setATK(int);
	void setDEF(int);
	void setLV(int);

	//数据成员的get函数
	int getPH();
	int getPrePH();
	int getATK();
	int getDEF();
	int getLV();

	//纯虚函数
	virtual void setPH_ATK_DEF() = 0;//升级后人物参数变化
	virtual void setPreEXP_EXP_LV(int lv) = 0;//打赢后人物参数变化

protected:
	int m_iPh;//血量
	int m_iPrePh;//当前血量
	int m_iAtk;//攻击力
	int m_iDef;//防御力
	int m_iLv;//等级
};

class Protagonist :public Role//主角，继承自role
{
public:
	//构造函数，初始化人物
	Protagonist(int lv);

	//纯虚函数
	virtual void setPH_ATK_DEF() = 0;//升级后人物参数变化
	virtual void setPreEXP_EXP_LV(int lv) = 0;//打赢后人物参数变化
	virtual std::string* getNivosseName() = 0;//获取人物技能名字
	virtual std::string getNivose_oneName() = 0;//获取人物第一个技能名字
	virtual std::string getNivose_twoName() = 0;//获取人物第二个技能名字
	virtual void setNivose_one() = 0;//设置第一个技能是否使用
	virtual void setNivose_two() = 0;//设置第二个技能是否使用

	//私有成员的set与get函数
	void setMoney(int);
	int getMoney();
	void setEXP(int);
	void setPreEXP(int);
	int getEXP();
	int getPreEXP();

protected:
	static int m_iMoney;//金钱
	int m_iExp;//总经验值
	int m_iPreExp;//当前经验值
};

class Saber :public Protagonist//Saber，主角之一，继承自Protagonist
{
public:
	//构造函数，初始化人物
	Saber(int lv);

	//虚函数的实现
	virtual void setPH_ATK_DEF();
	virtual void setPreEXP_EXP_LV(int lv);
	virtual std::string* getNivosseName();
	virtual std::string getNivose_oneName();
	virtual std::string getNivose_twoName();
	virtual void setNivose_one();
	virtual void setNivose_two();

	//数据成员
	bool m_bNivose_one;//判断第一个技能是否使用
	bool m_bNivose_two;//判断第二个技能是否使用
	std::string m_strNivoseName[3] = { "醉仙望月步","弦月斩" };//技能名字
};

class Archer :public Protagonist//Archer，主角之一，继承自Protagonist
{
public:
	//构造函数，初始化人物
	Archer(int lv);

	//虚函数的实现
	virtual void setPH_ATK_DEF();
	virtual void setPreEXP_EXP_LV(int lv);
	virtual std::string* getNivosseName();
	virtual std::string getNivose_oneName();
	virtual std::string getNivose_twoName();
	virtual void setNivose_one();
	virtual void setNivose_two();

	//数据成员
	bool m_bNivose_one;//判断第一个技能是否使用
	bool m_bNivose_two;//判断第二个技能是否使用
	std::string m_strNivoseName[3] = { "元灵归心术","蓄力攻击" };//技能名字
};

class Lancer :public Protagonist//Lancer，主角之一，继承自Protagonist
{
public:
	//构造函数，初始化人物
	Lancer(int lv);

	//虚函数的实现
	virtual void setPH_ATK_DEF();
	virtual void setPreEXP_EXP_LV(int lv);
	virtual std::string* getNivosseName();
	virtual std::string getNivose_oneName();
	virtual std::string getNivose_twoName();
	virtual void setNivose_one();
	virtual void setNivose_two();

	//数据成员
	bool m_bNivose_one;//判断第一个技能是否使用
	bool m_bNivose_two;//判断第二个技能是否使用
	std::string m_strNivoseName[3] = { "落日投射","风雷双式" };//技能名字
};

class Villain :public Role//配角，继承自role
{
public:
	//构造函数，初始化人物
	Villain(int lv);

	virtual void setPH_ATK_DEF();//升级后人物参数变化
	virtual void setPreEXP_EXP_LV(int lv);//打赢后人物参数变化

	//数据成员的set和get函数
	int getFlag();
	void setFlag(int);

private:
	enum//匿名枚举常量
	{
		MAJOR_PH = 0,
		MAJOR_ATK = 1,
		MAJOR_DEF = 2
	};
	int m_iType;//判断人物类型
	int m_iFlag;//判断人物是否已经被挑战
};

#endif  //ROLE_H