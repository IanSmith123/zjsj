// 刚开始进入游戏的场景
#include "getIntoMenu.h"
#include "GameDefine.h"

USING_NS_CC;

Scene*  GetIntoGame::createScene()
{
	auto scene = Scene::create();
	auto layer = GetIntoGame::create();
	scene->addChild(layer);

	return scene;
}

//初始化进入游戏的界面
bool GetIntoGame::init()
{

	if (!Layer::init())
		return false;

	//显示游戏的开始选择菜单

//	TTFConfig config("fonts/Marker Felt.ttf", winSize_width/10);//设置游戏开始的时候标题显示的字体
//显示zjsj按钮
	auto label_zjsj = Label::createWithTTF("Z J S J", "fonts/Marker Felt.ttf", 24);
	label_zjsj->setPosition(Point(winSize_width / 2, winSize_height / 8));
	this->addChild(label_zjsj);

//显示start按钮
	auto label_start = Label::createWithTTF("start", "fonts/Marker Felt.ttf", 18);
	label_start->setPosition(Point(winSize_width / 2, winSize_height*3 / 7));
	this->addChild(label_start);

//显示setting按钮
	auto label_setting = Label::createWithTTF("setting", "fonts/Marker Felt.ttf", 18);
	label_setting->setPosition(Point(winSize_width / 2, winSize_height * 4 / 7));
	this->addChild(label_setting);

//显示score按钮
	auto label_score = Label::createWithTTF("score", "fonts/Marker Felt.ttf", 18);
	label_score->setPosition(Point(winSize_width / 2, winSize_height * 5 / 7));
	this->addChild(label_score);

//显示exit按钮
	auto label_exit = Label::createWithTTF("start", "fonts/Marker Felt.ttf", 18);
	label_exit->setPosition(Point(winSize_width / 2, winSize_height * 6 / 7));
	this->addChild(label_exit);
}
//设定当点击菜单选项的时候调用的函数
//TODO: 当后面的每一个子模块写好了再来这里
/*
void GetIntoGame::menuCallBack(Ref* obj)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}
*/

