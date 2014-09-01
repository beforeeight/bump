#include "AppDelegate.h"
#include "AppMacros.h"
#include "SimpleAudioEngine.h"
#include "MenuLayer.h"
#include "MainLayer.h"
//#include "FinishLayer.h"

USING_NS_CC;

using namespace CocosDenshion;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
	// initialize director
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
	pDirector->setOpenGLView(pEGLView);
	pEGLView->setDesignResolutionSize(designResolutionSize.width,
			designResolutionSize.height, kResolutionFixedWidth);
	// turn on display FPS
	pDirector->setDisplayStats(false);

	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 60);

	//CCFileUtils::sharedFileUtils()->addSearchPath("");
	CCFileUtils::sharedFileUtils()->addSearchResolutionsOrder("iphone/");

	this->loadResources();

	CCScene *pScene = MenuLayer::scene();
	//CCScene *pScene = CCScene::create();
	pDirector->runWithScene(pScene);
	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
	CCDirector::sharedDirector()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
	CCDirector::sharedDirector()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void AppDelegate::showMenu()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCScene *pScene = MenuLayer::scene();
	pDirector->replaceScene(pScene);
}

void AppDelegate::showGame()
{

	//CCDirector* pDirector = CCDirector::sharedDirector();
	//pDirector->popScene();
	//CCScene *pScene = MainLayer::scene();
	//pDirector->pushScene(pScene);
}

void AppDelegate::showCounter()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCScene *pScene = MenuLayer::scene();
	pDirector->replaceScene(pScene);
}

void AppDelegate::loadResources() const
{
	//SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("music.mp3");
	//SimpleAudioEngine::sharedEngine()->preloadEffect("explosive.mp3");
	// create TARGET_DESIGN_RESOLUTION_SIZEa scene. it's an autorelease object
	//SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music.mp3");
	//CCTextureCache::sharedTextureCache()->addImage("airplan.png");

	CCTextureCache::sharedTextureCache()->addImage(("background.png"));
	CCTextureCache::sharedTextureCache()->addImage(("bg_bridge.png"));
	CCTextureCache::sharedTextureCache()->addImage(("pic_bird.png"));
	CCTextureCache::sharedTextureCache()->addImage(("pic_plane.png"));
	CCTextureCache::sharedTextureCache()->addImage(("bg_score.png"));
	CCTextureCache::sharedTextureCache()->addImage(("btn_big.png"));
	CCTextureCache::sharedTextureCache()->addImage(("btn_small.png"));
	CCTextureCache::sharedTextureCache()->addImage(("bg_gameover.png"));
	CCTextureCache::sharedTextureCache()->addImage(("dragon_big_1.png"));
	CCTextureCache::sharedTextureCache()->addImage(("dragon_small_1.png"));
	CCTextureCache::sharedTextureCache()->addImage(("ultraman_big_1.png"));
	CCTextureCache::sharedTextureCache()->addImage(("ultraman_small_1.png"));
	CCTextureCache::sharedTextureCache()->addImage(("pic_door.png"));
	CCTextureCache::sharedTextureCache()->addImage(("pic_door_light.png"));
	CCTextureCache::sharedTextureCache()->addImage(("pic_light_1.png"));
	CCTextureCache::sharedTextureCache()->addImage(("pic_light_2.png"));

//	CCTextureCache::sharedTextureCache()->addImage(respath("btn_feedback.png"));
//	CCTextureCache::sharedTextureCache()->addImage(
//			respath("btn_sound_off.png"));
//	CCTextureCache::sharedTextureCache()->addImage(respath("btn_sound_on.png"));

	/*Enemy Plane Explosion Animation*/
//	CCTextureCache::sharedTextureCache()->addImage("explode.png");
//	CCArray *explosions = CCArray::createWithCapacity(12);
//	for (int i = 0; i < 12; i++)
//	{
//		explosions->addObject(
//				CCSpriteFrame::createWithTexture(
//						CCTextureCache::sharedTextureCache()->textureForKey(
//								"explode.png"), CCRectMake(i * 64, 0, 64, 64)));
//	}
//	CCAnimation *exAnimation = CCAnimation::createWithSpriteFrames(explosions);
//	exAnimation->setDelayPerUnit(0.05f);
//	CCAnimationCache::sharedAnimationCache()->addAnimation(exAnimation,
//			"explosion");
}
