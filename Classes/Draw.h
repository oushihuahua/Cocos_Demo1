#ifndef Draw_H
#define Draw_H
#include "cocos2d.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocostudio;

#define DecoraChap  1
#define SnowChap 2
#define TaditionChap 3


USING_NS_CC;
class Draw : public Scene
{
public:
	Draw();
	~Draw();
	
	CREATE_FUNC(Draw);
	virtual bool init();
	//virtual void onExit() override;
	int Chap;
	bool initChap();
private:
	bool onContactBegin(PhysicsContact& contact);
	//void logic(float dt);
	//BackgroundLayer* m_backgroundLayer;
	void createOprUI();
	void JumptoGuanqia(Ref* sender, TouchEventType type);
	/*void moveDown(Ref* sender, TouchEventType type);
	void moveFart(Ref* sender, TouchEventType type);*/
	//Player m_Player;
};

#endif