#include"backpack.h"

Backpack::Backpack()
{
	m_iCurePH = 0;
	m_iCurePHgood = 0;
	m_iEnhanceEXP = 0;
	m_iBadge = 0;
}

int Backpack::getCurePH()
{
	return m_iCurePH;
}
void Backpack::setCurePH(int num)
{
	m_iCurePH = num;
}
int Backpack::getCurePHgood()
{
	return m_iCurePHgood;
}
void Backpack::setCurePHgood(int num)
{
	m_iCurePHgood = num;
}
int Backpack::getEnhanceEXP()
{
	return m_iEnhanceEXP;
}
void Backpack::setEnhanceEXP(int num)
{
	m_iEnhanceEXP = num;
}
int Backpack::getBadge()
{
	return m_iBadge;
}
void Backpack::setBadge(int num)
{
	m_iBadge = num;
}