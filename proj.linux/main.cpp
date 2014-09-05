#include "../Classes/AppDelegate.h"
#include "cocos2d.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>

USING_NS_CC;

int main(int argc, char **argv)
{
	// create the application instance
//	CCDirector* pDirector = CCDirector::sharedDirector();
//
//	pDirector->setOpenGLView(pEGLView);
	//pEGLView->setDesignResolutionSize(768.0f, 1280.0f, kResolutionShowAll);
	AppDelegate app;
	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
	/*iphone5*/
	//pEGLView->setFrameSize(640.0f, 1136.0f);
	//pEGLView->setFrameSize(480.0f, 852.0f);
	/*ipad*/
	//pEGLView->setFrameSize(1536.0f, 2048.0f);
	pEGLView->setFrameSize(512.0f, 682.67f);
	return CCApplication::sharedApplication()->run();
}
