#include "Enemy.h"

USING_NS_CC;

Enemy* Enemy::create()
{
	Enemy* pRet = new Enemy();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}


bool Enemy::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	Sprite* sprite;

	int n = rand() % 10;
	if (n >= 2)
	{
		sprite = Sprite::create("PaperPlane_01.png");
		m_hitScore = 100;
		m_isSoonDie = 1;
	}
	else
	{
		sprite = Sprite::create("PaperPlane_02.png");
		m_hitScore = 200;
		m_isSoonDie = 0;
	}

	this->addChild(sprite);

	m_hitNum = 0;

	return true;
}

void Enemy::setPositionRC(int row, int col)
{
	m_x = row;
	m_y = col;
	this->setPosition(Point(row, col));
}
Boss* Boss::create()
{
	Boss* pRet = new Boss();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
bool Boss::init()
{
	moveflag = 1;
	if (!Sprite::init())
	{
		return false;
	}

	Sprite* sprite;
	sprite = Sprite::create("Boss.png");
	m_hitScore = 2000;
	m_isSoonDie = 0;

	this->addChild(sprite);

	m_hitNum = 0;

	return true;
}
void Boss::setPositionRC(int row, int col)
{
	m_x = row;
	m_y = col;
	this->setPosition(Point(row, col));
}
EnemyBullet* EnemyBullet::create()
{
	EnemyBullet* pRet = new EnemyBullet();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
bool EnemyBullet::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	Sprite* sprite;
	sprite = Sprite::create("BossBullet.png");
	this->addChild(sprite);
	return true;
}
void EnemyBullet::setPositionRC(int row, int col)
{
	m_x = row;
	m_y = col;
	this->setPosition(Point(row, col));
}
