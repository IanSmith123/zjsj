#ifndef __GET_INTO_GAME_H__
#define __GET_INTO_GAME_H__

#include "cocos2d.h"
class GetIntoGame : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(GetIntoGame);
	

	void menuCallBack(cocos2d::Ref* obj);
};

#endif