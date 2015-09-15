#include "AppDelegate.h"
#include "TitleScene.h"
#include "../Live2D/include/Live2D.h"

#ifdef L2D_TARGET_ANDROID_ES2
#include "graphics/DrawParam_OpenGLES2.h"
#endif


using namespace live2d;
USING_NS_CC;

AppDelegate::AppDelegate() 
{
}

AppDelegate::~AppDelegate() 
{
	Live2D::dispose();
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#ifdef L2D_TARGET_ANDROID_ES2
		glview = GLViewImpl::create("MillionCode");
#else
		glview = GLViewImpl::create("MillionCode");
		glview->setFrameSize(1280, 720);
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	//Live2D initialization
	Live2D::init();

	//Extra init for Android
	#ifdef L2D_TARGET_ANDROID_ES2
		char *exts = (char*)glGetString(GL_EXTENSIONS);
		if (strstr(exts, "GL_NV_shader_framebuffer_fetch ")){
			live2d::DrawParam_OpenGLES2::setExtShaderMode(true, true);
		}
	#endif

    // create a scene. it's an autorelease object
    auto scene = TitleScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    //SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
