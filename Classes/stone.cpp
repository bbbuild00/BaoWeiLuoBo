#include"stone.h"
#include"GameScene.h"

cocos2d::Vec2 stone::getpos()//获得当前位置
{
    cocos2d::Vec2 position = stone_s->getPosition();
    return position;
}

void stone::addtower(tower* a) {
    Attacktower.pushBack(a);
}



void stone::mouse_click() {
    auto listener2 = cocos2d::EventListenerTouchOneByOne::create();//新建了一个监听器

    listener2->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
        log("stone:onTouchBegan, %p", this);
        auto touchLocation = this->convertToNodeSpace(touch->getLocation());
        // 检测鼠标是否点击精灵
        if (stone_s->getBoundingBox().containsPoint(touchLocation)) {
            // 在这里可以执行你需要的操作
            //在这里建一个点击以后的动画
            log("stone:clicked, %p", this);
            TowerLayer* pTower = dynamic_cast<TowerLayer*>(w->getChildByTag(TagTower));

            for (Node* child : pTower->getChildren()) {
                if (tower* e = dynamic_cast<tower*>(child)) {
                    bool a = e->check_if_in_range(this->getpos());
                    if (a) {
                        e->get_stone(this);

                    }
                }
            }


        }
        return false;
        };

    // 注册监听器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, stone_s);

}

void stone::Attacked(int damage) {
    HP -= damage;
    draw_hp();
    if (HP <= 0) {
        //调用函数：移走石头（防御塔和控制台），添加金币，
        //和炮塔层通讯
       // TowerLayer* pTower = dynamic_cast<TowerLayer*>(w->getChildByTag(TagTower));
        for (size_t i = 0; i < Attacktower.size(); i++) {
            tower* e;
            e = Attacktower.at(i);
            e->enemy_killed();
        }

        StoneLayer* pStone = dynamic_cast<StoneLayer*>(w->getChildByTag(TagStone));
        //调用函数：移走石头（防御塔和控制台），添加金币，
        pStone->removeStone(this, getmoney());

    }
}

stone1* stone1::create(cocos2d::Vec2 po, GameScene* lay) {
    stone1* layer = new stone1(po, lay);
    if (layer && layer->init()) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

stone2* stone2::create(cocos2d::Vec2 po, GameScene* lay) {
    stone2* layer = new stone2(po, lay);
    if (layer && layer->init()) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

stone3* stone3::create(cocos2d::Vec2 po, GameScene* lay) {
    stone3* layer = new stone3(po, lay);
    if (layer && layer->init()) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

stone4* stone4::create(cocos2d::Vec2 po, GameScene* lay) {
    stone4* layer = new stone4(po, lay);
    if (layer && layer->init()) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

stone5* stone5::create(cocos2d::Vec2 po, GameScene* lay) {
    stone5* layer = new stone5(po, lay);
    if (layer && layer->init()) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

stone6* stone6::create(cocos2d::Vec2 po, GameScene* lay) {
    stone6* layer = new stone6(po, lay);
    if (layer && layer->init()) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

stone7* stone7::create(cocos2d::Vec2 po, GameScene* lay) {
    stone7* layer = new stone7(po, lay);
    if (layer && layer->init()) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

stone8* stone8::create(cocos2d::Vec2 po, GameScene* lay) {
    stone8* layer = new stone8(po, lay);
    if (layer && layer->init()) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

stone9* stone9::create(cocos2d::Vec2 po, GameScene* lay) {
    stone9* layer = new stone9(po, lay);
    if (layer && layer->init()) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

stone1::stone1(cocos2d::Vec2 p, GameScene* lay) {
    point = p;
    w = lay;
    HP = 100;
    fullHP = 100;
}

stone2::stone2(cocos2d::Vec2 p, GameScene* lay) {
    point = p;
    w = lay;
    HP = 100;
    fullHP = 100;
}

stone3::stone3(cocos2d::Vec2 p, GameScene* lay) {
    point = p;
    w = lay;
    HP = 100;
    fullHP = 100;
}

stone4::stone4(cocos2d::Vec2 p, GameScene* lay) {
    point = p;
    w = lay;
    HP = 100;
    fullHP = 100;
}

stone5::stone5(cocos2d::Vec2 p, GameScene* lay) {
    point = p;
    w = lay;
    HP = 100;
    fullHP = 100;
}

stone6::stone6(cocos2d::Vec2 p, GameScene* lay) {
    point = p;
    w = lay;
    HP = 100;
    fullHP = 100;
}

stone7::stone7(cocos2d::Vec2 p, GameScene* lay) {
    point = p;
    w = lay;
    HP = 100;
    fullHP = 100;
}

stone8::stone8(cocos2d::Vec2 p, GameScene* lay) {
    point = p;
    w = lay;
    HP = 100;
    fullHP = 100;
}

stone9::stone9(cocos2d::Vec2 p, GameScene* lay) {
    point = p;
    w = lay;
    HP = 100;
    fullHP = 100;
}

void stone::draw_hp() {
        // 更新血条
        float percentage = HP / fullHP;
        Brush->setScaleX(0.02f * percentage);
    
}

void stone1::draw_stone() {
    // 创建 Sprite
    stone_s = cocos2d::Sprite::create("balloon.png");

    // 获取屏幕可见区域的大小
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // 设置位置
   // stone_s->setPosition(cocos2d::Director::getInstance()->getVisibleSize() / 2);
    stone_s->setPosition(6*75+40,6*75+20);

    // 设置精灵初始大小
    stone_s->setScale(0.15f); // 缩小为原来的倍数

    // 在初始化函数中创建矩形精灵
    Brush = cocos2d::Sprite::create("brush.png");
    Brush->setAnchorPoint(cocos2d::Vec2(0, 0.5)); // 设置锚点在左侧中心
    Brush->setPosition(6 * 75 + 40 - 20, 6 * 75 + 20+ 80); // 设置位置
    // 设置精灵初始大小
    Brush->setScale(0.02f); // 缩小为原来的倍数

   
}

void stone2::draw_stone() {
    // 创建 Sprite
    stone_s = cocos2d::Sprite::create("ball.png");

    // 获取屏幕可见区域的大小
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // 设置位置
    stone_s->setPosition(5*75,4*75+60);

    // 设置精灵初始大小
    stone_s->setScale(0.08f); // 缩小为原来的倍数

    // 在初始化函数中创建矩形精灵
    Brush = cocos2d::Sprite::create("brush.png");
    Brush->setAnchorPoint(cocos2d::Vec2(0, 0.5)); // 设置锚点在左侧中心
    Brush->setPosition(cocos2d::Vec2(5 * 75-20, 4 * 75 + 60+50)); // 设置位置
    // 设置精灵初始大小
    Brush->setScale(0.02f); // 缩小为原来的倍数

}

void stone3::draw_stone() {
    // 创建 Sprite
    stone_s = cocos2d::Sprite::create("cloud.png");

    // 获取屏幕可见区域的大小
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // 设置位置
    stone_s->setPosition(4*75,6*75);

    // 设置精灵初始大小
    stone_s->setScale(0.1f); // 缩小为原来的倍数

    // 在初始化函数中创建矩形精灵
    Brush = cocos2d::Sprite::create("brush.png");
    Brush->setAnchorPoint(cocos2d::Vec2(0, 0.5)); // 设置锚点在左侧中心
    Brush->setPosition(cocos2d::Vec2(4 * 75-20, 6 * 75+70)); // 设置位置
    // 设置精灵初始大小
    Brush->setScale(0.02f); // 缩小为原来的倍数

  
}

void stone4::draw_stone() {
    // 创建 Sprite
    stone_s = cocos2d::Sprite::create("rainbow.png");

    // 获取屏幕可见区域的大小
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // 设置位置
    stone_s->setPosition(6*75+20,2*75+45);

    // 设置精灵初始大小
    stone_s->setScale(0.085f); // 缩小为原来的倍数

    // 在初始化函数中创建矩形精灵
    Brush = cocos2d::Sprite::create("brush.png");
    Brush->setAnchorPoint(cocos2d::Vec2(0, 0.5)); // 设置锚点在左侧中心
    Brush->setPosition(cocos2d::Vec2(6 * 75 + 20-20, 2 * 75 + 45+60)); // 设置位置
    // 设置精灵初始大小
    Brush->setScale(0.02f); // 缩小为原来的倍数

   
}

void stone5::draw_stone() {
    // 创建 Sprite
    stone_s = cocos2d::Sprite::create("box.png");

    // 获取屏幕可见区域的大小
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // 设置位置
    stone_s->setPosition(6*75+30,1*75+25);

    // 设置精灵初始大小
    stone_s->setScale(0.09f); // 缩小为原来的倍数

    // 在初始化函数中创建矩形精灵
    Brush = cocos2d::Sprite::create("brush.png");
    Brush->setAnchorPoint(cocos2d::Vec2(0, 0.5)); // 设置锚点在左侧中心
    Brush->setPosition(cocos2d::Vec2(6 * 75 + 30-20, 1 * 75 + 25+60)); // 设置位置
    // 设置精灵初始大小
    Brush->setScale(0.02f); // 缩小为原来的倍数

  
}

void stone6::draw_stone() {
    // 创建 Sprite
    stone_s = cocos2d::Sprite::create("ball.png");

    // 获取屏幕可见区域的大小
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // 设置位置
    stone_s->setPosition(8 * 75, 4 * 75 + 60);

    // 设置精灵初始大小
    stone_s->setScale(0.08f); // 缩小为原来的倍数

    // 在初始化函数中创建矩形精灵
    Brush = cocos2d::Sprite::create("brush.png");
    Brush->setAnchorPoint(cocos2d::Vec2(0, 0.5)); // 设置锚点在左侧中心
    Brush->setPosition(cocos2d::Vec2(8 * 75-20, 4 * 75 + 60+50)); // 设置位置
    // 设置精灵初始大小
    Brush->setScale(0.02f); // 缩小为原来的倍数

}

void stone7::draw_stone() {
    // 创建 Sprite
    stone_s = cocos2d::Sprite::create("cloud.png");

    // 获取屏幕可见区域的大小
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // 设置位置
    stone_s->setPosition(9 * 75, 6 * 75 );

    // 设置精灵初始大小
    stone_s->setScale(0.1f); // 缩小为原来的倍数

    // 在初始化函数中创建矩形精灵
    Brush = cocos2d::Sprite::create("brush.png");
    Brush->setAnchorPoint(cocos2d::Vec2(0, 0.5)); // 设置锚点在左侧中心
    Brush->setPosition(cocos2d::Vec2(9 * 75-20, 6 * 75+70)); // 设置位置
    // 设置精灵初始大小
    Brush->setScale(0.02f); // 缩小为原来的倍数

}

void stone8::draw_stone() {
    // 创建 Sprite
    stone_s = cocos2d::Sprite::create("cloud.png");

    // 获取屏幕可见区域的大小
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // 设置位置
    stone_s->setPosition(3* 75, 3 * 75 +40);

    // 设置精灵初始大小
    stone_s->setScale(0.05f); // 缩小为原来的倍数

    // 在初始化函数中创建矩形精灵
    Brush = cocos2d::Sprite::create("brush.png");
    Brush->setAnchorPoint(cocos2d::Vec2(0, 0.5)); // 设置锚点在左侧中心
    Brush->setPosition(cocos2d::Vec2(3 * 75-20, 3 * 75 + 40+40)); // 设置位置
    // 设置精灵初始大小
    Brush->setScale(0.02f); // 缩小为原来的倍数
}

void stone9::draw_stone() {
    // 创建 Sprite
    stone_s = cocos2d::Sprite::create("cloud.png");

    // 获取屏幕可见区域的大小
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // 设置位置
    stone_s->setPosition(10 * 75, 3 * 75 + 40);

    // 设置精灵初始大小
    stone_s->setScale(0.05f); // 缩小为原来的倍数

    // 在初始化函数中创建矩形精灵
    Brush = cocos2d::Sprite::create("brush.png");
    Brush->setAnchorPoint(cocos2d::Vec2(0, 0.5)); // 设置锚点在左侧中心
    Brush->setPosition(cocos2d::Vec2(10 * 75-20, 3 * 75 + 40+40)); // 设置位置
    // 设置精灵初始大小
    Brush->setScale(0.02f); // 缩小为原来的倍数

    // 更新血条
    int percentage = HP / fullHP;
    Brush->setScaleX(0.02f * percentage);
}

// 初始化函数
bool stone::init() {
    if (!Layer::init()) {
        return false;
    }

    draw_stone();

    mouse_click();

    this->addChild(Brush);

    // 添加到场景
    this->addChild(stone_s);

    return true;
}