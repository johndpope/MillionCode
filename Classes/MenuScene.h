#ifndef __MillionCode__MenuScene__
#define __MillionCode__MenuScene__

#include <cocos2d.h>
#include "Generic.h"
#include "Live2DSprite.h"

class MenuScene : public cocos2d::Layer
{
private:
    cocos2d::Size visibleSize;
    cocos2d::Point origin;
    float m_Mag;
	
	bool buttonPressed[5];
	bool readyToBack;

	cocos2d::Sprite* m_battleBtn;
	cocos2d::Sprite* m_monsterBtn;
	cocos2d::Sprite* m_createBtn;
	cocos2d::Sprite* m_statusBtn;
	cocos2d::Sprite* m_bestiaryBtn;

	Live2DSprite* pixie;
	
	static bool m_monsterMenuEnable;

public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
	virtual void update(float dt) override;
    
	void animateButtons();
	void resetButtons();

	void eventHandler();
	void enableBackButton();

    void sceneTransition(int btnTag);
	void showEqMenu(cocos2d::Ref* pSender);
    
    void rtnTitleScene(cocos2d::Ref* pSender);
    
    void setUserInterface();
	void displayBackground();
    
    void backBtn();

private:
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* eventt);
	void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* eventt);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* eventt);

    CREATE_FUNC(MenuScene);
};



#endif /* defined(__MillionCode__MenuScene__) */
