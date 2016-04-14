#ifndef BackgroundLayer_H
#define BackgroundLayer_H

#include "cocos2d.h"

USING_NS_CC;



class ChooseChapLayer: public Layer
{
public:	
	ChooseChapLayer();
	~ChooseChapLayer();
	
	/*void restartCallback(CCObject* pSender);
	void nextCallback(CCObject* pSender);
	void backCallback(CCObject* pSender);

	void step(float dt);

	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExitTransitionDidStart();
	virtual void onExit();*/
	CREATE_FUNC(ChooseChapLayer);
private:
	virtual bool init();

};

#endif
