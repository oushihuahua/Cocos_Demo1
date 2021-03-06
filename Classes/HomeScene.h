#ifndef HomeScene_H
#define HomeScene_H
#include "cocos2d.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocostudio;

USING_NS_CC;
class HomeScene : public Layer
{
public:
	~HomeScene();
	static Scene* scene();//创建一个场景 这个方法中会创建BeginScene的layer
	CREATE_FUNC(HomeScene);
	virtual bool init();
	virtual void onExit() override;

private:
	//bool onContactBegin(PhysicsContact& contact);
	//void logic(float dt);
	//BackgroundLayer* m_backgroundLayer;
	void createOprUI();
	void Jumptocreate(Ref* sender, TouchEventType type);
	/*void moveDown(Ref* sender, TouchEventType type);
	void moveFart(Ref* sender, TouchEventType type);*/
	//Player m_Player;
};

#endif