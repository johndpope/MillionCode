#include "PickingPhase.h"

USING_NS_CC;

Picking::Picking(cocos2d::Layer* instance)
	:m_instance(instance),
	m_visibleSize(Director::getInstance()->getVisibleSize()),
	m_Mag(Generic::getScreenMagnification(m_visibleSize)),
	m_redutionCounter(0),
	eventOn(true),
	battleOn(false),
	m_battle(nullptr)
{
	for (int i = 0; i < 4; i++)
	{
		m_selected[i] = false;
	}
	loadData();
}

Picking::~Picking()
{
	if (m_battle != nullptr)
	{
		delete m_battle;
		m_battle = 0;
	}
}

void Picking::loadData()
{
	//preload images - called in constructor
	m_background = Sprite::create("img/BG/BattleBG/battleBg000.png");
}

void Picking::displayIcon()
{
	auto fileU = FileUtils::getInstance();
	auto fileContent = fileU->getStringFromFile("data/animData.xml");

	UserDefault* def = UserDefault::getInstance();
	int key = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eMonsterData01 + m_battleNum].c_str());

	doc.Parse(fileContent.c_str());
	fileContent = fileU->getStringFromFile("data/monsterData.xml");
	mData.Parse(fileContent.c_str());

	m_HP = atoi(mData.FirstChildElement()->FirstChildElement(MonsterNameData[key].c_str())->FirstChildElement("HP")->GetText());
	auto sprite = doc.FirstChildElement()->FirstChildElement(MonsterNameData[key].c_str());


	key = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eEnemyMonster01 + m_battleNum].c_str());
	m_enemyHP = atoi(mData.FirstChildElement()->FirstChildElement(MonsterNameData[key].c_str())->FirstChildElement("HP")->GetText());
	

	//cut image to fit inside frame
	m_iconSprite = Sprite::create(sprite->FirstChildElement("spriteList")->FirstChildElement("animation")->FirstChildElement("stand")->GetText());
	m_iconSprite->setScale(m_Mag * 1.5);
	m_iconSprite->setPosition(Vec2((m_visibleSize.width / 6) * 1.8, m_visibleSize.height / 2));
	
	m_instance->addChild(m_iconSprite);
}

void Picking::setCards()
{
	string cardPath;

	auto fileU = FileUtils::getInstance();
	auto fileContent = fileU->getStringFromFile("data/monsterData.xml");
	mData.Parse(fileContent.c_str());
	UserDefault* def = UserDefault::getInstance();

	//-----------------------------------------------------------------------------------
	//Player Special Card
	//-----------------------------------------------------------------------------------

	int key = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eMonsterData01 + m_battleNum].c_str());
	
	int type = atoi(mData.FirstChildElement()->FirstChildElement(MonsterNameData[key].c_str())->FirstChildElement("special")->FirstChildElement("type")->GetText());
	int level = atoi(mData.FirstChildElement()->FirstChildElement(MonsterNameData[key].c_str())->FirstChildElement("special")->FirstChildElement("level")->GetText());

	if (type == ROCK)
	{
		if (level == 0)
		{
			//normal
			cardPath = "img/UI/battle/UI_B_08.png";
			m_specialType = ROCK;
		}
		else if (level == 1)
		{
			cardPath = "img/UI/battle/UI_B_11.png";
			m_specialType = SUPER_ROCK;
		}
		else
		{
			//super or ultra
			cardPath = "img/UI/battle/UI_B_11-G.png";
			m_specialType = ULTRA_ROCK;
		}
	}
	else if (type == SISSORS)
	{
		if (level == 0) //normal
		{
			cardPath = "img/UI/battle/UI_B_09.png";
			m_specialType = SISSORS;
		}
		else if (level == 1)
		{
			cardPath = "img/UI/battle/UI_B_12.png";
			m_specialType = SUPER_SISSORS;
		}
		else //super or ultra
		{
			cardPath = "img/UI/battle/UI_B_12-G.png";
			m_specialType = ULTRA_SISSORS;
		}
			
	}
	else if (type == PAPER)
	{
		if (level == 0) //normal
		{
			cardPath = "img/UI/battle/UI_B_10.png";
			m_specialType = PAPER;
		}
		else if (level == 1)
		{
			cardPath = "img/UI/battle/UI_B_13.png";
			m_specialType = SUPER_PAPER;
		}
		else //super or ultra
		{
			cardPath = "img/UI/battle/UI_B_13-G.png";
			m_specialType = ULTRA_PAPER;
		}
			
	}

	//render player special card
	m_specialCard = Sprite::create(cardPath);
	m_specialCard->setScale(m_Mag * 0.5);
	m_specialCard->setPosition(Vec2(m_specialCard->getBoundingBox().getMaxX() * 1.8, m_specialCard->getBoundingBox().getMaxY()));
	m_specialCard->setScale(m_Mag * 1.2);
	m_specialCard->setZOrder(10);
	m_instance->addChild(m_specialCard);

	auto smallenPlayer = ScaleTo::create(0.5, m_Mag*0.5);
	m_specialCard->runAction(Sequence::create(smallenPlayer, NULL));

	//-----------------------------------------------------------------------------------
	//Enemy Special Card
	//-----------------------------------------------------------------------------------
	key = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eEnemyMonster01 + m_battleNum].c_str());

	type = atoi(mData.FirstChildElement()->FirstChildElement(MonsterNameData[key].c_str())->FirstChildElement("special")->FirstChildElement("type")->GetText());
	level = atoi(mData.FirstChildElement()->FirstChildElement(MonsterNameData[key].c_str())->FirstChildElement("special")->FirstChildElement("level")->GetText());

	if (type == ROCK)
	{
		if (level == 0)
		{
			//normal
			cardPath = "img/UI/battle/UI_B_08.png";
			m_enemySpecialType = ROCK;
		}
		else if (level == 1) //super
		{
			cardPath = "img/UI/battle/UI_B_11.png";
			m_enemySpecialType = SUPER_ROCK;
		}
		else //ultra
		{
			cardPath = "img/UI/battle/UI_B_11-G.png";
			m_enemySpecialType = ULTRA_ROCK;
		}
	}
	else if (type == SISSORS)
	{
		if (level == 0) //normal
		{
			cardPath = "img/UI/battle/UI_B_09.png";
			m_enemySpecialType = SISSORS;
		}
		else if (level == 1) //super
		{
			cardPath = "img/UI/battle/UI_B_12.png";
			m_enemySpecialType = SUPER_SISSORS;
		}
		else //ultra
		{
			cardPath = "img/UI/battle/UI_B_12-G.png";
			m_enemySpecialType = ULTRA_SISSORS;
		}

	}
	else if (type == PAPER)
	{
		if (level == 0) //normal
		{
			cardPath = "img/UI/battle/UI_B_10.png";
			m_enemySpecialType = PAPER;
		}
		else if (level == 1) //super
		{
			cardPath = "img/UI/battle/UI_B_13.png";
			m_enemySpecialType = SUPER_PAPER;
		}
		else //ultra
		{
			cardPath = "img/UI/battle/UI_B_13-G.png";
			m_enemySpecialType = ULTRA_PAPER;
		}

	}

	//render enemy Special card
	m_enemySpecial = Sprite::create(cardPath);
	m_enemySpecial->setScale(m_Mag * 0.5);
	m_enemySpecial->setPosition(Vec2(m_visibleSize.width - m_enemySpecial->getBoundingBox().getMaxX() * 1.8, m_visibleSize.height - m_enemySpecial->getBoundingBox().getMaxY()));
	m_enemySpecial->setScale(m_Mag * 1.2);
	m_enemySpecial->setZOrder(10);
	m_instance->addChild(m_enemySpecial);

	auto smallenEnemy = ScaleTo::create(0.5, m_Mag*0.5);
	m_enemySpecial->runAction(Sequence::create(smallenEnemy, NULL));

	//-----------------------------------------------------------------------------------
	//Other Cards
	//-----------------------------------------------------------------------------------

	srand(time(NULL));
	for (int i = 0; i < 4; i++)
	{
		randomize(i);
		m_hiddenCards[i] = Sprite::create("img/UI/battle/UI_B_14.png");
		m_hiddenCards[i]->setPositionX(m_cards[i]->getPositionX() - 270);
		m_hiddenCards[i]->setScale(m_Mag*0.5);
		m_hiddenCards[i]->setPositionY(m_visibleSize.height - m_hiddenCards[i]->getBoundingBox().getMaxY());
		m_instance->addChild(m_hiddenCards[i]);
	}

	auto callback = CallFunc::create([this](){this->displayUI(); });

	MoveTo* appear[4];
	MoveTo* appearEnemy[4];
	for (int i = 0; i < 4; i++)
	{
		//player other cards animation
		appear[i] = MoveTo::create((4-i)*0.5, Vec2(m_cards[i]->getPosition().x, m_cards[i]->getPosition().y));
		auto wait = DelayTime::create(1.5);
		m_cards[i]->setPosition(m_cards[i]->getPosition().x, -m_cards[i]->getBoundingBox().getMaxY()*(4-i));
		if (i == 3)
			m_cards[i]->runAction(Sequence::create(appear[i], wait, callback, NULL));
		else
			m_cards[i]->runAction(appear[i]);

		//enemy other cards animation
		appearEnemy[i] = MoveTo::create(i * 0.5, Vec2(m_hiddenCards[i]->getPositionX(), m_hiddenCards[i]->getPositionY()));
		m_hiddenCards[i]->setPosition(m_hiddenCards[i]->getPositionX(), m_visibleSize.height + m_hiddenCards[i]->getBoundingBox().getMaxY() * i);
		m_hiddenCards[i]->runAction(appearEnemy[i]);
	}
}

void Picking::randomize(int iterator)
{
	auto fileU = FileUtils::getInstance();
	auto fileContent = fileU->getStringFromFile("data/monsterData.xml");
	mData.Parse(fileContent.c_str());
	UserDefault* def = UserDefault::getInstance();
	int key = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eMonsterData01 + m_battleNum].c_str());

	int rockProb = atoi(mData.FirstChildElement()->FirstChildElement(MonsterNameData[key].c_str())->FirstChildElement("luck")->FirstChildElement("rock")->GetText());
	int sissorsProb = atoi(mData.FirstChildElement()->FirstChildElement(MonsterNameData[key].c_str())->FirstChildElement("luck")->FirstChildElement("sissors")->GetText());
	int paperProb = atoi(mData.FirstChildElement()->FirstChildElement(MonsterNameData[key].c_str())->FirstChildElement("luck")->FirstChildElement("paper")->GetText());
	//int monsterLevel = atoi(mData.FirstChildElement()->FirstChildElement(MonsterNameData[key].c_str())->FirstChildElement("special")->FirstChildElement("level")->GetText());

	int specialProb = rockProb + sissorsProb + paperProb;

	int randomNum = rand() % 100;
	if (randomNum < (100 - specialProb)) //------------------ normal card
	{
		randomNum = rand() % 3;
	}
	else if (randomNum >= (100 - specialProb)) //--------------------- super card
	{
		//randomNum = rand() % 3 + 3;
		randomNum = rand() % specialProb;
		if (randomNum <= rockProb)
		{
			randomNum = rand() % 10;
			if (randomNum < 7)
				randomNum = SUPER_ROCK;
			else
				randomNum = ULTRA_ROCK;
		}
		else if (randomNum <= (rockProb + sissorsProb) && randomNum > rockProb)
		{
			randomNum = rand() % 10;
			if (randomNum < 7)
				randomNum = SUPER_SISSORS;
			else
				randomNum = ULTRA_SISSORS;
		}
		else if (randomNum > (rockProb + sissorsProb))
		{
			randomNum = rand() % 10;
			if (randomNum < 7)
				randomNum = SUPER_PAPER;
			else
				randomNum = ULTRA_PAPER;
		}
		else //error case
			randomNum = rand() % 3;
	}
	else //error case
	{
		randomNum = rand() % 3;
	}

	switch (randomNum)
	{
	case ROCK:
		m_cards[iterator] = Sprite::create("img/UI/battle/UI_B_08.png");
		break;
	case SISSORS:
		m_cards[iterator] = Sprite::create("img/UI/battle/UI_B_09.png");
		break;
	case PAPER:
		m_cards[iterator] = Sprite::create("img/UI/battle/UI_B_10.png");
		break;
	case SUPER_ROCK:
		m_cards[iterator] = Sprite::create("img/UI/battle/UI_B_11.png");
		break;
	case SUPER_SISSORS:
		m_cards[iterator] = Sprite::create("img/UI/battle/UI_B_12.png");
		break;
	case SUPER_PAPER:
		m_cards[iterator] = Sprite::create("img/UI/battle/UI_B_13.png");
		break;
	case ULTRA_ROCK:
		m_cards[iterator] = Sprite::create("img/UI/battle/UI_B_11-G.png");
		break;
	case ULTRA_SISSORS:
		m_cards[iterator] = Sprite::create("img/UI/battle/UI_B_12-G.png");
		break;
	case ULTRA_PAPER:
		m_cards[iterator] = Sprite::create("img/UI/battle/UI_B_13-G.png");
		break;
	}

	m_cards[iterator]->setScale(m_Mag*0.5);
	m_cards[iterator]->setPosition(Vec2(m_visibleSize.width / 8 * (((iterator + 1) * 1.5) + 1), m_cards[iterator]->getBoundingBox().getMaxY()));
	m_cards[iterator]->setName("Cards" + Generic::intToStrnig(iterator));
	m_cards[iterator]->setZOrder(10);
	m_instance->addChild(m_cards[iterator]);
	cardData[iterator] = randomNum;
}

void Picking::displayHP()
{
	if (health != nullptr)
	{
		m_instance->removeChild(health);
	}
	std::string hp = "HP: " + Generic::intToStrnig(m_HP);
	health = Label::createWithTTF(hp, "fonts/arial.ttf", 40);
	health->enableOutline(Color4B::BLACK, 2);
	health->setPosition(Vec2(health->getBoundingBox().getMaxX(), m_specialCard->getBoundingBox().getMaxY() * 1.2));
	m_instance->addChild(health);

	hp = "HP: " + Generic::intToStrnig(m_enemyHP);
	enemyHealth = Label::createWithTTF(hp, "fonts/arial.ttf", 40);
	enemyHealth->enableOutline(Color4B::BLACK, 2);
	enemyHealth->setPosition(Vec2(m_visibleSize.width - enemyHealth->getBoundingBox().getMaxX(), m_visibleSize.height - m_specialCard->getBoundingBox().size.height * 1.2));
	m_instance->addChild(enemyHealth);
}

void Picking::displayUI()
{
	eventHandler();

	displayHP();

	for (int i = 0; i < 4; i++)
	{
		m_glow[i] = Sprite::create("img/UI/battle/glow.png");
		m_glow[i]->setScale(m_Mag*0.5);
		m_glow[i]->setPosition(Vec2(m_visibleSize.width / 8 * (((i + 1) * 1.5) + 1), m_cards[1]->getPositionY()));
		m_glow[i]->setZOrder(2);
		m_glow[i]->setTag(5);
		m_instance->addChild(m_glow[i]);
	}

	//instructions to reshuffle
	instructions = Label::createWithTTF("いらないカードをシャッフルしよう！", "fonts/ant-maru.ttf", 55);
	instructions->enableOutline(Color4B::BLACK, 2);
	instructions->setPosition(Vec2(m_visibleSize.width / 2, m_visibleSize.height /2.4));
	m_instance->addChild(instructions);

	auto Label = Label::createWithTTF("<< Enemy Card", "fonts/arial.ttf", 25);
	Label->setColor(Color3B::RED);
	Label->enableOutline(Color4B::BLACK, 2);
	Label->setPosition(Vec2(m_enemyCard->getPosition().x * 0.9, m_enemyCard->getBoundingBox().getMaxY()));
	Label->setName("EnemyCard");
	//m_instance->addChild(Label);
	
	MenuItemFont::setFontSize(80);
	MenuItemFont* goItem = MenuItemFont::create("Go!", CC_CALLBACK_1(Picking::startBattle, this));
	auto label = Label::createWithTTF("ＧＯ！", "fonts/ant-maru.ttf", 60);
	label->enableOutline(Color4B::RED, 2);
	goItem->setLabel(label);
	goItem->setPosition(Vec2(m_visibleSize.width / 1.15, m_visibleSize.height / 2));

	m_menu = Menu::create(goItem, NULL);
	m_menu->setPosition(Point::ZERO);
	m_instance->addChild(m_menu);
}

void Picking::renderPicking(int battleNumber)
{
	//Experimental BG
    /*
	m_background->setPosition(m_visibleSize.width / 2, m_visibleSize.height / 2);
	m_background->setScale(m_Mag);
	m_background->setName("BG");
	m_background->setColor(Color3B(100, 100, 100));
	m_instance->addChild(m_background);
     */
	m_battleNum = battleNumber;
	versusAnim();
}

void Picking::update(float dt)
{
	m_battle->update(dt);
}

void Picking::eventHandler()
{
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Picking::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(Picking::onTouchEnded, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, m_instance);
}

void Picking::onTouchEnded(Touch* touch, Event* eventt)
{
	Rect touchPoint = Rect(touch->getLocation().x, touch->getLocation().y, 2, 2);

	if (eventOn)
	{
		for (int i = 0; i < 4; i++)
		{
			if (touchPoint.intersectsRect(m_cards[i]->getBoundingBox()))
			{
				if (!m_selected[i])
				{
					m_cards[i]->setPosition(m_cards[i]->getPosition().x, (m_cards[i]->getPosition().y + 50));
					m_cards[i]->setColor(Color3B(150, 100, 100));
					m_glow[i]->setVisible(false);
					m_selected[i] = true;
				}
				else
				{
					m_cards[i]->setPosition(m_cards[i]->getPosition().x, (m_cards[i]->getPosition().y - 50));
					m_cards[i]->setColor(Color3B(255, 255, 255));
					m_glow[i]->setVisible(true);
					m_selected[i] = false;
				}

				if (m_selected[i])
				{
					if (penalty != nullptr)
					{
						m_instance->removeChild(penalty);
					}

					m_redutionCounter += 10;
					string counterText = "-" + Generic::intToStrnig(m_redutionCounter);
					penalty = Label::createWithTTF(counterText, "fonts/arial.ttf", 40);
					/*
					if (cardData[i] == ROCK)
					{
						penalty[i]->enableOutline(Color4B::BLACK, 2);
					}
					else if (cardData[i] == SISSORS)
					{
						penalty[i]->enableOutline(Color4B::BLACK, 2);
					}
					else if (cardData[i] == PAPER)
					{
						penalty[i]->enableOutline(Color4B::BLACK, 2);
					}
					*/
					penalty->enableOutline(Color4B::RED, 2);

					penalty->setPosition(health->getBoundingBox().getMaxX() * 1.3, health->getPosition().y);
					m_instance->addChild(penalty);
				}
				else
				{
					m_redutionCounter -= 10;
					if (penalty != nullptr)
					{
						m_instance->removeChild(penalty);
					}
					if (m_redutionCounter != 0)
					{
						
						string counterText = "-" + Generic::intToStrnig(m_redutionCounter);
						penalty = Label::createWithTTF(counterText, "fonts/arial.ttf", 40);
						penalty->enableOutline(Color4B::RED, 2);
						penalty->setPosition(health->getBoundingBox().getMaxX() * 1.3, health->getPosition().y);
						m_instance->addChild(penalty);
					}
				}
			}
		}
	}
}

bool Picking::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* eventt)
{
	return true;
}

void Picking::startBattle(cocos2d::Ref* pSender)
{
	m_HP -= m_redutionCounter;

	cleanUp();

	bool shuffled = false;

	for (int i = 0; i < 4; i++)
	{
		if (m_selected[i])
		{
			auto moveUp = MoveBy::create(0.3, Vec2(0, 300));
			auto moveDiscard = MoveBy::create(0.8, Vec2(-1000, 0));
			auto delay = DelayTime::create(0.5);
			auto shuffle = CallFunc::create([this, i](){this->shuffle(i); });

			if (penalty != nullptr)
			{
				m_instance->removeChild(penalty);
			}

			m_cards[i]->runAction(Sequence::create(moveUp, delay, moveDiscard, shuffle, delay, NULL));

			//displayHP();
			m_selected[i] = false;

			shuffled = true;
		}
	}
	eventOn = false;
	//m_background->runAction(TintTo::create(1.0f, Color3B(255, 255, 255)));
	battleOn = true;


	auto delay = DelayTime::create(2.0);
	auto nextPhase = CallFunc::create([this](){this->battleCallback(); });

	if (shuffled)
		m_instance->runAction(Sequence::create(delay, nextPhase, NULL));
	else
		m_instance->runAction(Sequence::create(nextPhase, NULL));
	
}

void Picking::battleCallback()
{
	m_battle->battlePhase(m_HP, cardData, m_specialType, m_enemySpecialType, m_battleNum);
	m_battle->renderBattle(m_cards, m_specialCard, enemyMonster);
	
}

void Picking::shuffle(int i)
{
	int cardCopy = cardData[i];
	do
	{
		m_instance->removeChild(m_cards[i]);
		randomize(i);
	} while (cardCopy == cardData[i]);
}

int Picking::getCardData(int iterator)
{
	if (battleOn)
	{
		CCLOG(Generic::intToStrnig(cardData[0]).c_str());
		return cardData[iterator];
	}
	
	return -1;
}

void Picking::versusAnim()
{
	if (m_battle == nullptr)
	{
		m_battle = new Battle(m_instance);
	}

	//display player
	displayIcon();
	//display enemy card
	displayEnemy();

	Generic::shake(m_instance);

	//enemy animation
	//auto hide = Hide::create();
	//auto jump = MoveBy::create(0.3, Vec2(0, 30));
	//auto back = MoveBy::create(0.3, Vec2(0, -30));
	//auto cFunc = CallFunc::create([this](){this->enemyFlipAnim(); });
	auto smallenEnemy = ScaleBy::create(0.5, 0.8);
	auto delayEnemy = DelayTime::create(1);
	auto moveEnemy = MoveBy::create(1, Vec2(0, 850));
	auto hideEnem = Hide::create();
	m_enemyCard->runAction(Sequence::create(smallenEnemy, delayEnemy, moveEnemy, hideEnem, NULL));

	//player animation
	auto smallenPlayer = ScaleBy::create(0.5, 0.8);
	auto delayPlayer = DelayTime::create(1);
	auto movePlayer = MoveBy::create(1, Vec2(0, -850));
	auto hidePlayer = Hide::create();
	auto callback = CallFunc::create([this](){this->setCards();});
	auto sequence = Sequence::create(smallenPlayer, delayPlayer, movePlayer, hidePlayer, callback, NULL);
	m_iconSprite->runAction(sequence);
}

void Picking::displayEnemy()
{
	auto fileU = FileUtils::getInstance();
	auto fileContent = fileU->getStringFromFile("data/animData.xml");
	doc.Parse(fileContent.c_str());

	UserDefault* def = UserDefault::getInstance();
	enemyMonster = def->getIntegerForKey(SaveDataKey[(n_DataKeyNum::eEnemyMonster01) + m_battleNum].c_str());

	auto sprite = doc.FirstChildElement()->FirstChildElement(MonsterNameData[enemyMonster].c_str());

	/*
	//CARD on the center
	m_enemySpecial = Sprite::create("img/UI/battle/UI_B_12.png");
	m_enemySpecial->setScale(m_Mag * 0.8);
	m_enemySpecial->setPosition(Vec2(m_visibleSize.width / 2, m_visibleSize.height - m_enemySpecial->getBoundingBox().getMaxY() * 0.75));
	m_instance->addChild(m_enemySpecial);
	m_enemySpecial->setVisible(false); //hidden for animation
	*/

	//Monster Sprite number 2
	m_enemyCard = Sprite::create(sprite->FirstChildElement("spriteList")->FirstChildElement("animation")->FirstChildElement("stand")->GetText());
	m_enemyCard->setScale(m_Mag * 1.5);
	m_enemyCard->setPosition(Vec2((m_visibleSize.width / 6) * 4.5, m_visibleSize.height /2));
	m_instance->addChild(m_enemyCard);

}

void Picking::enemyFlipAnim()
{
	/*
	auto show = Show::create();
	auto enlarge = ScaleBy::create(0.2, 1.2);
	auto reverse = ScaleBy::create(0.2, 0.8);
	auto cFunc = CallFunc::create([this](){this->cardAnim(); });
	m_enemyCard->runAction(Sequence::create(show, enlarge, reverse, enlarge, reverse, cFunc, NULL));
	*/
}

void Picking::cardAnim()
{
	auto enlarge = ScaleBy::create(0.1, 1.5);
	auto show = Show::create();
	auto reverse = ScaleBy::create(0.3, 0.5);
	m_enemySpecial->runAction(Sequence::create(enlarge, show, reverse, NULL));
}

void Picking::cleanUp()
{
	for (int i = 0; i < 4; i++)
	{
		m_instance->removeChild(m_glow[i]);
		m_instance->removeChild(m_hiddenCards[i]);
	}
	m_instance->removeChild(m_enemyCard);
	m_instance->removeChild(m_enemySpecial);
	m_instance->removeChild(m_cardBack);
	m_instance->removeChild(instructions);
	m_instance->removeChild(m_menu);
	m_instance->removeChild(health);
	m_instance->removeChild(enemyHealth);
	Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
}