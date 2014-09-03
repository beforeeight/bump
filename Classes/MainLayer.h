/*
 * MayLayer.h
 *
 *  Created on: Jun 23, 2014
 *      Author: zhangchen
 */

#ifndef MAINLAYER_H_
#define MAINLAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class MainLayer: public CCLayer
{

public:
	MainLayer();

	virtual ~MainLayer();

	virtual bool init();

	CREATE_FUNC(MainLayer)

	static CCScene * scene();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	virtual void update(float delta);
private:
	float speed;

	float ratio;

	bool disappearing;

	bool leftJumping;

	bool rightJumping;

	void createNewRole();

	void reCreateNewRole();

	void playRunAnimation();

	void playJumpAnimation(CCNode *node);

	void playDropAnimation();

	void playExplosionAnimation(const CCPoint &p);

	void gameover();
};

#endif
