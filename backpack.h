#ifndef BACKPACK_H
#define BACKPACK_H

class Backpack//������
{
public:
	//���캯������ʼ��˽�����ݳ�Ա
	Backpack();

	//˽�����ݳ�Ա��set��get����
	int getCurePH();
	void setCurePH(int);
	int getCurePHgood();
	void setCurePHgood(int);
	int getEnhanceEXP();
	void setEnhanceEXP(int);
	int getBadge();
	void setBadge(int);

private:
	//˽�����ݳ�Ա
	int m_iCurePH;//��Ѫ������
	int m_iCurePHgood;//��Ѫ������
	int m_iEnhanceEXP;//���鵤����
	int m_iBadge;//��������
};

#endif  //BACKPACK_H