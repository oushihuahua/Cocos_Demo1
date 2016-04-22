#include "HomeScene.h"
//#include "BackgroundLayer.h"
#include <iostream>
//#include "Player.h"
#include "cocostudio/CocoStudio.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
#include "ChooseChapScene.h"
#include "Draw.h"
using namespace cocos2d::ui;
using namespace cocostudio;

HomeScene::~HomeScene()
{
}

Scene* HomeScene::scene()
{
	auto scene = Scene::createWithPhysics();

	/* 微重力世界 */
	Vec2 gravity(0, -0.5f);// 初始化一个二维向量
	scene->getPhysicsWorld()->setGravity(gravity);

	/* 开启测试模式 */
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	//创建一个边界
	Size visibleSize = Director::getInstance()->getVisibleSize();

	/*
	创建一个空心盒子刚体，作为我们游戏世界的边界（避免游戏内的物体跑出屏幕）
	参数分别是刚体大小、材质（其实就是一些预设的配置数据）、边线厚度
	*/
	auto body = PhysicsBody::createEdgeBox(Size(visibleSize.width, visibleSize.height), PHYSICSBODY_MATERIAL_DEFAULT, 3);
	//creatEdgeXXX	静态刚体

	/* 创建一个节点，用于承载刚体，这样刚体就能参与到游戏的物理世界 */
	auto node = Node::create();
	node->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	node->setPhysicsBody(body);
	scene->addChild(node);
	auto background = Sprite::create("Home_bg.png");
	background->setPosition(ccp(background->getContentSize().width / 2, background->getContentSize().height / 2));
	scene->addChild(background, 0);

	/*auto layer = TestScene::create();//调用init函数创建layer
	scene->addChild(layer, 10);

	layer->m_backgroundLayer = backgroundLayer;
	*/
	auto layer = HomeScene::create();//调用init函数创建layer
	
	scene->addChild(layer, 10);
	return scene;
}


bool HomeScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	createOprUI();
	return true;
}

void HomeScene::onExit()
{
	Layer::onExit();
}
void HomeScene::createOprUI()
{
	auto UI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("UISnowL_1.ExportJson");
	this->addChild(UI);
	
	Button* Button_create = (Button*)Helper::seekWidgetByName(UI, "Button_Create");
	Button_create->addTouchEventListener(this, toucheventselector(HomeScene::Jumptocreate));


	Button* Button_guanqia = (Button*)Helper::seekWidgetByName(UI, "Button_Task");
	Button_guanqia->addTouchEventListener(this, toucheventselector(HomeScene::Jumptocreate));

	//Button* leftBtn = (Button*)Helper::seekWidgetByName(UI, "leftBtn");

	
}
void HomeScene::Jumptocreate(Ref* sender, TouchEventType type)
{
	if (type == ui::TouchEventType::TOUCH_EVENT_BEGAN)
	{
		auto Draw = Draw::create();
		if (Draw)
		{
			CCDirector::sharedDirector()->replaceScene(Draw);
		}
	}
    //CCDirector::sharedDirector()->end();  

}


