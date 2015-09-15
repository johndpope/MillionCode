//
//  EatScene.h
//  MillionCode
//
//  Created by 木村巧 on 2015/04/25.
//
//

#ifndef __MillionCode__EatScene__
#define __MillionCode__EatScene__

#include <cocos2d.h>
#include "Generic.h"
#include "DataKey.h"
class EatScene : public cocos2d::Layer
{
private:
    float m_Mag;
    cocos2d::Size visibleSize;
    cocos2d::Point origin;
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    void menuReturnCallback(cocos2d::Ref* pSender);
    
    void setUi();
    
    // プレイヤーのモンスター画像を表示
    
    
    // タッチ処理
    //    virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
    //    virtual void ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
    
    // implement the "static node()" method manually
    CREATE_FUNC(EatScene);
    
};


#endif /* defined(__MillionCode__EatScene__) */
