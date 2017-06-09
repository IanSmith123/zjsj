#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "Enemy.h"
#include "res.h"
#include "MenuScene.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>


class GameScene : public cocos2d::Layer
{
private:
	int m_x;									//记录触摸位置
	int m_y;
	int m_score;								//记录分数
	cocos2d::Vector<Enemy*> allEnemy;			//记录所有敌机
	cocos2d::Vector<cocos2d::Sprite*> allBullet;//记录所有子弹
	int dir;
	cocos2d::Sprite* galaxy1;	//星空背景
	cocos2d::Sprite* galaxy2;
	
	void scrollBG(float);
	void newBody(float t);
	void moveBody(float t);
	void newPlane();
	void newBullet();
	void newEnemy();
	void movePlane();
	void moveBullet();
	void moveEnemy();
	void newBomb(int x, int y, int type);		//爆炸动画
	void cleanBomb(Node* pRef);
	void update(float t);
	void gameOver();

	//BHY 2017年6月6日16:48:41
	cocos2d::Vector<cocos2d::Sprite*> allLostBlood;// 记录所有的掉落的生命
	cocos2d::Vector<cocos2d::Sprite*> allLostBullet;// 记录所有掉落的武器
	cocos2d::Vector<cocos2d::Sprite*> allLostClearScreen; //记录所有的清屏大招;

	int countHeart = 3; //记录玩家的血量
	int heartLimit = 5; // 限制玩家的最大血量
	int bulletLevel = 1;


	void moveLostHeart();//移动掉落的心形
	void moveLostBullet();//移动掉落的子弹

	void moveLostClearScreen();//移动掉落的大招



  //boss相关

	void newBoss();        //新建boss
	void newBossBullet();   //新建boss子弹
	void listenscore();
	void listne_schedule(float t);
	void newBossBullet_rewrite(float t); //boss出现时的newbody
	void moveBoss();        //boss移动
	void moveEnemyBullet(); //移动敌机子弹
	void moveBody_rewrite(float t); //boss出现时的movebody函数
	void createBoss(float t);
	void newBullet_rewrite(float t);
	void GameScene::gameOver(float t);
	void GameScene::moveBody_Bullet(float t);
	void GameScene::newBody_enemy(float t);
	void GameScene::newBody_bullet(float);

	Boss* cur_Boss;                             //记录当前boss
	cocos2d::Vector<EnemyBullet*> allEnemyBullet;
	bool is_boss_app;                           //判断boss是否出现


public:
	static cocos2d::Scene * createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);
	void menuCloseCallBack(Ref* obj);
	void menuBacktoMenuCallBack(Ref* obj);
	void menuBacktoGameCallBack(Ref* obj);
};

#endif