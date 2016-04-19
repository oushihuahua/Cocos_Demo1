#ifndef DrawUI_H
#define DrawUI_H
#include "cocos2d.h"

//#include "cocos-ext.h"

//using namespace 
//USING_NS_CC_EXT;
USING_NS_CC;



class DrawUI : public Menu
{


public:
	DrawUI();
	~DrawUI();
	virtual bool init();
	//»¬¶¯´¥·¢
	CREATE_FUNC(DrawUI);
	virtual void onExit() override;

public:
	virtual bool onTouchBegan(Touch *  touch,
		Event *  unused_event
		);

	/*void restartCallback(CCObject* pSender);
	void nextCallback(CCObject* pSender);
	void backCallback(CCObject* pSender);

	void step(float dt);

	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExitTransitionDidStart();
	virtual void onExit();*/


};

#endif