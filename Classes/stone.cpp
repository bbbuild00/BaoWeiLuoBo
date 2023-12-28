#include"stone.h"
#include"GameScene.h"

cocos2d::Vec2 stone::getpos()//��õ�ǰλ��
{
    cocos2d::Vec2 position = stone_s->getPosition();
    return position;
}

void stone::addtower(tower* a) {
    Attacktower.pushBack(a);
}

void stone::mouse_click() {
    auto listener = cocos2d::EventListenerMouse::create();

    listener->onMouseDown = [=](cocos2d::Event* event) {
        auto e = static_cast<cocos2d::EventMouse*>(event);
        float x = e->getCursorX();
        float y = e->getCursorY();
        // �������Ƿ�������
        if (stone_s->getBoundingBox().containsPoint(cocos2d::Vec2(x, y))) {
            // ���������ִ������Ҫ�Ĳ���
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
        };
    // ע�������
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, stone_s);
}


void stone::Attacked(int damage) {
    HP -= damage;
    if (HP <= 0) {
        //���ú���������ʯͷ���������Ϳ���̨������ӽ�ң�
        //��������ͨѶ
       // TowerLayer* pTower = dynamic_cast<TowerLayer*>(w->getChildByTag(TagTower));
        for (size_t i = 0; i < Attacktower.size(); i++) {
            tower* e;
            e = Attacktower.at(i);
            e->enemy_killed();
        }

        StoneLayer* pStone = dynamic_cast<StoneLayer*>(w->getChildByTag(TagStone));
        //���ú���������ʯͷ���������Ϳ���̨������ӽ�ң�
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
    // ���� Sprite
    stone_s = cocos2d::Sprite::create("balloon.png");

    // ��ȡ��Ļ�ɼ�����Ĵ�С
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // ����λ��
   // stone_s->setPosition(cocos2d::Director::getInstance()->getVisibleSize() / 2);
    stone_s->setPosition(6*75,6*75);

    // ���þ����ʼ��С
    stone_s->setScale(0.1f); // ��СΪԭ���ı���

    // �ڳ�ʼ�������д������ξ���
    Brush = cocos2d::Sprite::create("brush.png");
    Brush->setAnchorPoint(cocos2d::Vec2(0, 0.5)); // ����ê�����������
    Brush->setPosition(cocos2d::Vec2(cocos2d::Director::getInstance()->getVisibleSize().width / 2 - 20, cocos2d::Director::getInstance()->getVisibleSize().height / 2 + 40)); // ����λ��
    // ���þ����ʼ��С
    Brush->setScale(0.02f); // ��СΪԭ���ı���

    // ����Ѫ��
    int percentage = HP / fullHP;
    Brush->setScaleX(0.02f * percentage);
}

void stone2::draw_stone() {
    // ���� Sprite
    stone_s = cocos2d::Sprite::create("ball.png");

    // ��ȡ��Ļ�ɼ�����Ĵ�С
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // ����λ��
    stone_s->setPosition(5*75,4*75);

    // ���þ����ʼ��С
    stone_s->setScale(0.1f); // ��СΪԭ���ı���

    // �ڳ�ʼ�������д������ξ���
    Brush = cocos2d::Sprite::create("brush.png");
    Brush->setAnchorPoint(cocos2d::Vec2(0, 0.5)); // ����ê�����������
    Brush->setPosition(cocos2d::Vec2(cocos2d::Director::getInstance()->getVisibleSize().width / 2 - 20, cocos2d::Director::getInstance()->getVisibleSize().height / 2 + 40)); // ����λ��
    // ���þ����ʼ��С
    Brush->setScale(0.02f); // ��СΪԭ���ı���

    // ����Ѫ��
    int percentage = HP / fullHP;
    Brush->setScaleX(0.02f * percentage);
}

void stone3::draw_stone() {
    // ���� Sprite
    stone_s = cocos2d::Sprite::create("cloud.png");

    // ��ȡ��Ļ�ɼ�����Ĵ�С
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // ����λ��
    stone_s->setPosition(4*75,6*75);

    // ���þ����ʼ��С
    stone_s->setScale(0.1f); // ��СΪԭ���ı���

    // �ڳ�ʼ�������д������ξ���
    Brush = cocos2d::Sprite::create("brush.png");
    Brush->setAnchorPoint(cocos2d::Vec2(0, 0.5)); // ����ê�����������
    Brush->setPosition(cocos2d::Vec2(cocos2d::Director::getInstance()->getVisibleSize().width / 2 - 20, cocos2d::Director::getInstance()->getVisibleSize().height / 2 + 40)); // ����λ��
    // ���þ����ʼ��С
    Brush->setScale(0.02f); // ��СΪԭ���ı���

    // ����Ѫ��
    int percentage = HP / fullHP;
    Brush->setScaleX(0.02f * percentage);
}

void stone4::draw_stone() {
    // ���� Sprite
    stone_s = cocos2d::Sprite::create("rainbow.png");

    // ��ȡ��Ļ�ɼ�����Ĵ�С
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // ����λ��
    stone_s->setPosition(6*75,2*75);

    // ���þ����ʼ��С
    stone_s->setScale(0.1f); // ��СΪԭ���ı���

    // �ڳ�ʼ�������д������ξ���
    Brush = cocos2d::Sprite::create("brush.png");
    Brush->setAnchorPoint(cocos2d::Vec2(0, 0.5)); // ����ê�����������
    Brush->setPosition(cocos2d::Vec2(cocos2d::Director::getInstance()->getVisibleSize().width / 2 - 20, cocos2d::Director::getInstance()->getVisibleSize().height / 2 + 40)); // ����λ��
    // ���þ����ʼ��С
    Brush->setScale(0.02f); // ��СΪԭ���ı���

    // ����Ѫ��
    int percentage = HP / fullHP;
    Brush->setScaleX(0.02f * percentage);
}

void stone5::draw_stone() {
    // ���� Sprite
    stone_s = cocos2d::Sprite::create("box.png");

    // ��ȡ��Ļ�ɼ�����Ĵ�С
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // ����λ��
    stone_s->setPosition(6*75,1*75);

    // ���þ����ʼ��С
    stone_s->setScale(0.1f); // ��СΪԭ���ı���

    // �ڳ�ʼ�������д������ξ���
    Brush = cocos2d::Sprite::create("brush.png");
    Brush->setAnchorPoint(cocos2d::Vec2(0, 0.5)); // ����ê�����������
    Brush->setPosition(cocos2d::Vec2(cocos2d::Director::getInstance()->getVisibleSize().width / 2 - 20, cocos2d::Director::getInstance()->getVisibleSize().height / 2 + 40)); // ����λ��
    // ���þ����ʼ��С
    Brush->setScale(0.02f); // ��СΪԭ���ı���

    // ����Ѫ��
    int percentage = HP / fullHP;
    Brush->setScaleX(0.02f * percentage);
}

// ��ʼ������
bool stone::init() {
    if (!Layer::init()) {
        return false;
    }

    draw_stone();

    this->addChild(Brush);

    // ��ӵ�����
    this->addChild(stone_s);

    return true;
}