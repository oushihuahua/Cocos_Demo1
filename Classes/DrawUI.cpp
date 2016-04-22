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
	createOprUI();
}

void DrawUI::createOprUI()
{
	auto UI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("DrawDraw_1.ExportJson");
	this->addChild(UI);

	Button* Button_preview = (Button*)Helper::seekWidgetByName(UI, "Button_1");
	Button_preview->addTouchEventListener(this, toucheventselector(DrawUI::setPreview));


	Button* Button_undo = (Button*)Helper::seekWidgetByName(UI, "Button_2");
	Button_undo->addTouchEventListener(this, toucheventselector(DrawUI::setUndo));
}
void DrawUI::setPreview(Ref* sender, TouchEventType type)
{
	if (type == ui::TouchEventType::TOUCH_EVENT_BEGAN)
	{

	}
	//CCDirector::sharedDirector()->end();  

}

void DrawUI::setUndo(Ref* sender, TouchEventType type)
{
	if (type == ui::TouchEventType::TOUCH_EVENT_BEGAN)
	{
	}
	//CCDirector::sharedDirector()->end();  

}


