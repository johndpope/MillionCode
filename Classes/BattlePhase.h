#ifndef __MillionCode__Battle__
#define __MillionCode__Battle__

#include <cocos2d.h>
#include "Generic.h"
#include "ResultScene.h"
#include "DataKey.h"
#include "MonsterEqData.h"
#include "tinyxml2/tinyxml2.h"
#include "platform/CCFileUtils.h"
#include "Live2DSprite.h"

enum CARD_TYPE{
	ROCK,
	SISSORS,
	PAPER,
	SUPER_ROCK,
	SUPER_SISSORS,
	SUPER_PAPER,
	ULTRA_ROCK,
	ULTRA_SISSORS,
	ULTRA_PAPER,
	CARD_TYPE_TOTAL,
	WIN,
	LOSE,
	DRAW
};

class Battle
{
private:
	cocos2d::Size m_visibleSize;
	cocos2d::Point m_origin;
	float m_Mag;

	//old data
	cocos2d::Node* m_instance;
	cocos2d::Node* m_cards[5];
	cocos2d::Node* m_specialCard;
	cocos2d::Node* m_iconGroup;
	cocos2d::Node* m_background;

	//new data
	//cocos2d::Sprite* m_iconFrame;
    //cocos2d::Sprite* m_enemyIconFrame;
	cocos2d::Sprite* m_enemySprite;
	cocos2d::Sprite* m_playerSprite;
	//cocos2d::Node* m_enemyGroup;
	cocos2d::Label* playerhealth;
	cocos2d::Label* enemyHP;
	cocos2d::Label* instructions;
	cocos2d::Label* orderText[5];
	cocos2d::Sprite* m_glow[5];
	cocos2d::Menu* m_menu;
	cocos2d::Sprite* enemyCard;
	cocos2d::Sprite* result;
	cocos2d::Sprite* m_enemyMiniCards[5];
	Live2DSprite* m_enemyL2D;
	Live2DSprite* m_playerL2D;

	int m_enemyHPCounter;
	int m_playerHPCounter;
	bool battleBegan;
	bool m_selected[5];
	int cardData[5];
	int enemyData[5];
	int order[5];
	int enemyMonster;
	int m_specialType;
	int m_enemySpecialType;
	int m_battleNum;

	tinyxml2::XMLDocument doc;
	tinyxml2::XMLDocument mData;

	cocos2d::EventListenerTouchOneByOne* listener;

private:
	void displayEnemyIcon();
	void displayEnemyHP();
	void displayPlayerHP();
	void eventHandler();
	void animEnemy();
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* eventt);
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* eventt);
	void pickCardOrder();
	void getPreloadedData();
	void cleanUp();
	void fightCards(int i);
	void genEnemyCards();
	void showInstruction();
	void cardBattle(cocos2d::Ref* pSender);
	void wipeCards(int i);
	void endBattle();
	void playerGetDMG();
	void enemyGetDMG();
	void collisionEffect();

public:
	Battle(cocos2d::Layer* instance);
	~Battle();
	void renderBattle(cocos2d::Sprite** cards, cocos2d::Sprite* specialCard, int enemyMData);
	void battlePhase(int hp, int* cardType, int pSpecial, int eSpecial, int battleNumber);
	void update(float dt);
};

#endif /* defined(__MillionCode__Battle__) */
