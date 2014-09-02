/*
 * MenuLayer.h
 *
 *  Created on: Aug 28, 2014
 *      Author: zhangchen
 */

#ifndef MENULAYER_H_
#define MENULAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class MenuLayer: public CCMenu
{
public:
	MenuLayer();

	~MenuLayer();

	virtual bool init();

	CREATE_FUNC(MenuLayer)

	static CCScene * scene();

private:

	void onSoundItem(CCObject *object);

	void onFeedbackItem(CCObject *object);

	void onStartItem(CCObject *object);

	void onRankingItem(CCObject *object);

	void onMoreItem(CCObject *object);
};

class MenuBgLayer: public CCLayer
{
public:
	MenuBgLayer();

	~MenuBgLayer();

	virtual bool init();

	CREATE_FUNC(MenuBgLayer)

};
#endif /* MENULAYER_H_ */
