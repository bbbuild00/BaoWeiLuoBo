#include "radish.h"
#include "GameScene.h"
#include"GameSelectionScene.h"
#include <string>

radish::radish(cocos2d::Vec2& a,GameScene* b)
{
	//log("radish::radish: radish's pscene: %p", b);
	rpoint = a;
	grade = 0;
	HP = ALLHP;
	scene = b;
}

radish* radish::create(cocos2d::Vec2& a,GameScene* b) 
{
	//log("radish::create:radish's pscene: %p", b);
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
	if (a < 0) {
		experimental::AudioEngine::play2d("/radish/Crash.mp3");
	}

	std::string str;
	if (HP < 10) {
		char t = HP + '0';
		str += t;
	}
	else {
		
	    char t = HP/ 10 + '0';
		str += t;
		t = HP % 10 + '0';
		str += t;
	}

	label->setString(str);
	if (HP == 9) {
		MySprite->setTexture("/radish/HP9.png");
	}
	else if (HP == 8) {
		MySprite->setTexture("/radish/HP8.png");
	}
	else if (HP == 7) {
		MySprite->setTexture("/radish/HP7.png");
	}
	else if (HP == 6) {
		MySprite->setTexture("/radish/HP6.png");
	}
	else if (HP == 5) {
		MySprite->setTexture("/radish/HP5.png");
	}
	else if (HP == 4) {
		MySprite->setTexture("/radish/HP4.png");
	}
	else if (HP == 3) {
		MySprite->setTexture("/radish/HP3.png");
	}
	else if (HP == 2) {
		MySprite->setTexture("/radish/HP2.png");
	}
	else if (HP ==1) {
		MySprite->setTexture("/radish/HP1.png");
	}
	else if (HP == 0) {
		MySprite->setTexture("/radish/HP0.png");
	}
	MySprite->setPosition(rpoint);
	MySprite->setContentSize(cocos2d::Size(size_of_radish, size_of_radish));
	if (HP == 0) {
		// 切换到下一个场景
		cocos2d::Director::getInstance()->replaceScene(GameSelectionScene::createScene());
		return 1;   //血量清零，游戏结束，返回值为1
	}
	return 0;
}

void radish::if_money()
{
	//log("if_money: radish's pscene: %p", scene);
	MoneyLayer* pMoney = dynamic_cast<MoneyLayer*>(scene->getChildByTag(TagMoney));
	int allmoney = pMoney->getMoney();
	if (allmoney >= UPMONEY) {
		upSprite->setVisible(true);
	}
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

	//画血量的小爱心❤
	auto bloodSprite = cocos2d::Sprite::create("/radish/blood.png");
	bloodSprite->setPosition(cocos2d::Vec2(rpoint.x+ size_of_radish / 2 +size_of_blood/2, rpoint.y ));
	bloodSprite->setContentSize(cocos2d::Size(size_of_blood, size_of_blood));
	this->addChild(bloodSprite);

	//画血量的数字
	label = cocos2d::Label::createWithSystemFont("10", "Arial", 30);
	label->setPosition(cocos2d::Vec2(rpoint.x + size_of_radish / 2 + size_of_blood/2 , rpoint.y - 45));
	this->addChild(label);
	
	//每隔0.1s,监测一下如果钱足够，就出现升级标识
	upSprite = cocos2d::Sprite::create("/radish/updata.png");
	upSprite->setPosition(cocos2d::Vec2(rpoint.x, rpoint.y + (size_of_radish / 2) + (size_of_up / 2)));
	upSprite->setContentSize(cocos2d::Size(size_of_up, size_of_up));
	this->addChild(upSprite);
	upSprite->setVisible(false);  //将精灵设置为不可见

	this->schedule([this](float dt) {
		this->if_money();
		}, 0.1, "ShootScheduler"); //1.0f为间隔时间，"ShootScheduler"为调度器的标签名



	auto listen= cocos2d::EventListenerTouchOneByOne::create();//新建了一个监听器
	
	listen->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event){
		auto touchLocation = this->convertToNodeSpace(touch->getLocation());
		if (!upSprite->isVisible() || !upSprite->getBoundingBox().containsPoint( touchLocation)) {
			listen->setSwallowTouches(false);
			return true;
		}
		listen->setSwallowTouches(true);
		change_HP(1);
		MoneyLayer* pMoney = dynamic_cast<MoneyLayer*>(scene->getChildByTag(TagMoney));
		pMoney->updateMoney(-UPMONEY);
		int allmoney = pMoney->getMoney();
		if (allmoney < UPMONEY) {
			upSprite->setVisible(false);
		}
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
			listen->setSwallowTouches(true);
			//cartoon(0.2f);//加载两帧动画

			auto swingAction = cocos2d::Sequence::create(
				cocos2d::RotateBy::create(0.1f, 15.0f),
				cocos2d::RotateBy::create(0.1f, -15.0f),
				cocos2d::RotateBy::create(0.1f, -15.0f),
				cocos2d::RotateBy::create(0.1f, 15.0f),
				nullptr
			);

			auto standAction = cocos2d::RotateTo::create(0.3f, 0.0f);
			auto rotateAction = cocos2d::RepeatForever::create(
				cocos2d::Sequence::create(
					swingAction,
					cocos2d::DelayTime::create(6.0f),
					standAction,
					nullptr
				)
			);

			MySprite->runAction(rotateAction);
			
			experimental::AudioEngine::play2d("/radish/carrot2.mp3");


		}
		else {
			setSwallowsTouches(true);
		}

		
		return true;
	};

	// 注册监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, MySprite);
	
	return true;
}
