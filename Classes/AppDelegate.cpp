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
			designResolutionSize.height, kResolutionShowAll);
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
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm.mp3");
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
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("bgm.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("click.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("boom.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("jump.mp3");
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("gameover.mp3");

	// create TARGET_DESIGN_RESOLUTION_SIZEa scene. it's an autorelease object
	//SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music.mp3");
	//CCTextureCache::sharedTextureCache()->addImage("airplan.png");
	CCTextureCache::sharedTextureCache()->addImage(("background.png"));
	CCTextureCache::sharedTextureCache()->addImage(("bg_bridge.png"));
	CCTextureCache::sharedTextureCache()->addImage(("bg_score.png"));
	CCTextureCache::sharedTextureCache()->addImage(("btn_big.png"));
	CCTextureCache::sharedTextureCache()->addImage(("btn_small.png"));
	CCTextureCache::sharedTextureCache()->addImage(("bg_gameover.png"));

//	CCTextureCache::sharedTextureCache()->addImage(respath("btn_feedback.png"));
//	CCTextureCache::sharedTextureCache()->addImage(
//			respath("btn_sound_off.png"));
//	CCTextureCache::sharedTextureCache()->addImage(respath("btn_sound_on.png"));

	/*-- Animation --*/
	CCSpriteFrameCache *frameCache =
			CCSpriteFrameCache::sharedSpriteFrameCache();
	CCAnimationCache *animCache = CCAnimationCache::sharedAnimationCache();
	char str[100] =
	{ 0 };
	/*-- 鸟动画 2帧 --*/
	frameCache->addSpriteFramesWithFile("bird.plist");
	CCArray *birds = CCArray::createWithCapacity(2);
	for (unsigned int i = 0; i < birds->capacity(); i++)
	{
		sprintf(str, "bird_%d.png", i + 1);
		birds->addObject(frameCache->spriteFrameByName(str));
	}
	CCAnimation *bird = CCAnimation::createWithSpriteFrames(birds);
	bird->setDelayPerUnit(0.2f);
	animCache->addAnimation(bird, "bird");

	/*-- 飞机动画 --*/
	frameCache->addSpriteFramesWithFile("plane.plist");
	CCArray *planes = CCArray::createWithCapacity(2);
	for (unsigned int i = 0; i < planes->capacity(); i++)
	{
		sprintf(str, "plane_%d.png", i + 1);
		planes->addObject(frameCache->spriteFrameByName(str));
	}
	CCAnimation *plane = CCAnimation::createWithSpriteFrames(planes);
	plane->setDelayPerUnit(0.1f);
	animCache->addAnimation(plane, "plane");

	/*-- 爆炸动画 --*/
	frameCache->addSpriteFramesWithFile("boom.plist");
	CCArray *booms = CCArray::createWithCapacity(8);
	for (unsigned int i = 0; i < booms->capacity(); i++)
	{
		sprintf(str, "boom_%d.png", i + 1);
		booms->addObject(frameCache->spriteFrameByName(str));
	}
	CCAnimation *boom = CCAnimation::createWithSpriteFrames(booms);
	boom->setDelayPerUnit(1.0f / 8.0f);
	animCache->addAnimation(boom, "boom");

	/*-- 门动画 --*/
	frameCache->addSpriteFramesWithFile("door.plist");
	CCArray *doors = CCArray::createWithCapacity(2);
	for (unsigned int i = 0; i < doors->capacity(); i++)
	{
		sprintf(str, "door_%d.png", i + 1);
		doors->addObject(frameCache->spriteFrameByName(str));
	}
	CCAnimation *door = CCAnimation::createWithSpriteFrames(doors);
	door->setDelayPerUnit(0.01f);
	animCache->addAnimation(door, "door");

	/*-- 怪兽动画 --*/
	frameCache->addSpriteFramesWithFile("dragon_big.plist");
	CCArray *dragons = CCArray::createWithCapacity(15);
	CCArray *dragonjumps = CCArray::createWithCapacity(3);
	for (unsigned int i = 0; i < 18; i++)
	{
		sprintf(str, "dragon_big_%d.png", i + 1);
		if (i < 15)
		{
			dragons->addObject(frameCache->spriteFrameByName(str));
		}
		else
		{
			dragonjumps->addObject(frameCache->spriteFrameByName(str));
		}
	}
	CCAnimation *dragon = CCAnimation::createWithSpriteFrames(dragons);
	CCAnimation *dragonjump = CCAnimation::createWithSpriteFrames(dragonjumps);
	dragon->setDelayPerUnit(0.07f);
	dragonjump->setDelayPerUnit(0.25f);
	animCache->addAnimation(dragon, "dragon");
	animCache->addAnimation(dragonjump, "dragonjump");

	/*-- 奥特曼动画 --*/
	frameCache->addSpriteFramesWithFile("ultraman_big.plist");
	CCArray *ultramans = CCArray::createWithCapacity(15);
	CCArray *ultramanjumps = CCArray::createWithCapacity(3);
	for (unsigned int i = 0; i < 18; i++)
	{
		sprintf(str, "ultraman_big_%d.png", i + 1);
		if (i < 15)
		{
			ultramans->addObject(frameCache->spriteFrameByName(str));
		}
		else
		{
			ultramanjumps->addObject(frameCache->spriteFrameByName(str));
		}
	}
	CCAnimation *ultraman = CCAnimation::createWithSpriteFrames(ultramans);
	CCAnimation *ultramanjump = CCAnimation::createWithSpriteFrames(
			ultramanjumps);
	ultraman->setDelayPerUnit(0.07f);
	ultramanjump->setDelayPerUnit(0.25f);
	animCache->addAnimation(ultraman, "ultraman");
	animCache->addAnimation(ultramanjump, "ultramanjump");
}
