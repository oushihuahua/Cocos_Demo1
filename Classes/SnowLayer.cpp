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
	generated = false;
	bignode = Sprite::create();
	this->addChild(bignode);

	this->list =Vector< Sprite* >();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto m_bg1 = Sprite::create("DrawBG_1.png");
	auto m_bg2 = Sprite::create("DrawBG_2.png");

	m_bg2->setVisible(false);
	this->addChild(m_bg1);
	this->addChild(m_bg2);	
	m_bg2->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	m_bg1->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));

	
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();

	auto listen = EventListenerTouchAllAtOnce::create();
	listen->onTouchesBegan = CC_CALLBACK_2(SnowLayer::onTouchesBegan, this);
	listen->onTouchesMoved = CC_CALLBACK_2(SnowLayer::onTouchesMoved, this);
	eventDispatcher->addEventListenerWithSceneGraphPriority(listen,this);
/*	auto m_bg1 = Sprite::create("SnowChap.png");
	m_bg1->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(m_bg1, 0);*/
	//createOprUI();

	/*Size类public属性：float width   float height	*/
	//创建干净的画板
	pRt = RenderTexture::create(visibleSize.width,visibleSize.height);//锚点在中间
	CCAssert(pRt, "RenderTexture is invalid");
	pRt->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(pRt);

	pRt1= RenderTexture::create(visibleSize.width, visibleSize.height);//锚点在中间
	CCAssert(pRt1, "RenderTexture is invalid");
	pRt1->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(pRt1);

	pFlower1 = CCSprite::create("passive1.png");
	CCAssert(pFlower1, "Flower sprite is invalid");
	pFlower1->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	pFlower1->retain();

	//创建遮罩图片
	pMask = CCSprite::create("mask1.png");
	CCAssert(pMask, "mask sprite is invalid");
	pMask->getTexture()->setAliasTexParameters();
	masksize = pMask->getContentSize();
	pMask->setPosition(visibleSize.width / 2, visibleSize.height / 2);//锚点在中间
	pMask->retain();

	//this->addChild(pMask);
	//创建被遮罩图片
	pFlower = CCSprite::create("passive.png");
	CCAssert(pFlower, "Flower sprite is invalid");
	pFlower->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	pFlower->retain();

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
	return true;
}
void SnowLayer::onExit()
{
	Layer::onExit();
}

void SnowLayer::onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
	if (generated == false)
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
}
void SnowLayer::onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event  *event)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	for (auto &item : touches)
	{
		auto touch = item;
		Point touchPoint = touch->getLocation();
		if (generated == false)//bg1界面
		{
			if (touchPoint.y <= 200 && touchPoint.x <= 200 )// preview按钮
			{				
				generated = true;
				//ChangeBG();
			   
				
				for (int i = 0; i < 12; ++i){
					Sprite* sprite = Sprite::createWithTexture(this->getSector()->getTexture());
					sprite->setAnchorPoint(ccp(0.5, 59.5 / 1080));
					sprite->getTexture()->setAliasTexParameters();
					sprite->setRotation(i * 30);
					//	sprite->setBlendFunc(maskBlend);
					if (i % 2 == 1){
						sprite->setFlipX(true);
					}
					list.pushBack(sprite);
				}
				pRt->setVisible(false);
				for (auto& sprite : list)
				{

					sprite->setFlipY(true);
					sprite->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
					sprite->setScale(0.5f);			
					int a = bignode->getChildrenCount();
					bignode->addChild(sprite);
				}
				list.clear();
				//this->addChild(bignode);
				
				//创建遮罩图片
				//this->addChild(pMask);
				//创建被遮罩图片
				
				//this->addChild(pFlower);
				//先设置好 遮罩精灵 和 被遮罩精灵 在被渲染的时候采用什么样的颜色混合法则
				BlendFunc maskBlend = { GL_ONE, GL_ZERO };
				BlendFunc flowerBlend = { GL_DST_ALPHA, GL_ZERO };
				bignode->setBlendFunc(maskBlend);
				pFlower1->setBlendFunc(flowerBlend);
				pRt1->beginWithClear(0,0,0,0);
				bignode->visit();//stackoverflow
				pFlower1->visit();
				pRt1->end();
				pRt1->setVisible(true);
				this->bignode->removeAllChildren();
			}
			else if (touchPoint.x >= 741 && touchPoint.x <=902 && touchPoint.y >= 396 && touchPoint.y <= 457)//undo按钮 重新渲染
			{
				pRt->beginWithClear(0,0,0,0);
				pMask->visit();
				pFlower->visit();
				pRt->end();
			}
			else//画图
			{
				if (generated == false)//bg1界面才可以画图
				{
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
		}
		else if (generated==true)//preview界面
		{
			if (touchPoint.y <= 200 && touchPoint.x <= 200)//返回
			{
				pRt1->setVisible(false);				
				pRt->setVisible(true);
				generated = false;
			}
		}
		
	}
}


CCSprite * SnowLayer::getSector()
{
	return Sprite::createWithTexture(pRt->getSprite()->getTexture());
}

bool SnowLayer::ChangeBG()
{
	if (generated == false)//换成bg2
	{
		m_bg2->setVisible(true);
		m_bg1->setVisible(false);
		generated = true;
		return true;
	}
	else
	{
		m_bg1->setVisible(true);
		m_bg2->setVisible(false);
		generated = false;
		return true;
	}
}