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
#define TAG_ACTION_RUN 1
#define TAG_ACTION_JUMP 2
#define TAG_ACTION_DROP 2

MainLayer::MainLayer()
{
	// TODO Auto-generated constructor stub
	disappearing = false;
	speed = 5.0f;
	ratio = 2.0f;
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

	/*-- door --*/
	CCAnimation *doorAnimation =
			CCAnimationCache::sharedAnimationCache()->animationByName("door");
	//左侧
	CCSprite *leftDoor = CCSprite::createWithSpriteFrameName("door_1.png");
	leftDoor->setPosition(ccp(-200, -50));
	leftDoor->setAnchorPoint(ccp(0.5, 0.5));
	this->addChild(leftDoor);
	leftDoor->runAction(
			CCRepeatForever::create(CCAnimate::create(doorAnimation)));

	//右侧
	CCSprite *rightDoor = CCSprite::createWithSpriteFrameName("door_1.png");
	rightDoor->setPosition(ccp(200, -50));
	rightDoor->setAnchorPoint(ccp(0.5, 0.5));
	this->addChild(rightDoor);
	rightDoor->runAction(
			CCRepeatForever::create(CCAnimate::create(doorAnimation)));

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
			/*-- 背景 --*/
			CCLayer *bgLayer = BgLayer::create();
			scene->addChild(bgLayer);
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
{ /*-- 跳动作 --*/
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
	//playJumpAnimation(node);
	return true;
}

void MainLayer::createNewRole()
{
	CCSize vsize = CCDirector::sharedDirector()->getVisibleSize();
	float width = vsize.width / 2;
	float height = vsize.height / 2;
	CCTextureCache *cache = CCTextureCache::sharedTextureCache();

	CCSprite *left = CCSprite::createWithSpriteFrameName("ultraman_big_1.png");
//	CCSprite *left = CCSprite::createWithTexture(
//			CCTextureCache::sharedTextureCache()->textureForKey(
//					"ultraman_big_1.png"));
	//

	CCSprite *right = CCSprite::createWithSpriteFrameName("dragon_big_1.png");
	if (CCRANDOM_0_1() < 0.5)
	{
		left->setScale(0.5f);
	}
	else
	{
		right->setScale(0.5f);
	}
	left->setPosition(ccp(-width, -height + 230));
	left->setAnchorPoint(ccp(0, 0));
	this->addChild(left, 3, TAG_LEFT);
	right->setPosition(ccp(width, -height + 230));
	right->setAnchorPoint(ccp(1, 0));
	this->addChild(right, 3, TAG_RIGHT);
	left->runAction(CCMoveBy::create(speed, ccp(2 * width, 0)));
	right->runAction(CCMoveBy::create(speed, ccp(-2 * width, 0)));
	disappearing = false;

	/*-- 走路动画 --*/
	playRunAnimation();
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

	CCRect leftRect = left->boundingBox();
	CCRect rightRect = right->boundingBox();
	if (!disappearing)
	{
		if (leftRect.intersectsRect(rightRect))
		{
			disappearing = true;
			CCLog("left width: %f, right width: %f", leftRect.size.width,
					rightRect.size.width);
			CCLog("left getMinX: %f, left getMaxX: %f", leftRect.getMinX(),
					leftRect.getMaxX());
			CCLog("right getMinX: %f, right getMaxX: %f", rightRect.getMinX(),
					rightRect.getMaxX());
			/*爆炸*/
			playDropAnimation();
		}
		else if (left->getPosition().x > right->getPosition().x)
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

}

void MainLayer::playRunAnimation()
{
	CCSprite *left = (CCSprite*) this->getChildByTag(TAG_LEFT);
	CCSprite *right = (CCSprite*) this->getChildByTag(TAG_RIGHT);
	/*-- 走路动画 --*/
	left->stopActionByTag(TAG_ACTION_JUMP);
	right->stopActionByTag(TAG_ACTION_JUMP);
	CCAnimation* ultramanAnimation =
			CCAnimationCache::sharedAnimationCache()->animationByName(
					"ultraman");
	CCAnimation* dragonAnimation =
			CCAnimationCache::sharedAnimationCache()->animationByName("dragon");
	CCAction* ultraman = CCRepeatForever::create(
			CCAnimate::create(ultramanAnimation));
	CCAction* dragon = CCRepeatForever::create(
			CCAnimate::create(dragonAnimation));
	ultraman->setTag(TAG_ACTION_RUN);
	dragon->setTag(TAG_ACTION_RUN);
	left->runAction(ultraman);
	right->runAction(dragon);
}

void MainLayer::playJumpAnimation(CCNode *node)
{
	/*-- 走路动画 --*/
	node->stopActionByTag(TAG_ACTION_RUN);
	CCAction* animation;
	if (node->getTag() == TAG_LEFT)
	{
		CCAnimation* ultramanAnimation =
				CCAnimationCache::sharedAnimationCache()->animationByName(
						"ultramanjump");
		animation = CCRepeatForever::create(
				CCAnimate::create(ultramanAnimation));
	}
	else
	{
		CCAnimation* dragonAnimation =
				CCAnimationCache::sharedAnimationCache()->animationByName(
						"dragonjump");
		animation = CCRepeatForever::create(CCAnimate::create(dragonAnimation));
	}
	node->setTag(TAG_ACTION_JUMP);
	node->runAction(animation);
}

void MainLayer::playDropAnimation()
{
	CCSprite *left = (CCSprite*) this->getChildByTag(TAG_LEFT);
	CCSprite *right = (CCSprite*) this->getChildByTag(TAG_RIGHT);
	/*-- 走路动画 --*/
	left->stopAllActions();
	right->stopAllActions();
	CCPoint la = left->getAnchorPoint();
	CCPoint ra = right->getAnchorPoint();
	left->initWithSpriteFrameName("ultraman_big_18.png");
	right->initWithSpriteFrameName("dragon_big_18.png");
	left->setAnchorPoint(la);
	right->setAnchorPoint(ra);

	CCSize vsize = CCDirector::sharedDirector()->getVisibleSize();
	float width = vsize.width / 2;
	float height = vsize.height / 2;
	left->runAction(CCMoveTo::create(1.0f, ccp(left->getPositionX(), -height)));
	right->runAction(
			CCSequence::createWithTwoActions(
					CCMoveTo::create(1.0f, ccp(right->getPositionX(), -height)),
					CCCallFunc::create(this,
							callfunc_selector(MainLayer::gameover))));
}

void MainLayer::gameover()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCScene *pScene = FinishLayer::scene();
	pDirector->replaceScene(pScene);
}

