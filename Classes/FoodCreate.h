#ifndef __MillionCode__FoodCreate__
#define __MillionCode__FoodCreate__

#include <cocos2d.h>
#include <iostream>
#include "Generic.h"

class FoodCreate : public cocos2d::Layer
{
private:
    float m_Mag;
    cocos2d::Size m_VisibleSize;
    bool m_IsActiv;
    bool m_IsMakeEnd;
    
    std::string m_data;
    char *m_seed;
    
    cocos2d::Sprite *m_TapFont;
    
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    virtual void update(float delta);
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
    void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
    
    
    void make(void);
    void sprite(void);
    
    static void setSeed(const char* seedData);
    static int countBit(const char* data);
    
    // implement the "static node()" method manually
    CREATE_FUNC(FoodCreate);
};


#endif /* defined(__MillionCode__FoodCreate__) */
