#include "CheckScene.h"
#include "MenuScene.h"

using namespace cocos2d;
using namespace std;

enum SpriteTags
{
    BackGround,
    ReturnBtn,
    Monster,
};

Scene* CheckScene::createScene() 
{
    auto scene = Scene::create();
    auto layer = CheckScene::create();
    scene->addChild(layer);
    return scene;
}

bool CheckScene::init() 
{
    if ( !Layer::init() ) { return false; }
    
	//variable initialization
    m_VisibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    m_Mag = Generic::getScreenMagnification(m_VisibleSize);
	m_btnIsReady = false;
	m_onSubmenu = false;
	m_monsterName = nullptr;
	m_changeMenu = nullptr;
	m_changeIntruction = nullptr;
	m_live2dMonster = nullptr;
	m_name = nullptr;
	m_HP = nullptr;
	m_Special = nullptr;
	m_wins = nullptr;
	m_denyalMsg = nullptr;
	for (int i = 0; i < 3; i++)
	{
		m_selectedMon[i] = false;
		m_isPressed[i] = false;
		m_isMonPressed[i] = false;
	}
	m_selectedMon[0] = true;

	
	displayBG();
    setUi();
    setMonster();
	animateMonsters(0);
	eventHandler();
    
    return true;
}

void CheckScene::setUi()
{
	//Back Button
	string btn = "img/UI/menu/UI_M_009.png";
	string pushBtn = "img/UI/menu/UI_M_010.png";

	auto btnItem = MenuItemImage::create(btn.c_str(),
		pushBtn.c_str(),
		CC_CALLBACK_1(CheckScene::menuReturnCallback, this));
	btnItem->setScale(m_Mag * 1.1);
	btnItem->setTag(SpriteTags::ReturnBtn);
	Menu* rtnBtn = Menu::create(btnItem, NULL);
	rtnBtn->setPosition(Vec2(origin.x + m_VisibleSize.width - btnItem->getContentSize().width / 2,
		origin.y + btnItem->getContentSize().height / 2));
	this->addChild(rtnBtn);

	//change order button
	m_changeBtn = Sprite::create("img/UI/status/change.png");
	this->addChild(m_changeBtn);
	m_changeBtn->setScale(m_Mag * 0.9f);
	m_changeBtn->setColor(Color3B(220, 220, 220));
	m_changeBtn->setZOrder(100);
	buttonWidth = m_changeBtn->getBoundingBox().getMaxX();
	m_changeBtn->setPosition(Vec2(-m_changeBtn->getBoundingBox().getMaxX(), m_VisibleSize.height - m_changeBtn->getBoundingBox().getMaxY()));
	
	//check status button
	m_statusBtn = Sprite::create("img/UI/status/status.png");
	m_statusBtn->setScale(m_Mag*0.9f);
	m_statusBtn->setColor(Color3B(220, 220, 220));
	m_statusBtn->setZOrder(100);
	m_statusBtn->setPosition(Vec2(m_VisibleSize.width + m_statusBtn->getBoundingBox().getMaxX() + 47, m_VisibleSize.height - m_statusBtn->getBoundingBox().getMaxY()));
	this->addChild(m_statusBtn);
	
	//reset status button
	m_resetBtn = Sprite::create("img/UI/status/reset.png");
	m_resetBtn->setScale(m_Mag*0.9f);
	m_resetBtn->setColor(Color3B(220, 220, 220));
	m_resetBtn->setZOrder(100);
	m_resetBtn->setPosition(Vec2(-m_resetBtn->getBoundingBox().getMaxX() - 48, m_resetBtn->getBoundingBox().getMaxY()));
	m_resetBtn->setVisible(false);
	this->addChild(m_resetBtn);
	
	resetMenu();
}

void CheckScene::eventHandler()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(CheckScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(CheckScene::onTouchEnded, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void CheckScene::resetMenu()
{
	m_btnIsReady = false;
	auto width = m_changeBtn->getBoundingBox().getMaxX();
	auto changeMove = MoveTo::create(0.5f, Vec2(origin.x + buttonWidth - 47, m_changeBtn->getPositionY()));
	m_changeBtn->runAction(changeMove);

	auto statusMove = MoveBy::create(0.5f, Vec2(m_VisibleSize.width - m_statusBtn->getBoundingBox().getMaxX() + 47, m_VisibleSize.height - m_statusBtn->getBoundingBox().getMaxY()));
	m_statusBtn->runAction(statusMove);

	auto resetMove = MoveTo::create(0.5f, Vec2(origin.x +  buttonWidth - 48, m_resetBtn->getPositionY()));
	auto enable = CallFunc::create([this](){this->enableButtons(); });
	m_resetBtn->runAction(Sequence::create( resetMove, enable, NULL));
}

void CheckScene::enableButtons()
{
	m_btnIsReady = true;
}

void CheckScene::displayBG()
{
	auto bbg = Sprite::create("img/BG/menu.png");

	bbg->setPosition(Vec2(m_VisibleSize.width / 2, m_VisibleSize.height / 2));
	bbg->setScale(m_Mag);
	bbg->setTag(SpriteTags::BackGround);
	bbg->setZOrder(-100);
	this->addChild(bbg);

	//Moving BG
	Sprite* bg = Sprite::create("img/BG/MenuBG/main_00000.png");
	bg->setOpacity(100);
	bg->setZOrder(-90);
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
	//sprite->setColor(Color3B(100,100,100));
	bg->runAction(Animate::create(anim));
	bg->setPosition(Vec2(m_VisibleSize.width / 2, m_VisibleSize.height / 2));
	bg->setScale(m_Mag * 1.4);
	//bg->setOpacity(80);
	this->addChild(bg);
}

bool CheckScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* eventt)
{
	if (m_btnIsReady && !m_onSubmenu)
	{
		Rect touchPoint = Rect(touch->getLocation().x, touch->getLocation().y, 2, 2);

		Sprite* buttonArray[3] = { m_changeBtn, m_statusBtn, m_resetBtn };
		for (int i = 0; i < 3; i++)
		{
			if (touchPoint.intersectsRect(buttonArray[i]->getBoundingBox()))
			{
				m_isPressed[i] = true;
				buttonArray[i]->setColor(Color3B(100, 100, 100));
			}
			if (touchPoint.intersectsRect(monsterSlot[i]->getBoundingBox()))
			{
				if (!m_selectedMon[i])
				{
					if (m_selectedMon[0])
					{
						if (i == 1)
						{
							m_isMonPressed[i] = true;
						}
					}
					else if (m_selectedMon[2])
					{
						if (i == 1)
						{
							m_isMonPressed[i] = true;
						}
					}
					else
					{
						m_isMonPressed[i] = true;
					}
				}
			}
		}
	}

	return true;
}

void CheckScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* eventt)
{

	Rect touchPoint = Rect(touch->getLocation().x, touch->getLocation().y, 2, 2);
	Sprite* buttonArray[3] = { m_changeBtn, m_statusBtn, m_resetBtn };
	if (!m_onSubmenu)
	{
		for (int i = 0; i < 3; i++)
		{
			if (m_isPressed[i])
			{
				buttonArray[i]->setColor(Color3B(255, 255, 255));
				m_onSubmenu = true;
				animateButtons(i);

				int currentMonster = 0;
				for (int j = 0; j < 3; j++)
				{
					if (m_selectedMon[j])
						currentMonster = j;
				}

				switch (i)
				{
				case STATUS_OPTION:
					statsView(currentMonster);
					break;
				case CHANGE_OPTION:
					changeOrder(currentMonster);
					break;
				case RESET_OPTION:
					resetStats(currentMonster);
					break;
				default:
					break;
				}
			}
			else
				buttonArray[i]->setColor(Color3B(220, 220, 220));

			if (m_isMonPressed[i])
			{
				animateMonsters(i);
				for (int j = 0; j < 3; j++)
				{
					if (j != i)
					{
						m_selectedMon[j] = false;
					}
				}
				m_selectedMon[i] = true;
			}

			m_isMonPressed[i] = false;
			m_isPressed[i] = false;
		}
	}
}

void CheckScene::setMonster()
{
	auto fileU = FileUtils::getInstance();
	auto fileContent = fileU->getStringFromFile("data/animData.xml");
	doc.Parse(fileContent.c_str());
	UserDefault* def = UserDefault::getInstance();

	for (int i = 0; i < 3; i++)
	{
		int key = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eMonsterData01 + i].c_str());
		auto monsterName = MonsterNameData[key];
		auto spritePath = doc.FirstChildElement()->FirstChildElement(monsterName.c_str())->FirstChildElement("spriteList")->FirstChildElement("animation")->FirstChildElement("stand")->GetText();
		monsterSlot[i] = Sprite::create(spritePath);
		monsterSlot[i]->setScale(m_Mag*0.8);
		monsterSlot[i]->setZOrder(-10);
		switch (i)
		{
		case 0:
			monsterSlot[i]->setPosition(Vec2(m_VisibleSize.width / 6, m_VisibleSize.height / 2.0f));
			break;
		case 1:
			monsterSlot[i]->setPosition(Vec2((m_VisibleSize.width * 3) / 6, m_VisibleSize.height / 2.0f));
			break;
		case 2:
			monsterSlot[i]->setPosition(Vec2((m_VisibleSize.width * 5) / 6, m_VisibleSize.height / 2.0f));
			break;
		default:
			break;
		}
		this->addChild(monsterSlot[i]);
	}
}

void CheckScene::animateButtons(int option)
{
	//cOp = Change Option
	auto cOpChangeMove = MoveTo::create(0.5f, Vec2(m_VisibleSize.width / 2, m_changeBtn->getPositionY()));
	auto cOpStatusMove = MoveBy::create(0.5f, Vec2(350, 0));
	auto cOpResetMove = MoveBy::create(0.5f, Vec2(-350, 0));

	//sOp = Status Option
	auto sOpChangeMove = MoveBy::create(0.5f, Vec2(-350, 0));
	auto sOpStatusMove = MoveTo::create(0.5f, Vec2(m_VisibleSize.width / 2, m_statusBtn->getPositionY()));
	auto sOpResetMove = MoveBy::create(0.5f, Vec2(-350, 0));

	//rOp = Reset Option
	auto rOpChangeMove = MoveBy::create(0.5f, Vec2(-350, 0));
	auto rOpStatusMove = MoveBy::create(0.5f, Vec2(350, 0));
	auto rOpResetMove = MoveTo::create(0.5f, Vec2(m_VisibleSize.width/2, m_resetBtn->getPositionY()));

	auto enable = CallFunc::create([this](){this->enableButtons(); });

	m_btnIsReady = false;
	switch (option)
	{
	case CHANGE_OPTION:
		m_changeBtn->runAction(cOpChangeMove);
		m_statusBtn->runAction(cOpStatusMove);
		m_resetBtn->runAction(Sequence::create(cOpResetMove, enable, NULL));
		break;
	case STATUS_OPTION:
		m_changeBtn->runAction(sOpChangeMove);
		m_statusBtn->runAction(sOpStatusMove);
		m_resetBtn->runAction(Sequence::create(sOpResetMove, enable, NULL));
		break;
	case RESET_OPTION:
		m_changeBtn->runAction(rOpChangeMove);
		m_statusBtn->runAction(rOpStatusMove);
		m_resetBtn->runAction(Sequence::create(rOpResetMove, enable, NULL));
		break;
	default:
		break;
	}
}

void CheckScene::animateMonsters(int option)
{
	//-----------------------------------------------------------------------
	//monster animation
	//-----------------------------------------------------------------------

	float animationTime = 0.3f;
	float smallScale = 0.75f;
	float largeScale = 1.5f;
	float baseScale = m_Mag*0.8;

	auto fOpFMove = MoveTo::create(animationTime, Vec2(m_VisibleSize.width / 2, m_VisibleSize.height / 2));
	auto fOpFScale = ScaleBy::create(animationTime, largeScale);
	auto fOpSMove = MoveTo::create(animationTime, Vec2((m_VisibleSize.width * 5) / 6, m_VisibleSize.height / 2));
	auto fOpSScale = ScaleTo::create(animationTime, baseScale);
	auto fOpTMove = MoveTo::create(animationTime, Vec2(m_VisibleSize.width, m_VisibleSize.height / 2));
	auto fOpTScale = ScaleBy::create(animationTime, smallScale);

	auto sOpFMove = MoveTo::create(animationTime, Vec2(m_VisibleSize.width / 6, m_VisibleSize.height / 2));
	auto sOpFScale = ScaleTo::create(animationTime, baseScale);
	auto sOpSMove = MoveTo::create(animationTime, Vec2(m_VisibleSize.width / 2, m_VisibleSize.height / 2));
	auto sOpSScale = ScaleBy::create(animationTime, largeScale);
	auto sOpTMove = MoveTo::create(animationTime, Vec2((m_VisibleSize.width * 5) / 6, m_VisibleSize.height / 2.0f));
	auto sOpTScale = ScaleTo::create(animationTime, baseScale);

	auto tOpFMove = MoveTo::create(animationTime, Vec2(0, m_VisibleSize.height / 2));
	auto tOpFScale = ScaleBy::create(animationTime, smallScale);
	auto tOpSMove = MoveTo::create(animationTime, Vec2(m_VisibleSize.width / 6, m_VisibleSize.height / 2.0f));
	auto tOpSScale = ScaleTo::create(animationTime, baseScale);
	auto tOpTMove = MoveTo::create(animationTime, Vec2(m_VisibleSize.width / 2, m_VisibleSize.height / 2));
	auto tOpTScale = ScaleBy::create(animationTime, largeScale);

	m_btnIsReady = false;

	auto enable = CallFunc::create([this](){this->enableButtons(); });

	switch (option)
	{
	case FIRST_MONSTER:
		monsterSlot[0]->setZOrder(-1);
		monsterSlot[0]->runAction(Spawn::create(fOpFMove, fOpFScale, NULL));
		monsterSlot[1]->runAction(Spawn::create(fOpSMove, fOpSScale, NULL));
		monsterSlot[2]->runAction(Sequence::create(Spawn::create(fOpTMove, fOpTScale, NULL), enable, NULL));
		break;
	case SECOND_MONSTER:
		monsterSlot[1]->setZOrder(-1);
		monsterSlot[0]->runAction(Spawn::create(sOpFMove, sOpFScale, NULL));
		monsterSlot[1]->runAction(Spawn::create(sOpSMove, sOpSScale, NULL));
		monsterSlot[2]->runAction(Sequence::create(Spawn::create(sOpTMove, sOpTScale, NULL), enable, NULL));
		break;
	case THIRD_MONSTER:
		monsterSlot[2]->setZOrder(-1);
		monsterSlot[0]->runAction(Spawn::create(tOpFMove, tOpFScale, NULL));
		monsterSlot[1]->runAction(Spawn::create(tOpSMove, tOpSScale, NULL));
		monsterSlot[2]->runAction(Sequence::create(Spawn::create(tOpTMove, tOpTScale, NULL), enable, NULL));
		break;
	default:
		break;
	}

	for (int i = 0; i < 3; i++)
	{
		if (i != option)
		{
			monsterSlot[i]->setZOrder(-10);
		}
		if (option != 2)
		{
			monsterSlot[2]->setZOrder(-11);
		}
	}

	//-----------------------------------------------------------------------
	//display monster name
	//-----------------------------------------------------------------------

	if (m_monsterName != nullptr)
	{
		this->removeChild(m_monsterName);
	}

	auto fileU = FileUtils::getInstance();
	auto fileContent = fileU->getStringFromFile("data/monsterData.xml");
	UserDefault* def = UserDefault::getInstance();
	doc.Parse(fileContent.c_str());
	
	int key = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eMonsterData01 + option].c_str());
	auto monsterName = MonsterNameData[key];

	auto name = doc.FirstChildElement()->FirstChildElement(monsterName.c_str())->FirstChildElement("name")->GetText();

	m_monsterName = Label::createWithTTF(name, "fonts/ant-maru.ttf", 55);
	m_monsterName->enableOutline(Color4B::BLACK, 2);
	m_monsterName->setPosition(Vec2(m_VisibleSize.width / 2, m_VisibleSize.height / 1.07f));
	this->addChild(m_monsterName);
}

void CheckScene::statsView(int selectedMonster)
{
	m_monsterName->setVisible(false);
	for (int i = 0; i < 3; i++)
	{
		monsterSlot[i]->setVisible(false);
	}

	//----------------------------------------------------------------------
	//live 2d Monster
	//----------------------------------------------------------------------

	UserDefault* def = UserDefault::getInstance();
	int key = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eMonsterData01 + selectedMonster].c_str());

	float scale;
	float posX;
	float posY;

	switch (key)
	{
	case 4:
		scale = 1.9f;
		posX = 1.4f;
		posY = 1.75f;
		break;
	case 14:
		scale = 1.0f;
		posX = 0.95f;
		posY = 0.9f;
		break;
	case 16:
		scale = 1.3f;
		posX = 1.1f;
		posY = 1.2f;
		break;
	case 17:
		scale = 1.2f;
		posX = 1.0f;
		posY = 1.1f;
		break;
	case 18:
		scale = 0.5f;
		posX = 0.5f;
		posY = 1.0f;
		break;
	default:
		scale = 1.2f;
		posX = 1.0f;
		posY = 1.2f;
		break;
	}

	m_live2dMonster = Live2DSprite::createDrawNode(MonsterNameData[key], scale, scale, posX, posY);

	m_live2dMonster->setVisible(false);

	auto wait = FadeIn::create(0.5f);
	auto show = Show::create();
	this->addChild(m_live2dMonster);
	m_live2dMonster->runAction(Sequence::create(wait, show, NULL));

	//----------------------------------------------------------------------
	//Stats
	//----------------------------------------------------------------------
	auto fileU = FileUtils::getInstance();
	auto fileContent = fileU->getStringFromFile("data/monsterData.xml");
	doc.Parse(fileContent.c_str());

	int nameKey = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eMonsterData01 + selectedMonster].c_str());
	auto monsterName = MonsterNameData[nameKey];
	auto name = doc.FirstChildElement()->FirstChildElement(monsterName.c_str())->FirstChildElement("name")->GetText();
	auto hp = doc.FirstChildElement()->FirstChildElement(monsterName.c_str())->FirstChildElement("HP")->GetText();
	string hpText = hp;
	hpText = "HP: " + hpText;
	auto type = doc.FirstChildElement()->FirstChildElement(monsterName.c_str())->FirstChildElement("special")->FirstChildElement("type")->GetText();
	string::size_type sz;
	int inNum = atoi(type);
	string typeText = "";
	if (inNum == 0)
	{
		typeText = "グー";
	}
	else if (inNum == 1)
	{
		typeText = "チョキ";
	}
	else if (inNum == 2)
	{
		typeText = "パー";
	}
	auto level = doc.FirstChildElement()->FirstChildElement(monsterName.c_str())->FirstChildElement("special")->FirstChildElement("level")->GetText();
	inNum = atoi(level);
	if (inNum == 0)
	{
		typeText = "ノーマル・" + typeText;
	}
	else if (inNum == 1)
	{
		typeText = "スーパー・" + typeText;
	}
	else if (inNum == 2)
	{
		typeText = "ウルトラ・" + typeText;
	}
	auto win = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eMonster1Exp + selectedMonster].c_str());
	string winText = Generic::intToStrnig(win);
	winText = "経験値： " + winText;

	m_name = Label::createWithTTF(name, "fonts/ant-maru.ttf", 65);
	m_name->enableOutline(Color4B::BLACK, 2);
	m_name->setPosition(Vec2(m_VisibleSize.width * 1.5, (m_VisibleSize.height * 4.5) / 6));
	this->addChild(m_name);

	m_HP = Label::createWithTTF(hpText, "fonts/ant-maru.ttf", 55);
	m_HP->enableOutline(Color4B::BLACK, 2);
	m_HP->setPosition(Vec2((m_VisibleSize.width * 1.5), (m_VisibleSize.height * 3.5) / 6));
	this->addChild(m_HP);

	m_Special = Label::createWithTTF(typeText, "fonts/ant-maru.ttf", 60);
	m_Special->enableOutline(Color4B::BLACK, 2);
	m_Special->setPosition(Vec2((m_VisibleSize.width * 1.5), (m_VisibleSize.height * 2.5) / 6));
	this->addChild(m_Special);

	m_wins = Label::createWithTTF(winText, "fonts/ant-maru.ttf", 55);
	m_wins->enableOutline(Color4B::BLACK, 2);
	m_wins->setPosition(Vec2((m_VisibleSize.width * 1.5), (m_VisibleSize.height * 1.5) / 6));
	this->addChild(m_wins);

	auto nameMove = MoveTo::create(0.5f, Vec2((m_VisibleSize.width * 4.5f) / 6, (m_VisibleSize.height * 4.5) / 6));
	auto hpMove = MoveTo::create(0.5f, Vec2((m_VisibleSize.width * 4.5f) / 6, (m_VisibleSize.height * 3.5) / 6));
	auto specialMove = MoveTo::create(0.5f, Vec2((m_VisibleSize.width * 4.5f) / 6, (m_VisibleSize.height * 2.5) / 6));
	auto winMove = MoveTo::create(0.5f, Vec2((m_VisibleSize.width * 4.5f) / 6, (m_VisibleSize.height * 1.5) / 6));

	m_name->runAction(nameMove);
	m_HP->runAction(hpMove);
	m_Special->runAction(specialMove);
	m_wins->runAction(winMove);
}

void CheckScene::changeOrder(int selectedMonster)
{
	for (int i = 0; i < 3; i++)
	{
		monsterSlot[i]->setVisible(false);
	}
	m_monsterName->setVisible(false);
	monsterSlot[selectedMonster]->setVisible(true);
	monsterSlot[selectedMonster]->setColor(Color3B(100, 100, 100));

	if (selectedMonster == 2)
		monsterSlot[selectedMonster]->runAction(MoveTo::create(0.5f, Vec2((m_VisibleSize.width * 5)/ 6, m_VisibleSize.height / 2)));
	else if (selectedMonster == 0)
		monsterSlot[selectedMonster]->runAction(MoveTo::create(0.5f, Vec2(m_VisibleSize.width / 6, m_VisibleSize.height / 2)));

	//-------------------------------------------------------------------------------
	//Monster selection
	//-------------------------------------------------------------------------------
	
	int first = 0;
	int second = 0;

	if (selectedMonster == 0)
	{
		first = 1;
		second = 2;
	}
	else if (selectedMonster == 1)
	{
		first = 0;
		second = 2;
	}
	else
	{
		first = 0;
		second = 1;
	}
	auto fileU = FileUtils::getInstance();
	auto fileContent = fileU->getStringFromFile("data/animData.xml");
	doc.Parse(fileContent.c_str());
	UserDefault* def = UserDefault::getInstance();

	int key = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eMonsterData01 + first].c_str());
	auto monsterName = MonsterNameData[key];
	auto spritePath = doc.FirstChildElement()->FirstChildElement(monsterName.c_str())->FirstChildElement("spriteList")->FirstChildElement("animation")->FirstChildElement("stand")->GetText();
	
	monsterItem[0] = MenuItemImage::create(spritePath, spritePath, CC_CALLBACK_1(CheckScene::changeOrderCallback, this, first, 0, selectedMonster));
	monsterItem[0]->setScale(m_Mag );
	if (key == 0)
	{
		monsterItem[0]->setEnabled(false);
		monsterItem[0]->setColor(Color3B(255, 150, 150));
	}

	key = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eMonsterData01 + second].c_str());
	monsterName = MonsterNameData[key];
	spritePath = doc.FirstChildElement()->FirstChildElement(monsterName.c_str())->FirstChildElement("spriteList")->FirstChildElement("animation")->FirstChildElement("stand")->GetText();
	monsterItem[1] = MenuItemImage::create(spritePath, spritePath, CC_CALLBACK_1(CheckScene::changeOrderCallback, this, second, 1, selectedMonster));
	monsterItem[1]->setScale(m_Mag);
	if (key == 0)
	{
		monsterItem[1]->setEnabled(false);
		monsterItem[1]->setColor(Color3B(255, 150, 150));
	}

	switch (first)
	{
	case 0:
		monsterItem[0]->setPosition(Vec2(m_VisibleSize.width / 6, m_VisibleSize.height / 2));
		break;
	case 1:
		monsterItem[0]->setPosition(Vec2(m_VisibleSize.width / 2, m_VisibleSize.height / 2));
		break;
	case 2:
		monsterItem[0]->setPosition(Vec2((m_VisibleSize.width*5) / 6, m_VisibleSize.height / 2));
		break;
	default:
		break;
	}

	switch (second)
	{
	case 0:
		monsterItem[1]->setPosition(Vec2(m_VisibleSize.width / 6, m_VisibleSize.height / 2));
		break;
	case 1:
		monsterItem[1]->setPosition(Vec2(m_VisibleSize.width / 2, m_VisibleSize.height / 2));
		break;
	case 2:
		monsterItem[1]->setPosition(Vec2((m_VisibleSize.width * 5) / 6, m_VisibleSize.height / 2));
		break;
	default:
		break;
	}

	m_changeMenu = Menu::create(monsterItem[0], monsterItem[1], NULL);
	m_changeMenu->setPosition(Point::ZERO);
	this->addChild(m_changeMenu);
	
	//-------------------------------------------------------------------------------
	//show instructions
	//-------------------------------------------------------------------------------

	m_changeIntruction = Label::createWithTTF("入れ替えるモンスターを選択してください。", "fonts/ant-maru.ttf", 50);
	m_changeIntruction->enableOutline(Color4B::BLACK, 2);
	m_changeIntruction->setPosition(Vec2(m_VisibleSize.width / 2, m_VisibleSize.height / 10.0f));
	this->addChild(m_changeIntruction);
}

void CheckScene::resetStats(int selectedMonster)
{
	m_monsterName->setVisible(false);
}

void CheckScene::changeOrderCallback(cocos2d::Ref *pSender, int option, int slot, int current)
{
	UserDefault* def = UserDefault::getInstance();
	int monsterNum1;
	int monsterNum2;
	int winNum1;
	int winNum2;

	int tmp;
	for (int i = 0; i < 3; i++)
	{
		if (m_selectedMon[i])
		{
			tmp = i;
		}
	}

	monsterNum1 = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eMonsterData01 + tmp].c_str());
	monsterNum2 = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eMonsterData01 + option].c_str());
	def->setIntegerForKey(SaveDataKey[n_DataKeyNum::eMonsterData01 + tmp].c_str(), monsterNum2);
	def->setIntegerForKey(SaveDataKey[n_DataKeyNum::eMonsterData01 + option].c_str(), monsterNum1);

	winNum1 = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eMonster1Exp + tmp].c_str());
	winNum2 = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eMonster1Exp + option].c_str());
	def->setIntegerForKey(SaveDataKey[n_DataKeyNum::eMonster1Exp + tmp].c_str(), winNum2);
	def->setIntegerForKey(SaveDataKey[n_DataKeyNum::eMonster1Exp + option].c_str(), winNum1);

	def->flush();

	monsterItem[slot]->runAction(MoveTo::create(0.5f, Vec2(monsterSlot[current]->getPosition())));

	auto nextScene = MenuScene::createScene();
	auto pScene = TransitionFade::create(0.5f, nextScene);
	auto exit = CallFunc::create([this](){this->exitScene(); });
	
	auto waiter = Node::create();
	auto wait = FadeIn::create(0.5f);
	auto moveMonster = MoveTo::create(0.5f, Vec2(monsterItem[slot]->getPosition()));

	monsterSlot[current]->runAction(Sequence::create(moveMonster, wait, exit, NULL));
}

void CheckScene::exitScene()
{
	auto nextScene = MenuScene::createScene();
	auto pScene = TransitionFade::create(0.5f, nextScene);
	Director::getInstance()->replaceScene(pScene);
}

void CheckScene::menuReturnCallback(cocos2d::Ref *pSender)
{
	if (!m_onSubmenu)
	{
		auto nextScene = MenuScene::createScene();
		auto pScene = TransitionFade::create(0.5f, nextScene);
		Director::getInstance()->replaceScene(pScene);
	}
	else
	{
		m_changeBtn->setColor(Color3B(220, 220, 220));
		m_statusBtn->setColor(Color3B(220, 220, 220));
		m_resetBtn->setColor(Color3B(220, 220, 220));
		resetMenu();
		int currentMonster;
		for (int i = 0; i < 3; i++)
		{
			monsterSlot[i]->setVisible(true);
			monsterSlot[i]->setColor(Color3B::WHITE);
			for (int j = 0; j < 3; j++)
			{
				if (m_selectedMon[j])
				{
					currentMonster = j;
				}
			}
		}
		monsterSlot[currentMonster]->runAction(MoveTo::create(0.5f, Vec2(m_VisibleSize.width / 2, m_VisibleSize.height/2)));
		m_monsterName->setVisible(true);
		m_onSubmenu = false;

		if (m_changeMenu != nullptr)
		{
			this->removeChild(m_changeMenu);
		}
		if (m_changeIntruction != nullptr)
		{
			this->removeChild(m_changeIntruction);
		}
		if (m_live2dMonster != nullptr)
		{
			this->removeChild(m_live2dMonster);
		}
		if (m_name != nullptr)
		{
			this->removeChild(m_name);
		}
		if (m_HP != nullptr)
		{
			this->removeChild(m_HP);
		}
		if (m_Special != nullptr)
		{
			this->removeChild(m_Special);
		}
		if (m_wins != nullptr)
		{
			this->removeChild(m_wins);
		}
	}
}
