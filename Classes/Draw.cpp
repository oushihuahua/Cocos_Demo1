#include "Draw.h"
#include "cocostudio/CocoStudio.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
#include "SnowLayer.h"

//using namespace 
using namespace cocos2d::ui;
using namespace cocostudio;



Draw::Draw()
{

}
Draw::~Draw()
{
}


bool Draw :: init()
{
	if (!Scene::init())
	{
		return false;
	}
	return true;
}




bool Draw::initChap()
{
	if (this->Chap == SnowChap)
	{
		auto layer = SnowLayer::create();
		this->addChild(layer);
	}
	return true;
}


