#ifndef __MillionCode__CheckScene__
#define __MillionCode__CheckScene__

#include <cocos2d.h>
#include <string>
#include "DataKey.h"
#include "MonsterEqData.h"
#include "Generic.h"
#include "Live2DSprite.h"
#include "tinyxml2/tinyxml2.h"
#include "platform/CCFileUtils.h"

class CheckScene : public cocos2d::Layer
{
private:
	enum
	{
		CHANGE_OPTION,
		STATUS_OPTION,
		RESET_OPTION
	};

	enum
	{
		FIRST_MONSTER,
		SECOND_MONSTER,
		THIRD_MONSTER
	};

    cocos2d::Size m_VisibleSize;
    cocos2d::Point origin;
    ST st;
    float m_Mag;

	bool m_selectedMon[3];
	bool m_onSubmenu;

	cocos2d::Sprite* m_changeBtn;
	cocos2d::Sprite* m_statusBtn;
	cocos2d::Sprite* m_resetBtn;
	cocos2d::Label* m_monsterName;

	//change sub menu
	cocos2d::Menu* m_changeMenu;
	cocos2d::Label* m_changeIntruction;
	cocos2d::Label* m_denyalMsg;
	cocos2d::MenuItemImage* monsterItem[2];
	
	//stats sub menu
	Live2DSprite* m_live2dMonster;
	cocos2d::Label* m_name;
	cocos2d::Label* m_HP;
	cocos2d::Label* m_Special;
	cocos2d::Label* m_wins;

	float buttonWidth;

	cocos2d::Sprite* monsterSlot[3];

	tinyxml2::XMLDocument doc;
	bool m_isPressed[3];
	bool m_isMonPressed[3];
	bool m_btnIsReady;
    
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();

	//initialization
    void setUi();
	void displayBG();
    void setMonster();
	void eventHandler();
    
	//animation related
	void resetMenu();
	void animateButtons(int option);
	void animateMonsters(int option);

	//sub menu processes
	void statsView(int selectedMonster);
	void changeOrder(int selectedMonster);
	void resetStats(int selectedMonster);
	
	//callback related
	void enableButtons();
	void changeOrderCallback(cocos2d::Ref* pSender, int option, int slot, int current);
    void menuReturnCallback(cocos2d::Ref* pSender);
	void exitScene();

	//event handling
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* eventt);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* eventt);

    
    CREATE_FUNC(CheckScene);
};

#endif /* defined(__MillionCode__CheckScene__) */
