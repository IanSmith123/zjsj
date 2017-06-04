// �տ�ʼ������Ϸ�ĳ���
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

//��ʼ��������Ϸ�Ľ���
bool GetIntoGame::init()
{

	if (!Layer::init())
		return false;

	//��ʾ��Ϸ�Ŀ�ʼѡ��˵�

//	TTFConfig config("fonts/Marker Felt.ttf", winSize_width/10);//������Ϸ��ʼ��ʱ�������ʾ������
//��ʾzjsj��ť
	auto label_zjsj = Label::createWithTTF("Z J S J", "fonts/Marker Felt.ttf", 24);
	label_zjsj->setPosition(Point(winSize_width / 2, winSize_height / 8));
	this->addChild(label_zjsj);

//��ʾstart��ť
	auto label_start = Label::createWithTTF("start", "fonts/Marker Felt.ttf", 18);
	label_start->setPosition(Point(winSize_width / 2, winSize_height*3 / 7));
	this->addChild(label_start);

//��ʾsetting��ť
	auto label_setting = Label::createWithTTF("setting", "fonts/Marker Felt.ttf", 18);
	label_setting->setPosition(Point(winSize_width / 2, winSize_height * 4 / 7));
	this->addChild(label_setting);

//��ʾscore��ť
	auto label_score = Label::createWithTTF("score", "fonts/Marker Felt.ttf", 18);
	label_score->setPosition(Point(winSize_width / 2, winSize_height * 5 / 7));
	this->addChild(label_score);

//��ʾexit��ť
	auto label_exit = Label::createWithTTF("start", "fonts/Marker Felt.ttf", 18);
	label_exit->setPosition(Point(winSize_width / 2, winSize_height * 6 / 7));
	this->addChild(label_exit);
}
//�趨������˵�ѡ���ʱ����õĺ���
//TODO: �������ÿһ����ģ��д������������
/*
void GetIntoGame::menuCallBack(Ref* obj)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}
*/

