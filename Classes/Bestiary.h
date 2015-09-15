#ifndef __MillionCode__Bestiary__
#define __MillionCode__Bestiary__

#include <cocos2d.h>
#include "Generic.h"
#include "ui/CocosGUI.h"
#include "tinyxml2/tinyxml2.h"

class Bestiary : public cocos2d::Layer
{
private:
	cocos2d::Size m_visibleSize;
	float m_mag;
	const int MAX_NUM_MONSTERS = 31;

	cocos2d::ui::ScrollView* m_bestiaryScroll;

	bool m_isOnDesc;
	
	cocos2d::DrawNode* m_border;
	cocos2d::Node* m_descNode;
	cocos2d::Sprite* m_descBG;

	tinyxml2::XMLDocument doc;
	tinyxml2::XMLDocument mData;

public:
	static cocos2d::Scene* createScene();
	virtual bool init() override;

	void setBackBtn();
	void displayBG();
	void createBestiary();

	void returnCallback(cocos2d::Ref *pSender);
	void showDesc(cocos2d::Ref *pSender, int monsterNum);

	CREATE_FUNC(Bestiary);
};

#endif //__MillionCode__Bestiary__