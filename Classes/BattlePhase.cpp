#include "BattlePhase.h"
#include "BattleScene.h"
USING_NS_CC;

Battle::Battle(cocos2d::Layer* instance)
	:m_instance(instance),
	m_visibleSize(Director::getInstance()->getVisibleSize()),
	m_Mag(Generic::getScreenMagnification(m_visibleSize)),
	battleBegan(false),
	playerhealth(nullptr),
	enemyHP(nullptr),
	result(nullptr),
	m_enemySprite(nullptr),
	m_playerSprite(nullptr),
	m_playerL2D(nullptr),
	m_enemyL2D(nullptr)
{
	for (int i = 0; i < 5; i++)
	{
		m_selected[i] = false;
		order[i] = -1;
	}
	
	getPreloadedData();
}

Battle::~Battle()
{
}

void Battle::getPreloadedData()
{
	MenuItemFont::setFontSize(60);
	auto goItem = MenuItemFont::create("FIGHT!", CC_CALLBACK_1(Battle::cardBattle, this));
	auto label = Label::createWithTTF("FIGHT!", "fonts/arial.ttf", 60);
	label->enableOutline(Color4B::RED, 3);
	goItem->setLabel(label);
	m_menu = Menu::create(goItem, NULL);
	m_menu->setPosition(m_visibleSize.width / 2, m_visibleSize.height / 4.1);
	m_menu->setEnabled(false);
	m_menu->setVisible(false);
	m_instance->addChild(m_menu);

	for (int i = 0; i < 5; i++)
	{
		m_glow[i] = Sprite::create("img/UI/battle/glow.png");
		m_glow[i]->setZOrder(2);
		m_glow[i]->setScale(m_Mag * 0.5);
		m_glow[i]->setVisible(false);
		m_instance->addChild(m_glow[i]);
	}

	m_iconGroup = m_instance->getChildByName("Icon");
	m_background = m_instance->getChildByName("BG");
}

void Battle::renderBattle(cocos2d::Sprite** cards, cocos2d::Sprite* specialCard, int enemyMData)
{
	enemyMonster = enemyMData;

	for (int i = 0; i < 4; i++)
	{
		m_cards[i] = cards[i];
	}
	m_cards[4] = specialCard;

	genEnemyCards();
	animEnemy();
}

void Battle::displayEnemyIcon()
{
	if (m_playerL2D != nullptr)
	{
		m_instance->removeChild(m_playerL2D);
		m_playerL2D = nullptr;
	}

	if (m_enemyL2D != nullptr)
	{
		m_instance->removeChild(m_enemyL2D);
		m_enemyL2D = nullptr;
	}
	auto fileU = FileUtils::getInstance();
	auto fileContent = fileU->getStringFromFile("data/animData.xml");

	UserDefault* def = UserDefault::getInstance();
	int key = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eMonsterData01 + m_battleNum].c_str());
	/*
	doc.Parse(fileContent.c_str());
	auto sprite = doc.FirstChildElement()->FirstChildElement(MonsterNameData[enemyMonster].c_str());

	m_enemySprite = Sprite::create(sprite->FirstChildElement("spriteList")->FirstChildElement("animation")->FirstChildElement("stand")->GetText());
	m_enemySprite->setScale(m_Mag*0.4f);
	m_enemySprite->setPosition(Vec2(m_visibleSize.width / 1.25,m_visibleSize.height / 5));
	//m_enemySprite->setVisible(false);
	m_instance->addChild(m_enemySprite);

	
	sprite = doc.FirstChildElement()->FirstChildElement(MonsterNameData[key].c_str());

	m_playerSprite = Sprite::create(sprite->FirstChildElement("spriteList")->FirstChildElement("animation")->FirstChildElement("stand")->GetText());
	m_playerSprite->setScale(m_Mag*0.4);
	m_playerSprite->setPosition(Vec2(m_visibleSize.width / 4.8, m_visibleSize.height / 5));
	//m_playerSprite->setVisible(false);
	m_instance->addChild(m_playerSprite);
	*/

	float scale;
	float posX;
	float posY;
	float ePosX;


	switch (key)
	{
	default:
		scale = 0.4f;
		posX = 0.8f;
		ePosX = -0.4f;
		posY = -0.17f;
		break;
	}

	m_enemyL2D = Live2DSprite::createDrawNode(MonsterNameData[enemyMonster], scale, scale, ePosX, posY);
	m_instance->addChild(m_enemyL2D);

	m_playerL2D = Live2DSprite::createDrawNode(MonsterNameData[key], scale, scale, posX, posY);
	m_instance->addChild(m_playerL2D);
}

void Battle::animEnemy()
{
	
	for (int i = 0; i < 5; i++)
	{
		m_glow[i]->setPosition(m_cards[i]->getPosition());
	}
	
	auto wait = FadeIn::create(1.5f);
	auto showInstruction = CallFunc::create([this](){this->showInstruction(); }); //----------- show instruction
	auto startBattle = CallFunc::create([this](){this->battleBegan = true; }); //------------enable battle selection
	m_instance->runAction(Sequence::create( showInstruction, startBattle, NULL));
}

void Battle::update(float dt)
{
}

void Battle::displayEnemyHP()
{
	if (enemyHP != nullptr)
	{
		m_instance->removeChild(enemyHP);
		enemyHP = nullptr;
	}
	if (m_enemyHPCounter < 0)
	{
		m_enemyHPCounter = 0;
	}
	std::string hp = "HP: " + Generic::intToStrnig(m_enemyHPCounter);
	enemyHP = Label::createWithTTF(hp, "fonts/arial.ttf", 40);
	enemyHP->enableOutline(Color4B::BLACK, 2);
	enemyHP->setPosition(Vec2(m_visibleSize.width / 1.25, enemyHP->getBoundingBox().getMaxY() * 1.2));
	m_instance->addChild(enemyHP);
}

void Battle::displayPlayerHP()
{
	if (playerhealth != nullptr)
	{
		m_instance->removeChild(playerhealth);
		playerhealth = nullptr;
	}
	if (m_playerHPCounter < 0)
	{
		m_playerHPCounter = 0;
	}
	std::string hp = "HP: " + Generic::intToStrnig(m_playerHPCounter);
	playerhealth = Label::createWithTTF(hp, "fonts/arial.ttf", 40);
	playerhealth->enableOutline(Color4B::BLACK, 2);
	playerhealth->setPosition(Vec2(m_visibleSize.width / 4.8, playerhealth->getBoundingBox().getMaxY() * 1.2));
	m_instance->addChild(playerhealth);
}


void Battle::showInstruction()
{
	instructions = Label::createWithTTF("カードの順番を決めよう！", "fonts/ant-maru.ttf", 45);
	instructions->enableOutline(Color4B::BLACK, 2);
	instructions->setPosition(Vec2(m_visibleSize.width / 2, m_visibleSize.height / 2.4));
	m_instance->addChild(instructions);

	for (int i = 0; i < 5; i++)
	{
		m_glow[i]->setVisible(true);
	}
}

void Battle::eventHandler()
{
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Battle::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(Battle::onTouchEnded, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, m_instance);
}

bool Battle::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* eventt)
{
	return true;
}

void Battle::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* eventt)
{
	
	Rect touchPoint = Rect(touch->getLocation().x, touch->getLocation().y, 2, 2);
	
	int number = -1;
	if (battleBegan)
	{
		for(int i = 0; i < 5; i++)
		{
			if (touchPoint.intersectsRect(m_cards[i]->getBoundingBox()))
			{
				if (m_selected[i])
				{
					m_selected[i] = false;
				}
				else
				{
					m_selected[i] = true;
				}

				if (m_selected[i])
				{
					for (int j = 0; j < 5; j++)
					{
						if (order[j] == -1)
						{
							order[j] = i;
							number = j;
							break;
						}
					}
					m_cards[i]->setScale(0.2);
					m_cards[i]->setPosition(m_cards[i]->getBoundingBox().size.width + 50, m_visibleSize.height - (m_cards[i]->getBoundingBox().size.height * (number+1)) * 1.3 );
					if ((cardData[i] == ROCK || cardData[i] == SUPER_ROCK || cardData[i] == ULTRA_ROCK))
					{
						//m_cards[i]->setColor(Color3B(150, 100, 100));
					}
					else if ((cardData[i] == SISSORS || cardData[i] == SUPER_SISSORS || cardData[i] == ULTRA_SISSORS))
					{
						//m_cards[i]->setColor(Color3B(150, 150, 100));
					}
					else if ((cardData[i] == PAPER || cardData[i] == SUPER_PAPER || cardData[i] == ULTRA_PAPER))
					{
						//m_cards[i]->setColor(Color3B(100, 100, 150));
					}

					orderText[i] = Label::createWithTTF(Generic::intToStrnig(number + 1), "fonts/arial.ttf", 30);
					orderText[i]->enableOutline(Color4B::BLACK, 2);

					orderText[i]->setPosition(m_cards[i]->getPosition().x - 60, m_cards[i]->getPositionY());
					m_instance->addChild(orderText[i]);
					m_glow[i]->setVisible(false);
				}
				else
				{
					if (i == 4)
					{
						m_cards[i]->setPosition(m_cards[i]->getBoundingBox().size.width * 2.25, (m_cards[i]->getBoundingBox().size.height + 18));
					}
					else
					{
						m_cards[i]->setPosition(m_visibleSize.width / 8 * (((i + 1) * 1.5) + 1), (m_cards[i]->getBoundingBox().size.height + 18));
					}
					
					m_cards[i]->setScale(0.5);
					m_cards[i]->setColor(Color3B(255, 255, 255));
					
					for (int j = 0; j < 5; j++)
					{
						if (order[j] == i)
						{
							order[j] = -1;
							break;
						}
					}
					if (orderText[i] != nullptr)
					{
						m_instance->removeChild(orderText[i]);
					}
					m_glow[i]->setVisible(true);
				}
			}
		}
	}

	if (result != nullptr)
	{
		UserDefault* def = UserDefault::getInstance();
		int battleNumber = def->getIntegerForKey("Battle");
		int nextBattle = battleNumber + 1;
		def->setIntegerForKey("Battle", nextBattle);

		Scene* nextScene;

		if (battleNumber == 2)
		{
			//after third battle jump to result scene
			nextScene = ResultScene::createScene();
		}
		else
		{
			//otherwise run the next battle
			nextScene = BattleScene::createScene();
		}
		
		
		auto pScene = TransitionFade::create(0.5f, nextScene);
		Director::getInstance()->replaceScene(pScene);
	}

	pickCardOrder();
}

void Battle::pickCardOrder()
{
	if (m_selected[0] && m_selected[1] && m_selected[2] && m_selected[3] && m_selected[4])
	{
		if (m_menu != nullptr)
		{
			m_menu->setEnabled(true);
			m_menu->setVisible(true);
			
		}
	}
	else
	{
		if (m_menu != nullptr)
		{
			m_menu->setEnabled(false);
			m_menu->setVisible(false);
		}
	}
}

void Battle::cardBattle(cocos2d::Ref* pSender)
{
	for (int i = 0; i < 5; i++)
	{
		switch (enemyData[i])
		{
		case ROCK:
			m_enemyMiniCards[i] = Sprite::create("img/UI/battle/UI_B_08.png");
			break;
		case SISSORS:
			m_enemyMiniCards[i] = Sprite::create("img/UI/battle/UI_B_09.png");
			break;
		case PAPER:
			m_enemyMiniCards[i] = Sprite::create("img/UI/battle/UI_B_10.png");
			break;

		case SUPER_ROCK:
			m_enemyMiniCards[i] = Sprite::create("img/UI/battle/UI_B_11.png");
			break;
		case SUPER_SISSORS:
			m_enemyMiniCards[i] = Sprite::create("img/UI/battle/UI_B_12.png");
			break;
		case SUPER_PAPER:
			m_enemyMiniCards[i] = Sprite::create("img/UI/battle/UI_B_13.png");
			break;

		case ULTRA_ROCK:
			m_enemyMiniCards[i] = Sprite::create("img/UI/battle/UI_B_11-G.png");
			break;
		case ULTRA_SISSORS:
			m_enemyMiniCards[i] = Sprite::create("img/UI/battle/UI_B_12-G.png");
			break;
		case ULTRA_PAPER:
			m_enemyMiniCards[i] = Sprite::create("img/UI/battle/UI_B_13-G.png");
			break;
		}
		m_enemyMiniCards[i]->setScale(0.2);
		m_enemyMiniCards[i]->setPositionX(m_visibleSize.width - m_enemyMiniCards[i]->getBoundingBox().size.height * 1.2);
		m_enemyMiniCards[i]->setPositionY(m_cards[order[i]]->getPositionY());
		m_instance->addChild(m_enemyMiniCards[i]);
	}
	

	cleanUp();
	displayEnemyHP();
	displayPlayerHP();
	auto fight = CallFunc::create([this](){this->fightCards(0); });
	m_instance->runAction(Sequence::create(fight, NULL));
}

void Battle::fightCards(int i)
{
	Sprite* playerReflexion;
	Sprite* enemyReflexion;
	//-----------------------------------------------------------------------------------
	//Player Card
	//-----------------------------------------------------------------------------------
	Sprite* playerCard;
	switch (cardData[order[i]])
	{
	case ROCK:
		playerCard = Sprite::create("img/UI/battle/UI_B_08.png");
		playerReflexion = Sprite::create("img/UI/status/rock.png");
		break;
	case SISSORS:
		playerCard = Sprite::create("img/UI/battle/UI_B_09.png");
		playerReflexion = Sprite::create("img/UI/status/sissors.png");
		break;
	case PAPER:
		playerCard = Sprite::create("img/UI/battle/UI_B_10.png");
		playerReflexion = Sprite::create("img/UI/status/paper.png");
		break;

	case SUPER_ROCK:
		playerCard = Sprite::create("img/UI/battle/UI_B_11.png");
		playerReflexion = Sprite::create("img/UI/status/rock.png");
		break;
	case SUPER_SISSORS:
		playerCard = Sprite::create("img/UI/battle/UI_B_12.png");
		playerReflexion = Sprite::create("img/UI/status/sissors.png");
		break;
	case SUPER_PAPER:
		playerCard = Sprite::create("img/UI/battle/UI_B_13.png");
		playerReflexion = Sprite::create("img/UI/status/paper.png");
		break;

	case ULTRA_ROCK:
		playerCard = Sprite::create("img/UI/battle/UI_B_11-G.png");
		playerReflexion = Sprite::create("img/UI/status/rock.png");
		break;
	case ULTRA_SISSORS:
		playerCard = Sprite::create("img/UI/battle/UI_B_12-G.png");
		playerReflexion = Sprite::create("img/UI/status/sissors.png");
		break;
	case ULTRA_PAPER:
		playerCard = Sprite::create("img/UI/battle/UI_B_13-G.png");
		playerReflexion = Sprite::create("img/UI/status/paper.png");
		break;
	}

	playerCard->setName("pCard");
	playerCard->setScale(m_Mag*0.5);
	playerCard->setPosition(Vec2(m_visibleSize.width / 3.1, m_visibleSize.height/2));
	m_instance->addChild(playerCard);

	playerReflexion->setPosition(playerCard->getPosition());
	playerReflexion->setVisible(false);
	playerReflexion->setOpacity(0);
	playerReflexion->setName("pRef");
	m_instance->addChild(playerReflexion);

	//-----------------------------------------------------------------------------------
	//Enemy Card
	//-----------------------------------------------------------------------------------
	switch (enemyData[i])
	{
	case ROCK:
		enemyCard = Sprite::create("img/UI/battle/UI_B_08.png");
		enemyReflexion = Sprite::create("img/UI/status/rock.png");
		break;
	case SISSORS:
		enemyCard = Sprite::create("img/UI/battle/UI_B_09.png");
		enemyReflexion = Sprite::create("img/UI/status/sissors.png");
		break;
	case PAPER:
		enemyCard = Sprite::create("img/UI/battle/UI_B_10.png");
		enemyReflexion = Sprite::create("img/UI/status/paper.png");
		break;

	case SUPER_ROCK:
		enemyCard = Sprite::create("img/UI/battle/UI_B_11.png");
		enemyReflexion = Sprite::create("img/UI/status/rock.png");
		break;
	case SUPER_SISSORS:
		enemyCard = Sprite::create("img/UI/battle/UI_B_12.png");
		enemyReflexion = Sprite::create("img/UI/status/sissors.png");
		break;
	case SUPER_PAPER:
		enemyCard = Sprite::create("img/UI/battle/UI_B_13.png");
		enemyReflexion = Sprite::create("img/UI/status/paper.png");
		break;

	case ULTRA_ROCK:
		enemyCard = Sprite::create("img/UI/battle/UI_B_11-G.png");
		enemyReflexion = Sprite::create("img/UI/status/rock.png");
		break;
	case ULTRA_SISSORS:
		enemyCard = Sprite::create("img/UI/battle/UI_B_12-G.png");
		enemyReflexion = Sprite::create("img/UI/status/sissors.png");
		break;
	case ULTRA_PAPER:
		enemyCard = Sprite::create("img/UI/battle/UI_B_13-G.png");
		enemyReflexion = Sprite::create("img/UI/status/paper.png");
		break;
	}
	enemyCard->setScale(m_Mag*0.5);
	enemyCard->setPosition(Vec2(m_visibleSize.width / 1.4, m_visibleSize.height/ 2));
	m_instance->addChild(enemyCard);

	enemyReflexion->setPosition(enemyCard->getPosition());
	enemyReflexion->setVisible(false);
	enemyReflexion->setOpacity(0);
	enemyReflexion->setName("eRef");
	m_instance->addChild(enemyReflexion);
	//-----------------------------------------------------------------------------------
	//DMG calculation
	//-----------------------------------------------------------------------------------
	int result = -1;

	int basicDmg = 20;
	int mediumDmg = 50;

	const int PAPER_TYPE = 0;
	const int ROCK_TYPE = 1;
	const int SISSORS_TYPE = 2;


	int dmgType[3] = { 30, 50, 100 };
	int defenceType[3] = { 5, 15, 25 };
	
	//NORMAL SUPER OR ULTRA (0, 1, 2)
	int playerSpecific = floor((cardData[order[i]] + 1) / 3);
	int enemySpecific = floor((enemyData[i] + 1) / 3);

	//ROCK SISSORS OR PAPER (1, 2, 0)
	int playerCardType = (cardData[order[i]] + 1) % 3; 
	int enemyCardType = (enemyData[i] + 1) % 3;

	if (playerCardType == 0)
	{
		playerSpecific -= 1;
	}
	if (enemyCardType == 0)
	{
		enemySpecific -= 1;
	}

	if (playerCardType == ROCK_TYPE)
	{
		switch (enemyCardType)
		{
		case ROCK_TYPE:
			if (playerSpecific == enemySpecific)
			{
				result = DRAW;
			}
			else if (playerSpecific > enemySpecific)
			{
				result = WIN;
				if (playerSpecific - 1 == enemySpecific)
				{
					m_enemyHPCounter -= basicDmg;
				}
				else
				{
					m_enemyHPCounter -= mediumDmg;
				}
			}
			else if (playerSpecific < enemySpecific)
			{
				result = LOSE;
				if (playerSpecific == enemySpecific - 1)
				{
					m_playerHPCounter -= basicDmg;
				}
				else
				{
					m_playerHPCounter -= mediumDmg;
				}
			}
			break;
		case SISSORS_TYPE:
			result = WIN;
			m_enemyHPCounter -= dmgType[playerSpecific];
			m_enemyHPCounter += defenceType[enemySpecific];
			break;
		case PAPER_TYPE:
			result = LOSE;
			m_playerHPCounter -= dmgType[enemySpecific];
			m_playerHPCounter += defenceType[playerSpecific];
			break;
		}
	}

	else if (playerCardType == SISSORS_TYPE)
	{
		switch (enemyCardType)
		{
		case ROCK_TYPE:
			result = LOSE;
			m_playerHPCounter -= dmgType[enemySpecific];
			m_playerHPCounter += defenceType[playerSpecific];
			break;
		case SISSORS_TYPE:
			if (playerSpecific == enemySpecific)
			{
				result = DRAW;
			}
			else if (playerSpecific > enemySpecific)
			{
				result = WIN;
				if (playerSpecific - 1 == enemySpecific)
				{
					m_enemyHPCounter -= basicDmg;
				}
				else
				{
					m_enemyHPCounter -= mediumDmg;
				}
			}
			else if (playerSpecific < enemySpecific)
			{
				result = LOSE;
				if (playerSpecific == enemySpecific - 1)
				{
					m_playerHPCounter -= basicDmg;
				}
				else
				{
					m_playerHPCounter -= mediumDmg;
				}
			}
			break;
		case PAPER_TYPE:
			result = WIN;
			m_enemyHPCounter -= dmgType[playerSpecific];
			m_enemyHPCounter += defenceType[enemySpecific];
			break;
		}
	}
	else if (playerCardType == PAPER_TYPE)
	{
		switch (enemyCardType)
		{
		case ROCK_TYPE:
			result = WIN;
			m_enemyHPCounter -= dmgType[playerSpecific];
			m_enemyHPCounter += defenceType[enemySpecific];
			break;
		case SISSORS_TYPE:
			result = LOSE;
			m_playerHPCounter -= dmgType[enemySpecific];
			m_playerHPCounter += defenceType[playerSpecific];
			break;
		case PAPER_TYPE:
			if (playerSpecific == enemySpecific)
			{
				result = DRAW;
			}
			else if (playerSpecific > enemySpecific)
			{
				result = WIN;
				if (playerSpecific - 1 == enemySpecific)
				{
					m_enemyHPCounter -= basicDmg;
				}
				else
				{
					m_enemyHPCounter -= mediumDmg;
				}
			}
			else if (playerSpecific < enemySpecific)
			{
				result = LOSE;
				if (playerSpecific == enemySpecific - 1)
				{
					m_playerHPCounter -= basicDmg;
				}
				else
				{
					m_playerHPCounter -= mediumDmg;
				}
			}
			break;
		}
	}

	
	displayEnemyIcon();

	//-----------------------------------------------------------------------------------
	//Result Handler --- (Obsolete!)
	//-----------------------------------------------------------------------------------

	switch (result)
	{
	case WIN:
		break;
	case LOSE:
		break;
	case DRAW:
		break;
	}

	//-----------------------------------------------------------------------------------
	//animation
	//-----------------------------------------------------------------------------------
	
	auto showPRef = Show::create();
	auto fadeInPRef = FadeIn::create(0.5);
	auto enlargePRef = ScaleBy::create(0.5, 2);
	auto fadeOutPRef = FadeOut::create(0.5);

	auto showERef = Show::create();
	auto fadeInERef = FadeIn::create(0.5);
	auto enlargeERef = ScaleBy::create(0.5, 2);
	auto fadeOutERef = FadeOut::create(0.5);

	playerReflexion->runAction(Sequence::create(showPRef, fadeInPRef, Spawn::create(enlargePRef, fadeOutPRef, NULL), NULL));
	enemyReflexion->runAction(Sequence::create(showERef, fadeInERef, Spawn::create(enlargeERef, fadeOutERef, NULL), NULL));

	auto playerY = playerCard->getBoundingBox().getMidY();
	auto playerX = playerCard->getPositionX() - 1000;
	auto enemyY = m_visibleSize.height /2;
	auto enemyX = enemyCard->getPositionX() + 1000;

	float time = 0.6f;
	auto playerDelay = DelayTime::create(1);
	auto enemyDelay = DelayTime::create(1);
	auto moveToCenter = MoveTo::create(time, Vec2(m_visibleSize.width / 2, m_visibleSize.height / 2));
	auto moveToCenter2 = MoveTo::create(time, Vec2(m_visibleSize.width / 2, m_visibleSize.height / 2));
	auto movePlayerBack = MoveTo::create(time, Vec2(playerX, playerY));
	auto moveEnemyBack = MoveTo::create(time, Vec2(enemyX, enemyY));

	int j = i + 1;
	CallFunc* recursiveCall = nullptr;
	auto dmgPlayer = CallFunc::create([this](){this->playerGetDMG(); });
	auto dmgEnemy = CallFunc::create([this](){this->enemyGetDMG(); });
	auto colEffect = CallFunc::create([this](){this->collisionEffect(); });
	auto cleanCards = CallFunc::create([this, i](){this->wipeCards(i); });

	if (j < 5)
	{
		recursiveCall = CallFunc::create([this, j](){this->fightCards(j); });
	}
	
	

	if (result == WIN)
	{
		auto denyMark = Sprite::create("img/UI/battle/deny.png");
		denyMark->setScale(0.2);
		denyMark->setPosition(m_enemyMiniCards[i]->getPosition());
		denyMark->setZOrder(20);
		m_instance->addChild(denyMark);

		if (recursiveCall != nullptr)
		{
			enemyCard->runAction(Sequence::create(enemyDelay, moveToCenter2, Spawn::create(moveEnemyBack, dmgEnemy, colEffect, NULL), cleanCards, recursiveCall, NULL));
		}
		else
		{
			enemyCard->runAction(Sequence::create(enemyDelay, moveToCenter2, Spawn::create(moveEnemyBack, dmgEnemy, colEffect, NULL), cleanCards, NULL));
		}
			
		playerCard->runAction(Sequence::create(playerDelay, moveToCenter, NULL));
	}
	else if (result == LOSE)
	{
		auto denyMark = Sprite::create("img/UI/battle/deny.png");
		denyMark->setScale(0.2);
		denyMark->setPosition(m_cards[order[i]]->getPosition());
		denyMark->setZOrder(20);
		m_instance->addChild(denyMark);

		if (recursiveCall != nullptr)
		{
			playerCard->runAction(Sequence::create(playerDelay, moveToCenter, Spawn::create(movePlayerBack, dmgPlayer, colEffect, NULL), cleanCards, recursiveCall, NULL));
		}
		else
		{
			playerCard->runAction(Sequence::create(playerDelay, moveToCenter, Spawn::create(movePlayerBack, dmgPlayer, colEffect, NULL), cleanCards, NULL));
		}
		enemyCard->runAction(Sequence::create(enemyDelay, moveToCenter2, NULL));
	}
	else
	{
		if (recursiveCall != nullptr)
		{
			playerCard->runAction(Sequence::create(playerDelay, moveToCenter, colEffect, movePlayerBack, cleanCards, recursiveCall, NULL));
		}
		else
		{
			playerCard->runAction(Sequence::create(playerDelay, moveToCenter, colEffect, movePlayerBack, cleanCards, NULL));
		}
		enemyCard->runAction(Sequence::create(enemyDelay, moveToCenter2, moveEnemyBack, cleanCards, NULL));
	}

	if (j == 5)
	{
		//end battle
		auto fadeOut = DelayTime::create(2);
		auto callback = CallFunc::create([this](){this->endBattle(); });
		m_instance->runAction(Sequence::create(fadeOut, callback, NULL));
	}
}

void Battle::collisionEffect()
{
	Sprite* sprite = Sprite::create();
	Animation* anim = Animation::create();

	anim->addSpriteFrameWithFileName("img/effect/effects/collision/effect02_orange00000.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/collision/effect02_orange00001.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/collision/effect02_orange00002.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/collision/effect02_orange00003.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/collision/effect02_orange00004.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/collision/effect02_orange00005.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/collision/effect02_orange00006.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/collision/effect02_orange00007.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/collision/effect02_orange00008.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/collision/effect02_orange00009.png");

	anim->setLoops(1);
	anim->setDelayPerUnit(0.03f);
	anim->setRestoreOriginalFrame(true);
	//sprite->setColor(Color3B(100,100,100));
	sprite->runAction(Animate::create(anim));
	sprite->setPosition(m_visibleSize.width / 2, m_visibleSize.height / 2);
	sprite->setScale(m_Mag*1.6);

	m_instance->addChild(sprite);
}

void Battle::playerGetDMG()
{
	displayEnemyHP();
	displayPlayerHP();

	Sprite* sprite = Sprite::create();
	Animation* anim = Animation::create();

	anim->addSpriteFrameWithFileName("img/effect/effects/dmg/effect_001.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/dmg/effect_002.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/dmg/effect_003.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/dmg/effect_004.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/dmg/effect_005.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/dmg/effect_006.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/dmg/effect_007.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/dmg/effect_008.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/dmg/effect_009.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/dmg/effect_010.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/dmg/effect_011.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/dmg/effect_012.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/dmg/effect_013.png");

	anim->setLoops(1);
	anim->setDelayPerUnit(0.07f);
	anim->setRestoreOriginalFrame(true);
	//sprite->setColor(Color3B(100,100,100));
	sprite->runAction(Animate::create(anim));
	sprite->setPosition(Vec2(m_visibleSize.width / 4.8, m_visibleSize.height / 5));
	sprite->setScale(m_Mag*1.2);

	m_instance->addChild(sprite);
}

void Battle::enemyGetDMG()
{
	displayEnemyHP();
	displayPlayerHP();

	Sprite* sprite = Sprite::create();
	Animation* anim = Animation::create();

	anim->addSpriteFrameWithFileName("img/effect/effects/dmg/effect_001.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/dmg/effect_002.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/dmg/effect_003.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/dmg/effect_004.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/dmg/effect_005.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/dmg/effect_006.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/dmg/effect_007.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/dmg/effect_008.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/dmg/effect_009.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/dmg/effect_010.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/dmg/effect_011.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/dmg/effect_012.png");
	anim->addSpriteFrameWithFileName("img/effect/effects/dmg/effect_013.png");

	anim->setLoops(1);
	anim->setDelayPerUnit(0.07f);
	anim->setRestoreOriginalFrame(true);
	//sprite->setColor(Color3B(100,100,100));
	sprite->runAction(Animate::create(anim));
	sprite->setPosition(Vec2(m_visibleSize.width / 1.25, m_visibleSize.height / 5));
	sprite->setScale(m_Mag*1.2);

	m_instance->addChild(sprite);
}

void Battle::endBattle()
{
	UserDefault* def = UserDefault::getInstance();

	if (m_playerHPCounter > m_enemyHPCounter)
	{
		def->setIntegerForKey(SaveDataKey[n_DataKeyNum::eWinResult01 + m_battleNum].c_str(), 0);
		result = Sprite::create("img/UI/battle/UI_B_012.png");
	}
	else if (m_playerHPCounter == m_enemyHPCounter)
	{
		def->setIntegerForKey(SaveDataKey[n_DataKeyNum::eWinResult01 + m_battleNum].c_str(), 1);
		result = Sprite::create("img/UI/battle/UI_B_014.png");
	}
	else if (m_playerHPCounter < m_enemyHPCounter)
	{
		def->setIntegerForKey(SaveDataKey[n_DataKeyNum::eWinResult01 + m_battleNum].c_str(), 2);
		result = Sprite::create("img/UI/battle/UI_B_013.png");
	}

	if (result != nullptr)
	{
		result->setPosition(Vec2(m_visibleSize.width / 2, m_visibleSize.height / 2));
		m_instance->addChild(result);
	}
}

void Battle::wipeCards(int i)
{
	m_instance->removeChild(enemyCard);
	m_instance->removeChildByName("pCard");
	m_instance->removeChildByName("pRef");
	m_instance->removeChildByName("eRef");
}

void Battle::genEnemyCards()
{
	int randomNum;
	
	auto fileU = FileUtils::getInstance();
	auto fileContent = fileU->getStringFromFile("data/monsterData.xml");
	mData.Parse(fileContent.c_str());
	UserDefault* def = UserDefault::getInstance();
	int key = def->getIntegerForKey(SaveDataKey[n_DataKeyNum::eEnemyMonster01 + m_battleNum].c_str());

	int rockProb = atoi(mData.FirstChildElement()->FirstChildElement(MonsterNameData[key].c_str())->FirstChildElement("luck")->FirstChildElement("rock")->GetText());
	int sissorsProb = atoi(mData.FirstChildElement()->FirstChildElement(MonsterNameData[key].c_str())->FirstChildElement("luck")->FirstChildElement("sissors")->GetText());
	int paperProb = atoi(mData.FirstChildElement()->FirstChildElement(MonsterNameData[key].c_str())->FirstChildElement("luck")->FirstChildElement("paper")->GetText());
	//int monsterLevel = atoi(mData.FirstChildElement()->FirstChildElement(MonsterNameData[key].c_str())->FirstChildElement("special")->FirstChildElement("level")->GetText());

	m_enemyHPCounter = atoi(mData.FirstChildElement()->FirstChildElement(MonsterNameData[key].c_str())->FirstChildElement("HP")->GetText());

	int specialProb = rockProb + sissorsProb + paperProb;

	srand(time(NULL));

	for (int i = 0; i < 5; i++)
	{
		randomNum = rand() % 100;
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
			else if (randomNum >(rockProb + sissorsProb))
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

		enemyData[i] = randomNum;
	}

	int randomPlace = rand() % 5;
	enemyData[randomPlace] = m_enemySpecialType;//-----------------------------enemy special card
}

void Battle::battlePhase(int hp, int* cardType, int pSpecial, int eSpecial, int battleNumber)
{
	m_playerHPCounter = hp;
	for (int i = 0; i < 4; i++)
	{
		cardData[i] = cardType[i];
	}
	m_specialType = pSpecial;
	m_enemySpecialType = eSpecial;
	m_battleNum = battleNumber;

	cardData[4] = m_specialType;

	eventHandler();
}

void Battle::cleanUp()
{
	m_instance->removeChild(instructions);
	for (int i = 0; i < 5; i++)
	{
		m_instance->removeChild(orderText[i]);
	}
	m_instance->removeChild(m_menu);
	m_menu = nullptr;

	for (int i = 0; i < 5; i++)
	{
		//m_cards[i]->setPosition(m_cards[i]->getPosition().x, (m_cards[i]->getPosition().y - 50));
		//m_cards[i]->setColor(Color3B(255, 255, 255));
		m_selected[i] = false;
		//m_cards[i]->setVisible(false);
	}

	battleBegan = false;
}