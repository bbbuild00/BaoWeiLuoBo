#include"stone.h"

void stone::Attacked(int damage) {
    HP -= damage;
    if (HP <= 0) {
        //调用函数：移走石头（防御塔和控制台），添加金币，
        //和炮塔层通讯
        TowerLayer* pTower = dynamic_cast<TowerLayer*>(w->getChildByTag(TagTower));
        //调用函数：移走石头（防御塔和控制台），添加金币，
        w->removeMonster(stone);
        pTower->enemy_killed();
        //和金币层通讯
        MoneyLayer* pMoney = dynamic_cast<MoneyLayer*>(w->getChildByTag(TagMoney));
        pMoney->update(getmoney());
    }
}

static stone* create(cocos2d::Vec2 po, GameScene* lay) {
    stone* layer = new stone1(po, lay);
    stone* layer = new stone2(po, lay);
    stone* layer = new stone3(po, lay);
    stone* layer = new stone4(po, lay);
    stone* layer = new stone5(po, lay);
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

void stone1::draw_stone() {
    // 创建 Sprite
    stone_1 = cocos2d::Sprite::create("balloon.png");

    // 获取屏幕可见区域的大小
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // 设置位置
    stone_1->setPosition(cocos2d::Director::getInstance()->getVisibleSize() / 2);

    // 设置精灵初始大小
    stone_1->setScale(0.1f); // 缩小为原来的倍数

    // 在初始化函数中创建矩形精灵
    Brush = cocos2d::Sprite::create("brush.png");
    Brush->setAnchorPoint(cocos2d::Vec2(0, 0.5)); // 设置锚点在左侧中心
    Brush->setPosition(cocos2d::Vec2(cocos2d::Director::getInstance()->getVisibleSize().width / 2 - 20, cocos2d::Director::getInstance()->getVisibleSize().height / 2 + 40)); // 设置位置
    // 设置精灵初始大小
    Brush->setScale(0.02f); // 缩小为原来的倍数

    // 更新血条
    int percentage = HP / fullHP;
    Brush->setScaleX(0.02f * percentage);
}

void stone2::draw_stone() {
    // 创建 Sprite
    stone_1 = cocos2d::Sprite::create("ball.png");

    // 获取屏幕可见区域的大小
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // 设置位置
    stone_1->setPosition(cocos2d::Director::getInstance()->getVisibleSize() / 2);

    // 设置精灵初始大小
    stone_1->setScale(0.1f); // 缩小为原来的倍数

    // 在初始化函数中创建矩形精灵
    Brush = cocos2d::Sprite::create("brush.png");
    Brush->setAnchorPoint(cocos2d::Vec2(0, 0.5)); // 设置锚点在左侧中心
    Brush->setPosition(cocos2d::Vec2(cocos2d::Director::getInstance()->getVisibleSize().width / 2 - 20, cocos2d::Director::getInstance()->getVisibleSize().height / 2 + 40)); // 设置位置
    // 设置精灵初始大小
    Brush->setScale(0.02f); // 缩小为原来的倍数

    // 更新血条
    int percentage = HP / fullHP;
    Brush->setScaleX(0.02f * percentage);
}

void stone3::draw_stone() {
    // 创建 Sprite
    stone_1 = cocos2d::Sprite::create("cloud.png");

    // 获取屏幕可见区域的大小
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // 设置位置
    stone_1->setPosition(cocos2d::Director::getInstance()->getVisibleSize() / 2);

    // 设置精灵初始大小
    stone_1->setScale(0.1f); // 缩小为原来的倍数

    // 在初始化函数中创建矩形精灵
    Brush = cocos2d::Sprite::create("brush.png");
    Brush->setAnchorPoint(cocos2d::Vec2(0, 0.5)); // 设置锚点在左侧中心
    Brush->setPosition(cocos2d::Vec2(cocos2d::Director::getInstance()->getVisibleSize().width / 2 - 20, cocos2d::Director::getInstance()->getVisibleSize().height / 2 + 40)); // 设置位置
    // 设置精灵初始大小
    Brush->setScale(0.02f); // 缩小为原来的倍数

    // 更新血条
    int percentage = HP / fullHP;
    Brush->setScaleX(0.02f * percentage);
}

void stone4::draw_stone() {
    // 创建 Sprite
    stone_1 = cocos2d::Sprite::create("rainbow.png");

    // 获取屏幕可见区域的大小
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // 设置位置
    stone_1->setPosition(cocos2d::Director::getInstance()->getVisibleSize() / 2);

    // 设置精灵初始大小
    stone_1->setScale(0.1f); // 缩小为原来的倍数

    // 在初始化函数中创建矩形精灵
    Brush = cocos2d::Sprite::create("brush.png");
    Brush->setAnchorPoint(cocos2d::Vec2(0, 0.5)); // 设置锚点在左侧中心
    Brush->setPosition(cocos2d::Vec2(cocos2d::Director::getInstance()->getVisibleSize().width / 2 - 20, cocos2d::Director::getInstance()->getVisibleSize().height / 2 + 40)); // 设置位置
    // 设置精灵初始大小
    Brush->setScale(0.02f); // 缩小为原来的倍数

    // 更新血条
    int percentage = HP / fullHP;
    Brush->setScaleX(0.02f * percentage);
}

void stone5::draw_stone() {
    // 创建 Sprite
    stone_1 = cocos2d::Sprite::create("box.png");

    // 获取屏幕可见区域的大小
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // 设置位置
    stone_1->setPosition(cocos2d::Director::getInstance()->getVisibleSize() / 2);

    // 设置精灵初始大小
    stone_1->setScale(0.1f); // 缩小为原来的倍数

    // 在初始化函数中创建矩形精灵
    Brush = cocos2d::Sprite::create("brush.png");
    Brush->setAnchorPoint(cocos2d::Vec2(0, 0.5)); // 设置锚点在左侧中心
    Brush->setPosition(cocos2d::Vec2(cocos2d::Director::getInstance()->getVisibleSize().width / 2 - 20, cocos2d::Director::getInstance()->getVisibleSize().height / 2 + 40)); // 设置位置
    // 设置精灵初始大小
    Brush->setScale(0.02f); // 缩小为原来的倍数

    // 更新血条
    int percentage = HP / fullHP;
    Brush->setScaleX(0.02f * percentage);
}

// 初始化函数
bool stone::init(){
    if (!Layer::init()) {
        return false;
    }

    draw_stone();

    this->addChild(Brush);

    // 添加到场景
    this->addChild(stone_1);

    return true;
}