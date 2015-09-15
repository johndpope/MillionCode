//
//  LinkJava.cpp
//  MillionCode
//
//  Created by æœ¨æ�‘å·§ on 2015/04/20.
//
//
#include "LinkJava.h"
#include <string>

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "platform/android/jni/JniHelper.h"
#include <jni.h>

using namespace cocos2d;

// å‘¼ã�³å‡ºã�—å…ˆã�®ãƒ¡ã‚½ãƒƒãƒ‰ã‚’è¨˜è¼‰ã�—ã�¦ã�„ã‚‹ãƒ‘ãƒƒã‚±ãƒ¼ã‚¸å��ã�¨ã‚¯ãƒ©ã‚¹å��ã‚’defineã�§å®šç¾©ã�—ã�¦ã�Šã��
#define CLASS_NAME  "org/cocos2dx/cpp/QrReader"
#define CLASS_NAME2 "org/cocos2dx/cpp/AppActivity"

std::string LinkJava::JavaEvent()
{
	JniMethodInfo methodInfo;
    
    // ã‚¯ãƒ©ã‚¹å��ã�¨ãƒ¡ã‚½ãƒƒãƒ‰å��ã‚’æŒ‡å®š
    if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME2, "JavaEvent", "()Ljava/lang/String;")) {
        
        //Javaå�´ã�®ãƒ¡ã‚½ãƒƒãƒ‰ã‚’å®Ÿè¡Œã�™ã‚‹
		jstring returnData = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
        //é–‹æ”¾
        methodInfo.env->DeleteLocalRef(methodInfo.classID);

        const char* dataString = methodInfo.env->GetStringUTFChars(returnData, NULL);
        std::string data(dataString);
        methodInfo.env->ReleaseStringUTFChars(returnData, dataString);

        if(data == "")
        {
        	data == "1";
        }

        return data;
    }
    else
    {
            return "www.defaulturl.com";
    }
}

std::string LinkJava::GetData()
{
	JniMethodInfo methodInfo;

	// ã‚¯ãƒ©ã‚¹å��ã�¨ãƒ¡ã‚½ãƒƒãƒ‰å��ã‚’æŒ‡å®š
	if (JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME2, "GetData", "()Ljava/lang/String;")) {

		//Javaå�´ã�®ãƒ¡ã‚½ãƒƒãƒ‰ã‚’å®Ÿè¡Œã�™ã‚‹
		jstring returnData = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
		//é–‹æ”¾
		methodInfo.env->DeleteLocalRef(methodInfo.classID);

		const char* dataString = methodInfo.env->GetStringUTFChars(returnData, NULL);
		std::string data(dataString);
		methodInfo.env->ReleaseStringUTFChars(returnData, dataString);

		if (data == "")
		{
			data == "1";
		}

		return data;
	}
	else
	{
		return "www.defaulturl.com";
	}
}

#endif
