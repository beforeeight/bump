/*
 * FinishLayer.cpp
 *
 *  Created on: Aug 28, 2014
 *      Author: zhangchen
 */

#include "FinishLayer.h"
#include "Counter.h"
#include "BgLayer.h"
#include "MenuLayer.h"
#include "MainLayer.h"
#include "AppMacros.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

FinishLayer::FinishLayer()
{
	// TODO Auto-generated constructor stub
}

FinishLayer::~FinishLayer()
{
	// TODO Auto-generated destructor stub
}

bool FinishLayer::init()
{
	if (CCMenu::init())
	{

		CCSize vsize = CCDirector::sharedDirector()->getVisibleSize();
		float width = vsize.width / 2;
		float height = vsize.height / 2;
		/* initialize the counter */
		Counter *counter = Counter::sharedCounter();
		counter->save();
		/*-- 声音 --*/
		if (counter->isSound())
		{
			SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
					"gameover.mp3", false);
		}
		/*-- 本局得分 --*/
		/*-- 分数 --*/
		CCLabelTTF *titleLabel = CCLabelTTF::create(
				counter->getStringByKey("score"),
				counter->getStringByKey("font"), 46);
		titleLabel->setColor(ccc3(98, 104, 191));
		CCMenuItemSprite *title = CCMenuItemSprite::create(titleLabel,
				titleLabel, titleLabel);
		title->setAnchorPoint(ccp(0.5, 0.5));
		title->setPosition(ccp(0, height - 130));
		this->addChild(title);

		CCNode *scoreLabel = counter->create_label();
		CCMenuItemSprite *score = CCMenuItemSprite::create(scoreLabel,
				scoreLabel, scoreLabel);
		score->setPosition(ccp(0, height - 200));
		score->setAnchorPoint(ccp(0.5, 1));
		this->addChild(score, 3);

		/*-- 所有按钮 --*/
		//最高分
		CCMenuItem *scorebg = CCMenuItemImage::create("bg_gameover.png",
				"bg_gameover.png");
		scorebg->setPosition(ccp(0, 50));
		scorebg->setAnchorPoint(ccp(0.5, 0.5));
		this->addChild(scorebg);
		CCLabelBMFont *highScore = CCLabelBMFont::create(
				CCString::createWithFormat("%d",
						Counter::sharedCounter()->getHighScore())->getCString(),
				"fonts.fnt");
		CCLabelBMFont *times = CCLabelBMFont::create(
				CCString::createWithFormat("%d",
						Counter::sharedCounter()->getTimes())->getCString(),
				"fonts.fnt");
		highScore->setPosition(ccp(450, 100));
		times->setPosition(ccp(450, 30));
		scorebg->addChild(highScore);
		scorebg->addChild(times);
		//开始游戏
		CCMenuItemImage *startbg = CCMenuItemImage::create(("btn_big.png"),
				("btn_big.png"));
		startbg->setTarget(startbg, menu_selector(FinishLayer::onAgainItem));
		CCMenuItemFont *starttxt = CCMenuItemFont::create(
				counter->getStringByKey("again"));
		starttxt->setFontName(counter->getStringByKey("font"));
		startbg->setPosition(ccp(1, -130));
		startbg->setAnchorPoint(ccp(0.5, 0.5));
		starttxt->setPosition(
				ccp(startbg->getContentSize().width / 2,
						startbg->getContentSize().height / 2));
		this->addChild(startbg, 2);
		startbg->addChild(starttxt, 3);

		//分享
		CCMenuItem *sharebg = CCMenuItemImage::create(("btn_big.png"),
				("btn_big.png"));
		sharebg->setTarget(sharebg, menu_selector(FinishLayer::onShareItem));
		CCMenuItemFont *sharetxt = CCMenuItemFont::create(
				counter->getStringByKey("share"));
		sharetxt->setFontName(counter->getStringByKey("font"));
		sharebg->setPosition(
				ccp(1,
						startbg->getPosition().y
								- (startbg->getContentSize().height) - 20));
		sharebg->setAnchorPoint(ccp(0.5, 0.5));
		sharetxt->setPosition(
				ccp(sharebg->getContentSize().width / 2,
						sharebg->getContentSize().height / 2));
		this->addChild(sharebg, 2);
		sharebg->addChild(sharetxt);

		//返回主页
		CCMenuItem *morebg = CCMenuItemImage::create(("btn_big.png"),
				("btn_big.png"));
		morebg->setTarget(morebg, menu_selector(FinishLayer::onBackItem));
		CCMenuItemFont *moretxt = CCMenuItemFont::create(
				counter->getStringByKey("menu"));
		moretxt->setFontName(counter->getStringByKey("font"));
		morebg->setPosition(
				ccp(0,
						sharebg->getPosition().y
								- (sharebg->getContentSize().height) - 20));
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

CCScene * FinishLayer::scene()
{
	CCScene *scene = CCScene::create();
	if (scene && scene->init())
	{
		if (scene)
		{
			/*-- 背景 --*/
			scene->addChild(BgLayer::create());
			FinishLayer *layer = FinishLayer::create();
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

void FinishLayer::onAgainItem(CCObject *object)
{
	Counter::sharedCounter()->playEffect("click.mp3");
	CCNode *node = (CCNode *) object;
	node->runAction(
			CCSequence::createWithTwoActions(CCScaleBy::create(0.1f, 0.95f),
					CCScaleBy::create(0.1f, 10.0 / 9.5f)));
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCScene *pScene = MainLayer::scene();
	CCScene *reScene = CCTransitionFadeDown::create(0.5f, pScene);
	pDirector->replaceScene(reScene);
}

void FinishLayer::onShareItem(CCObject *object)
{
	Counter::sharedCounter()->playEffect("click.mp3");
	CCNode *node = (CCNode *) object;
	node->runAction(
			CCSequence::createWithTwoActions(CCScaleBy::create(0.1f, 0.95f),
					CCScaleBy::create(0.1f, 10.0 / 9.5f)));
}

void FinishLayer::onBackItem(CCObject *object)
{
	Counter::sharedCounter()->playEffect("click.mp3");
	CCNode *node = (CCNode *) object;
	node->runAction(
			CCSequence::createWithTwoActions(CCScaleBy::create(0.1f, 0.95f),
					CCScaleBy::create(0.1f, 10.0 / 9.5f)));
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCScene *pScene = MenuLayer::scene();
	CCScene *reScene = CCTransitionFadeDown::create(0.5f, pScene);
	pDirector->replaceScene(reScene);
}
