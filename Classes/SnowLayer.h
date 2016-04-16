#ifndef SnowLayer_H
#define SnowLayer_H
#include "cocos2d.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
//using namespace cocos2d::ui;
//using namespace cocostudio;


//#include "cocos-ext.h"

//using namespace 
//USING_NS_CC_EXT;
USING_NS_CC;



class SnowLayer : public Layer
{


public:
	SnowLayer();
	~SnowLayer();
	virtual bool init();
	//»¬¶¯´¥·¢
	CREATE_FUNC(SnowLayer);
	virtual void onExit() override;
	virtual void onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event);
	virtual void onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event);
	//void createOprUI();
	CCSprite* getSector();
private:
	Sprite* m_bg1;
	RenderTexture* pRt;
	Sprite* pEraser;
	


};

#endif
