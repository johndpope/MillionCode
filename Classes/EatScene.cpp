 //
//  EatScene.cpp
//  MillionCode
//
//  Created by 木村巧 on 2015/04/25.
//
//

#include "EatScene.h"
#include "MenuScene.h"

using namespace cocos2d;
using namespace std;

enum SpriteTags
{
    e_BG,
    e_BackBtn,
    e_Monster,
    e_Food,
    e_TapFont,
    e_ViewHp,
    e_ViewAtk,
    e_ViewDef,
    e_ViewDex,
    e_HpUp,
    e_AtkUp,
    e_DefUp,
    e_DexUp,
    e_Num
};

Scene* EatScene::createScene() {
    auto scene = Scene::create();
    auto layer = EatScene::create();
    scene->addChild(layer);
    return scene;
}

bool EatScene::init() {
    if ( !Layer::init() ) { return false; }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    m_Mag = Generic::getScreenMagnification(visibleSize);
    
    
    this->setUi();
    
    return true;
}

void EatScene::setUi() {
    // 背景画像
    Sprite* bg = Sprite::create("img/BG/menu.png");
    {
        bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
        bg->setScale(m_Mag);
        bg->setTag(SpriteTags::e_BG);
        this->addChild(bg);
    }
    
    MenuItemImage *pCloseItem = MenuItemImage::create("img/UI/menu/UI_M_009.png",
                                                      "img/UI/menu/UI_M_010.png",
                                                      CC_CALLBACK_1(EatScene::menuReturnCallback, this));
    
    pCloseItem->setPosition(Vec2(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));
    pCloseItem->setTag(SpriteTags::e_BackBtn);
    // create menu, it's an autorelease object
    Menu* pMenu = Menu::create(pCloseItem, NULL);
    pMenu->setPosition(Point::ZERO);
    this->addChild(pMenu);
}


void EatScene::menuReturnCallback(cocos2d::Ref *pSender)
{
    auto nextScene = MenuScene::createScene();
    auto pScene = TransitionFade::create(0.5f, nextScene);
    Director::getInstance()->replaceScene(pScene);
}
