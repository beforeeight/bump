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

#define TAG_SCENE_BG 1;
#define TAG_SCENE_MENUBG 2;
#define TAG_SCENE_MENU 3;

#define TAG_LAYER_SOUND 1;
#define TAG_LAYER_FEEDBACK 2;
#define TAG_LAYER_START 3;
#define TAG_LAYER_RANKING 4;
#define TAG_LAYER_MORE 5;

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
		if (counter->isSound())
		{
			SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm.mp3",
					true);
		}
		/*-- 所有按钮 --*/
		//标题
		CCMenuItemImage *title;
		if (CCApplication::sharedApplication()->getCurrentLanguage()
				== kLanguageChinese)
		{
			title = CCMenuItemImage::create("gamename_cn.png",
					"gamename_cn.png");
		}
		else
		{
			title = CCMenuItemImage::create("gamename_us.png",
					"gamename_us.png");
		}
		title->setAnchorPoint(ccp(0.5, 0.5));
		title->setPosition(ccp(0, height - 180));
		this->addChild(title);

		//声音
		CCMenuItemImage *soundbg = CCMenuItemImage::create(("btn_small.png"),
				("btn_small.png"));
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
		soundtxt->setTarget(soundbg, menu_selector(MenuLayer::onSoundItem));

		soundbg->setPosition(ccp(-width + 15, height - 15));
		soundbg->setAnchorPoint(ccp(0, 1));
		soundtxt->setPosition(
				ccp(
						soundbg->getPosition().x
								+ soundbg->getContentSize().width / 2,
						soundbg->getPosition().y
								- soundbg->getContentSize().height / 2));
		soundtxt->setAnchorPoint(ccp(0.5, 0.5));
		soundbg->setEnabled(false);
		this->addChild(soundtxt, 3);
		this->addChild(soundbg, 2);

		//反馈
		CCMenuItemImage *feedbackbg = CCMenuItemImage::create(("btn_small.png"),
				("btn_small.png"));
		feedbackbg->setTarget(feedbackbg,
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
				("btn_big.png"));
		startbg->setTarget(startbg, menu_selector(MenuLayer::onStartItem));
		CCMenuItemFont *starttxt = CCMenuItemFont::create(
				counter->getStringByKey("start"));
		starttxt->setFontName(counter->getStringByKey("font"));
		startbg->setPosition(ccp(1, -160));
		startbg->setAnchorPoint(ccp(0.5, 0.5));
		starttxt->setPosition(
				ccp(startbg->getPosition().x, startbg->getPosition().y));
		starttxt->setAnchorPoint(ccp(0.5, 0.5));
		this->addChild(startbg, 2);
		this->addChild(starttxt, 3);

		//排行榜
		CCMenuItem *rankingbg = CCMenuItemImage::create(("btn_big.png"),
				("btn_big.png"));
		rankingbg->setTarget(rankingbg,
				menu_selector(MenuLayer::onRankingItem));
		CCMenuItemFont *rankingtxt = CCMenuItemFont::create(counter->getStringByKey("ranking"));
		rankingtxt->setFontName(counter->getStringByKey("font"));
		rankingbg->setPosition(
				ccp(1,
						startbg->getPosition().y
								- (startbg->getContentSize().height) - 20));
		rankingbg->setAnchorPoint(ccp(0.5, 0.5));
		rankingtxt->setPosition(
				ccp(rankingbg->getContentSize().width / 2,
						rankingbg->getContentSize().height / 2));

//		rankingtxt->setPosition(
//				ccp(
//						rankingbg->getPosition().x
//								+ rankingbg->getContentSize().width / 2,
//								rankingbg->getPosition().y
//								- rankingbg->getContentSize().height / 2));

		this->addChild(rankingbg, 2);
		rankingbg->addChild(rankingtxt);

		//更多游戏
		CCMenuItem *morebg = CCMenuItemImage::create(("btn_big.png"),
				("btn_big.png"));
		morebg->setTarget(morebg, menu_selector(MenuLayer::onMoreItem));
		CCMenuItemFont *moretxt = CCMenuItemFont::create(counter->getStringByKey("more"));
		moretxt->setFontName(counter->getStringByKey("font"));
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
			/*-- 背景 --*/
			scene->addChild(BgLayer::create());
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
	Counter::sharedCounter()->playEffect("click.mp3");
	CCNode *node = (CCNode *) this;
	node->runAction(
			CCSequence::createWithTwoActions(CCScaleBy::create(0.1f, 0.95f),
					CCScaleBy::create(0.1f, 10.0 / 9.5f)));
	Counter *counter = Counter::sharedCounter();
	if (counter->isSound())
	{
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	}
	else
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgm.mp3", true);
	}
	counter->toggleSound();
}

void MenuLayer::onFeedbackItem(CCObject *object)
{
	Counter::sharedCounter()->playEffect("click.mp3");
	CCNode *node = (CCNode *) object;
	node->runAction(
			CCSequence::createWithTwoActions(CCScaleBy::create(0.1f, 0.95f),
					CCScaleBy::create(0.1f, 10.0 / 9.5f)));
}

void MenuLayer::onStartItem(CCObject *object)
{
	Counter::sharedCounter()->playEffect("click.mp3");
	CCNode *node = (CCNode *) object;
	node->runAction(
			CCSequence::createWithTwoActions(CCScaleBy::create(0.1f, 0.95f),
					CCScaleBy::create(0.1f, 10.0 / 9.5f)));
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCScene *pScene = MainLayer::scene();
	CCScene *reScene = CCTransitionFadeDown::create(0.5f, pScene);
	pDirector->replaceScene(reScene);
}

void MenuLayer::onRankingItem(CCObject *object)
{
	Counter::sharedCounter()->playEffect("click.mp3");
	CCNode *node = (CCNode *) object;
	node->runAction(
			CCSequence::createWithTwoActions(CCScaleBy::create(0.1f, 0.95f),
					CCScaleBy::create(0.1f, 10.0 / 9.5f)));
}

void MenuLayer::onMoreItem(CCObject *object)
{
	Counter::sharedCounter()->playEffect("click.mp3");
	CCNode *node = (CCNode *) object;
	node->runAction(
			CCSequence::createWithTwoActions(CCScaleBy::create(0.1f, 0.95f),
					CCScaleBy::create(0.1f, 10.0 / 9.5f)));
}

bool MenuBgLayer::init()
{
	CCTextureCache *cache = CCTextureCache::sharedTextureCache();
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	this->ignoreAnchorPointForPosition(true);
	setAnchorPoint(ccp(0.5f, 0.5f));
	this->setContentSize(s);
	setPosition(ccp(s.width / 2, s.height / 2));
	CCSize vsize = CCDirector::sharedDirector()->getVisibleSize();
	float width = vsize.width / 2;
	float height = vsize.height / 2;

	CCSprite *soundbg = CCSprite::createWithTexture(
			cache->textureForKey(("btn_small.png")));
	soundbg->setPosition(ccp(-width + 15, height - 15));
	soundbg->setAnchorPoint(ccp(0, 1));
	return true;
}
