#include "HomeScene.h"
//#include "BackgroundLayer.h"
#include <iostream>
//#include "Player.h"
#include "cocostudio/CocoStudio.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
#include "ChooseChapScene.h"
using namespace cocos2d::ui;
using namespace cocostudio;

HomeScene::~HomeScene()
{
}

Scene* HomeScene::scene()
{
	auto scene = Scene::createWithPhysics();

	/* ΢�������� */
	Vec2 gravity(0, -0.5f);// ��ʼ��һ����ά����
	scene->getPhysicsWorld()->setGravity(gravity);

	/* ��������ģʽ */
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	//����һ���߽�
	Size visibleSize = Director::getInstance()->getVisibleSize();

	/*
	����һ�����ĺ��Ӹ��壬��Ϊ������Ϸ����ı߽磨������Ϸ�ڵ������ܳ���Ļ��
	�����ֱ��Ǹ����С�����ʣ���ʵ����һЩԤ����������ݣ������ߺ��
	*/
	auto body = PhysicsBody::createEdgeBox(Size(visibleSize.width, visibleSize.height), PHYSICSBODY_MATERIAL_DEFAULT, 3);
	//creatEdgeXXX	��̬����

	/* ����һ���ڵ㣬���ڳ��ظ��壬����������ܲ��뵽��Ϸ���������� */
	auto node = Node::create();
	node->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	node->setPhysicsBody(body);
	scene->addChild(node);

	auto background = Sprite::create("Home_bg.png");
	background->setPosition(ccp(background->getContentSize().width / 2, background->getContentSize().height / 2));
	scene->addChild(background, 0);

	/*auto layer = TestScene::create();//����init��������layer
	scene->addChild(layer, 10);

	layer->m_backgroundLayer = backgroundLayer;
	*/
	auto layer = HomeScene::create();//����init��������layer
	
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

	/*

	Size visbleSize = Director::getInstance()->getVisibleSize();
	m_player = Player::create();
	m_player->setPosition(Point(visbleSize.width*0.5f, visbleSize.height*0.5f));
	this->addChild(m_player, 5);
	/*����UI
	createOprUI();
	/*��ײ����
	/*auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin=CC_CALLBACK_1
	this->schedule(schedule_selector(BeginScene::logic));
	//BeginScene���layerÿ��ִ��update
	*/
	//this->schedule(schedule_selector(TestScene::logic));
	return true;
}

void HomeScene::onExit()
{
	Layer::onExit();
}
void HomeScene::createOprUI()
{
	auto UI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("NewUi_1.ExportJson");
	this->addChild(UI);
	
	Button* Button_guanqia = (Button*)Helper::seekWidgetByName(UI, "Button_guanqia");
	Button_guanqia->addTouchEventListener(this, toucheventselector(HomeScene::JumptoGuanqia));

	//Button* quickMoveBtn = (Button*)Helper::seekWidgetByName(UI, "quickMoveBtn");

	//Button* leftBtn = (Button*)Helper::seekWidgetByName(UI, "leftBtn");

	
}
void HomeScene::JumptoGuanqia(Ref* sender, TouchEventType type)
{
	// "close" menu item clicked  
    
  
    //CCScene* psScene = CCTransitionShrinkGrow::create(1, s);  

	
	auto ChooseChapS = ChooseChapScene::create();
	if (ChooseChapS)
	{  
		CCDirector::sharedDirector()->replaceScene(ChooseChapS);
	}     
    //CCDirector::sharedDirector()->end();  

}


