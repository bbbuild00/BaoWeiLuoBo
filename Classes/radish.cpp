#include "radish.h"
#include "GameScene.h"

radish::radish(cocos2d::Vec2& a,GameScene* b)
{
	rpoint = a;
	grade = 0;
	HP = ALLHP;
	scene = b;
}

radish* radish::create(cocos2d::Vec2& a,GameScene* b) 
{
	radish* layer = new radish(a,b);
	if (layer && layer->init()) {
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}

int radish::change_HP(int a)
{
	HP += a;
	if (HP == 9) {
		MySprite = cocos2d::Sprite::create("/radish/HP9.png");
	}
	else if (HP == 8) {
		MySprite = cocos2d::Sprite::create("/radish/HP8.png");
	}
	else if (HP == 7) {
		MySprite = cocos2d::Sprite::create("/radish/HP7.png");
	}
	else if (HP == 6) {
		MySprite = cocos2d::Sprite::create("/radish/HP6.png");
	}
	else if (HP == 5) {
		MySprite = cocos2d::Sprite::create("/radish/HP5.png");
	}
	else if (HP == 4) {
		MySprite = cocos2d::Sprite::create("/radish/HP4.png");
	}
	else if (HP == 3) {
		MySprite = cocos2d::Sprite::create("/radish/HP3.png");
	}
	else if (HP == 2) {
		MySprite = cocos2d::Sprite::create("/radish/HP2.png");
	}
	else if (HP ==1) {
		MySprite = cocos2d::Sprite::create("/radish/HP1.png");
	}
	else if (HP == 0) {
		MySprite = cocos2d::Sprite::create("/radish/HP0.png");
	}
	MySprite->setPosition(rpoint);
	MySprite->setContentSize(cocos2d::Size(size_of_radish, size_of_radish));
	if (HP == 0) {
		return 1;   //血量清零，游戏结束，返回值为1
	}
	return 0;
}

bool radish::init()
{
	if (!Layer::init()) {
		return false;
	}
	// 在这里进行更多的初始化操作
	MySprite = cocos2d::Sprite::create("/radish/HP10.png");
	MySprite->setPosition(rpoint);
	MySprite->setContentSize(cocos2d::Size(size_of_radish, size_of_radish));
	this->addChild(MySprite);

	//每隔0.1s,监测一下如果钱足够，就出现升级标识
	auto upSprite = cocos2d::Sprite::create("/radish/updata.png");
	upSprite->setPosition(cocos2d::Vec2(rpoint.x, rpoint.y + (size_of_radish / 2) + (size_of_up / 2)));
	upSprite->setContentSize(cocos2d::Size(size_of_up, size_of_up));
	this->addChild(upSprite);
	upSprite->setVisible(false);  //将精灵设置为不可见

	auto listen= cocos2d::EventListenerTouchOneByOne::create();//新建了一个监听器
	listen->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event){
		auto touchLocation = this->convertToNodeSpace(touch->getLocation());
		if (!upSprite->isVisible() || !upSprite->getBoundingBox().containsPoint( touchLocation)) {
			return true;
		}
		change_HP(1);
		MoneyLayer* pMoney = dynamic_cast<MoneyLayer*>(scene->getChildByTag(TagMoney));
		pMoney->update(-UPMONEY);
		upSprite->setVisible(false);
		return true;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listen, upSprite);

	this->schedule([=](float dt)
		{
			MoneyLayer* pMoney = dynamic_cast<MoneyLayer*>(scene->getChildByTag(TagMoney));
			int allmoney = pMoney->getMoney();
			if(allmoney >= UPMONEY) {
				upSprite->setVisible(true);
			} 
			else {
				upSprite->setVisible(false);
			}
		}, 0.1f, "check_key");




	auto listener= cocos2d::EventListenerTouchOneByOne::create();//新建了一个监听器

	listener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event){
		auto touchLocation = this->convertToNodeSpace(touch->getLocation());
		// 检测鼠标是否点击精灵
		if (MySprite->getBoundingBox().containsPoint(touchLocation)) {
			// 在这里可以执行你需要的操作
			//在这里建一个点击以后的动画


			


			
			


		}


		return true;
	};

	// 注册监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, MySprite);

	return true;
}
