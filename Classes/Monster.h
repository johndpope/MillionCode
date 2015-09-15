#ifndef __MillionCode__Monster__
#define __MillionCode__Monster__

#include <cocos2d.h>
#include "Generic.h"
#include "MonsterData.h"

namespace n_Monster {
    enum ImgNum
    {
        e_Stand,
        e_Damage,
        e_Attack00,
        e_Attack01,
        e_Num
    };
}


class Monster : public cocos2d::Node
{
public:
    
    bool initWithFile(const char* fileName, int num);
    bool initWithPlayer(const char* fileName, int num);
    
    
    static Monster* create(const char* fileName, int num);
    static Monster* createPlayer(const char* fileName, int num);
    static Monster* createEnemy(const char* race);
    
    
    void addScene(cocos2d::Node* scene);
    void addScene(cocos2d::Node* scene, int tag);
    void addScene(cocos2d::Node* scene, int zOrder, int tag);
    
    
    void setTexture(const char* fileName, int num);
    void setPlayerTexture(const char* fileName, int num);
    
    
    void setPosition(const cocos2d::Point &pos);
    
    cocos2d::Point getPos();
    
    
    cocos2d::Size getContentSize();
    
    
    void setScale(float fScale);
    void setScaleX(float fScaleX);
    void setScaleY(float fScaleY);
    
private:
    cocos2d::Sprite* m_Sprite;
};


#endif /* defined(__MillionCode__Monster__) */
