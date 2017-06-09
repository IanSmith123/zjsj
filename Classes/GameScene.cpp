#include "GameScene.h"
#include "Plane.h"
#include "Enemy.h"
#include "GameDefine.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

cocos2d::Scene * GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if(!Layer::init())
		return false;

	//����
	galaxy1 = Sprite::create("galaxy.png");
	galaxy1->setAnchorPoint(Point::ZERO);
	galaxy1->setPosition(Point::ZERO);
	addChild(galaxy1);

	galaxy2 = Sprite::create("galaxy.png");
	galaxy2->setAnchorPoint(Point::ZERO);
	galaxy2->setPosition(Point::ZERO);
	addChild(galaxy2);

	//����
	m_score = 0;
	auto scoreNum = Label::createWithSystemFont("Score: 0", "Consolas", 30);
	scoreNum->setTag(110);
	scoreNum->setPosition(Point(winSize_width/5, winSize_height*15/16));
	addChild(scoreNum, 1);

	//����
	for (int i = 1; i <=countHeart; ++i)
	{
		auto heart = Sprite::create("heart.png");
		heart->setPosition(Point(winSize_width * 3 / 5 + i * 32, winSize_height * 15 / 16));
		heart->setTag(200 + i);
		addChild(heart, 1);
	}

	//�ɻ�
	dir = 0;	//Ĭ�ϴ���ֹͣ״̬
	newPlane();

	//��������
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [&](Touch * t, Event * e){
		m_x = t->getLocation().x;
		m_y = t->getLocation().y;
		return true;
	};

	listener->onTouchMoved = [&](Touch * t, Event * e){
		int px = t->getLocation().x - m_x;
		int py = t->getLocation().y - m_y;

		auto p = this->getChildByTag(120);
		p->runAction(MoveBy::create(0, Point(px, py)));

		m_x = t->getLocation().x;
		m_y = t->getLocation().y;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//�����¼�����
	auto listener2 = EventListenerKeyboard::create();

	listener2->onKeyPressed = [&](EventKeyboard::KeyCode k, Event * e) {//�ж��ƶ����򲢸ı䷽��

		switch (k)
		{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			dir = 1;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			dir = 2;
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			dir = 3;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			dir = 4;
			break;
		case EventKeyboard::KeyCode::KEY_ESCAPE:
			if (esconpressed == false)
			{
				Director::getInstance()->stopAnimation();
				esconpressed = true;
				TTFConfig config("fonts/Marker Felt.ttf", 30);
				auto labelItemBacktoGame = Label::createWithTTF(config, "Resume");
				auto menuItemBacktoGame = MenuItemLabel::create(labelItemBacktoGame, CC_CALLBACK_1(GameScene::menuBacktoGameCallBack, this));
				auto labelItemBacktoMenu = Label::createWithTTF(config, "Menu");
				auto menuItemBacktoMenu = MenuItemLabel::create(labelItemBacktoMenu, CC_CALLBACK_1(GameScene::menuBacktoMenuCallBack, this));
				auto labelItemExit = Label::createWithTTF(config, "Exit");
				auto menuItemExit = MenuItemLabel::create(labelItemExit, CC_CALLBACK_1(GameScene::menuCloseCallBack, this));
				auto menu = Menu::create(menuItemBacktoGame,menuItemBacktoMenu,menuItemExit, NULL);
				menu->setTag(321);
				menu->setPosition(Point(winSize_width / 2, winSize_height /2));
				menu->alignItemsVerticallyWithPadding(50.0f);
				this->addChild(menu);
			}
			else
			{
				this->removeChildByTag(321);
				Director::getInstance()->startAnimation();
				esconpressed = false;
			}
			

		default:
			dir = 0;
			break;
			

		}
	};

	listener2->onKeyReleased = [&](EventKeyboard::KeyCode k, Event * e) {
		dir = 0;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener2, this);

	////�ƶ�����
	//this->schedule(schedule_selector(GameScene::scrollBG), 0.01f);

	////�����ӵ����л�
	//this->schedule(schedule_selector(GameScene::newBody), 1);

	////�ƶ��ɻ����ӵ����л�
	//this->schedule(schedule_selector(GameScene::moveBody), 0.02);
	//�ƶ�����
	this->schedule(schedule_selector(GameScene::scrollBG), 0.01f);
	//�����ӵ����л�
	this->schedule(schedule_selector(GameScene::newBody_bullet), 0.5f);
	this->schedule(schedule_selector(GameScene::newBody_enemy), 0.5f);

	//�ƶ��ɻ����ӵ����л�
	this->schedule(schedule_selector(GameScene::moveBody), 0.02f);
	//test
	this->scheduleOnce(schedule_selector(GameScene::listne_schedule), 5);

	//��ײ������Ϸ�߼�
	this->scheduleUpdate();

	//���ű�������

	if (bgmswitch == 1)
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("action_world1.mp3", true);
	}
		
	return true;
}

void GameScene::scrollBG(float t)
{
	//��������ѭ���ƶ�
	galaxy1->setPositionY(galaxy1->getPositionY() - 1.0f);
	galaxy2->setPositionY(galaxy1->getPositionY() + galaxy1->getContentSize().height - 2.0f);
	if (galaxy2->getPositionY() <= 0)
		galaxy1->setPosition(Point::ZERO);
}

void GameScene::newBody(float t)
{
	newBullet();
	newEnemy();
}

void GameScene::moveBody(float t)
{
	movePlane();
	moveBullet();
	moveEnemy();


	moveLostBullet();
	moveLostHeart();
	moveLostClearScreen();
}

void GameScene::newPlane()
{
	auto plane = PlaneSprite::create();
	plane->setTag(120);
	plane->setPosition(Point(winSize_width / 2, winSize_height / 4));
	addChild(plane);
}

void GameScene::newBullet()
{
	PlaneSprite* plane = (PlaneSprite*)this->getChildByTag(120);
	auto bullet = Sprite::create("bullet_03.png");
	bullet->setPosition(Point(plane->getPosition().x, plane->getPosition().y + plane->getContentSize().height));
	this->addChild(bullet);
	allBullet.pushBack(bullet);
}

void GameScene::newEnemy()
{
	auto enemy = Enemy::create();
	enemy->setPositionRC(rand() % (winSize_width - 30), winSize_height);
	this->addChild(enemy);
	allEnemy.pushBack(enemy);
}

void GameScene::movePlane()
{
	auto p = this->getChildByTag(120);
	
	switch (dir)
	{
	case 1:
		p->runAction(MoveBy::create(0, Point(-5, 0)));
		break;
	case 2:
		p->runAction(MoveBy::create(0, Point(5, 0)));
		break;
	case 3:
		p->runAction(MoveBy::create(0, Point(0, 5)));
		break;
	case 4:
		p->runAction(MoveBy::create(0, Point(0, -5)));
		break;
	}
}

void GameScene::moveBullet()
{
	for (int i = 0; i<allBullet.size(); ++i)
	{
		auto nowBullet = allBullet.at(i);
		nowBullet->setPositionY(nowBullet->getPositionY() + 5);
		if (nowBullet->getPositionY() > winSize_height)
		{
			nowBullet->removeFromParent();
			allBullet.eraseObject(nowBullet);
			i--;
		}
	}
}

void GameScene::moveEnemy()
{
	for (int i = 0; i < allEnemy.size(); ++i)
	{
		auto enemy = allEnemy.at(i);
		enemy->setPositionRC(enemy->m_x, enemy->m_y - 3);
		if (enemy->m_y < 0)
		{
			enemy->removeFromParent();
			allEnemy.eraseObject(enemy);
			i--;
		}
	}
}


//

//�ƶ����������
void GameScene::moveLostHeart()
{
	for (int i = 0; i < allLostBlood.size(); i++)
	{
		auto newHeart = allLostBlood.at(i);
		newHeart->setPositionY(newHeart->getPositionY() - 1);

		if (newHeart->getPositionY() > winSize_height)//��������Ѫ�ƶ�������Ļ֮�⣬���Ƴ��������
		{
			newHeart->removeFromParent();
			allLostBlood.eraseObject(newHeart);
			i--;
		}

	}

}



//�ƶ�������ӵ��ӳ�
void GameScene::moveLostBullet()
{
	for (int i = 0; i < allLostBullet.size(); i++)
	{
		auto nowLostBullet = allLostBullet.at(i);
		nowLostBullet->setPositionY(nowLostBullet->getPositionY() - 1);
		if (nowLostBullet->getPositionY() > winSize_height)
		{
			nowLostBullet->removeFromParent();
			allLostBullet.eraseObject(nowLostBullet);
			i--;
		}

	}
}

//�ƶ��������������
void GameScene::moveLostClearScreen()
{
	for (int i = 0; i < allLostClearScreen.size(); i++)
	{
		auto nowLostClearScreen = allLostClearScreen.at(i);
		nowLostClearScreen->setPositionY(nowLostClearScreen->getPositionY() - 1);
		if (nowLostClearScreen->getPositionY() > winSize_height)
		{
			nowLostClearScreen->removeFromParent();
			allLostClearScreen.eraseObject(nowLostClearScreen);
			i--;
		}
	}
}
//boss���
//�ƶ�boss�ӵ�
//��ط���
void GameScene::listne_schedule(float t) {
	listenscore();
}
void GameScene::listenscore()
{
	this->unschedule(schedule_selector(GameScene::newBody_enemy));
	createBoss(0);
}
void GameScene::moveEnemyBullet()
{
	for (int i = 0; i<allEnemyBullet.size(); i++)
	{
		auto nowEnemyBullet = allEnemyBullet.at(i);
		nowEnemyBullet->setPositionRC(nowEnemyBullet->m_x, nowEnemyBullet->m_y - 6);
		if (nowEnemyBullet->m_y < 0)
		{
			nowEnemyBullet->removeFromParent();
			allEnemyBullet.eraseObject(nowEnemyBullet);
			i--;
		}
	}
}
//����boss
void GameScene::newBoss()
{
	auto new_Boss = Boss::create();
	new_Boss->setPositionRC(winSize_width / 2, winSize_height);
	this->addChild(new_Boss);
	cur_Boss = new_Boss;
	is_boss_app = 1;
}
//����boss���ӵ�
void GameScene::newBossBullet()
{
	auto BossBullet = EnemyBullet::create();
	BossBullet->setPositionRC(cur_Boss->m_x, cur_Boss->m_y - 100);
	this->addChild(BossBullet);
	allEnemyBullet.pushBack(BossBullet);
}
//�ƶ�boss
void GameScene::moveBoss()
{
	if (cur_Boss->m_y>winSize_height - 200)
		cur_Boss->setPositionRC(cur_Boss->m_x, cur_Boss->m_y - 3);
	else
	{
		cur_Boss->setPositionRC((cur_Boss->m_x - (cur_Boss->moveflag == 1 ? (1) : (-1))), cur_Boss->m_y);
		if (cur_Boss->m_x < 50)
			cur_Boss->moveflag = 0;
		else if (cur_Boss->m_x > 400)
			cur_Boss->moveflag = 1;
	}
}
//newbody
void GameScene::newBossBullet_rewrite(float t)
{

	newBossBullet();
}
void GameScene::newBullet_rewrite(float t)
{
	newBullet();
}
void GameScene::moveBody_rewrite(float t)
{
	moveBoss();
}
void GameScene::moveBody_Bullet(float t)
{
	moveEnemyBullet();
	movePlane();
}
void GameScene::createBoss(float t)
{
	newBoss();
	this->schedule(schedule_selector(GameScene::newBossBullet_rewrite), 1);
	this->schedule(schedule_selector(GameScene::moveBody_rewrite), 0.05);
	this->schedule(schedule_selector(GameScene::moveBody_Bullet), 0.05);
}
void GameScene::newBody_bullet(float t)
{
	newBullet();
}
void GameScene::newBody_enemy(float t)
{
	newEnemy();
}
void GameScene::gameOver(float t)
{
	gameOver();
}





//��ը����
void GameScene::newBomb(int x, int y, int type)
{
	std::string typestr;

	if (type == 1)
		typestr = "bomb_01.png";
	else
		typestr = "bomb_02.png";

	Vector<SpriteFrame*> allBomb;
	for (int i = 0; i < 5; ++i)
	{
		auto bomb = SpriteFrame::create(typestr, Rect(i * 102, 0, 102, 128));
		allBomb.pushBack(bomb);
	}

	auto ani = Animation::createWithSpriteFrames(allBomb, 0.25);
	auto sprite = Sprite::create();
	auto act = Sequence::create(
		Animate::create(ani),
		CCCallFuncN::create(sprite, callfuncN_selector(GameScene::cleanBomb)),
		nullptr);
	sprite->setPosition(Point(x, y));
	sprite->runAction(act);
	this->addChild(sprite);
}

void GameScene::cleanBomb(Node* pRef)
{
	pRef->removeFromParentAndCleanup(true);
}

void GameScene::update(float t)
{
	PlaneSprite* plane = (PlaneSprite*)this->getChildByTag(120);

	for (int i = 0; i < allEnemy.size(); ++i)
	{
		auto enemy = allEnemy.at(i);
		Rect er(enemy->m_x, enemy->m_y, 64, 64);

		//���л����ӵ���ײ
		for (int j = 0; j < allBullet.size(); ++j)
		{
			auto nowBullet = allBullet.at(j);
			Rect br(nowBullet->getPositionX(), nowBullet->getPositionY(), 64, 64);
			if (er.intersectsRect(br))
			{
				if (enemy->m_isSoonDie)
				{
					//�ӷ�
					Label* labScore = (Label*)this->getChildByTag(110);
					m_score += enemy->m_hitScore;
					labScore->setString(StringUtils::format("score: %d", m_score));
					//��ըЧ��
					newBomb(nowBullet->getPositionX(), nowBullet->getPositionY(), 1);
					//������Ч
					auto ps = ParticleSystemQuad::create("bomb.plist");
					ps->setPosition(Point(nowBullet->getPositionX(), nowBullet->getPositionY()));
					this->addChild(ps);




					//

					//��������Ѫ���߼��ӵ�
					int randNum = rand() % 60;
					if (randNum == 10)
					{
						//�����Ѫ


						auto lostBlood = Sprite::create("lostBlood.png");
						lostBlood->setPosition(enemy->getPosition());
						lostBlood->setTag(280);
						this->addChild(lostBlood);
						allLostBlood.pushBack(lostBlood);

					}
					else if (randNum == 12)
					//else
					{
						//�����ӵ��ӳ�
						auto lostBullet = Sprite::create("lostBullet.png");

						lostBullet->setPosition(enemy->getPosition());
						lostBullet->setTag(260);
						this->addChild(lostBullet);
						allLostBullet.pushBack(lostBullet);
					}
					else if (randNum == 9)
						//else
					{
						//������������
						auto lostClearScreen = Sprite::create("clearScreen.png");

						lostClearScreen->setPosition(enemy->getPosition());
						this->addChild(lostClearScreen);
						allLostClearScreen.pushBack(lostClearScreen);
					}







					//������Ч
					if(bgmswitch==1)	SimpleAudioEngine::getInstance()->playEffect("explosion3.mp3");
					//�ӵ���ʧ
					nowBullet->removeFromParent();
					allBullet.eraseObject(nowBullet);
					//�л���ʧ
					enemy->removeFromParent();
					allEnemy.eraseObject(enemy);
					i--;
					j--;
					break;
				}
				else
				{
					enemy->m_hitNum++;
					//������Ч
					if (bgmswitch == 1)	SimpleAudioEngine::getInstance()->playEffect("explosion3.mp3");
					//�ӵ���ʧ
					nowBullet->removeFromParent();
					allBullet.eraseObject(nowBullet);

					if (enemy->m_hitScore == 200)
					{
						if (enemy->m_hitNum == 1)
							enemy->m_isSoonDie = 1;
					}
					break;
				}
			}

		}

		//���л���ɻ���ײ
		Rect pr(plane->getPositionX(), plane->getPositionY(), plane->getContentSize().width, plane->getContentSize().height);
		if (er.intersectsRect(pr))
		{
			auto heart = this->getChildByTag(200 + countHeart);
			heart->removeFromParent();
			countHeart--;


			//�л���ʧ
			enemy->removeFromParent();
			allEnemy.eraseObject(enemy);
			//��ըЧ��
			newBomb(plane->getPositionX(), plane->getPositionY(), 2);
			//������Ч
			if (bgmswitch == 1)	SimpleAudioEngine::getInstance()->playEffect("explosion3.mp3");


			//���Ѫ��Ϊ0
			if (countHeart == 0)
			{
				gameOver();
			}

			
		}
	}

	//�������Һͼӳ�buff�йص���ײ
	Rect planeRect(plane->getPositionX(), plane->getPositionY(), 64, 64);//���ݷɻ���һ�����64����

																		 //���͵����Ѫ����ײ
	for (int i = 0; i < allLostBlood.size(); i++)
	{
		auto nowLostBlood = allLostBlood.at(i);
		Rect bloodRect(nowLostBlood->getPositionX(), nowLostBlood->getPositionY(), 64, 64);//���ݵ����Ѫ����һ�����64�ľ���
																						   //��⽻��
		if (planeRect.intersectsRect(bloodRect))
		{
			//���Ѫ�����࣬�Ͳ�������
			if (countHeart == heartLimit)
				break;
			//���»�һ����, ����countHeart

			countHeart += 1;
			auto heart = Sprite::create("heart.png");
			heart->setPosition(Point(winSize_width * 3 / 5 + countHeart * 32, winSize_height * 15 / 16));
			heart->setTag(200 + countHeart);
			addChild(heart, 1);

			nowLostBlood->removeFromParent();
			allLostBlood.eraseObject(nowLostBlood);
		}

	}
	//���͵�����ӵ�����ײ

	for (int i = 0; i < allLostBullet.size(); i++)
	{
		auto nowLostBullet = allLostBullet.at(i);
		Rect bulletRect(nowLostBullet->getPositionX(), nowLostBullet->getPositionY(), 64, 64);

		//���������ײ
		if (planeRect.intersectsRect(bulletRect))
		{
			bulletLevel += 1;
			//����������ӵ�Buff
			switch (bulletLevel)
			{
			case 2:
				unschedule(schedule_selector(GameScene::newBody));
				schedule(schedule_selector(GameScene::newBody), 0.5);
				break;
			case 3:
				unschedule(schedule_selector(GameScene::newBody));
				schedule(schedule_selector(GameScene::newBody), 0.4);
				break;
			case 4:
				unschedule(schedule_selector(GameScene::newBody));
				schedule(schedule_selector(GameScene::newBody), 0.3);
				break;
			default:
				bulletLevel = 4;
				break;
			}
			nowLostBullet->removeFromParent();
			allLostBullet.eraseObject(nowLostBullet);
			i--;

		}
	}

	//���͵�����������е���ײ
	for (int i = 0; i < allLostClearScreen.size(); i++)
	{
		auto nowLostClearScreen = allLostClearScreen.at(i);
		Rect ClearRect(nowLostClearScreen->getPositionX(), nowLostClearScreen->getPositionY(), 64, 64);

		if (planeRect.intersectsRect(ClearRect))
		{
			//�Ƴ�����ս��
			for (int en = 0; en < allEnemy.size(); en++)
			{
				auto enemyObj = allEnemy.at(en);
				enemyObj->removeFromParent();
				allEnemy.eraseObject(enemyObj);
				en--;

			}

			nowLostClearScreen->removeFromParent();
			allLostClearScreen.eraseObject(nowLostClearScreen);
			i--;
		}
	}

	Rect pr(plane->getPositionX(), plane->getPositionY(), plane->getContentSize().width, plane->getContentSize().height);
	//���boss���ӵ�����ײ
	for (int j = 0; j < allBullet.size(); ++j)
	{
		auto nowBullet = allBullet.at(j);
		Rect br(nowBullet->getPositionX(), nowBullet->getPositionY(), 64, 64);
		if (is_boss_app)
		{
			Rect bossr(cur_Boss->m_x - 50, cur_Boss->m_y - 50, 50, 50);//����boss
			if (bossr.intersectsRect(br))
			{
				if (cur_Boss->m_isSoonDie)
				{
					//�ӷ�
					Label* labScore = (Label*)this->getChildByTag(110);
					m_score += cur_Boss->m_hitScore;
					labScore->setString(StringUtils::format("score: %d", m_score));
					//��ըЧ��
					newBomb(nowBullet->getPositionX() + 50, nowBullet->getPositionY(), 1);
					newBomb(nowBullet->getPositionX(), nowBullet->getPositionY(), 1);
					newBomb(nowBullet->getPositionX() - 50, nowBullet->getPositionY() + 50, 1);
					newBomb(nowBullet->getPositionX() + 70, nowBullet->getPositionY() + 50, 1);
					newBomb(nowBullet->getPositionX() - 34, nowBullet->getPositionY() + 23, 1);
					newBomb(nowBullet->getPositionX() + 43, nowBullet->getPositionY() + 94, 1);
					newBomb(nowBullet->getPositionX() - 46, nowBullet->getPositionY() + 38, 1);
					newBomb(nowBullet->getPositionX() + 60, nowBullet->getPositionY() + 50, 1);
					//������Ч
					auto ps = ParticleSystemQuad::create("bomb.plist");
					ps->setPosition(Point(nowBullet->getPositionX(), nowBullet->getPositionY()));
					this->addChild(ps);
					//������Ч
					SimpleAudioEngine::getInstance()->playEffect("explosion3.mp3");
					//�ӵ���ʧ
					nowBullet->removeFromParent();
					allBullet.eraseObject(nowBullet);
					//�л���ʧ
					cur_Boss->removeFromParent();
					this->unschedule(schedule_selector(GameScene::newBossBullet_rewrite));
					this->unschedule(schedule_selector(GameScene::moveBody_rewrite));
					this->schedule(schedule_selector(GameScene::newBody_enemy), 0.5f);
					this->scheduleOnce(schedule_selector(GameScene::listne_schedule), 5);
					is_boss_app = 0;
					cur_Boss = NULL;
					is_boss_app = 0;
					this->unschedule(schedule_selector(GameScene::moveBody_rewrite));
					j--;
					//this->scheduleOnce(schedule_selector(GameScene::gameOver), 1.0f);
					break;
				}
				else
				{
					cur_Boss->m_hitNum++;
					//������Ч
					SimpleAudioEngine::getInstance()->playEffect("explosion3.mp3");
					//�ӵ���ʧ
					//������Ч
					auto ps = ParticleSystemQuad::create("bomb.plist");
					ps->setPosition(Point(nowBullet->getPositionX(), nowBullet->getPositionY()));
					this->addChild(ps);
					nowBullet->removeFromParent();
					allBullet.eraseObject(nowBullet);
					j--;
					if (cur_Boss->m_hitNum > 3)
					{
						cur_Boss->m_isSoonDie = 1;
					}
					break;
				}
			}
		}
	}
		//���ɻ���л��ӵ���ײ
//	Rect pr(plane->getPositionX(), plane->getPositionY(), plane->getContentSize().width, plane->getContentSize().height);
	for (int j = 0; j < allEnemyBullet.size(); ++j)
		{
			auto enemy_bullet = allEnemyBullet.at(j);
			Rect ebr(enemy_bullet->m_x, enemy_bullet->m_y, 64, 64);
			if (pr.intersectsRect(ebr))
			{
				auto heart = this->getChildByTag(200 + countHeart);
				heart->removeFromParent();
				countHeart--;
				//plane->m_hitNum++;

				//�л���ʧ
				enemy_bullet->removeFromParent();
				allEnemyBullet.eraseObject(enemy_bullet);
				//��ըЧ��
				newBomb(plane->getPositionX(), plane->getPositionY(), 2);
				//������Ч
				SimpleAudioEngine::getInstance()->playEffect("explosion3.mp3");
			}
		}


	//���Ѫ��Ϊ0
	if (countHeart == 0)
	{
		gameOver();
	}

}

void GameScene::gameOver()
{
	FILE *p;
	if (m_score > score[0])
	{
		score[2] = score[1];
		score[1] = score[0];
		score[0] = m_score;
	}
	else if (m_score > score[1])
	{
		score[2] = score[1];
		score[1] = m_score;
	}
	else if (m_score > score[2])
	{
		score[2] = m_score;
	}
	if ((fopen_s(&p,"score.txt", "w")) == NULL)
	{
		fwrite(score, sizeof(int), 3, p);
		//fprintf(p, "%d\n%d\n%d\n", score[0], score[1], score[2]);
		fclose(p);
	}


	SimpleAudioEngine::getInstance()->stopBackgroundMusic();

	this->unscheduleAllSelectors();
	this->unscheduleUpdate();

	auto scene = GameOver::createScene();
	Director::getInstance()->replaceScene(TransitionProgressOutIn::create(0.5, scene));
}

void GameScene::menuCloseCallBack(Ref* obj)
{
	Director::getInstance()->end();
}

void GameScene::menuBacktoMenuCallBack(Ref* obj)
{
	Director::getInstance()->startAnimation();
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	esconpressed = false;
	auto scene = MenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionProgressOutIn::create(0.5, scene));
}

void GameScene::menuBacktoGameCallBack(Ref* obj)
{
	this->removeChildByTag(321);
	Director::getInstance()->startAnimation();
	esconpressed = false;
}