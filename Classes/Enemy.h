#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "cocos2d.h"

class Enemy : public cocos2d::Sprite
{
public:
	int m_x;			//��¼�ɻ���������
	int m_y;
	int m_hitNum;		//�ɻ������д���
	int m_hitScore;		//���зɻ��ӵķ���
	bool m_isSoonDie;	//�ɻ��Ƿ�Ҫ����

	void setPositionRC(int row, int col);//����λ��

	static Enemy* create();
	virtual bool init();
};
class Boss : public cocos2d::Sprite
{
public:
	int m_x;			//��¼boss��������
	int m_y;
	int moveflag;
	int m_hitNum;		//boss�����д���
	int m_hitScore;		//����boss�ӵķ���
	bool m_isSoonDie;	//boss�Ƿ�Ҫ����
	void setPositionRC(int row, int col);//����λ��
	static Boss* create();
	virtual bool init();
	int final_position_x; //��¼bossֹͣλ�ú�����
	int final_position_y; //��¼bossֹͣΪֹ������

};
class EnemyBullet :public cocos2d::Sprite
{
public:
	int m_x;			//��¼�з��ӵ���������
	int m_y;
	void setPositionRC(int row, int col);//����λ��
	static EnemyBullet* create();
	virtual bool init();
};
#endif
