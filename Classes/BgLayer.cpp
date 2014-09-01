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

		CCSize vsize = CCDirector::sharedDirector()->getVisibleSize();
		float width = vsize.width / 2;
		float height = vsize.height / 2;
		/* initialize the counter */
		Counter *counter = Counter::sharedCounter();
		CCTextureCache *cache = CCTextureCache::sharedTextureCache();
		/*-- 背景 --*/
		CCLog(CCFileUtils::sharedFileUtils()->fullPathForFilename("background.png").c_str());
		CCSprite *bg = CCSprite::createWithTexture(
				cache->textureForKey(("background.png")));
		this->addChild(bg, 0);

		CCSprite *bridge = CCSprite::createWithTexture(
				cache->textureForKey(("bg_bridge.png")));
		bridge->setPosition(ccp(0, -height));
		bridge->setAnchorPoint(ccp(0.5, 0));
		this->addChild(bridge, 1);

		CCSprite *bird = CCSprite::createWithTexture(
				cache->textureForKey(("pic_bird.png")));
		bird->setPosition(ccp(150, 180));
		this->addChild(bird, 1);

		CCSprite *plane = CCSprite::createWithTexture(
				cache->textureForKey(("pic_plane.png")));
		plane->setPosition(ccp(260, 180));
		this->addChild(plane, 1);

		/*-- 计分 --*/
		//当前得分
		CCSprite *title = CCLabelTTF::createWithTexture(
				cache->textureForKey(("bg_score.png")));
		title->setPosition(ccp(0, height - 30));
		title->setAnchorPoint(ccp(0.5, 1));

		CCLabelTTF *titletxt = CCLabelTTF::create();
		titletxt->setString(counter->getDisplayCounter());
		titletxt->setFontSize(30);
		titletxt->setColor(ccc3(255, 0, 0));
		titletxt->setAnchorPoint(ccp(0.5, 0.5));
		titletxt->setPosition(
				ccp(title->getContentSize().width / 2,
						title->getContentSize().height / 2));
		title->addChild(titletxt);
		this->addChild(title);
		return true;
	}
	else
	{
		return false;
	}
}
