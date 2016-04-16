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

	/*Size��public���ԣ�float width   float height	*/
	//�����ɾ��Ļ���
	pRt = RenderTexture::create(515, 961);//ê�����м�
	CCAssert(pRt, "RenderTexture is invalid");
	pRt->setPosition(515 / 2, 961 / 2);
	addChild(pRt);
	//��������ͼƬ
	Sprite *pMask = CCSprite::create("mask1.png");
	CCAssert(pMask, "mask sprite is invalid");
	pMask->getTexture()->setAliasTexParameters();
	pMask->setPosition(CCPointMake(pMask->getContentSize().width / 2, pMask->getContentSize().height / 2));//ê�����м�
	//this->addChild(pMask);
	//����������ͼƬ
	Sprite *pFlower = CCSprite::create("passive.png");
	CCAssert(pFlower, "Flower sprite is invalid");
	pFlower->setPosition(CCPointMake(pFlower->getContentSize().width / 2, pFlower->getContentSize().height / 2));
	//this->addChild(pFlower);
	//�����ú� ���־��� �� �����־��� �ڱ���Ⱦ��ʱ�����ʲô������ɫ��Ϸ���
	BlendFunc maskBlend = { GL_ONE, GL_ZERO };
	BlendFunc flowerBlend = { GL_DST_ALPHA, GL_ZERO };
	pMask->setBlendFunc(maskBlend);
	pFlower->setBlendFunc(flowerBlend);


	// ����һ����Ƥ����ע����ɫ��������ȫ͸����ɫ
	//��Ƥ������һ��������ά�����ʻ�ʽ�ʹ�С
	pEraser = Sprite::create("eraser.png");
	pEraser->retain();


	//��ʼ�Ѹ��־�����Ⱦ��������
	pRt->begin();
	//����Ⱦ���־��顣������Ϊ�и������ȱ���Ⱦ������pMask�ǵڶ�������Ⱦ�ģ�������Ⱦ��
	//��������һ��pMask��Դ��ɫ������pMask->visit()��ʱ��ɾ���pMask�ϵ�ÿ�����ص�RGBA������1.0��ˡ�
	//��������ͼƬ��ԭģԭ������Ⱦ����.
	//����Ⱦ�����ֵľ���.����һ��,֮ǰ����pMask����Ⱦ������pFlower����Ⱦ��pFlower����Դ��ɫ��֮ǰ��pMask����Ŀ����ɫ��
	//����pFlower->visit()��ʱ��,����pFlower�ϵĶ�Ӧ���ص�RGBA������pMask�ϵĶ�Ӧ���ص�A�������.��Ϊǰ��������GL_DST_ALPHA��
	pMask->visit();
	pFlower->visit();
	pRt->end();
	/*Point��Vec2�ı��� Vec2���ԣ�float x,float y*/
	/*������Ե���*/
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
	// ��ȡ�������겢�ƶ���Ƥ����������
	for (auto &item : touches)
	{
		auto touch = item;
		Point touchPoint = touch->getLocation();
		pEraser->setPosition(touchPoint);

		// ���û��ģʽ
		BlendFunc blendFunc = { GL_ZERO, GL_ONE_MINUS_SRC_ALPHA };
		pEraser->setBlendFunc(blendFunc);

		// ����Ƥ����������Ⱦ�������ϣ���ԭ�������ؽ��л��
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

		// ���û��ģʽ
		BlendFunc blendFunc = { GL_ZERO, GL_ONE_MINUS_SRC_ALPHA };
		pEraser->setBlendFunc(blendFunc);

		// ����Ƥ����������Ⱦ�������ϣ���ԭ�������ؽ��л��
		pRt->begin();
		pEraser->visit();
		pRt->end();
	}
}


CCSprite * SnowLayer::getSector()
{
	return Sprite::createWithTexture(pRt->getSprite()->getTexture());
}

