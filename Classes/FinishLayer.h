/*
 * FinishLayer.h
 *
 *  Created on: Aug 28, 2014
 *      Author: zhangchen
 */

#ifndef FINISHLAYER_H_
#define FINISHLAYER_H_
#include "cocos2d.h"

USING_NS_CC;

class FinishLayer: public CCMenu
{
public:
	FinishLayer();

	~FinishLayer();

	virtual bool init();

	CREATE_FUNC(FinishLayer)

	static CCScene * scene();

private:
	void onAgainItem(CCObject *object);

	void onShareItem(CCObject *object);

	void onBackItem(CCObject *object);
};

#endif /* FINISHLAYER_H_ */
