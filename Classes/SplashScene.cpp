#include "SplashScene.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene * SplashScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SplashScene::create();
	scene->addChild(layer);
	return scene;
}

bool SplashScene::init()
{
	if(!Layer::init())
		return false;

	auto size = Director::getInstance()->getWinSize();

	TTFConfig config("fonts/Marker Felt.ttf", 100);

	auto GameName = Label::createWithTTF(config, "ZJSJ");
	GameName->setPosition(Point(size.width/2, size.height/2));
	this->addChild(GameName);

	auto GameAuthor = Label::createWithTTF(config, "GAME BY BHY");
	GameAuthor->setPosition(Point(size.width/2, size.height/3));
	GameAuthor->setScale(0.3);
	this->addChild(GameAuthor);

	FILE *p = fopen("score.txt", "r");
	if (p)
	{
		fread(score, sizeof(int), 3, p);
		//fscanf(p, "%d", score[0]);
		fclose(p);
	}

	this->scheduleOnce(schedule_selector(SplashScene::jumpToMenu), 1);

	return true;
}

void SplashScene::jumpToMenu(float t)
{
	auto scene = MenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionProgressOutIn::create(0.5, scene));
}