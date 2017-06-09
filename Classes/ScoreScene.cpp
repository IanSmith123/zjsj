#include "ScoreScene.h"
#include "GameDefine.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
cocos2d::Scene * ScoreScene::createScene()
{
	auto scene = Scene::create();
	auto layer = ScoreScene::create();
	scene->addChild(layer);
	return scene;
}

bool ScoreScene::init()
{
	if (!Layer::init())
		return false;

	galaxy1 = Sprite::create("galaxy.png");
	galaxy1->setAnchorPoint(Point::ZERO);
	galaxy1->setPosition(Point::ZERO);
	addChild(galaxy1);

	std::string strscore1 = std::to_string(score[0]);
	std::string strscore2 = std::to_string(score[1]);
	std::string strscore3 = std::to_string(score[2]);
	TTFConfig config0("fonts/Marker Felt.ttf", 60);
	TTFConfig config1("fonts/Marker Felt.ttf", 30);
	auto labelScoreBoard = Label::createWithTTF(config0, "Score Board");
	labelScoreBoard->setPosition(Point(winSize_width / 2, winSize_height * 8 / 9));
	this->addChild(labelScoreBoard);

	auto labelScoreBoard1 = Label::createWithTTF(config1, "1st");
	labelScoreBoard1->setPosition(Point(winSize_width / 3, winSize_height * 7 / 9));
	this->addChild(labelScoreBoard1);
	auto labelScore1 = Label::createWithTTF(config1, strscore1);
	labelScore1->setPosition(Point(winSize_width * 2 / 3, winSize_height * 7 / 9));
	this->addChild(labelScore1);

	auto labelScoreBoard2 = Label::createWithTTF(config1, "2nd");
	labelScoreBoard2->setPosition(Point(winSize_width / 3, winSize_height * 6 / 9));
	this->addChild(labelScoreBoard2);
	auto labelScore2 = Label::createWithTTF(config1, strscore2);
	labelScore2->setPosition(Point(winSize_width *2/ 3, winSize_height * 6 / 9));
	this->addChild(labelScore2);

	auto labelScoreBoard3 = Label::createWithTTF(config1, "3rd");
	labelScoreBoard3->setPosition(Point(winSize_width / 3, winSize_height * 5 / 9));
	this->addChild(labelScoreBoard3);
	auto labelScore3 = Label::createWithTTF(config1, strscore3);
	labelScore3->setPosition(Point(winSize_width * 2 / 3, winSize_height * 5 / 9));
	this->addChild(labelScore3);


	auto labelItemScoreBack = Label::createWithTTF(config1, "Back");
	auto menuItemScoreBack = MenuItemLabel::create(labelItemScoreBack, CC_CALLBACK_1(ScoreScene::menuBackCallBack, this));
	auto menuScoreBack = Menu::create(menuItemScoreBack, NULL);
	menuScoreBack->setPosition(Point::ZERO);
	menuItemScoreBack->setPosition(Point(winSize_width * 7 / 9, winSize_height * 1 / 9));
	this->addChild(menuScoreBack);
}


void ScoreScene::menuBackCallBack(Ref* obj)
{
	auto scene = MenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionProgressOutIn::create(0.5, scene));
}
