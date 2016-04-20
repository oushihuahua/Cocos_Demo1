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

	/*Size��public���ԣ�float width   float height	*/
	//�����ɾ��Ļ���
	pRt = RenderTexture::create(visibleSize.width,visibleSize.height);//ê�����м�
	CCAssert(pRt, "RenderTexture is invalid");
	pRt->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(pRt);

	pRt1= RenderTexture::create(visibleSize.width, visibleSize.height);//ê�����м�
	CCAssert(pRt1, "RenderTexture is invalid");
	pRt1->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(pRt1);

	pFlower1 = CCSprite::create("passive1.png");
	CCAssert(pFlower1, "Flower sprite is invalid");
	pFlower1->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	pFlower1->retain();

	//��������ͼƬ
	pMask = CCSprite::create("mask1.png");
	CCAssert(pMask, "mask sprite is invalid");
	pMask->getTexture()->setAliasTexParameters();
	masksize = pMask->getContentSize();
	pMask->setPosition(visibleSize.width / 2, visibleSize.height / 2);//ê�����м�
	pMask->retain();

	//this->addChild(pMask);
	//����������ͼƬ
	pFlower = CCSprite::create("passive.png");
	CCAssert(pFlower, "Flower sprite is invalid");
	pFlower->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	pFlower->retain();

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

			// ���û��ģʽ
			BlendFunc blendFunc = { GL_ZERO, GL_ONE_MINUS_SRC_ALPHA };
			pEraser->setBlendFunc(blendFunc);

			// ����Ƥ����������Ⱦ�������ϣ���ԭ�������ؽ��л��
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
		if (generated == false)//bg1����
		{
			if (touchPoint.y <= 200 && touchPoint.x <= 200 )// preview��ť
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
				
				//��������ͼƬ
				//this->addChild(pMask);
				//����������ͼƬ
				
				//this->addChild(pFlower);
				//�����ú� ���־��� �� �����־��� �ڱ���Ⱦ��ʱ�����ʲô������ɫ��Ϸ���
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
			else if (touchPoint.x >= 741 && touchPoint.x <=902 && touchPoint.y >= 396 && touchPoint.y <= 457)//undo��ť ������Ⱦ
			{
				pRt->beginWithClear(0,0,0,0);
				pMask->visit();
				pFlower->visit();
				pRt->end();
			}
			else//��ͼ
			{
				if (generated == false)//bg1����ſ��Ի�ͼ
				{
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
		}
		else if (generated==true)//preview����
		{
			if (touchPoint.y <= 200 && touchPoint.x <= 200)//����
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
	if (generated == false)//����bg2
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