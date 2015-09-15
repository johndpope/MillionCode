//
//  MonsterCreate.h
//  MillionCode
//
//  Created by æœ¨æ�‘å·§ on 2015/04/24.
//
//

#ifndef __MillionCode__MonsterCreate__
#define __MillionCode__MonsterCreate__

#include <cocos2d.h>
#include "Generic.h"
#include "DataKey.h"
#include "tinyxml2/tinyxml2.h"

class MonsterCreate : public cocos2d::Layer
{
private:

	enum{
		STARTING,
		ENDING
	};

    float m_Mag;
    cocos2d::Size m_VisibleSize;
    bool m_IsActiv;
    bool m_IsMakeEnd;
    cocos2d::Label* testingText;
    std::string text;
	std::string seedStr;
    cocos2d::Sprite* tmpWaiter;
	tinyxml2::XMLDocument doc;
    
    std::string m_data;
    char *m_seed;
    
    int m_test;
    cocos2d::Sprite *test[3];
    cocos2d::Sprite *m_TapFont;
    cocos2d::Rect rect[3];

	cocos2d::Label* instructions;
	cocos2d::Menu* selectionMenu;
	cocos2d::Sprite* m_confirm;
	cocos2d::Menu* m_rtnBtn;
	int m_slot;
    
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    void update(float delta);
    
    bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
    void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
    
    void make(void);
    void sprite(void);

	void runCamera();
	void confirmation(int confirmCase);
	void eventHandler();
	void getData();
	void slotSelection();

	void menuReturn(cocos2d::Ref* pSender);

	void cameraProcess(cocos2d::Ref *pSender, int slot);

    static void setSeed(const char* seedData);
    static int countBit(const char* data);
    
    
    CREATE_FUNC(MonsterCreate);
};
#endif /* defined(__MillionCode__MonsterCreate__) */
