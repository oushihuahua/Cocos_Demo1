#ifndef DrawUI_H
#define DrawUI_H
#include "cocos2d.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocostudio;

USING_NS_CC;


class DrawUI : public Layer
{


public:
	DrawUI();
	~DrawUI();
	virtual bool init();
	//»¬¶¯´¥·¢
	CREATE_FUNC(DrawUI);

private:
	void createOprUI();
	void Jumptocreate(Ref* sender, TouchEventType type);
	void setPreview(Ref* sender, TouchEventType type);
	void setUndo(Ref* sender, TouchEventType type);
};

#endif