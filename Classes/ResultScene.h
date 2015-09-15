#ifndef __MillionCode__ResultScene__
#define __MillionCode__ResultScene__

#include <cocos2d.h>
#include <iostream>
#include "Generic.h"
#include "tinyxml2\tinyxml2.h"

class ResultScene : public cocos2d::Layer
{
private:
	enum
	{
		WIN,
		DRAW,
		LOSE
	};

private:
	int BASEXP = 300;
	int EVOLVE_COND = 30;

    float m_Mag;
    cocos2d::Size visibleSize;
    cocos2d::Point origin;

	cocos2d::Sprite* m_playerMonsters[3];
	cocos2d::Sprite* m_enemyMonsters[3];
	cocos2d::Node* m_marks;
	cocos2d::Sprite* m_result;
	cocos2d::Node* m_expText;
	cocos2d::Sprite* m_descBG;

	int m_resultFlag;
	bool m_overviewMode;
	bool m_evolvingMode;
	bool m_standBy;
	bool m_evolveState[3];
	int winRes[3];

	tinyxml2::XMLDocument doc;
	tinyxml2::XMLDocument mData;

private:
	void eventHandler();
	void backButton();
	void displayBG();
	void displayResult();
	void expShare();
	void wipeResult();
	void evolve();
	void checkEvolution(int i);
	//void wipeExp();

public:
    virtual bool init();
    static cocos2d::Scene* createScene();
    
    void rtnHome();
    bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
    void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
    
    // implement the "static node()" method manually
    CREATE_FUNC(ResultScene);
};

#endif /* defined(__MillionCode__ResultScene__) */
