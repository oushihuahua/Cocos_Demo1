#include "ChooseChapLayer.h"
#include "cocostudio/CocoStudio.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
#include "Draw.h"

#define DecoraChap  1;
#define SnowChap 2;
#define TaditionChap 3;

//using namespace 
using namespace cocos2d::ui;
using namespace cocostudio;



ChooseChapLayer::ChooseChapLayer()
{
	 
}
ChooseChapLayer::~ChooseChapLayer()
{
}


bool ChooseChapLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto ChooseChap_bg = Sprite::create("ChooseChapBg.png");
	ChooseChap_bg->setPosition(ccp(ChooseChap_bg->getContentSize().width / 2, ChooseChap_bg->getContentSize().height/2));
	this->addChild(ChooseChap_bg);
	createOprUI();




	/*auto ChooseChapBg = Sprite::create("ChooseChapBg.png");
	ChooseChapBg->setPosition(ccp(ChooseChapBg->getContentSize().width / 2, ChooseChapBg->getContentSize().height / 2));
	this->addChild(ChooseChapBg);

	tScrollView = ScrollView::create();
	tScrollView->setDirection(ScrollView::Direction::HORIZONTAL);
	//不要用滑动层了 我的心好痛啊 好痛啊 
	//tScrollView->createContainer(this, 5, CCSizeMake(CCDirector::sharedDirector()->getVisibleSize().width * 0.8, CCDirector::sharedDirector()->getVisibleSize().height));
	*/
	return true;
}
void ChooseChapLayer::onExit()
{
	Layer::onExit();
}


void ChooseChapLayer::createOprUI()
{
	auto UI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ChosseChapUi_1.ExportJson");
	this->addChild(UI);

	Button* Button_Decora = (Button*)Helper::seekWidgetByName(UI, "Button_1");
	Button_Decora->addTouchEventListener(this, toucheventselector(ChooseChapLayer::JumptoDecora));

	//Button* quickMoveBtn = (Button*)Helper::seekWidgetByName(UI, "quickMoveBtn");
	Button* Button_Snow = (Button*)Helper::seekWidgetByName(UI, "Button_2");
	Button_Snow->addTouchEventListener(this, toucheventselector(ChooseChapLayer::JumptoSnow));





	//Button* leftBtn = (Button*)Helper::seekWidgetByName(UI, "leftBtn");
	Button* Button_Tradition = (Button*)Helper::seekWidgetByName(UI, "Button_3");
	Button_Tradition->addTouchEventListener(this, toucheventselector(ChooseChapLayer::JumptoTradition));

}
//Button_1 装饰 Button_2 雪花 Button_3 传统
void ChooseChapLayer::JumptoSnow(Ref* sender, TouchEventType type)
{
	
	auto Draw = Draw::create();
	Draw->Chap = SnowChap;
	bool initok = Draw->initChap();
	if (initok)
	{
		CCDirector::sharedDirector()->replaceScene(Draw);
	}
}
void ChooseChapLayer::JumptoDecora(Ref* sender, TouchEventType type)
{

}
void ChooseChapLayer::JumptoTradition(Ref* sender, TouchEventType type)
{

}


