#ifndef __MillionCode__TitleScene__
#define __MillionCode__TitleScene__

#include <iostream>
#include <vector>
#include <string>
#include "cocos2d.h"
#include "Generic.h"
#include "AudioControl.h"
#include "tinyxml2/tinyxml2.h"

class TitleScene : public cocos2d::Layer
{
private:
    cocos2d::Size visibleSize;
    float m_Mag;

	cocos2d::Menu* startMenu;
	cocos2d::Menu* loadMenu;
	cocos2d::Sprite* bg;
	cocos2d::Sprite* bg2;

	tinyxml2::XMLDocument doc;

public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
	virtual void update(float dt) override;
    
    void displayMenu(bool loadContent = false);
	void displayBG();

	void showLoadMenu(cocos2d::Ref* pSender, cocos2d::Menu* Menu);
    void menuSceneTransition(cocos2d::Ref* pSender, bool newGame);
    
    void setSound();

    void menuCloseCallback(cocos2d::Ref* pSender);

    
    CREATE_FUNC(TitleScene);
};

#endif /* defined(__MillionCode__TitleScene__) */
