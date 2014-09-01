/*
 * Counter.h
 *
 *  Created on: Aug 4, 2014
 *      Author: zhangchen
 */

#ifndef COUNTER_H_
#define COUNTER_H_

#include "cocos2d.h"

USING_NS_CC;

class Counter: public cocos2d::CCLabelTTF
{
public:
	Counter();

	~Counter();

	Counter& operator++(int);

	static Counter *sharedCounter();

	int getCounter() const;

	int getHighScore() const;

	int getTimes() const;

	void save() const;

	void load();

	const char* getDisplayCounter() const;

	const char* getDisplayHighScore() const;

	const char* getDisplayTimes() const;

	const bool isSound();

	bool toggleSound();
private:
	unsigned int counter;

	unsigned int highScore;

	unsigned int times;

	bool sound;
};

#endif /* COUNTER_H_ */
