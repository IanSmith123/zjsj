#ifndef _ABOUTSCENE_H__
#define _ABOUTSCENE_H__

#include "cocos2d.h"
#include "MenuScene.h"

class AboutScene : public cocos2d::Layer
{
private:
	cocos2d::Sprite* galaxy1;
public:
	static cocos2d::Scene * createScene();
	virtual bool init();
	CREATE_FUNC(AboutScene);
	void menuBackCallBack(Ref* obj);
};



#endif // !_ABOUTSCENE_H__

