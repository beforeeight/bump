/*
 * BgLayer.h
 *
 *  Created on: Aug 31, 2014
 *      Author: zhangchen
 */

#ifndef BGLAYER_H_
#define BGLAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class BgLayer: public CCLayer
{
public:
	BgLayer();

	~BgLayer();

	virtual bool init();

	CREATE_FUNC(BgLayer)

};

#endif /* BGLAYER_H_ */
