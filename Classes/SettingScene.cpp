#include "SettingScene.h"
#include "GameDefine.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;
using namespace CocosDenshion;

cocos2d::Scene * SettingScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SettingScene::create();
	scene->addChild(layer);
	return scene;
}

bool SettingScene::init()
{
	if (!Layer::init())
		return false;

	galaxy1 = Sprite::create("galaxy.png");
	galaxy1->setAnchorPoint(Point::ZERO);
	galaxy1->setPosition(Point::ZERO);
	addChild(galaxy1);

	TTFConfig config1("fonts/Marker Felt.ttf", 30);
	if (bgmswitch == 1)
	{
		auto labelItemBGMSwitch = Label::createWithTTF(config1, "BGM Switch : On");
		auto menuItemBGMSwitch = MenuItemLabel::create(labelItemBGMSwitch, CC_CALLBACK_1(SettingScene::menuBGMSwitchCallBack, this));
		auto menuSetting = Menu::create(menuItemBGMSwitch, NULL);
		menuSetting->setPosition(Point::ZERO);
		menuItemBGMSwitch->setPosition(Point(winSize_width / 2, winSize_height * 5 / 7));
		this->addChild(menuSetting);
	}
	else
	{
		auto labelItemBGMSwitch = Label::createWithTTF(config1, "BGM Switch : Off");
		auto menuItemBGMSwitch = MenuItemLabel::create(labelItemBGMSwitch, CC_CALLBACK_1(SettingScene::menuBGMSwitchCallBack, this));
		auto menuSetting = Menu::create(menuItemBGMSwitch, NULL);
		menuSetting->setPosition(Point::ZERO);
		menuItemBGMSwitch->setPosition(Point(winSize_width / 2, winSize_height * 5 / 7));
		this->addChild(menuSetting);
	}
	
	auto labelItemSettingBack = Label::createWithTTF(config1, "Back");
	auto menuItemSettingBack = MenuItemLabel::create(labelItemSettingBack, CC_CALLBACK_1(SettingScene::menuBackCallBack, this));
	auto menuSettingBack = Menu::create(menuItemSettingBack, NULL);
	menuSettingBack->setPosition(Point::ZERO);
	menuSettingBack->setPosition(Point(winSize_width / 2, winSize_height * 3 / 7));
	this->addChild(menuSettingBack);
}


void SettingScene::menuBackCallBack(Ref* obj)
{
	auto scene = MenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionProgressOutIn::create(0.5, scene));
}

void SettingScene::menuBGMSwitchCallBack(Ref* obj)
{
	if (bgmswitch == 1)
	{
		bgmswitch = 0;
		auto scene = SettingScene::createScene();
		Director::getInstance()->replaceScene(TransitionProgressOutIn::create(0.1, scene));
	}
	else
	{
		bgmswitch = 1;
		auto scene = SettingScene::createScene();
		Director::getInstance()->replaceScene(TransitionProgressOutIn::create(0.1, scene));
	}
}
