#include"role.h"

Role::Role(int lv)
{
	m_iLv = lv;
	m_iPh = 20;
	m_iPrePh = m_iPh;
	m_iAtk = 10;
	m_iDef = 5;
}
void Role::setPH(int temp)
{
	m_iPh = temp;
}
void Role::setPrePH(int temp)
{
	m_iPrePh = temp;
}
void Role::setATK(int temp)
{
	m_iAtk = temp;
}
void Role::setDEF(int temp)
{
	m_iDef = temp;
}
void Role::setLV(int temp)
{
	m_iLv = temp;
}
int Role::getPH()
{
	return m_iPh;
}
int Role::getPrePH()
{
	return m_iPrePh;
}
int Role::getATK()
{
	return m_iAtk;
}
int Role::getDEF()
{
	return m_iDef;
}
int Role::getLV()
{
	return m_iLv;
}

int Protagonist::m_iMoney = 0;//��̬��Ա�ĳ�ʼ��
Protagonist::Protagonist(int lv) :Role(lv)
{
	m_iExp = lv * 10;
	m_iPreExp = 0;
	m_iMoney = 0;
}
void Protagonist::setMoney(int money)
{
	m_iMoney = money;
}
int Protagonist::getMoney()
{
	return m_iMoney;
}
void Protagonist::setEXP(int temp)
{
	m_iExp = temp;
}
void Protagonist::setPreEXP(int temp)
{
	m_iPreExp = temp;
}
int Protagonist::getEXP()
{
	return m_iExp;
}
int Protagonist::getPreEXP()
{
	return m_iPreExp;
}

Saber::Saber(int lv) :Protagonist(lv)
{
	for (int i = 0; i < lv; i++)
		setPH_ATK_DEF();
}
//������������ҽ�ɫ�Ĳ����仯
void Saber::setPH_ATK_DEF()
{
	m_iPh = m_iPh + (rand() % 2 + 2);
	m_iPrePh = m_iPh;
	m_iAtk = m_iAtk + (rand() % 2 + 2);
	m_iDef = m_iDef + (rand() % 2 + 2);
}
//����սʤ����ҽ�ɫ����仯�͵ȼ��仯
void Saber::setPreEXP_EXP_LV(int lv)
{
	m_iPreExp += 5 + lv * 2;//���ӵľ���
	if (m_iPreExp >= m_iExp)
	{
		m_iPreExp = m_iPreExp % m_iExp;
		m_iLv += 1;
		m_iExp = m_iLv * 10;
		setPH_ATK_DEF();
	}
}
std::string* Saber::getNivosseName()
{
	return m_strNivoseName;
}
std::string Saber::getNivose_oneName()
{
	return m_strNivoseName[0];
}
std::string Saber::getNivose_twoName()
{
	return m_strNivoseName[1];
}
void  Saber::setNivose_one()
{
	m_bNivose_one = true;
}
void Saber::setNivose_two()
{
	m_bNivose_two = true;
}

Archer::Archer(int lv) :Protagonist(lv)
{
	for (int i = 0; i < lv; i++)
		setPH_ATK_DEF();
}
//������������ҽ�ɫ�Ĳ����仯
void Archer::setPH_ATK_DEF()
{
	m_iPh = m_iPh + (rand() % 2 + 1);
	m_iPrePh = m_iPh;
	m_iAtk = m_iAtk + (rand() % 2 + 3);
	m_iDef = m_iDef + (rand() % 2 + 2);
}
//����սʤ����ҽ�ɫ����仯�͵ȼ��仯
void Archer::setPreEXP_EXP_LV(int lv)
{
	m_iPreExp += 5 + lv * 2;//���ӵľ���
	if (m_iPreExp >= m_iExp)
	{
		m_iPreExp = m_iPreExp % m_iExp;
		m_iLv += 1;
		m_iExp = m_iLv * 10;
		setPH_ATK_DEF();
	}
}
std::string* Archer::getNivosseName()
{
	return m_strNivoseName;
}
std::string Archer::getNivose_oneName()
{
	return m_strNivoseName[0];
}
std::string Archer::getNivose_twoName()
{
	return m_strNivoseName[1];
}
void  Archer::setNivose_one()
{
	m_bNivose_one = true;
}
void Archer::setNivose_two()
{
	m_bNivose_two = true;
}

Lancer::Lancer(int lv) :Protagonist(lv)
{
	for (int i = 0; i < lv; i++)
		setPH_ATK_DEF();
}
//������������ҽ�ɫ�Ĳ����仯
void Lancer::setPH_ATK_DEF()
{
	m_iPh = m_iPh + (rand() % 2 + 2);
	m_iPrePh = m_iPh;
	m_iAtk = m_iAtk + (rand() % 2 + 3);
	m_iDef = m_iDef + (rand() % 2 + 1);
}
//����սʤ����ҽ�ɫ����仯�͵ȼ��仯
void Lancer::setPreEXP_EXP_LV(int lv)
{
	m_iPreExp += 5 + lv * 2;//���ӵľ���
	if (m_iPreExp >= m_iExp)
	{
		m_iPreExp = m_iPreExp % m_iExp;
		m_iLv += 1;
		m_iExp = m_iLv * 10;
		setPH_ATK_DEF();
	}
}
std::string* Lancer::getNivosseName()
{
	return m_strNivoseName;
}
std::string Lancer::getNivose_oneName()
{
	return m_strNivoseName[0];
}
std::string Lancer::getNivose_twoName()
{
	return m_strNivoseName[1];
}
void  Lancer::setNivose_one()
{
	m_bNivose_one = true;
}
void Lancer::setNivose_two()
{
	m_bNivose_two = true;
}

Villain::Villain(int lv) :Role(lv)
{
	m_iFlag = 0;
	for (int i = 0; i < lv; i++)
		setPH_ATK_DEF();
}
int Villain::getFlag()
{
	return m_iFlag;
}

void Villain::setFlag(int flag)
{
	m_iFlag = flag;
}
//������������Խ�ɫ�Ĳ����仯
void Villain::setPH_ATK_DEF()
{
	int type = rand() % 2;
	if (type == MAJOR_PH)
	{
		m_iPh = m_iPh + (rand() % 2 + 3);
		m_iPrePh = m_iPh;
		m_iAtk = m_iAtk + (rand() % 2 + 2);
		m_iDef = m_iDef + (rand() % 2 + 1);
	}
	else if (type == MAJOR_ATK)
	{
		m_iPh = m_iPh + (rand() % 2 + 2);
		m_iPrePh = m_iPh;
		m_iAtk = m_iAtk + (rand() % 2 + 3);
		m_iDef = m_iDef + (rand() % 2 + 1);
	}
	else if (type == MAJOR_DEF)
	{
		m_iPh = m_iPh + (rand() % 2 + 1);
		m_iPrePh = m_iPh;
		m_iAtk = m_iAtk + (rand() % 2 + 2);
		m_iDef = m_iDef + (rand() % 2 + 3);
	}
}
//������Խ�ɫ����仯�͵ȼ��仯
void Villain::setPreEXP_EXP_LV(int lv)
{
	for(int count = 0; count < lv;count++)
	{
		m_iLv += 1;
		setPH_ATK_DEF();
	}
}