#include "DrawUI.h"
#include "cocostudio/CocoStudio.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"

//using namespace 
using namespace cocos2d::ui;
using namespace cocostudio;



DrawUI::DrawUI()
{

}
DrawUI::~DrawUI()
{
}


bool DrawUI::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->setSwallowsTouches(false);
	this->setTouchEnabled(true);
	/*auto m_bg1 = Sprite::create("SnowChap.png");
	m_bg1->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(m_bg1,0);*/

	auto button_generate = MenuItemImage::create();
	button_generate->setNormalImage(Sprite::create("generate.png"));
	button_generate->setPosition(100, 200);
	this->addChild(button_generate);




	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();

	auto listen = EventListenerTouchOneByOne::create();
	listen->onTouchBegan = CC_CALLBACK_2(DrawUI::onTouchBegan, this);
	return true;
}
void DrawUI::onExit()
{
	Layer::onExit();
}


bool DrawUI::onTouchBegan(Touch *  touch,Event *  unused_event)
{
	return true;
}



