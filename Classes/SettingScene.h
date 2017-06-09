#ifndef _SETTINGSCENE_H__
#define _SETTINGSCENE_H__

#include "cocos2d.h"
#include "MenuScene.h"
#include "res.h"

class SettingScene : public cocos2d::Layer
{
private:
	cocos2d::Sprite* galaxy1;
public:
	static cocos2d::Scene * createScene();
	virtual bool init();
	CREATE_FUNC(SettingScene);
	void menuBackCallBack(Ref* obj);
	void menuBGMSwitchCallBack(cocos2d::Ref* obj);
};







#endif // !_SETTINGSCENE_H__
