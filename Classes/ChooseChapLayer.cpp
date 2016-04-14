#include "ChooseChapLayer.h"
#include "cocostudio/CocoStudio.h"
#include "editor-support/cocostudio/CCSGUIReader.h"


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
	auto ChooseChapBg = Sprite::create("ChooseChapBg.png");
	ChooseChapBg->setPosition(ccp(ChooseChapBg->getContentSize().width / 2, ChooseChapBg->getContentSize().height / 2));
	this->addChild(ChooseChapBg);
	return true;
}