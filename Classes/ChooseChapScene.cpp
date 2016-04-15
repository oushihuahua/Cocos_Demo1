#include "ChooseChapScene.h"
#include "cocostudio/CocoStudio.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
#include "ChooseChapLayer.h"


ChooseChapScene::ChooseChapScene()
{
	
}
ChooseChapScene::~ChooseChapScene()
{
}

bool ChooseChapScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto subLayer = ChooseChapLayer::create();
	this->addChild(subLayer);
	return true;
}