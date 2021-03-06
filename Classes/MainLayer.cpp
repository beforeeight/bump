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
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

#define TAG_LEFT 0
#define TAG_RIGHT 1
#define TAG_SCORE 3
#define TAG_ACTION_RUN 1
#define TAG_ACTION_JUMP 2
#define TAG_ACTION_DROP 3
#define TAG_ACTION_MOVE 4

MainLayer::MainLayer()
{
	// TODO Auto-generated constructor stub
	disappearing = false;
	speed = 3.0f;
	ratio = 5.3f;
	leftJumping = false;
	rightJumping = false;
}

bool MainLayer::init()
{
	/*-- 设置整体层属性 --*/
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
	counter->clearScore();
	if (counter->isSound()
			&& !SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm.mp3", true);
	}
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

	/*-- 分数 --*/
	CCLabelTTF *titletxt = CCLabelTTF::create(counter->getStringByKey("score"),
			counter->getStringByKey("font"), 46);
	titletxt->setColor(ccc3(98, 104, 191));
	titletxt->setAnchorPoint(ccp(0.5, 0.5));
	titletxt->setPosition(ccp(0, height - 130));
	this->addChild(titletxt);
	CCNode *scoreLabel = counter->create_label();
	scoreLabel->setPosition(ccp(0, height - 200));
	scoreLabel->setAnchorPoint(ccp(0.5, 1));
	this->addChild(scoreLabel, 3, TAG_SCORE);
	/*-- role --*/
	return true;
}

void MainLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
	this->createNewRole();
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

void MainLayer::createNewRole()
{
	CCSize vsize = CCDirector::sharedDirector()->getVisibleSize();
	float width = vsize.width / 2;
	float height = vsize.height / 2;
	CCSprite *left = CCSprite::createWithSpriteFrameName("ultraman_big_1.png");
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
	CCAction *leftMoving = CCMoveBy::create(speed, ccp(2 * width, 0));
	CCAction *rightMoving = CCMoveBy::create(speed, ccp(-2 * width, 0));
	leftMoving->setTag(TAG_ACTION_MOVE);
	rightMoving->setTag(TAG_ACTION_MOVE);

	left->runAction(leftMoving);
	right->runAction(rightMoving);
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

bool MainLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{ /*-- 跳动作 --*/
	//CCDirector::sharedDirector()->replaceScene(FinishLayer::scene());
	CCSize vsize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint location = pTouch->getLocation();
	CCNode *node = 0;
	if (location.x < vsize.width / 2)
	{
		if (!leftJumping)
		{
			node = this->getChildByTag(TAG_LEFT);
			leftJumping = true;
		}
	}
	else
	{
		if (!rightJumping)
		{
			node = this->getChildByTag(TAG_RIGHT);
			rightJumping = true;
		}
	}
	if (node)
	{
		CCActionInterval *jump = CCJumpBy::create(speed / ratio, ccp(0, 0),
				node->getContentSize().height, 1);
		node->runAction(jump);
		CCActionInterval *moving = (CCActionInterval*) node->getActionByTag(
		TAG_ACTION_MOVE);
		if (moving)
		{
			node->runAction(CCSpeed::create(moving, 1.2f));
		}
		playJumpAnimation(node);
	}
	return true;
}

void MainLayer::update(float delta)
{
	if (!disappearing)
	{
		CCNode *left = this->getChildByTag(TAG_LEFT);
		CCNode *right = this->getChildByTag(TAG_RIGHT);
		if (left && right)
		{

			CCRect leftRect = left->boundingBox();
			CCRect rightRect = right->boundingBox();
			leftRect.size = leftRect.size * 0.85f;
			rightRect.size = rightRect.size * 0.8f;
			if (leftRect.intersectsRect(rightRect))
			{
				disappearing = true;
				/*爆炸*/
				playDropAnimation();
			}
			else if (left->getPosition().x > right->getPosition().x)
			{
				disappearing = true;
				leftJumping = false;
				rightJumping = false;
				//计分
				Counter *counter = Counter::sharedCounter();
				(*counter)++;
				this->reCreateNewRole();
//			left->runAction(CCFadeOut::create(0.8f));
//			right->runAction(
//					CCSequence::createWithTwoActions(CCFadeOut::create(0.8f),
//							CCCallFunc::create(this,
//									callfunc_selector(
//											MainLayer::reCreateNewRole))));
			}
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
	/*-- 跳动画 --*/
	Counter::sharedCounter()->playEffect("jump.mp3");
	node->stopActionByTag(TAG_ACTION_RUN);
	CCAction* animation;
	if (node->getTag() == TAG_LEFT)
	{
		CCAnimation* ultramanAnimation =
				CCAnimationCache::sharedAnimationCache()->animationByName(
						"ultramanjump");
		animation = CCAnimate::create(ultramanAnimation);
	}
	else
	{
		CCAnimation* dragonAnimation =
				CCAnimationCache::sharedAnimationCache()->animationByName(
						"dragonjump");
		animation = CCAnimate::create(dragonAnimation);
	}
	animation->setTag(TAG_ACTION_JUMP);
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
	left->initWithSpriteFrameName("ultraman_big_19.png");
	right->initWithSpriteFrameName("dragon_big_19.png");
	left->setAnchorPoint(la);
	right->setAnchorPoint(ra);

	CCSize vsize = CCDirector::sharedDirector()->getVisibleSize();
	float width = vsize.width / 2;
	float height = vsize.height / 2;
	left->runAction(
			CCMoveTo::create(0.6f,
					ccp(left->getPositionX(),
							-height - left->getContentSize().height)));
	right->runAction(
			CCMoveTo::create(0.6f,
					ccp(right->getPositionX(),
							-height - right->getContentSize().height)));
	CCPoint p = (left->getPosition() + ccp(0, left->getContentSize().height / 2)
			+ right->getPosition() + ccp(0, right->getContentSize().height / 2))
			/ 2.0f;
	playExplosionAnimation(p);
}

void MainLayer::playExplosionAnimation(const CCPoint &p)
{
	Counter::sharedCounter()->playEffect("boom.mp3");
	CCSprite *explostion = CCSprite::createWithSpriteFrame(
			CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
					"boom_1.png"));
	CCAnimation* explostionAnimation =
			CCAnimationCache::sharedAnimationCache()->animationByName("boom");
	explostion->setPosition(p);
	this->addChild(explostion);
	explostion->runAction(
			CCSequence::createWithTwoActions(
					CCAnimate::create(explostionAnimation),
					CCCallFunc::create(this,
							callfunc_selector(MainLayer::gameover))));
}

void MainLayer::gameover()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCScene *pScene = FinishLayer::scene();
	CCScene *reScene = CCTransitionFadeDown::create(0.5f, pScene);
	pDirector->replaceScene(reScene);
}

