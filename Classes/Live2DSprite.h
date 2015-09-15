/**
*
*
You can modify and use this source freely
*  only for the development of application related Live2D.
*
*  (c) Live2D Inc. All rights reserved.
*/

#ifndef _Live2DSprite_H_
#define _Live2DSprite_H_

#include "cocos2d.h"
#include "2d/CCSprite.h"
#include <vector>
#include "../live2d/include/Live2DModelOpenGL.h"
//#include "rapidxml/rapidxml.hpp"
#include "tinyxml2/tinyxml2.h"
#include <fstream>
#include <string>

class Live2DSprite :public cocos2d::DrawNode {
private:
	live2d::Live2DModelOpenGL* m_live2DModel;
	std::vector<cocos2d::Texture2D*> m_textures;
	//rapidxml::xml_document<> doc;
	tinyxml2::XMLDocument doc;
	std::string m_spriteName;

public:
	Live2DSprite(std::string spriteName, float scaleX, float scaleY, float posX, float posY);
	virtual ~Live2DSprite();

	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
	void onDraw(const cocos2d::Mat4 &transform, uint32_t flags);
	static Live2DSprite* createDrawNode(std::string spriteName, float scaleX, float scaleY, float posX, float posY);
protected:
	void releaseTexture();
	cocos2d::CustomCommand _customCommand;
};

#endif

