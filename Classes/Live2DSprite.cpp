/**
*

*  You can modify and use this source freely
*  only for the development of application related Live2D.
*
*  (c) Live2D Inc. All rights reserved.
*/

#include "Live2DSprite.h"
#include "base/CCDirector.h"
#include "../live2d/include//util/UtSystem.h"
#include "../live2d/include//graphics/DrawProfileCocos2D.h"
#include "platform/CCFileUtils.h"

using namespace live2d;
using namespace tinyxml2;
USING_NS_CC;

Live2DSprite::Live2DSprite( std::string spriteName, float scaleX, float scaleY, float posX, float posY )
	:m_spriteName(spriteName) //Copy of the sprite name
{
	auto fileU = FileUtils::getInstance();
	auto fileContent = fileU->getStringFromFile("data/animData.xml");

	doc.Parse(fileContent.c_str());
	auto sprite = doc.FirstChildElement()->FirstChildElement(m_spriteName.c_str());

	unsigned char* buf;
	ssize_t bufSize;
	buf = FileUtils::getInstance()->getFileData(sprite->FirstChildElement("model")->GetText(), "rb", &bufSize);

	m_live2DModel = Live2DModelOpenGL::loadModel(buf, bufSize);
	free(buf);
	
	int i = 0;
	for (auto textureList = sprite->FirstChildElement("textureList")->FirstChildElement(); textureList; textureList = textureList->NextSiblingElement())
	{
		auto texture = Director::getInstance()->getTextureCache()->addImage(std::string(textureList->GetText()));
		Texture2D::TexParams texParams = { GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE };
		texture->setTexParameters(texParams);
		texture->generateMipmap();

		int glTexNo = texture->getName();

		m_live2DModel->setTexture(i, glTexNo);
		m_textures.push_back(texture);
		i++;
	}

	float w = Director::getInstance()->getWinSize().width;
	float h = Director::getInstance()->getWinSize().height;
	float scx = scaleX / m_live2DModel->getCanvasWidth();
	float scy = -scaleY / m_live2DModel->getCanvasWidth() * (w / h);
	float x = -posX;
	float y = posY;
	float matrix[] = {
		scx, 0, 0, 0,
		0, scy, 0, 0,
		0, 0, 1, 0,
		x, y, 0, 1
	};

	m_live2DModel->setMatrix(matrix);

	m_live2DModel->setPremultipliedAlpha(true);
}

void Live2DSprite::releaseTexture()
{
	auto fileU = FileUtils::getInstance();
	auto fileContent = fileU->getStringFromFile("data/animData.xml");

	doc.Parse(fileContent.c_str());
	auto sprite = doc.FirstChildElement()->FirstChildElement(m_spriteName.c_str());

	for (auto textureList = sprite->FirstChildElement("textureList")->FirstChildElement(); textureList; textureList = textureList->NextSiblingElement())
	{
		Director::getInstance()->getTextureCache()->removeTextureForKey(std::string(textureList->GetText()));
		//Director::getInstance()->getTextureCache()->removeUnusedTextures();
	}
}

Live2DSprite::~Live2DSprite()
{
	delete m_live2DModel;
	//releaseTexture();
}


void Live2DSprite::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
	DrawNode::draw(renderer, transform, flags);

	_customCommand.init(_globalZOrder);
	_customCommand.func = CC_CALLBACK_0(Live2DSprite::onDraw, this, transform, flags);
	renderer->addCommand(&_customCommand);
}

void Live2DSprite::onDraw(const cocos2d::Mat4 &transform, uint32_t flags)
{
	kmGLPushMatrix();
	kmGLLoadMatrix(&transform);

	double t = (UtSystem::getUserTimeMSec() / 1000.0) * 2 * M_PI;
	double cycle = 3.0;
	double cycle2 = 8.0;
	double cycle3 = 6.0;
	double value = sin(t / cycle);
	double value2 = sin(t / cycle2);
	double value3 = sin(t / cycle3);
	m_live2DModel->setParamFloat("PARAM_MOUTH_OPEN_Y", (float)(20 * value2) - 19);
	m_live2DModel->setParamFloat("PARAM_BODY_ANGLE_X", (float)(10 * value));
	m_live2DModel->setParamFloat("PARAM_EYE_L_OPEN", (float)((20 * value3) + 20));
	m_live2DModel->setParamFloat("PARAM_EYE_R_OPEN", (float)((20 * value3) + 20));
	m_live2DModel->setParamFloat("PARAM_HAIR_SIDE", (float)(( value3)));
	m_live2DModel->setParamFloat("PARAM_HAIR_BACK", (float)(( value3)));
	m_live2DModel->setParamFloat("PARAM_BREATH", (float)(value));
	m_live2DModel->setParamFloat("PARAM_BODY_ANGLE_Z", (float)((10 * value3)));
	m_live2DModel->setParamFloat("PARAM_BODY_ANGLE_W", (float)((10 * value3)));
	m_live2DModel->setParamFloat("PARAM_HAIR_FRONT", (float)(( value3)));
	
	live2d::DrawProfileCocos2D::preDraw();

	m_live2DModel->update();
	m_live2DModel->draw();

	live2d::DrawProfileCocos2D::postDraw();

	kmGLPopMatrix();
}

Live2DSprite* Live2DSprite::createDrawNode(std::string spriteName, float scaleX, float scaleY, float posX, float posY)
{
	Live2DSprite *ret = new Live2DSprite(spriteName, scaleX, scaleY, posX, posY);
	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}


