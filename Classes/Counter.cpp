/*
 * Counter.cpp
 *
 *  Created on: Aug 4, 2014
 *      Author: zhangchen
 */

#include "Counter.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

Counter::Counter()
{
	this->counter = 0;
	sound = true;
	load();
	scoreLabel = 0;
	//获取当前系统环境语言类型
	ccLanguageType languageType =
			CCApplication::sharedApplication()->getCurrentLanguage();
	if (kLanguageChinese == languageType)
		//根据语言选择不同的属性表
		langDic = CCDictionary::createWithContentsOfFile("cn.plist");
	else
		langDic = CCDictionary::createWithContentsOfFile("en.plist");
	if (langDic)
	{
		CC_SAFE_RETAIN(langDic);
	}
}

Counter::~Counter()
{
	CC_SAFE_RELEASE(langDic);
}

CCLabelBMFont * Counter::create_label()
{
	if (scoreLabel)
	{
		CC_SAFE_RELEASE(scoreLabel);
	}
	scoreLabel = CCLabelBMFont::create(
			CCString::createWithFormat("%d",
					Counter::sharedCounter()->getCounter())->getCString(),
			"fonts.fnt");
	if (scoreLabel)
	{
		CC_SAFE_RETAIN(scoreLabel);
	}
	return scoreLabel;
}

Counter* Counter::sharedCounter()
{
	static Counter* counter = NULL;
	if (counter == NULL)
	{
		counter = new Counter();
	}

	return counter;
}

Counter& Counter::operator++(int)
{
	this->counter++;
	scoreLabel->setString(
			CCString::createWithFormat("%d", counter)->getCString());
	return *this;
}

void Counter::clearScore()
{
	this->counter = 0;

}

int Counter::getCounter() const
{
	return this->counter;
}

int Counter::getHighScore() const
{
	return this->highScore;
}

int Counter::getTimes() const
{
	return this->times;
}

void Counter::save()
{
	times++;
	if (counter > highScore)
	{
		highScore = counter;
	}
	CCUserDefault::sharedUserDefault()->setIntegerForKey("highScore",
			highScore);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("times", times);
	CCUserDefault::sharedUserDefault()->flush();
}

void Counter::load()
{
	this->highScore = CCUserDefault::sharedUserDefault()->getIntegerForKey(
			"highScore", 0);
	this->times = CCUserDefault::sharedUserDefault()->getIntegerForKey("times",
			0);
}

const char* Counter::getDisplayCounter() const
{
	CCString* pString = CCString::createWithFormat("Score: %d",
			this->getCounter());
	return pString->getCString();
}

const char* Counter::getDisplayHighScore() const
{
	CCString* pString = CCString::createWithFormat("High Score: %d",
			this->getHighScore());
	return pString->getCString();
}

const char* Counter::getDisplayTimes() const
{
	CCString* pString = CCString::createWithFormat("Play Times: %d",
			this->getTimes());
	return pString->getCString();
}

const bool Counter::isSound()
{
	return sound;
}

void Counter::playEffect(const char* file)
{
	if (isSound())
	{
		SimpleAudioEngine::sharedEngine()->playEffect(file);
	}
}

bool Counter::toggleSound()
{
	sound = !sound;
	return sound;
}

const char* Counter::getStringByKey(const char * key)
{

	std::string keyStr = key;
	//返回key对应的value
	return (langDic->valueForKey(keyStr))->getCString();
}
