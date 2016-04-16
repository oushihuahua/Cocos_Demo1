#ifndef BackgroundLayer_H
#define BackgroundLayer_H
#include "cocos2d.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocostudio;


//#include "cocos-ext.h"

//using namespace 
//USING_NS_CC_EXT;
USING_NS_CC;



class ChooseChapLayer : public Layer
{
	

	public:
		ChooseChapLayer();
		~ChooseChapLayer();
		 virtual bool init();    
		 //»¬¶¯´¥·¢
		 CREATE_FUNC(ChooseChapLayer);
		 virtual void onExit() override;
	
	public:	
		bool onContactBegin(PhysicsContact& contact);
		void createOprUI();
		void JumptoSnow(Ref* sender, TouchEventType type);
		void JumptoDecora(Ref* sender, TouchEventType type);
		void JumptoTradition(Ref* sender, TouchEventType type);
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
