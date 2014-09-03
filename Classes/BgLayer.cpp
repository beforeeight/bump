/*
 * BgLayer.cpp
 *
 *  Created on: Aug 31, 2014
 *      Author: zhangchen
 */

#include "BgLayer.h"
#include "Counter.h"
#include "AppMacros.h"

BgLayer::BgLayer()
{
	// TODO Auto-generated constructor stub

}

BgLayer::~BgLayer()
{
	// TODO Auto-generated destructor stub
}

bool BgLayer::init()
{
	if (CCLayer::init())
	{
		CCSize s = CCDirector::sharedDirector()->getWinSize();
		this->ignoreAnchorPointForPosition(true);
		setAnchorPoint(ccp(0.5f, 0.5f));
		this->setContentSize(s);
		setPosition(ccp(s.width / 2, s.height / 2));
		CCSize vsize = CCDirector::sharedDirector()->getVisibleSize();
		float width = vsize.width / 2;
		float height = vsize.height / 2;
		/* initialize the counter */
		Counter *counter = Counter::sharedCounter();
		CCTextureCache *cache = CCTextureCache::sharedTextureCache();
		/*-- 背景 --*/
		CCSprite *bg = CCSprite::createWithTexture(
				cache->textureForKey(("background.png")));
		this->addChild(bg, 0);

		CCSprite *bridge = CCSprite::createWithTexture(
				cache->textureForKey(("bg_bridge.png")));
		bridge->setPosition(ccp(0, -height));
		bridge->setAnchorPoint(ccp(0.5, 0));
		this->addChild(bridge, 1);

		/*-- 小鸟 --*/
		CCSprite *bird = CCSprite::createWithSpriteFrameName("bird_1.png");
		bird->setPosition(ccp(width + bird->getContentSize().width, 180));
		this->addChild(bird, 1);
		CCAnimation *birdAnimation =
				CCAnimationCache::sharedAnimationCache()->animationByName(
						"bird");
		bird->runAction(
				CCRepeatForever::create(CCAnimate::create(birdAnimation)));
		bird->runAction(
				CCRepeatForever::create(
						CCSequence::create(
								CCMoveTo::create(2,
										ccp(
												-width
														- bird->getContentSize().width,
												bird->getPositionY())),
								CCFlipX::create(true),
								CCDelayTime::create(1.0f),
								CCMoveTo::create(2,
										ccp(
												width
														+ bird->getContentSize().width,
												bird->getPositionY())),
								CCFlipX::create(false),
								NULL)));

		/*-- 飞机 --*/
		CCSprite *plane = CCSprite::createWithSpriteFrameName("plane_1.png");
		plane->setPosition(ccp(width + plane->getContentSize().width, 180));
		this->addChild(plane, 1);
		CCAnimation *planeAnimation =
				CCAnimationCache::sharedAnimationCache()->animationByName(
						"plane");
		plane->runAction(
				CCRepeatForever::create(CCAnimate::create(planeAnimation)));

		plane->runAction(
				CCRepeatForever::create(
						CCSequence::create(CCDelayTime::create(0.5f),
								CCMoveTo::create(2,
										ccp(
												-width
														- plane->getContentSize().width,
												plane->getPositionY())),
								CCFlipX::create(true),
								CCMoveTo::create(2,
										ccp(
												width
														+ plane->getContentSize().width,
												plane->getPositionY())),
								CCFlipX::create(false),
								CCDelayTime::create(0.5f),
								NULL)));

		/*-- 计分 --*/
		//当前得分
		CCSprite *title = CCLabelTTF::createWithTexture(
				cache->textureForKey(("bg_score.png")));
		title->setPosition(ccp(0, height - 30));
		title->setAnchorPoint(ccp(0.5, 1));
		this->addChild(title);
		return true;
	}
	else
	{
		return false;
	}
}
