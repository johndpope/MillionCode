//
//  LinkJava.h
//  MillionCode
//
//  Created by æœ¨æ�‘å·§ on 2015/04/20.
//
//

#ifndef __MillionCode__LinkJava__
#define __MillionCode__LinkJava__

#include <cocos2d.h>
#include <string>

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
class LinkJava
{
public:
    static std::string JavaEvent();
	static std::string GetData();
};

#endif /* if() */

#endif /* defined(__MillionCode__LinkJava__) */
