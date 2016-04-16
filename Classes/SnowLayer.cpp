#include "SnowLayer.h"
#include "cocostudio/CocoStudio.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"

//using namespace 
//using namespace cocos2d::ui;
//using namespace cocostudio;



SnowLayer::SnowLayer()
{

}
SnowLayer::~SnowLayer()
{
}


bool SnowLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	


	this->setTouchEnabled(true);
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();

	auto listen = EventListenerTouchAllAtOnce::create();
	listen->onTouchesBegan = CC_CALLBACK_2(SnowLayer::onTouchesBegan, this);
	listen->onTouchesMoved = CC_CALLBACK_2(SnowLayer::onTouchesMoved, this);
	eventDispatcher->addEventListenerWithSceneGraphPriority(listen, this);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto m_bg1 = Sprite::create("SnowChap.png");
	m_bg1->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(m_bg1, 0);
	//createOprUI();

	/*Size类public属性：float width   float height	*/
	//创建干净的画板
	pRt = RenderTexture::create(515, 961);//锚点在中间
	CCAssert(pRt, "RenderTexture is invalid");
	pRt->setPosition(515 / 2, 961 / 2);
	addChild(pRt);
	//创建遮罩图片
	Sprite *pMask = CCSprite::create("mask1.png");
	CCAssert(pMask, "mask sprite is invalid");
	pMask->getTexture()->setAliasTexParameters();
	pMask->setPosition(CCPointMake(pMask->getContentSize().width / 2, pMask->getContentSize().height / 2));//锚点在中间
	//this->addChild(pMask);
	//创建被遮罩图片
	Sprite *pFlower = CCSprite::create("passive.png");
	CCAssert(pFlower, "Flower sprite is invalid");
	pFlower->setPosition(CCPointMake(pFlower->getContentSize().width / 2, pFlower->getContentSize().height / 2));
	//this->addChild(pFlower);
	//先设置好 遮罩精灵 和 被遮罩精灵 在被渲染的时候采用什么样的颜色混合法则
	BlendFunc maskBlend = { GL_ONE, GL_ZERO };
	BlendFunc flowerBlend = { GL_DST_ALPHA, GL_ZERO };
	pMask->setBlendFunc(maskBlend);
	pFlower->setBlendFunc(flowerBlend);


	// 创建一个橡皮擦，注意颜色的设置是全透明黑色
	//橡皮擦单设一个类用来维护画笔花式和大小
	pEraser = Sprite::create("eraser.png");
	pEraser->retain();


	//开始把各种精灵渲染到画板上
	pRt->begin();
	//先渲染遮罩精灵。但是因为有个画板先被渲染。所以pMask是第二个被渲染的，即后被渲染。
	//所以在这一刻pMask是源颜色。调用pMask->visit()的时候吧精灵pMask上的每个像素的RGBA分量和1.0相乘。
	//所以遮罩图片被原模原样的渲染出来.
	//再渲染被遮罩的精灵.在这一刻,之前先有pMask被渲染。所以pFlower后被渲染。pFlower就是源颜色。之前的pMask就是目标颜色。
	//调用pFlower->visit()的时候,精灵pFlower上的对应像素的RGBA分量和pMask上的对应像素的A分量相乘.因为前面设置了GL_DST_ALPHA。
	pMask->visit();
	pFlower->visit();
	pRt->end();
	/*Point是Vec2的别名 Vec2属性：float x,float y*/
	/*创建边缘锯齿*/
	//this->addTouchListener

	cocos2d::Vector<cocos2d::Sprite*> list;
	for (int i = 0; i <12; ++i){
		Sprite* sprite = Sprite::createWithTexture(this->getSector()->getTexture());
		sprite->setAnchorPoint(ccp(0.5, 0));
		sprite->getTexture()->setAliasTexParameters();
		sprite->setRotation(i * 30);
		if (i % 2 == 1){
			sprite->setFlipX(true);
		}
		list.pushBack(sprite);
	}
	for (auto& sprite : list)
	{
		sprite->setFlipY(true);
		sprite->setPosition(ccp(1000, 500));
		this->removeChild(sprite);
		this->addChild(sprite);
	}
	
	return true;
}
void SnowLayer::onExit()
{
	Layer::onExit();
}


/*void SnowLayer::createOprUI()
{
	auto UI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("DrawScene_1.ExportJson");
	this->addChild(UI);

	cocos2d::ui::Button* Button_back = (cocos2d::ui::Button*)cocos2d::ui::Helper::seekWidgetByName(UI, "Button_back");
	//Button_back->addTouchEventListener(this, cocos2d::toucheventselector(SnowLayer::onExit));

	//Button* quickMoveBtn = (Button*)Helper::seekWidgetByName(UI, "quickMoveBtn");
	cocos2d::ui::Button* Button_generate = (cocos2d::ui::Button*)cocos2d::ui::Helper::seekWidgetByName(UI, "Button_generate");
	//Button_generate->addTouchEventListener(this, toucheventselector(ChooseChapLayer::JumptoSnow));





	//Button* leftBtn = (Button*)Helper::seekWidgetByName(UI, "leftBtn");
	cocos2d::ui::Button* Button_redo = (cocos2d::ui::Button*)cocos2d::ui::Helper::seekWidgetByName(UI, "Button_redo");
	//Button_redo->addTouchEventListener(this, toucheventselector(ChooseChapLayer::JumptoTradition));
	return;
}*/
void SnowLayer::onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
	// 获取触摸坐标并移动橡皮擦到该坐标
	for (auto &item : touches)
	{
		auto touch = item;
		Point touchPoint = touch->getLocation();
		pEraser->setPosition(touchPoint);

		// 设置混合模式
		BlendFunc blendFunc = { GL_ZERO, GL_ONE_MINUS_SRC_ALPHA };
		pEraser->setBlendFunc(blendFunc);

		// 将橡皮擦的像素渲染到画布上，与原来的像素进行混合
		pRt->begin();
		pEraser->visit();
		pRt->end();
	}
}
void SnowLayer::onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
	for (auto &item : touches)
	{
		auto touch = item;
		Point touchPoint = touch->getLocation();
		pEraser->setPosition(touchPoint);

		// 设置混合模式
		BlendFunc blendFunc = { GL_ZERO, GL_ONE_MINUS_SRC_ALPHA };
		pEraser->setBlendFunc(blendFunc);

		// 将橡皮擦的像素渲染到画布上，与原来的像素进行混合
		pRt->begin();
		pEraser->visit();
		pRt->end();
	}
}


CCSprite * SnowLayer::getSector()
{
	return Sprite::createWithTexture(pRt->getSprite()->getTexture());
}

