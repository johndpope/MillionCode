#ifndef __MillionCode__PickingPhase__
#define __MillionCode__PickingPhase__

#include <cocos2d.h>
#include "Generic.h"
#include "BattlePhase.h"

class Picking
{
private:
	cocos2d::Size m_visibleSize;
	float m_Mag;
	bool m_selected[4];
	bool eventOn;
	bool battleOn;
	int cardData[4];
	int enemyMonster;
	int m_HP;
	int m_specialType;
	int m_enemySpecialType;
	int m_enemyHP;
	int m_redutionCounter;

	int m_battleNum;
	cocos2d::Layer* m_instance;
	//cocos2d::Sprite* m_iconFrame; //Name: "IconFrame"
	cocos2d::Sprite* m_iconSprite;  //Name: "IconSprite"
	cocos2d::Sprite* m_cards[4]; //Name: "Cards" + i
	cocos2d::Sprite* m_glow[4];
	cocos2d::Sprite* m_hiddenCards[4];
	cocos2d::Sprite* m_specialCard; //Name: "SpCard"
	cocos2d::Sprite* m_enemyCard;
	cocos2d::Sprite* m_enemySpecial;
	cocos2d::Sprite* m_cardBack;
	//cocos2d::Node* m_iconGroup; //Name: "Icon"
	cocos2d::Label* penalty; //---auto clean up
	cocos2d::Label* health; //Name: "HP"
	cocos2d::Label* enemyHealth;
	cocos2d::Label* instructions; //--- removed in cleanUp()
	cocos2d::Sprite* m_background; //Name: "BG"
	cocos2d::Menu* m_menu; //--- removed in cleanUp()

	Battle* m_battle;

	tinyxml2::XMLDocument doc;
	tinyxml2::XMLDocument mData;

	cocos2d::EventListenerTouchOneByOne* listener;

private:
	void shuffle(int i);
	void displayIcon();
	void loadData();
	void displayHP();
	void displayUI();
	void versusAnim();
	void randomize(int iterator); //randomize cards[iterator]
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* eventt);
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* eventt);
	void startBattle(cocos2d::Ref* pSender);
	void cleanUp();
	void setCards();
	void displayEnemy();
	void enemyFlipAnim();
	void eventHandler();
	void cardAnim();
	void battleCallback();

public:
	Picking(cocos2d::Layer* instance);
	~Picking();
	int getCardData(int iterator);
	void renderPicking(int battleNumber);
	void update(float dt);
};

#endif /* defined(__MillionCode__PickingPhase__) */
