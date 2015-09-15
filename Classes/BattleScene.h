#ifndef __MillionCode__BattleScene__
#define __MillionCode__BattleScene__

#include <cocos2d.h>
#include "Generic.h"
#include "PickingPhase.h"

class BattleScene : public cocos2d::Layer
{
private:
    cocos2d::Size visibleSize;
    cocos2d::Point origin;
    float m_Mag;
	Picking* m_pickingPhase;
	int cardData[4];
	
private:
	void runBattle();
    
public:
    static cocos2d::Scene* createScene();
    
	BattleScene();
	~BattleScene();

	virtual bool init();
	virtual void update(float dt) override;
    
	void displayAnimBG();
	void backBtn();

    void menuCloseCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(BattleScene);
};

#endif /* defined(__MillionCode__BattleScene__) */
