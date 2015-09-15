#ifndef __MillionCode__TutorialScene__
#define __MillionCode__TutorialScene__

#include <iostream>
#include <string>
#include "cocos2d.h"

class TutorialScene : public cocos2d::Layer
{
private:
	cocos2d::Size visibleSize;
	float m_Mag;
	cocos2d::Point origin;
	cocos2d::Menu* confirmMenu;

public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void setBackBtn();
	void setConfirm();
	void resetSaveData();

	void rtrnTitleScene(cocos2d::Ref *pSender);
	//void resetData(cocos2d::Ref *pSender);
	void menuSceneTransition(cocos2d::Ref* pSender);
	void continueToMenu();

	CREATE_FUNC(TutorialScene);
};

#endif /* defined(__MillionCode__TutorialScene__) */
