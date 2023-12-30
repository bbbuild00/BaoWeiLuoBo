#include"enemy.h"
#include"GameScene.h"
#include"waypoint.h"

cocos2d::Vec2 enemy::getpos()//获得当前位置
{
    cocos2d::Vec2 position = monster->getPosition();
    return position;
}

void enemy::addtower(tower* a) {
    Attacktower.pushBack(a);
}

void enemy::getout(tower* a) {
    Attacktower.eraseObject(a);
}

enemy1::enemy1(GameScene* lay) {
    // mpos = st->getpos();
    log("Enemy's GameScene p: %p", lay);
    stop = false;
    slowice = false;
    active = false;
    w = lay;
    
    //mpos=st->getpos();
}

enemy2::enemy2(GameScene* lay) {
    //mpos = st->getpos();
    stop = false;
    slowice = false;
    active = false;
    w = lay;
    //mpos=st->getpos();
}

enemy3::enemy3(GameScene* lay) {
    //mpos = st->getpos();
    stop = false;
    slowice = false;
    active = false;
    w = lay;
    //mpos=st->getpos();
}

enemy1* enemy1::create(GameScene* lay) {
    enemy1* layer = new enemy1(lay);
    if (layer && layer->init()) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

enemy2* enemy2::create(GameScene* lay) {
    enemy2* layer = new enemy2(lay);
    if (layer && layer->init()) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

enemy3* enemy3::create(GameScene* lay) {
    enemy3* layer = new enemy3(lay);
    if (layer && layer->init()) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

void enemy::mouse_click() {
    auto listener = cocos2d::EventListenerTouchOneByOne::create();

    listener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
        //获取点击位置
        auto touchLocation = this->convertToNodeSpace(touch->getLocation());
        // 检测是否点击精灵
        if (monster->getBoundingBox().containsPoint(touchLocation) ){
            // 在这里可以执行你需要的操作
            TowerLayer* pTower = dynamic_cast<TowerLayer*>(w->getChildByTag(TagTower));

            for (Node* child : pTower->getChildren()) {
                if (tower* e = dynamic_cast<tower*>(child)) {
                    bool a = e->check_if_in_range(this->getpos());
                    if (a) {
                        e->get_enemy(this);

                    }
                }
            }
        }
        return true;
        };
    // 注册监听器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, monster);
}

// 初始化函数
bool enemy::init() {
    if (!Layer::init()) {
        return false;
    }

    draw_enemy();

    mouse_click();//点击事件

    move();

    this->addChild(brush);

    // 添加到场景
    this->addChild(monster);

    return true;
}

void enemy1::cartoon(float dt) {
    // 创建一个用于存储精灵帧的容器
    cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;
    animFrames.reserve(2);

    // 获取纹理缓存
    auto textureCache = cocos2d::Director::getInstance()->getTextureCache();
    // 加载图片纹理
    cocos2d::Texture2D* texture = textureCache->addImage("monster1_1.png");

    // 获取纹理的宽度和高度
    float width_1 = texture->getContentSize().width;
    float height_1 = texture->getContentSize().height;

    // 获取纹理缓存
    textureCache = cocos2d::Director::getInstance()->getTextureCache();

    // 加载图片纹理
    texture = textureCache->addImage("monster1_2.png");

    // 获取纹理的宽度和高度
    float width_2 = texture->getContentSize().width;
    float height_2 = texture->getContentSize().height;

    // 将不同方向的精灵帧添加到容器中
    animFrames.pushBack(cocos2d::SpriteFrame::create("monster1_1.png", cocos2d::Rect(0, 0, width_1, height_1)));
    animFrames.pushBack(cocos2d::SpriteFrame::create("monster1_2.png", cocos2d::Rect(0, 0, width_2, height_2)));

    // 使用精灵帧容器创建一个动画对象，每一帧间隔为 0.2 秒
    cocos2d::Animation* animation = cocos2d::Animation::createWithSpriteFrames(animFrames, dt);

    // 使用动画对象创建一个动作对象
    cocos2d::Animate* animate = cocos2d::Animate::create(animation);

    // 将动作对象添加到精灵上，并使其永久重复播放
    monster->runAction(cocos2d::RepeatForever::create(animate));
}

void enemy1::draw_enemy() {
    // 创建 Sprite
    monster = cocos2d::Sprite::create("monster1_1.png");

    // 获取屏幕可见区域的大小
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // 获取屏幕可见区域的原点坐标
   // cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    // 设置位置
   // monster->setPosition(cocos2d::Director::getInstance()->getVisibleSize() / 2);
   // monster->setPosition(cocos2d::Vec2(40,275));
    monster->setPosition(cocos2d::Vec2(2 * 75 - 10, 6 * 75));

    // 设置精灵初始大小
    monster->setScale(0.05f); // 缩小为原来的倍数

    cartoon(0.2f);//加载两帧动画

    // 在初始化函数中创建矩形精灵
    brush = cocos2d::Sprite::create("brush.png");
    brush->setAnchorPoint(cocos2d::Vec2(0, 0.5)); // 设置锚点在左侧中心
    brush->setPosition(2 * 75 - 10-20, 6 * 75+40); // 设置位置
    // 设置精灵初始大小
    brush->setScale(0.02f); // 缩小为原来的倍数

}

void enemy2::cartoon(float dt) {
    // 创建一个用于存储精灵帧的容器
    cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;
    animFrames.reserve(2);

    // 获取纹理缓存
    auto textureCache = cocos2d::Director::getInstance()->getTextureCache();

    // 加载图片纹理
    cocos2d::Texture2D* texture = textureCache->addImage("monster2_1.png");

    // 获取纹理的宽度和高度
    float width_1 = texture->getContentSize().width;
    float height_1 = texture->getContentSize().height;

    // 获取纹理缓存
    textureCache = cocos2d::Director::getInstance()->getTextureCache();

    // 加载图片纹理
    texture = textureCache->addImage("monster2_2.png");

    // 获取纹理的宽度和高度
    float width_2 = texture->getContentSize().width;
    float height_2 = texture->getContentSize().height;

    // 将不同方向的精灵帧添加到容器中
    animFrames.pushBack(cocos2d::SpriteFrame::create("monster2_1.png", cocos2d::Rect(0, 0, width_1, height_1)));
    animFrames.pushBack(cocos2d::SpriteFrame::create("monster2_2.png", cocos2d::Rect(0, 0, width_2, height_2)));

    // 使用精灵帧容器创建一个动画对象，每一帧间隔为 0.2 秒
    cocos2d::Animation* animation = cocos2d::Animation::createWithSpriteFrames(animFrames, dt);

    // 使用动画对象创建一个动作对象
    cocos2d::Animate* animate = cocos2d::Animate::create(animation);

    // 将动作对象添加到精灵上，并使其永久重复播放
    monster->runAction(cocos2d::RepeatForever::create(animate));
}

void enemy2::draw_enemy() {
    // 创建 Sprite
    monster = cocos2d::Sprite::create("monster2_1.png");

    // 获取屏幕可见区域的大小
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // 获取屏幕可见区域的原点坐标
   // cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    // 设置位置
   // monster->setPosition(cocos2d::Director::getInstance()->getVisibleSize() / 2);
   // monster->setPosition(cocos2d::Vec2(40,275));
    monster->setPosition(cocos2d::Vec2(2 * 75 - 10, 6 * 75));

    // 设置精灵初始大小
    monster->setScale(0.05f); // 缩小为原来的倍数

    cartoon(0.2f);//加载两帧动画

    // 在初始化函数中创建矩形精灵
    brush = cocos2d::Sprite::create("brush.png");
    brush->setAnchorPoint(cocos2d::Vec2(0, 0.5)); // 设置锚点在左侧中心
    brush->setPosition(cocos2d::Vec2(2 * 75 - 30, 6 * 75 + 40)); // 设置位置
    // 设置精灵初始大小
    brush->setScale(0.02f); // 缩小为原来的倍数

}

void enemy3::cartoon(float dt) {
    // 创建一个用于存储精灵帧的容器
    cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;
    animFrames.reserve(2);


    // 获取纹理缓存
    auto textureCache = cocos2d::Director::getInstance()->getTextureCache();

    // 加载图片纹理
    cocos2d::Texture2D* texture = textureCache->addImage("monster3_1.png");

    // 获取纹理的宽度和高度
    float width_1 = texture->getContentSize().width;
    float height_1 = texture->getContentSize().height;

    // 获取纹理缓存
    textureCache = cocos2d::Director::getInstance()->getTextureCache();

    // 加载图片纹理
    texture = textureCache->addImage("monster3_2.png");

    // 获取纹理的宽度和高度
    float width_2 = texture->getContentSize().width;
    float height_2 = texture->getContentSize().height;

    // 将不同方向的精灵帧添加到容器中
    animFrames.pushBack(cocos2d::SpriteFrame::create("monster3_1.png", cocos2d::Rect(0, 0, width_1, height_1)));
    animFrames.pushBack(cocos2d::SpriteFrame::create("monster3_2.png", cocos2d::Rect(0, 0, width_2, height_2)));

    // 使用精灵帧容器创建一个动画对象，每一帧间隔为 0.2 秒
    cocos2d::Animation* animation = cocos2d::Animation::createWithSpriteFrames(animFrames, dt);

    // 使用动画对象创建一个动作对象
    cocos2d::Animate* animate = cocos2d::Animate::create(animation);

    // 将动作对象添加到精灵上，并使其永久重复播放
    monster->runAction(cocos2d::RepeatForever::create(animate));

}

void enemy3::draw_enemy() {
    // 创建 Sprite
    monster = cocos2d::Sprite::create("monster3_1.png");

    // 获取屏幕可见区域的大小
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // 获取屏幕可见区域的原点坐标
   // cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    // 设置位置
   // monster->setPosition(cocos2d::Director::getInstance()->getVisibleSize() / 2);
   // monster->setPosition(cocos2d::Vec2(40,275));
    monster->setPosition(cocos2d::Vec2(2 * 75 - 10, 6 * 75));

    // 设置精灵初始大小
    monster->setScale(0.05f); // 缩小为原来的倍数

    cartoon(0.2f);//加载两帧动画

    // 在初始化函数中创建矩形精灵
    brush = cocos2d::Sprite::create("brush.png");
    brush->setAnchorPoint(cocos2d::Vec2(0, 0.5)); // 设置锚点在左侧中心
    brush->setPosition(cocos2d::Vec2(2 * 75 - 30, 6 * 75 + 40)); // 设置位置
    // 设置精灵初始大小
    brush->setScale(0.02f); // 缩小为原来的倍数

}

void enemy::move() {
    addWayPoint1(m_waypointList, monster);//走向的航点
    if (slowice) {
        auto moveTo1 = cocos2d::MoveTo::create(2, m_waypointList.at(0)->getpos());
        auto moveTo2 = cocos2d::MoveTo::create(2, m_waypointList.at(1)->getpos());
        auto moveTo3 = cocos2d::MoveTo::create(2, m_waypointList.at(2)->getpos());
        auto moveTo4 = cocos2d::MoveTo::create(2, m_waypointList.at(3)->getpos());
        auto moveTo5 = cocos2d::MoveTo::create(1, m_waypointList.at(4)->getpos());
        auto moveTo6 = cocos2d::MoveTo::create(1, m_waypointList.at(5)->getpos());
        auto moveTo7 = cocos2d::MoveTo::create(1, m_waypointList.at(6)->getpos());
        auto moveTo8 = cocos2d::MoveTo::create(1, m_waypointList.at(7)->getpos());
        auto moveTo9 = cocos2d::MoveTo::create(1, m_waypointList.at(8)->getpos());
        auto moveTo10 = cocos2d::MoveTo::create(1, m_waypointList.at(9)->getpos());
        auto moveTo11 = cocos2d::MoveTo::create(1, m_waypointList.at(10)->getpos());
        auto moveTo12 = cocos2d::MoveTo::create(1, m_waypointList.at(11)->getpos());
        auto moveTo13 = cocos2d::MoveTo::create(1, m_waypointList.at(12)->getpos());
        auto moveTo14 = cocos2d::MoveTo::create(1, m_waypointList.at(13)->getpos());
        auto moveTo15 = cocos2d::MoveTo::create(1, m_waypointList.at(14)->getpos());
        auto moveTo16 = cocos2d::MoveTo::create(1, m_waypointList.at(15)->getpos());
        auto moveTo17 = cocos2d::MoveTo::create(1, m_waypointList.at(16)->getpos());

        auto moveTo1b = cocos2d::MoveTo::create(2, cocos2d::Vec2(m_waypointList.at(0)->getpos().x - 20, m_waypointList.at(0)->getpos().y + 40));
        auto moveTo2b = cocos2d::MoveTo::create(2, cocos2d::Vec2(m_waypointList.at(1)->getpos().x - 20, m_waypointList.at(1)->getpos().y + 40));
        auto moveTo3b = cocos2d::MoveTo::create(2, cocos2d::Vec2(m_waypointList.at(2)->getpos().x - 20, m_waypointList.at(2)->getpos().y + 40));
        auto moveTo4b = cocos2d::MoveTo::create(2, cocos2d::Vec2(m_waypointList.at(3)->getpos().x - 20, m_waypointList.at(3)->getpos().y + 40));
        auto moveTo5b = cocos2d::MoveTo::create(1, cocos2d::Vec2(m_waypointList.at(4)->getpos().x - 20, m_waypointList.at(4)->getpos().y + 40));
        auto moveTo6b = cocos2d::MoveTo::create(1, cocos2d::Vec2(m_waypointList.at(5)->getpos().x - 20, m_waypointList.at(5)->getpos().y + 40));
        auto moveTo7b = cocos2d::MoveTo::create(1, cocos2d::Vec2(m_waypointList.at(6)->getpos().x - 20, m_waypointList.at(6)->getpos().y + 40));
        auto moveTo8b = cocos2d::MoveTo::create(1, cocos2d::Vec2(m_waypointList.at(7)->getpos().x - 20, m_waypointList.at(7)->getpos().y + 40));
        auto moveTo9b = cocos2d::MoveTo::create(1, cocos2d::Vec2(m_waypointList.at(8)->getpos().x - 20, m_waypointList.at(8)->getpos().y + 40));
        auto moveTo10b = cocos2d::MoveTo::create(1, cocos2d::Vec2(m_waypointList.at(9)->getpos().x - 20, m_waypointList.at(9)->getpos().y + 40));
        auto moveTo11b = cocos2d::MoveTo::create(1, cocos2d::Vec2(m_waypointList.at(10)->getpos().x - 20, m_waypointList.at(10)->getpos().y + 40));
        auto moveTo12b = cocos2d::MoveTo::create(1, cocos2d::Vec2(m_waypointList.at(11)->getpos().x - 20, m_waypointList.at(11)->getpos().y + 40));
        auto moveTo13b = cocos2d::MoveTo::create(1, cocos2d::Vec2(m_waypointList.at(12)->getpos().x - 20, m_waypointList.at(12)->getpos().y + 40));
        auto moveTo14b = cocos2d::MoveTo::create(1, cocos2d::Vec2(m_waypointList.at(13)->getpos().x - 20, m_waypointList.at(13)->getpos().y + 40));
        auto moveTo15b = cocos2d::MoveTo::create(1, cocos2d::Vec2(m_waypointList.at(14)->getpos().x - 20, m_waypointList.at(14)->getpos().y + 40));
        auto moveTo16b = cocos2d::MoveTo::create(1, cocos2d::Vec2(m_waypointList.at(15)->getpos().x - 20, m_waypointList.at(15)->getpos().y + 40));
        auto moveTo17b = cocos2d::MoveTo::create(1, cocos2d::Vec2(m_waypointList.at(16)->getpos().x - 20, m_waypointList.at(16)->getpos().y + 40));

        // 创建一个空的动作序列
        auto sequence1 = cocos2d::Sequence::create(moveTo1, moveTo2, moveTo3, moveTo4, moveTo5, moveTo6, moveTo7, moveTo8, moveTo9, moveTo10, moveTo11, moveTo12, moveTo13, moveTo14,
            moveTo15, moveTo16, moveTo17, NULL);
        auto sequence2 = cocos2d::Sequence::create(moveTo1b, moveTo2b, moveTo3b, moveTo4b, moveTo5b, moveTo6b, moveTo7b, moveTo8b, moveTo9b, moveTo10b, moveTo11b, moveTo12b, moveTo13b, moveTo14b,
            moveTo15b, moveTo16b, moveTo17b, NULL);

        monster->runAction(sequence1);
        brush->runAction(sequence2);
    }

    else {
        auto moveTo1 = cocos2d::MoveTo::create(1, m_waypointList.at(0)->getpos());
        auto moveTo2 = cocos2d::MoveTo::create(1, m_waypointList.at(1)->getpos());
        auto moveTo3 = cocos2d::MoveTo::create(1, m_waypointList.at(2)->getpos());
        auto moveTo4 = cocos2d::MoveTo::create(1, m_waypointList.at(3)->getpos());
        auto moveTo5 = cocos2d::MoveTo::create(1, m_waypointList.at(4)->getpos());
        auto moveTo6 = cocos2d::MoveTo::create(1, m_waypointList.at(5)->getpos());
        auto moveTo7 = cocos2d::MoveTo::create(1, m_waypointList.at(6)->getpos());
        auto moveTo8 = cocos2d::MoveTo::create(1, m_waypointList.at(7)->getpos());
        auto moveTo9 = cocos2d::MoveTo::create(1, m_waypointList.at(8)->getpos());
        auto moveTo10 = cocos2d::MoveTo::create(1, m_waypointList.at(9)->getpos());
        auto moveTo11 = cocos2d::MoveTo::create(1, m_waypointList.at(10)->getpos());
        auto moveTo12 = cocos2d::MoveTo::create(1, m_waypointList.at(11)->getpos());
        auto moveTo13 = cocos2d::MoveTo::create(1, m_waypointList.at(12)->getpos());
        auto moveTo14 = cocos2d::MoveTo::create(1, m_waypointList.at(13)->getpos());
        auto moveTo15 = cocos2d::MoveTo::create(1, m_waypointList.at(14)->getpos());
        auto moveTo16 = cocos2d::MoveTo::create(1, m_waypointList.at(15)->getpos());
        auto moveTo17 = cocos2d::MoveTo::create(1, m_waypointList.at(16)->getpos());

        auto moveTo1b = cocos2d::MoveTo::create(1, cocos2d::Vec2(m_waypointList.at(0)->getpos().x - 20, m_waypointList.at(0)->getpos().y + 40));
        auto moveTo2b = cocos2d::MoveTo::create(1, cocos2d::Vec2(m_waypointList.at(1)->getpos().x - 20, m_waypointList.at(1)->getpos().y + 40));
        auto moveTo3b = cocos2d::MoveTo::create(1, cocos2d::Vec2(m_waypointList.at(2)->getpos().x - 20, m_waypointList.at(2)->getpos().y + 40));
        auto moveTo4b = cocos2d::MoveTo::create(1, cocos2d::Vec2(m_waypointList.at(3)->getpos().x - 20, m_waypointList.at(3)->getpos().y + 40));
        auto moveTo5b = cocos2d::MoveTo::create(1, cocos2d::Vec2(m_waypointList.at(4)->getpos().x - 20, m_waypointList.at(4)->getpos().y + 40));
        auto moveTo6b = cocos2d::MoveTo::create(1, cocos2d::Vec2(m_waypointList.at(5)->getpos().x - 20, m_waypointList.at(5)->getpos().y + 40));
        auto moveTo7b = cocos2d::MoveTo::create(1, cocos2d::Vec2(m_waypointList.at(6)->getpos().x - 20, m_waypointList.at(6)->getpos().y + 40));
        auto moveTo8b = cocos2d::MoveTo::create(1, cocos2d::Vec2(m_waypointList.at(7)->getpos().x - 20, m_waypointList.at(7)->getpos().y + 40));
        auto moveTo9b = cocos2d::MoveTo::create(1, cocos2d::Vec2(m_waypointList.at(8)->getpos().x - 20, m_waypointList.at(8)->getpos().y + 40));
        auto moveTo10b = cocos2d::MoveTo::create(1, cocos2d::Vec2(m_waypointList.at(9)->getpos().x - 20, m_waypointList.at(9)->getpos().y + 40));
        auto moveTo11b = cocos2d::MoveTo::create(1, cocos2d::Vec2(m_waypointList.at(10)->getpos().x - 20, m_waypointList.at(10)->getpos().y + 40));
        auto moveTo12b = cocos2d::MoveTo::create(1, cocos2d::Vec2(m_waypointList.at(11)->getpos().x - 20, m_waypointList.at(11)->getpos().y + 40));
        auto moveTo13b = cocos2d::MoveTo::create(1, cocos2d::Vec2(m_waypointList.at(12)->getpos().x - 20, m_waypointList.at(12)->getpos().y + 40));
        auto moveTo14b = cocos2d::MoveTo::create(1, cocos2d::Vec2(m_waypointList.at(13)->getpos().x - 20, m_waypointList.at(13)->getpos().y + 40));
        auto moveTo15b = cocos2d::MoveTo::create(1, cocos2d::Vec2(m_waypointList.at(14)->getpos().x - 20, m_waypointList.at(14)->getpos().y + 40));
        auto moveTo16b = cocos2d::MoveTo::create(1, cocos2d::Vec2(m_waypointList.at(15)->getpos().x - 20, m_waypointList.at(15)->getpos().y + 40));
        auto moveTo17b = cocos2d::MoveTo::create(1, cocos2d::Vec2(m_waypointList.at(16)->getpos().x - 20, m_waypointList.at(16)->getpos().y + 40));

        // 创建一个空的动作序列
        auto sequence1 = cocos2d::Sequence::create(moveTo1, moveTo2, moveTo3, moveTo4, moveTo5, moveTo6, moveTo7, moveTo8, moveTo9, moveTo10, moveTo11, moveTo12, moveTo13, moveTo14,
            moveTo15, moveTo16, moveTo17, NULL);
        auto sequence2 = cocos2d::Sequence::create(moveTo1b, moveTo2b, moveTo3b, moveTo4b, moveTo5b, moveTo6b, moveTo7b, moveTo8b, moveTo9b, moveTo10b, moveTo11b, moveTo12b, moveTo13b, moveTo14b,
            moveTo15b, moveTo16b, moveTo17b, NULL);

        monster->runAction(sequence1);
       brush->runAction(sequence2);
    }
}

enemy1::~enemy1() {
    // enemy_killed();
}
enemy2::~enemy2() {
    //enemy_killed();
}
enemy3::~enemy3() {
    // enemy_killed();
}



void enemy1::slowdown() {

    // 切换精灵帧动画

    // 加载图片纹理
     // 创建一个用于存储精灵帧的容器
    cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;
    animFrames.reserve(2);

    // 获取纹理缓存
    auto textureCache = cocos2d::Director::getInstance()->getTextureCache();
    cocos2d::Texture2D* texture = textureCache->addImage("ice1_1.png");


    // 获取纹理的宽度和高度
    float width_1 = texture->getContentSize().width;
    float height_1 = texture->getContentSize().height;

    // 获取纹理缓存
    textureCache = cocos2d::Director::getInstance()->getTextureCache();

    // 加载图片纹理
    texture = textureCache->addImage("ice1_2.png");

    // 获取纹理的宽度和高度
    float width_2 = texture->getContentSize().width;
    float height_2 = texture->getContentSize().height;

    // 将不同方向的精灵帧添加到容器中
    animFrames.pushBack(cocos2d::SpriteFrame::create("ice1_1.png", cocos2d::Rect(0, 0, width_1, height_1)));
    animFrames.pushBack(cocos2d::SpriteFrame::create("ice1_2.png", cocos2d::Rect(0, 0, width_2, height_2)));

    // 使用精灵帧容器创建一个动画对象，每一帧间隔为 0.2 秒
    cocos2d::Animation* animation = cocos2d::Animation::createWithSpriteFrames(animFrames, 0.2f);

    animation->setDelayPerUnit(1.0f);//只切换1秒

    // 使用动画对象创建一个动作对象
    cocos2d::Animate* animate = cocos2d::Animate::create(animation);

    // 将动作对象添加到精灵上，并使其永久重复播放
    monster->runAction(cocos2d::RepeatForever::create(animate));

    this->scheduleOnce(schedule_selector(enemy1::cartoon), 2.0f);  // 2秒后执行

    speed *= 0.75;
    slowice = true;
}

void enemy2::slowdown() {

    // 切换精灵帧动画

    // 加载图片纹理
     // 创建一个用于存储精灵帧的容器
    cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;
    animFrames.reserve(2);

    // 获取纹理缓存
    auto textureCache = cocos2d::Director::getInstance()->getTextureCache();
    cocos2d::Texture2D* texture = textureCache->addImage("ice2_1.png");


    // 获取纹理的宽度和高度
    float width_1 = texture->getContentSize().width;
    float height_1 = texture->getContentSize().height;

    // 获取纹理缓存
    textureCache = cocos2d::Director::getInstance()->getTextureCache();

    // 加载图片纹理
    texture = textureCache->addImage("ice2_2.png");

    // 获取纹理的宽度和高度
    float width_2 = texture->getContentSize().width;
    float height_2 = texture->getContentSize().height;

    // 将不同方向的精灵帧添加到容器中
    animFrames.pushBack(cocos2d::SpriteFrame::create("ice2_1.png", cocos2d::Rect(0, 0, width_1, height_1)));
    animFrames.pushBack(cocos2d::SpriteFrame::create("ice2_2.png", cocos2d::Rect(0, 0, width_2, height_2)));

    // 使用精灵帧容器创建一个动画对象，每一帧间隔为 0.2 秒
    cocos2d::Animation* animation = cocos2d::Animation::createWithSpriteFrames(animFrames, 0.2f);

    animation->setDelayPerUnit(1.0f);//只切换1秒

    // 使用动画对象创建一个动作对象
    cocos2d::Animate* animate = cocos2d::Animate::create(animation);

    // 将动作对象添加到精灵上，并使其永久重复播放
    monster->runAction(cocos2d::RepeatForever::create(animate));

    this->scheduleOnce(schedule_selector(enemy1::cartoon), 2.0f);  // 2秒后执行

    speed *= 0.75;
    slowice = true;
}

void enemy3::slowdown() {

    // 切换精灵帧动画

    // 加载图片纹理
     // 创建一个用于存储精灵帧的容器
    cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;
    animFrames.reserve(2);

    // 获取纹理缓存
    auto textureCache = cocos2d::Director::getInstance()->getTextureCache();
    cocos2d::Texture2D* texture = textureCache->addImage("ice3_1.png");


    // 获取纹理的宽度和高度
    float width_1 = texture->getContentSize().width;
    float height_1 = texture->getContentSize().height;

    // 获取纹理缓存
    textureCache = cocos2d::Director::getInstance()->getTextureCache();

    // 加载图片纹理
    texture = textureCache->addImage("ice3_2.png");

    // 获取纹理的宽度和高度
    float width_2 = texture->getContentSize().width;
    float height_2 = texture->getContentSize().height;

    // 将不同方向的精灵帧添加到容器中
    animFrames.pushBack(cocos2d::SpriteFrame::create("ice3_1.png", cocos2d::Rect(0, 0, width_1, height_1)));
    animFrames.pushBack(cocos2d::SpriteFrame::create("ice3_2.png", cocos2d::Rect(0, 0, width_2, height_2)));

    // 使用精灵帧容器创建一个动画对象，每一帧间隔为 0.2 秒
    cocos2d::Animation* animation = cocos2d::Animation::createWithSpriteFrames(animFrames, 0.2f);

    animation->setDelayPerUnit(1.0f);//只切换1秒

    // 使用动画对象创建一个动作对象
    cocos2d::Animate* animate = cocos2d::Animate::create(animation);

    // 将动作对象添加到精灵上，并使其永久重复播放
    monster->runAction(cocos2d::RepeatForever::create(animate));

    this->scheduleOnce(schedule_selector(enemy1::cartoon), 2.0f);  // 2秒后执行

    speed *= 0.75;
    slowice = true;
}

void enemy::draw_hp() {
    // 更新血条
    float percentage = HP / fullHP;
    brush->setScaleX(0.02f*percentage);

}

void enemy::Attacked(int damage) {
    log("Attacked pScene: %p", w);
    HP -= damage;
    draw_hp();
    if (HP <= 0) {
        //和炮塔层通讯
       /*TowerLayer* pTower = dynamic_cast<TowerLayer*>(w->getChildByTag(TagTower));

        for (Node* child : pTower->getChildren()) {
            if (tower* e = dynamic_cast<tower*>(child)) {
                bool a = e->check_if_in_range(this->getpos());
                if (a) {
                    e->get_enemy(this);
                    Attacktower.pushBack(e);
                }
            }
        }*/
        for (size_t i = 0; i < Attacktower.size(); i++) {
            tower* e;
            e = Attacktower.at(i);
            e->enemy_killed();
        }

        MonsterLayer* pMonster = dynamic_cast<MonsterLayer*>(w->getChildByTag(TagMonster));
        //调用函数：移走石头（防御塔和控制台），添加金币，
        pMonster->removeMonster(this,getmoney());

    }
}