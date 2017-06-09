#include "MenuScene.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene * MenuScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MenuScene::create();
	scene->addChild(layer);
	return scene;
}

bool MenuScene::init()
{
	if (!Layer::init())
		return false;

	galaxy1 = Sprite::create("galaxy.png");
	galaxy1->setAnchorPoint(Point::ZERO);
	galaxy1->setPosition(Point::ZERO);
	addChild(galaxy1);

	auto size = Director::getInstance()->getWinSize();
	TTFConfig config("fonts/Marker Felt.ttf", 30);
	//显示start按钮
	auto labelItemStart= Label::createWithTTF(config, "Start");
	auto menuItemStart = MenuItemLabel::create(labelItemStart, CC_CALLBACK_1(MenuScene::menuStartCallBack, this));
	//显示setting按钮
	auto labelItemSetting = Label::createWithTTF(config, "Setting");
	auto menuItemSetting = MenuItemLabel::create(labelItemSetting, CC_CALLBACK_1(MenuScene::menuSettingCallBack, this));
	//显示score按钮
	auto labelItemScore = Label::createWithTTF(config, "Score");
	auto menuItemScore = MenuItemLabel::create(labelItemScore, CC_CALLBACK_1(MenuScene::menuScoreCallBack, this));
	//显示about us按钮
	auto labelItemAbout= Label::createWithTTF(config, "About Us");
	auto menuItemAbout = MenuItemLabel::create(labelItemAbout, CC_CALLBACK_1(MenuScene::menuAboutCallBack, this));
	//显示exit按钮
	auto labelItemExit = Label::createWithTTF(config, "Exit");
	auto menuItemExit = MenuItemLabel::create(labelItemExit, CC_CALLBACK_1(MenuScene::menuCloseCallBack, this));
	auto menu = Menu::create(menuItemStart,menuItemSetting,menuItemScore,menuItemAbout,menuItemExit, NULL);
	menu->setPosition(Point(winSize_width / 2, winSize_height / 2));
	/*
	menuItemStart->setPosition(Point(winSize_width / 2, winSize_height * 7 / 9));
	menuItemSetting->setPosition(Point(winSize_width / 2, winSize_height * 6 / 9));
	menuItemScore->setPosition(Point(winSize_width / 2, winSize_height * 5 / 9));
	menuItemAbout->setPosition(Point(winSize_width / 2, winSize_height * 4 / 9));
	menuItemExit->setPosition(Point(winSize_width /2, winSize_height *3/ 9));
	*/
	menu->alignItemsVerticallyWithPadding(50.0f);
	this->addChild(menu);
    
	return true;
}

void MenuScene::menuStartCallBack(Ref* obj)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionProgressOutIn::create(0.5, scene));
}

void MenuScene::menuSettingCallBack(Ref* obj)
{
	auto scene = SettingScene::createScene();
	Director::getInstance()->replaceScene(TransitionProgressOutIn::create(0.5, scene));
}

void MenuScene::menuScoreCallBack(Ref* obj)
{
	auto scene = ScoreScene::createScene();
	Director::getInstance()->replaceScene(TransitionProgressOutIn::create(0.5, scene));
}

void MenuScene::menuAboutCallBack(Ref* obj)
{
	auto scene = AboutScene::createScene();
	Director::getInstance()->replaceScene(TransitionProgressOutIn::create(0.5, scene));
}

void MenuScene::menuCloseCallBack(Ref* obj)
{
	Director::getInstance()->end();
}

