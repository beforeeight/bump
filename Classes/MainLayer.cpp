/*
 * MenuLayer.cpp
 *
 *  Created on: Aug 28, 2014
 *      Author: zhangchen
 */

#include "MainLayer.h"

#include "AppMacros.h"
#include "BgLayer.h"
#include "Counter.h"
#include "FinishLayer.h"

#define TAG_LEFT 0
#define TAG_RIGHT 1

MainLayer::MainLayer()
{
	// TODO Auto-generated constructor stub
	disappearing = false;
	speed = 5.0f;
	ratio = 3.5f;
}

bool MainLayer::init()
{
	this->setTouchMode(kCCTouchesOneByOne);
	this->setTouchEnabled(true);
	this->scheduleUpdate();
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	this->ignoreAnchorPointForPosition(true);
	setAnchorPoint(ccp(0.5f, 0.5f));
	this->setContentSize(s);
	setPosition(ccp(s.width / 2, s.height / 2));
	CCSize vsize = CCDirector::sharedDirector()->getVisibleSize();
	float width = vsize.width / 2;
	float height = vsize.height / 2;
	Counter *counter = Counter::sharedCounter();
	CCTextureCache *cache = CCTextureCache::sharedTextureCache();
	/*-- 背景 --*/
	CCLayer *bgLayer = BgLayer::create();
	this->addChild(bgLayer);

	/*-- door --*/
	//左侧
	CCSprite *leftDoor = CCSprite::createWithTexture(
			cache->textureForKey(("pic_door_light.png")));
	CCSprite *leftDoorb = CCSprite::createWithTexture(
			cache->textureForKey(("pic_door.png")));
	CCSprite *leftDoorf = CCSprite::createWithTexture(
			cache->textureForKey(("pic_light_1.png")));

	leftDoorf->setPosition(
			ccp(leftDoorb->getContentSize().width / 2,
					leftDoorb->getContentSize().height / 2));
	leftDoorf->setAnchorPoint(ccp(0.5, 0.5));
	leftDoorb->addChild(leftDoorf);
	leftDoorb->setPosition(
			ccp(leftDoor->getContentSize().width / 2,
					leftDoor->getContentSize().height / 2));
	leftDoorb->setAnchorPoint(ccp(0.5, 0.5));
	leftDoor->addChild(leftDoorb);
	leftDoor->setPosition(ccp(-200, -50));
	leftDoor->setAnchorPoint(ccp(0.5, 0.5));
	this->addChild(leftDoor);

	//右侧
	CCSprite *rightDoor = CCSprite::createWithTexture(
			cache->textureForKey(("pic_door_light.png")));
	CCSprite *rightDoorb = CCSprite::createWithTexture(
			cache->textureForKey(("pic_door.png")));
	CCSprite *rightDoorf = CCSprite::createWithTexture(
			cache->textureForKey(("pic_light_1.png")));

	rightDoorf->setPosition(
			ccp(rightDoorb->getContentSize().width / 2,
					rightDoorb->getContentSize().height / 2));
	rightDoorf->setAnchorPoint(ccp(0.5, 0.5));
	rightDoorb->addChild(rightDoorf);
	rightDoorb->setPosition(
			ccp(rightDoor->getContentSize().width / 2,
					rightDoor->getContentSize().height / 2));
	rightDoorb->setAnchorPoint(ccp(0.5, 0.5));
	rightDoor->addChild(rightDoorb);
	rightDoor->setPosition(ccp(200, -50));
	rightDoor->setAnchorPoint(ccp(0.5, 0.5));
	this->addChild(rightDoor);
	/*-- role --*/
	this->createNewRole();
	return true;
}

MainLayer::~MainLayer()
{
}

CCScene * MainLayer::scene()
{
	CCScene *scene = CCScene::create();
	if (scene && scene->init())
	{
		if (scene)
		{
			MainLayer *layer = MainLayer::create();
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

bool MainLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	//CCDirector::sharedDirector()->replaceScene(FinishLayer::scene());
	CCSize vsize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint location = pTouch->getLocation();
	CCNode *node;
	if (location.x < vsize.width / 2)
	{
		node = this->getChildByTag(TAG_LEFT);
	}
	else
	{
		node = this->getChildByTag(TAG_RIGHT);
	}
	node->runAction(
			CCJumpBy::create(speed / ratio, ccp(0, 0),
					node->getContentSize().height, 1));
	return true;
}

void MainLayer::createNewRole()
{
	CCSize vsize = CCDirector::sharedDirector()->getVisibleSize();
	float width = vsize.width / 2;
	float height = vsize.height / 2;
	CCTextureCache *cache = CCTextureCache::sharedTextureCache();
	float random = CCRANDOM_0_1();
	CCSprite *left, *right;
	if (random < 0.5)
	{
		left = CCSprite::createWithTexture(
				cache->textureForKey(("ultraman_big_1.png")));
		right = CCSprite::createWithTexture(
				cache->textureForKey(("dragon_small_1.png")));
	}
	else
	{
		left = CCSprite::createWithTexture(
				cache->textureForKey(("ultraman_small_1.png")));
		right = CCSprite::createWithTexture(
				cache->textureForKey(("dragon_big_1.png")));
	}
	left->setPosition(ccp(-width, -height + 230));
	left->setAnchorPoint(ccp(0, 0));
	this->addChild(left, 3, TAG_LEFT);
	right->setPosition(ccp(width, -height + 230));
	right->setAnchorPoint(ccp(1, 0));
	this->addChild(right, 3, TAG_RIGHT);
	disappearing = false;
	left->runAction(CCMoveBy::create(speed, ccp(2 * width, 0)));
	right->runAction(CCMoveBy::create(speed, ccp(-2 * width, 0)));
}

void MainLayer::reCreateNewRole()
{
	this->removeChildByTag(TAG_LEFT);
	this->removeChildByTag(TAG_RIGHT);
	this->createNewRole();
}

void MainLayer::update(float delta)
{
	CCNode *left = this->getChildByTag(TAG_LEFT);
	CCNode *right = this->getChildByTag(TAG_RIGHT);
	if (left->getPosition().x > right->getPosition().x && !disappearing)
	{
		disappearing = true;
		left->runAction(CCFadeOut::create(1.0f));
		right->runAction(
				CCSequence::createWithTwoActions(CCFadeOut::create(1.0f),
						CCCallFunc::create(this,
								callfunc_selector(
										MainLayer::reCreateNewRole))));
	}

}
