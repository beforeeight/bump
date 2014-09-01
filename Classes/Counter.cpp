/*
 * Counter.cpp
 *
 *  Created on: Aug 4, 2014
 *      Author: zhangchen
 */

#include "Counter.h"

Counter::Counter()
{
	this->counter = 0;
	sound = true;
	load();
}

Counter::~Counter()
{
// TODO Auto-generated destructor stub
}

Counter* Counter::sharedCounter()
{
	static Counter* counter = NULL;
	if (counter == NULL)
	{
		counter = new Counter();
		counter->initWithString(counter->getDisplayCounter(), "Courier", 20.0f);
	}
	return counter;
}

Counter& Counter::operator++(int)
{
	this->counter++;
	this->setString(this->getDisplayCounter());
	return *this;
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

void Counter::save() const
{

}

void Counter::load()
{
	this->highScore = 2000;
	this->times = 123;
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

bool Counter::toggleSound()
{
	sound = !sound;
	return sound;
}
