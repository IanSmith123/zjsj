#ifndef _MENUSCENE_H
#define _MENUSCENE_H
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "GameDefine.h"
#include "SettingScene.h"
#include "AboutScene.h"
#include "ScoreScene.h"

class MenuScene : public cocos2d::Layer
{
private:
	cocos2d::Sprite* galaxy1;
public:
	static cocos2d::Scene * createScene();
	virtual bool init();
	
	CREATE_FUNC(MenuScene);
	void menuStartCallBack(cocos2d::Ref* obj);
	void menuSettingCallBack(cocos2d::Ref* obj);
	void menuScoreCallBack(Ref* obj);
	void menuAboutCallBack(Ref* obj);
	void menuCloseCallBack(cocos2d::Ref* obj);
};

#endif // !_MENUSCENE_H

