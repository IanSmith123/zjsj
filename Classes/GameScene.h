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
	int m_x;									//��¼����λ��
	int m_y;
	int m_score;								//��¼����
	cocos2d::Vector<Enemy*> allEnemy;			//��¼���ел�
	cocos2d::Vector<cocos2d::Sprite*> allBullet;//��¼�����ӵ�
	int dir;
	cocos2d::Sprite* galaxy1;	//�ǿձ���
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
	void newBomb(int x, int y, int type);		//��ը����
	void cleanBomb(Node* pRef);
	void update(float t);
	void gameOver();

	//BHY 2017��6��6��16:48:41
	cocos2d::Vector<cocos2d::Sprite*> allLostBlood;// ��¼���еĵ��������
	cocos2d::Vector<cocos2d::Sprite*> allLostBullet;// ��¼���е��������
	cocos2d::Vector<cocos2d::Sprite*> allLostClearScreen; //��¼���е���������;

	int countHeart = 3; //��¼��ҵ�Ѫ��
	int heartLimit = 5; // ������ҵ����Ѫ��
	int bulletLevel = 1;


	void moveLostHeart();//�ƶ����������
	void moveLostBullet();//�ƶ�������ӵ�

	void moveLostClearScreen();//�ƶ�����Ĵ���



  //boss���

	void newBoss();        //�½�boss
	void newBossBullet();   //�½�boss�ӵ�
	void listenscore();
	void listne_schedule(float t);
	void newBossBullet_rewrite(float t); //boss����ʱ��newbody
	void moveBoss();        //boss�ƶ�
	void moveEnemyBullet(); //�ƶ��л��ӵ�
	void moveBody_rewrite(float t); //boss����ʱ��movebody����
	void createBoss(float t);
	void newBullet_rewrite(float t);
	void GameScene::gameOver(float t);
	void GameScene::moveBody_Bullet(float t);
	void GameScene::newBody_enemy(float t);
	void GameScene::newBody_bullet(float);

	Boss* cur_Boss;                             //��¼��ǰboss
	cocos2d::Vector<EnemyBullet*> allEnemyBullet;
	bool is_boss_app;                           //�ж�boss�Ƿ����


public:
	static cocos2d::Scene * createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);
	void menuCloseCallBack(Ref* obj);
	void menuBacktoMenuCallBack(Ref* obj);
	void menuBacktoGameCallBack(Ref* obj);
};

#endif