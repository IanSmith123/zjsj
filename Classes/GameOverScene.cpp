#include "GameOverScene.h"
#include "GameScene.h"
#include "GameDefine.h"
#include "MenuScene.h"

USING_NS_CC;

Scene* GameOver::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOver::create();
	scene->addChild(layer);
	return scene;
}

bool GameOver::init()
{
	if(!Layer::init())
		return false;

	//显示GameOver
	TTFConfig config("fonts/Marker Felt.ttf", winSize_width/8);
	auto label = Label::createWithTTF(config, "GAME OVER");
	label->setPosition(Point(winSize_width/2, winSize_height/2));
	this->addChild(label);

	TTFConfig config1("fonts/Marker Felt.ttf", 30);
	//添加返回按钮
	auto labelItemMenu = Label::createWithTTF(config1, "Menu");
	auto labelItemNewGame = Label::createWithTTF(config1, "New Game");
	auto menuItemMenu = MenuItemLabel::create(labelItemMenu, CC_CALLBACK_1(GameOver::menuMenuCallBack, this));
	auto menuItemNewGame= MenuItemLabel::create(labelItemNewGame, CC_CALLBACK_1(GameOver::menuNewGameCallBack, this));
	auto menu = Menu::create(menuItemMenu,menuItemNewGame, NULL);

	menu->setPosition(Point::ZERO);
	menuItemMenu->setPosition(Point(winSize_width * 4 / 6, winSize_height * 2 / 8));
	menuItemNewGame->setPosition(Point(winSize_width * 4 / 6, winSize_height * 1 / 8));
	this->addChild(menu);
	return true;
}

void GameOver::menuNewGameCallBack(Ref* obj)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}
void GameOver::menuMenuCallBack(Ref* obj)
{
	auto scene = MenuScene::createScene();
	Director::getInstance()->replaceScene(scene);
}