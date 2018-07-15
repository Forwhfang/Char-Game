#ifndef ROLE_H
#define ROLE_H

#include<string>

class Role//�����ࣨ������ࣩ
{
public:
	//��ʼ������������Ϊ����ȼ���
	Role(int lv);

	//���ݳ�Ա��set����
	void setPH(int);
	void setPrePH(int);
	void setATK(int);
	void setDEF(int);
	void setLV(int);

	//���ݳ�Ա��get����
	int getPH();
	int getPrePH();
	int getATK();
	int getDEF();
	int getLV();

	//���麯��
	virtual void setPH_ATK_DEF() = 0;//��������������仯
	virtual void setPreEXP_EXP_LV(int lv) = 0;//��Ӯ����������仯

protected:
	int m_iPh;//Ѫ��
	int m_iPrePh;//��ǰѪ��
	int m_iAtk;//������
	int m_iDef;//������
	int m_iLv;//�ȼ�
};

class Protagonist :public Role//���ǣ��̳���role
{
public:
	//���캯������ʼ������
	Protagonist(int lv);

	//���麯��
	virtual void setPH_ATK_DEF() = 0;//��������������仯
	virtual void setPreEXP_EXP_LV(int lv) = 0;//��Ӯ����������仯
	virtual std::string* getNivosseName() = 0;//��ȡ���＼������
	virtual std::string getNivose_oneName() = 0;//��ȡ�����һ����������
	virtual std::string getNivose_twoName() = 0;//��ȡ����ڶ�����������
	virtual void setNivose_one() = 0;//���õ�һ�������Ƿ�ʹ��
	virtual void setNivose_two() = 0;//���õڶ��������Ƿ�ʹ��

	//˽�г�Ա��set��get����
	void setMoney(int);
	int getMoney();
	void setEXP(int);
	void setPreEXP(int);
	int getEXP();
	int getPreEXP();

protected:
	static int m_iMoney;//��Ǯ
	int m_iExp;//�ܾ���ֵ
	int m_iPreExp;//��ǰ����ֵ
};

class Saber :public Protagonist//Saber������֮һ���̳���Protagonist
{
public:
	//���캯������ʼ������
	Saber(int lv);

	//�麯����ʵ��
	virtual void setPH_ATK_DEF();
	virtual void setPreEXP_EXP_LV(int lv);
	virtual std::string* getNivosseName();
	virtual std::string getNivose_oneName();
	virtual std::string getNivose_twoName();
	virtual void setNivose_one();
	virtual void setNivose_two();

	//���ݳ�Ա
	bool m_bNivose_one;//�жϵ�һ�������Ƿ�ʹ��
	bool m_bNivose_two;//�жϵڶ��������Ƿ�ʹ��
	std::string m_strNivoseName[3] = { "�������²�","����ն" };//��������
};

class Archer :public Protagonist//Archer������֮һ���̳���Protagonist
{
public:
	//���캯������ʼ������
	Archer(int lv);

	//�麯����ʵ��
	virtual void setPH_ATK_DEF();
	virtual void setPreEXP_EXP_LV(int lv);
	virtual std::string* getNivosseName();
	virtual std::string getNivose_oneName();
	virtual std::string getNivose_twoName();
	virtual void setNivose_one();
	virtual void setNivose_two();

	//���ݳ�Ա
	bool m_bNivose_one;//�жϵ�һ�������Ƿ�ʹ��
	bool m_bNivose_two;//�жϵڶ��������Ƿ�ʹ��
	std::string m_strNivoseName[3] = { "Ԫ�������","��������" };//��������
};

class Lancer :public Protagonist//Lancer������֮һ���̳���Protagonist
{
public:
	//���캯������ʼ������
	Lancer(int lv);

	//�麯����ʵ��
	virtual void setPH_ATK_DEF();
	virtual void setPreEXP_EXP_LV(int lv);
	virtual std::string* getNivosseName();
	virtual std::string getNivose_oneName();
	virtual std::string getNivose_twoName();
	virtual void setNivose_one();
	virtual void setNivose_two();

	//���ݳ�Ա
	bool m_bNivose_one;//�жϵ�һ�������Ƿ�ʹ��
	bool m_bNivose_two;//�жϵڶ��������Ƿ�ʹ��
	std::string m_strNivoseName[3] = { "����Ͷ��","����˫ʽ" };//��������
};

class Villain :public Role//��ǣ��̳���role
{
public:
	//���캯������ʼ������
	Villain(int lv);

	virtual void setPH_ATK_DEF();//��������������仯
	virtual void setPreEXP_EXP_LV(int lv);//��Ӯ����������仯

	//���ݳ�Ա��set��get����
	int getFlag();
	void setFlag(int);

private:
	enum//����ö�ٳ���
	{
		MAJOR_PH = 0,
		MAJOR_ATK = 1,
		MAJOR_DEF = 2
	};
	int m_iType;//�ж���������
	int m_iFlag;//�ж������Ƿ��Ѿ�����ս
};

#endif  //ROLE_H