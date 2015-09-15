#ifndef __MillionCode__VersusScene__
#define __MillionCode__VersusScene__

#include <cocos2d.h>
#include <iostream>
#include "Generic.h"
#include "DataKey.h"
#include "tinyxml2/tinyxml2.h"


class VersusScene : public cocos2d::Layer
{
private:
	float m_Mag;
	cocos2d::Size visibleSize;
	cocos2d::Point origin;
	cocos2d::Menu* m_difficulty;

	int m_diffLevel;
	tinyxml2::XMLDocument doc;

private:
	void difficultySelect();
	void eventHandler();
	void displayBG();
	void showTeam();
	void showVersus();
public:
	virtual bool init();
	static cocos2d::Scene* createScene();

	void rtnHome();
	bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);

	//callbacks
	void runVersus(cocos2d::Ref *pSender, int difficulty);

	// implement the "static node()" method manually
	CREATE_FUNC(VersusScene);
};

#endif /* defined(__MillionCode__VersusScene__) */
