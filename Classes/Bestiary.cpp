#include "Bestiary.h"
#include "MenuScene.h"
#include "DataKey.h"
#include "MonsterEqData.h"

using namespace cocos2d;
using namespace ui;

Scene* Bestiary::createScene()
{
	auto scene = Scene::create();
	auto layer = Bestiary::create();
	scene->addChild(layer);
	return scene;
}

bool Bestiary::init()
{
	if (!Layer::init())
	{
		return false;
	}

	m_visibleSize = Director::getInstance()->getVisibleSize();
	m_mag = Generic::getScreenMagnification(m_visibleSize);
	m_descNode = nullptr;
	m_isOnDesc = false;

	displayBG();
	createBestiary();
	setBackBtn();
	
	return true;
}

void Bestiary::setBackBtn()
{
	//Back Button
	string btn = "img/UI/menu/UI_B_005.png";
	string pushBtn = "img/UI/menu/UI_B_005.png";

	auto btnItem = MenuItemImage::create(btn.c_str(),
		pushBtn.c_str(),
		CC_CALLBACK_1(Bestiary::returnCallback, this));
	btnItem->setScale(m_mag*1.5f);
	btnItem->setPosition(Vec2(m_visibleSize.width - btnItem->getBoundingBox().getMaxX(),
		btnItem->getBoundingBox().getMaxY()));
	Menu* rtnBtn = Menu::create(btnItem, NULL);
	rtnBtn->setPosition(Point::ZERO);
	this->addChild(rtnBtn);
}

void Bestiary::returnCallback(cocos2d::Ref *pSender)
{
	if (m_isOnDesc)
	{
		//m_border->setVisible(true);
		m_bestiaryScroll->setVisible(true);
		if (m_descNode != nullptr)
		{
			this->removeChild(m_descNode);
		}
		m_isOnDesc = false;
	}
	else
	{
		auto nextScene = MenuScene::createScene();
		auto pScene = TransitionFade::create(0.5f, nextScene);
		Director::getInstance()->replaceScene(pScene);
	}
	
}

void Bestiary::displayBG()
{
	auto bbg = Sprite::create("img/BG/menu.png");

	bbg->setPosition(Vec2(m_visibleSize.width / 2, m_visibleSize.height / 2));
	bbg->setScale(m_mag);
	bbg->setZOrder(-10);
	this->addChild(bbg);

	//Moving BG
	Sprite* bg = Sprite::create("img/BG/MenuBG/main_00000.png");
	bg->setOpacity(100);
	bg->setZOrder(-9);
	Animation* anim = Animation::create();

	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00001.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00002.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00003.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00004.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00005.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00006.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00007.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00008.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00009.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00010.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00011.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00012.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00013.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00014.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00015.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00016.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00017.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00018.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00019.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00020.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00021.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00022.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00023.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00024.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00025.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00026.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00027.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00028.png");
	anim->addSpriteFrameWithFileName("img/BG/MenuBG/main_00029.png");

	anim->setLoops(-1);
	anim->setDelayPerUnit(0.1f);
	bg->runAction(Animate::create(anim));
	bg->setPosition(Vec2(m_visibleSize.width / 2, m_visibleSize.height / 2));
	bg->setScale(m_mag * 1.4);
	//bg->setOpacity(80);
	this->addChild(bg);
}

void Bestiary::createBestiary()
{
	//border
	m_border = DrawNode::create();
	m_border->drawSolidRect(Vec2(m_visibleSize.width / 10, m_visibleSize.height * 9.1 / 10), Vec2(m_visibleSize.width * 9 / 10, m_visibleSize.height * 0.9  / 10), Color4F::BLACK);
	//this->addChild(m_border);

	//scroll creation
	int numberOfRows = ceil(MAX_NUM_MONSTERS / 4);
	m_bestiaryScroll = ScrollView::create();
	m_bestiaryScroll->setContentSize(Size(m_visibleSize.width / 1.3f, m_visibleSize.height / 1.3));
	float squareDimention = m_bestiaryScroll->getContentSize().width / 4;
	m_bestiaryScroll->setInnerContainerSize(Size(m_visibleSize.width / 1.3f, squareDimention * 8));
	m_bestiaryScroll->setAnchorPoint(Vec2(0.5f, 0.5f));
	m_bestiaryScroll->setPosition(Vec2(m_visibleSize.width / 2, m_visibleSize.height / 2));
	m_bestiaryScroll->setDirection(ScrollView::Direction::VERTICAL);
	m_bestiaryScroll->setBackGroundColorType(LayoutBackGroundColorType::SOLID);
	m_bestiaryScroll->setBackGroundColor(Color3B(80, 140, 230));
	m_bestiaryScroll->setBackGroundColorOpacity(90);
	m_bestiaryScroll->setBounceEnabled(true);
	this->addChild(m_bestiaryScroll);

	//monster selection
	auto fileU = FileUtils::getInstance();
	auto fileContent = fileU->getStringFromFile("data/animData.xml");
	doc.Parse(fileContent.c_str());
	UserDefault* def = UserDefault::getInstance();

	int monsterNum = 0;

	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			if (monsterNum < MAX_NUM_MONSTERS)
			{
				auto monsterName = BestiaryNameData[monsterNum];
				auto basePath = doc.FirstChildElement()->FirstChildElement(monsterName.c_str())->FirstChildElement("spriteList")->FirstChildElement("animation")->FirstChildElement("stand")->GetText();
				auto button = Button::create(basePath);
				button->addClickEventListener(CC_CALLBACK_1(Bestiary::showDesc, this, monsterNum));
				button->setScale(m_mag*0.45);
				button->setAnchorPoint(Vec2(0, 1));
				button->setPosition(Vec2(i * squareDimention, m_bestiaryScroll->getInnerContainerSize().height - j * squareDimention));
				if (!def->getBoolForKey(SaveDataKey[n_DataKeyNum::eKnownData01 + monsterNum].c_str()))
				{
						button->setColor(Color3B::BLACK);
				}
				string text = Generic::intToStrnig(monsterNum + 1);
				if (monsterNum >= 10)
					text = "No.0" + text;
				else
					text = "No.00" + text;
				auto numberText = Label::createWithTTF(text, "fonts/ant-maru.ttf", 35);
				numberText->enableOutline(Color4B::BLACK, 1);
				numberText->setPosition(Vec2((i * squareDimention) + (squareDimention / 2), m_bestiaryScroll->getInnerContainerSize().height - (j * squareDimention) - squareDimention*0.85f));
				
				m_bestiaryScroll->addChild(button);
				m_bestiaryScroll->addChild(numberText);
			}

			monsterNum++;
		}
	}
}

void Bestiary::showDesc(cocos2d::Ref *pSender, int monsterNum)
{
	m_descNode = Node::create();

	m_bestiaryScroll->setVisible(false);
	//m_border->setVisible(false);
	m_isOnDesc = true;

	string name;
	string description;
	auto fileU = FileUtils::getInstance();
	auto fileContent = fileU->getStringFromFile("data/animData.xml");
	doc.Parse(fileContent.c_str());
	fileContent = fileU->getStringFromFile("data/monsterData.xml");
	mData.Parse(fileContent.c_str());
	UserDefault* def = UserDefault::getInstance();

	auto monsterName = BestiaryNameData[monsterNum];

	//------------------------------------------------------------------------------------
	//Monster BG effect
	//------------------------------------------------------------------------------------
	if (def->getBoolForKey(SaveDataKey[n_DataKeyNum::eKnownData01 + monsterNum].c_str()))
	{
		string cardType = mData.FirstChildElement()->FirstChildElement(monsterName.c_str())->FirstChildElement("special")->FirstChildElement("type")->GetText();
		if (cardType == "0")
		{
			m_descBG = Sprite::create("img/effect/effects/red/background_red_00000.png");
			//bg->setColor(Color3B(150, 150, 150));
			Animation* anim = Animation::create();

			anim->addSpriteFrameWithFileName("img/effect/effects/red/background_red_00001.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/red/background_red_00002.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/red/background_red_00003.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/red/background_red_00004.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/red/background_red_00005.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/red/background_red_00006.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/red/background_red_00007.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/red/background_red_00008.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/red/background_red_00009.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/red/background_red_00010.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/red/background_red_00011.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/red/background_red_00012.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/red/background_red_00013.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/red/background_red_00014.png");

			anim->setLoops(-1);
			anim->setDelayPerUnit(0.1f);
			//sprite->setColor(Color3B(100,100,100));
			m_descBG->runAction(Animate::create(anim));
			m_descBG->setPosition(Vec2(m_visibleSize.width / 2, m_visibleSize.height / 1.6));
			m_descBG->setScale(m_mag * 1.4);

			m_descNode->addChild(m_descBG);
		}
		else if (cardType == "1")
		{
			m_descBG = Sprite::create("img/effect/effects/yellow/background_Yellow_00000.png");
			//bg->setColor(Color3B(150, 150, 150));
			Animation* anim = Animation::create();

			anim->addSpriteFrameWithFileName("img/effect/effects/yellow/background_Yellow_00001.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/yellow/background_Yellow_00002.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/yellow/background_Yellow_00003.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/yellow/background_Yellow_00004.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/yellow/background_Yellow_00005.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/yellow/background_Yellow_00006.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/yellow/background_Yellow_00007.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/yellow/background_Yellow_00008.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/yellow/background_Yellow_00009.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/yellow/background_Yellow_00010.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/yellow/background_Yellow_00011.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/yellow/background_Yellow_00012.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/yellow/background_Yellow_00013.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/yellow/background_Yellow_00014.png");

			anim->setLoops(-1);
			anim->setDelayPerUnit(0.1f);
			//sprite->setColor(Color3B(100,100,100));
			m_descBG->runAction(Animate::create(anim));
			m_descBG->setPosition(Vec2(m_visibleSize.width / 2, m_visibleSize.height / 1.6));
			m_descBG->setScale(m_mag * 1.4);

			m_descNode->addChild(m_descBG);
		}
		else if (cardType == "2")
		{
			m_descBG = Sprite::create("img/effect/effects/blue/background_blue_00000.png");
			//bg->setColor(Color3B(150, 150, 150));
			Animation* anim = Animation::create();

			anim->addSpriteFrameWithFileName("img/effect/effects/blue/background_blue_00001.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/blue/background_blue_00002.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/blue/background_blue_00003.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/blue/background_blue_00004.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/blue/background_blue_00005.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/blue/background_blue_00006.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/blue/background_blue_00007.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/blue/background_blue_00008.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/blue/background_blue_00009.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/blue/background_blue_00010.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/blue/background_blue_00011.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/blue/background_blue_00012.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/blue/background_blue_00013.png");
			anim->addSpriteFrameWithFileName("img/effect/effects/blue/background_blue_00014.png");

			anim->setLoops(-1);
			anim->setDelayPerUnit(0.1f);
			//sprite->setColor(Color3B(100,100,100));
			m_descBG->runAction(Animate::create(anim));
			m_descBG->setPosition(Vec2(m_visibleSize.width / 2, m_visibleSize.height / 1.6));
			m_descBG->setScale(m_mag * 1.4);

			m_descNode->addChild(m_descBG);
		}
		
	}
	
	auto basePath = doc.FirstChildElement()->FirstChildElement(monsterName.c_str())->FirstChildElement("spriteList")->FirstChildElement("animation")->FirstChildElement("stand")->GetText();


	if (!def->getBoolForKey(SaveDataKey[n_DataKeyNum::eKnownData01 + monsterNum].c_str()))
	{
		auto monsterSprite = Sprite::create(basePath);
		monsterSprite->setScale(m_mag* 0.8);
		monsterSprite->setPosition(Vec2(m_visibleSize.width / 2, m_visibleSize.height / 1.45f));
		monsterSprite->setColor(Color3B::BLACK);
		name = "????";
		description = mData.FirstChildElement()->FirstChildElement(monsterName.c_str())->FirstChildElement("sDesc")->GetText();
		m_descNode->addChild(monsterSprite);
	}
	else
	{
		int key = monsterNum;

		float scale;
		float posX;
		float posY;

		switch (key)
		{
		case 4:
			scale = 1.0f;
			posX = 0.5f;
			posY = 1.25f;
			break;
		case 14:
			scale = 0.6f;
			posX = 0.3f;
			posY = 0.9f;
			break;
		case 16:
			scale = 0.55f;
			posX = 0.3f;
			posY = 0.85f;
			break;
		case 20:
			scale = 0.6f;
			posX = 0.3f;
			posY = 0.82f;
			break;
		default:
			scale = 0.6f;
			posX = 0.3f;
			posY = 0.9f;
			break;
		}

		auto pixie = Live2DSprite::createDrawNode(MonsterNameData[key], scale, scale, posX, posY);
		m_descNode->addChild(pixie);
		name = mData.FirstChildElement()->FirstChildElement(monsterName.c_str())->FirstChildElement("name")->GetText();
		description = mData.FirstChildElement()->FirstChildElement(monsterName.c_str())->FirstChildElement("lDesc")->GetText();
	}

	auto descRect = DrawNode::create();
	descRect->drawSolidRect(Vec2(m_visibleSize.width / 10.f, (m_visibleSize.height * 1) / 10.0f), Vec2((m_visibleSize.width * 9) / 10.f, (m_visibleSize.height) / 2.4f), Color4F(0, 0, 0, 90));
	descRect->setAnchorPoint(Vec2(0.5f, 0.5f));
	m_descNode->addChild(descRect);

	float textPosY = ( ((m_visibleSize.height) / 2.4f) - ((m_visibleSize.height * 1) / 10.0f * 2.5) );

	auto nameLabel = Label::createWithTTF(name, "fonts/ant-maru.ttf", 55);
	nameLabel->setPosition(Vec2(m_visibleSize.width * 2 / 10.f, m_visibleSize.height / 2.2));
	nameLabel->enableOutline(Color4B::BLACK, 2);
	m_descNode->addChild(nameLabel);


	auto descText = RichText::create();
	descText->ignoreContentAdaptWithSize(false);
	descText->setContentSize(Size(Vec2(800, 300)));
	descText->pushBackElement(RichElementText::create(0, Color3B::WHITE, 255, description, "fonts/ant-maru.ttf", 35));
	descText->setAnchorPoint(Vec2(0.5f, 0.5f));
	descText->setPosition(Vec2(m_visibleSize.width / 2, textPosY));
	
	m_descNode->addChild(descText);

	this->addChild(m_descNode);
}