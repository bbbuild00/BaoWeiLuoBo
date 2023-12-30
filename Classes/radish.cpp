#include "radish.h"
#include "GameScene.h"
#include <string>
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
	std::string str;
	if (a < 10) {
		char t = a + '0';
		str += t;
	}
	else {
		char t = a/10 + '0';
		str += t;
		t = a % 10 + '0';
		str += t;
	}

	label->setString(str);
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

/*void radish::if_money()
{
	MoneyLayer* pMoney = dynamic_cast<MoneyLayer*>(scene->getChildByTag(TagMoney));
	int allmoney = pMoney->getMoney();
	if (allmoney >= UPMONEY) {
		upSprite->setVisible(true);
	}
}*/
/*
void radish::cartoon(float dt) {
	// 创建一个用于存储精灵帧的容器
	cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;
	animFrames.reserve(3);

	// 获取纹理缓存
	auto textureCache = cocos2d::Director::getInstance()->getTextureCache();
	// 加载图片纹理
	cocos2d::Texture2D* texture = textureCache->addImage("ani1.png");

	// 获取纹理的宽度和高度
	float width_1 = texture->getContentSize().width;
	float height_1 = texture->getContentSize().height;

	// 获取纹理缓存
	textureCache = cocos2d::Director::getInstance()->getTextureCache();
	// 加载图片纹理
	texture = textureCache->addImage("ani2.png");

	// 获取纹理的宽度和高度
	float width_2 = texture->getContentSize().width;
	float height_2 = texture->getContentSize().height;

	// 获取纹理缓存
	textureCache = cocos2d::Director::getInstance()->getTextureCache();
	// 加载图片纹理
	texture = textureCache->addImage("ani3.png");

	// 获取纹理的宽度和高度
	float width_3 = texture->getContentSize().width;
	float height_3 = texture->getContentSize().height;

	// 将不同方向的精灵帧添加到容器中
	animFrames.pushBack(cocos2d::SpriteFrame::create("ani1.png", cocos2d::Rect(0, 0, width_1, height_1)));
	animFrames.pushBack(cocos2d::SpriteFrame::create("ani2.png", cocos2d::Rect(0, 0, width_2, height_2)));
	animFrames.pushBack(cocos2d::SpriteFrame::create("ani3.png", cocos2d::Rect(0, 0, width_3, height_3)));

	// 使用精灵帧容器创建一个动画对象，每一帧间隔为 0.2 秒
	cocos2d::Animation* animation = cocos2d::Animation::createWithSpriteFrames(animFrames, dt);

	// 使用动画对象创建一个动作对象
	cocos2d::Animate* animate = cocos2d::Animate::create(animation);

	// 将动作对象添加到精灵上，并使其永久重复播放
	MySprite->runAction(cocos2d::Action::create(animate));
}*/

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
	label->setPosition({cocos2d::Vec2(rpoint.x + size_of_radish / 2 + size_of_blood +15, rpoint.y);
	this->addChild(label);

	//每隔0.1s,监测一下如果钱足够，就出现升级标识
	upSprite = cocos2d::Sprite::create("/radish/updata.png");
	upSprite->setPosition(cocos2d::Vec2(rpoint.x, rpoint.y + (size_of_radish / 2) + (size_of_up / 2)));
	upSprite->setContentSize(cocos2d::Size(size_of_up, size_of_up));
	this->addChild(upSprite);
	upSprite->setVisible(false);  //将精灵设置为不可见

	/*this->schedule([this](float dt) {
		this->if_money();
		}, 0.1, "ShootScheduler"); //1.0f为间隔时间，"ShootScheduler"为调度器的标签名



	auto listen= cocos2d::EventListenerTouchOneByOne::create();//新建了一个监听器
	listen->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event){
		auto touchLocation = this->convertToNodeSpace(touch->getLocation());
		if (!upSprite->isVisible() || !upSprite->getBoundingBox().containsPoint( touchLocation)) {
			return true;
		}
		change_HP(1);
		MoneyLayer* pMoney = dynamic_cast<MoneyLayer*>(scene->getChildByTag(TagMoney));
		pMoney->update(-UPMONEY);
		int allmoney = pMoney->getMoney();
		if (allmoney < UPMONEY) {
			upSprite->setVisible(false);
		}
		return true;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listen, upSprite);

	/*this->schedule([=](float dt)
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
*/



	auto listener= cocos2d::EventListenerTouchOneByOne::create();//新建了一个监听器

	listener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event){
		auto touchLocation = this->convertToNodeSpace(touch->getLocation());
		// 检测鼠标是否点击精灵
		if (MySprite->getBoundingBox().containsPoint(touchLocation)) {
			// 在这里可以执行你需要的操作
			//在这里建一个点击以后的动画


			//cartoon(0.2f);//加载两帧动画

			auto swingAction = cocos2d::Sequence::create(
				cocos2d::RotateBy::create(0.3f, 30.0f),
				cocos2d::RotateBy::create(0.3f, -30.0f),
				cocos2d::RotateBy::create(0.3f, -30.0f),
				cocos2d::RotateBy::create(0.3f, 30.0f),
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
			
			


		}

		
		return true;
	};

	// 注册监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, MySprite);
	
	return true;
}
