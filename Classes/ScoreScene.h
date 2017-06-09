#ifndef _SCORESCENE_H
#define _SCORESCENE_H

#include "cocos2d.h"
#include "MenuScene.h"
#include "res.h"
#include<string>

class ScoreScene : public cocos2d::Layer
{
private:
	cocos2d::Sprite* galaxy1;
public:
	static cocos2d::Scene * createScene();
	virtual bool init();

	CREATE_FUNC(ScoreScene);
	void menuBackCallBack(Ref* obj);
};






#endif // !_SCORESCENE_H
