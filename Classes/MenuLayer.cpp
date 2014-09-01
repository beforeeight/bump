/*
 * MenuLayer.cpp
 *
 *  Created on: Aug 28, 2014
 *      Author: zhangchen
 */
#include "SimpleAudioEngine.h"
#include "MenuLayer.h"
#include "MainLayer.h"
#include "BgLayer.h"
#include "Counter.h"
#include "AppMacros.h"

using namespace CocosDenshion;

MenuLayer::MenuLayer()
{
	// TODO Auto-generated constructor stub

}

MenuLayer::~MenuLayer()
{
	// TODO Auto-generated destructor stub
}

bool MenuLayer::init()
{
	if (CCMenu::init())
	{

		CCSize vsize = CCDirector::sharedDirector()->getVisibleSize();
		float width = vsize.width / 2;
		float height = vsize.height / 2;
		/* initialize the counter */
		Counter *counter = Counter::sharedCounter();
		CCTextureCache *cache = CCTextureCache::sharedTextureCache();

		/*-- 背景 --*/
		this->addChild(BgLayer::create());

		/*-- 所有按钮 --*/
		//声音
		CCSprite *soundbg = CCSprite::createWithTexture(
				cache->textureForKey(("btn_small.png")));

		CCMenuItemImage *soundon = CCMenuItemImage::create(("btn_sound_on.png"),
				("btn_sound_on.png"));
		CCMenuItemImage *soundoff = CCMenuItemImage::create(
				("btn_sound_off.png"), ("btn_sound_off.png"));
		CCMenuItemToggle *soundtxt;
		if (counter->isSound())
		{
			soundtxt = CCMenuItemToggle::create(soundon);
			soundtxt->addSubItem(soundoff);
		}
		else
		{
			soundtxt = CCMenuItemToggle::create(soundoff);
			soundtxt->addSubItem(soundon);
		}
		soundtxt->setTarget(soundtxt, menu_selector(MenuLayer::onSoundItem));

		soundbg->setPosition(ccp(-width + 15, height - 15));
		soundbg->setAnchorPoint(ccp(0, 1));
		soundtxt->setPosition(
				ccp(
						soundbg->getPosition().x
								+ soundbg->getContentSize().width / 2,
						soundbg->getPosition().y
								- soundbg->getContentSize().height / 2));

//		soundtxt->setAnchorPoint(ccp(0.5, 0.5));
		this->addChild(soundtxt, 3);
		this->addChild(soundbg, 2);
		//反馈
		CCMenuItemImage *feedbackbg = CCMenuItemImage::create(("btn_small.png"),
				("btn_small.png"), this,
				menu_selector(MenuLayer::onFeedbackItem));
		CCMenuItemImage *feedbacktxt = CCMenuItemImage::create(
				("btn_feedback.png"), ("btn_feedback.png"));
		feedbackbg->setPosition(ccp(width - 15, height - 15));
		feedbackbg->setAnchorPoint(ccp(1, 1));
		feedbacktxt->setPosition(
				ccp(feedbackbg->getContentSize().width / 2,
						feedbackbg->getContentSize().height / 2));
		this->addChild(feedbackbg, 2);
		feedbackbg->addChild(feedbacktxt, 3);
		//开始游戏
		CCMenuItemImage *startbg = CCMenuItemImage::create(("btn_big.png"),
				("btn_big.png"), this, menu_selector(MenuLayer::onStartItem));
		CCMenuItemFont *starttxt = CCMenuItemFont::create("start game");
		startbg->setPosition(ccp(1, -160));
		startbg->setAnchorPoint(ccp(0.5, 0.5));
		starttxt->setPosition(
				ccp(startbg->getContentSize().width / 2,
						startbg->getContentSize().height / 2));
		this->addChild(startbg, 2);
		startbg->addChild(starttxt, 3);

		//排行榜
		CCMenuItem *rankingbg = CCMenuItemImage::create(("btn_big.png"),
				("btn_big.png"), this, menu_selector(MenuLayer::onRankingItem));
		CCMenuItemFont *rankingtxt = CCMenuItemFont::create("Ranking");
		rankingbg->setPosition(
				ccp(1,
						startbg->getPosition().y
								- (startbg->getContentSize().height) - 20));
		rankingbg->setAnchorPoint(ccp(0.5, 0.5));
		rankingtxt->setPosition(
				ccp(rankingbg->getContentSize().width / 2,
						rankingbg->getContentSize().height / 2));
		this->addChild(rankingbg, 2);
		rankingbg->addChild(rankingtxt);

		//更多游戏
		CCMenuItem *morebg = CCMenuItemImage::create(("btn_big.png"),
				("btn_big.png"), this, menu_selector(MenuLayer::onMoreItem));
		CCMenuItemFont *moretxt = CCMenuItemFont::create("More Games");
		morebg->setPosition(
				ccp(0,
						rankingbg->getPosition().y
								- (rankingbg->getContentSize().height) - 20));
		morebg->setAnchorPoint(ccp(0.5, 0.5));
		moretxt->setPosition(
				ccp(morebg->getContentSize().width / 2,
						morebg->getContentSize().height / 2));
		this->addChild(morebg, 2);
		morebg->addChild(moretxt);

		return true;
	}
	else
	{
		return false;
	}
}

CCScene * MenuLayer::scene()
{
	CCScene *scene = CCScene::create();
	if (scene && scene->init())
	{
		if (scene)
		{
			MenuLayer *layer = MenuLayer::create();
			scene->addChild(layer);
		}
		return scene;
	}
	else
	{
		CC_SAFE_DELETE(scene);
		return NULL;
	}
}

void MenuLayer::onSoundItem(CCObject *object)
{
	CCMenuItemToggle *soundtxt = (CCMenuItemToggle *) object;
	Counter *counter = Counter::sharedCounter();
	if (counter->isSound())
	{
		//trun off
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();

		CCLog("关音乐");
	}
	else
	{
		//trun on
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();

		CCLog("开音乐");
	}
	counter->toggleSound();
}

void MenuLayer::onFeedbackItem(CCObject *object)
{
	CCLog("反馈");
}

void MenuLayer::onStartItem(CCObject *object)
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCScene *pScene = MainLayer::scene();
	pDirector->replaceScene(pScene);
}

void MenuLayer::onRankingItem(CCObject *object)
{
	CCLog("排行榜");
}

void MenuLayer::onMoreItem(CCObject *object)
{
	CCLog("更多游戏");
}

