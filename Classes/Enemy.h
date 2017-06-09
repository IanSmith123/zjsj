#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "cocos2d.h"

class Enemy : public cocos2d::Sprite
{
public:
	int m_x;			//记录飞机横纵坐标
	int m_y;
	int m_hitNum;		//飞机被打中次数
	int m_hitScore;		//打中飞机加的分数
	bool m_isSoonDie;	//飞机是否将要死亡

	void setPositionRC(int row, int col);//设置位置

	static Enemy* create();
	virtual bool init();
};
class Boss : public cocos2d::Sprite
{
public:
	int m_x;			//记录boss横纵坐标
	int m_y;
	int moveflag;
	int m_hitNum;		//boss被打中次数
	int m_hitScore;		//打中boss加的分数
	bool m_isSoonDie;	//boss是否将要死亡
	void setPositionRC(int row, int col);//设置位置
	static Boss* create();
	virtual bool init();
	int final_position_x; //记录boss停止位置横坐标
	int final_position_y; //记录boss停止为止纵坐标

};
class EnemyBullet :public cocos2d::Sprite
{
public:
	int m_x;			//记录敌方子弹横纵坐标
	int m_y;
	void setPositionRC(int row, int col);//设置位置
	static EnemyBullet* create();
	virtual bool init();
};
#endif
