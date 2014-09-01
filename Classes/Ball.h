/*
 * Ball.h
 *
 *  Created on: Aug 27, 2014
 *      Author: zhangchen
 */

#ifndef BALL_H_
#define BALL_H_

#include "cocos2d.h"

USING_NS_CC;

class Ball: public CCSprite
{
public:

	Ball();

	virtual ~Ball();

	virtual bool init();

	CREATE_FUNC(Ball)

	virtual void jump();
private:

	float ratio;
};

#endif /* BALL_H_ */
