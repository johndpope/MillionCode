//
//  LinkCpp.cpp
//  MillionCode
//
//  Created by æœ¨æ�‘å·§ on 2015/04/20.
//
//
#include "Generic.h"
#include "cocos2d.h"
#include "platform\android\jni\JniHelper.h"

#include "LinkCpp.h"

using namespace cocos2d;

extern "C"
{
	JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_QrReader_Java2CEvent(JNIEnv* env, jobject thiz, jstring filePath)
	{
		const char* path = env->GetStringUTFChars(filePath, NULL);

		if(path == "")
		{
			path = "www.fuckthisshit.com";
		}

		UserDefault* userDef = UserDefault::getInstance();
		userDef->setStringForKey("SeedString", path);
		userDef->setBoolForKey("IsSeedGet", true);
		userDef->flush();

		env->ReleaseStringUTFChars(filePath, path);
	}
}

