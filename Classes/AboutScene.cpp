#include "AboutScene.h"
#include "GameDefine.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
cocos2d::Scene * AboutScene::createScene()
{
	auto scene = Scene::create();
	auto layer = AboutScene::create();
	scene->addChild(layer);
	return scene;
}

bool AboutScene::init()
{
	if (!Layer::init())
		return false;
	galaxy1 = Sprite::create("galaxy.png");
	galaxy1->setAnchorPoint(Point::ZERO);
	galaxy1->setPosition(Point::ZERO);
	addChild(galaxy1);

	TTFConfig config0("fonts/Marker Felt.ttf", 100);
	TTFConfig config1("fonts/Marker Felt.ttf", 30);
	auto Producedby = Label::createWithTTF(config0, "Produced By");
	Producedby->setPosition(Point(winSize_width / 2, winSize_height * 8 / 9));
	this->addChild(Producedby);

	auto BHY = Label::createWithTTF(config1, "BHY");
	BHY->setPosition(Point(winSize_width / 2, winSize_height * 6 / 9));
	this->addChild(BHY);

	auto WYL = Label::createWithTTF(config1, "WYL");
	WYL->setPosition(Point(winSize_width / 2, winSize_height * 5 / 9));
	this->addChild(WYL);

	auto CYH = Label::createWithTTF(config1, "CYH");
	CYH->setPosition(Point(winSize_width / 2, winSize_height * 4 / 9));
	this->addChild(CYH);

	auto CDS = Label::createWithTTF(config1, "CDS");
	CDS->setPosition(Point(winSize_width / 2, winSize_height * 3 / 9));
	this->addChild(CDS);

	auto RJL = Label::createWithTTF(config1, "RJL");
	RJL->setPosition(Point(winSize_width / 2, winSize_height * 2 / 9));
	this->addChild(RJL);

	auto ZCH = Label::createWithTTF(config1, "ZCH");
	ZCH->setPosition(Point(winSize_width / 2, winSize_height * 1 / 9));
	this->addChild(ZCH);

	auto labelItemAboutBack = Label::createWithTTF(config1, "Back");
	auto menuItemAboutBack = MenuItemLabel::create(labelItemAboutBack, CC_CALLBACK_1(AboutScene::menuBackCallBack, this));
	auto menuAboutBack = Menu::create(menuItemAboutBack, NULL);
	menuAboutBack->setPosition(Point::ZERO);
	menuItemAboutBack->setPosition(Point(winSize_width * 7 / 9, winSize_height * 1 / 9));
	this->addChild(menuAboutBack);
}


void AboutScene::menuBackCallBack(Ref* obj)
{
	auto scene = MenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionProgressOutIn::create(0.5, scene));
}
