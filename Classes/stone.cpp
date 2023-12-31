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
    auto listener2 = cocos2d::EventListenerTouchOneByOne::create();//�½���һ��������

    listener2->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
        log("stone:onTouchBegan, %p", this);
        auto touchLocation = this->convertToNodeSpace(touch->getLocation());
        // �������Ƿ�������
        if (stone_s->getBoundingBox().containsPoint(touchLocation)) {
            // ���������ִ������Ҫ�Ĳ���
            //�����ｨһ������Ժ�Ķ���
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

    // ע�������
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, stone_s);

}

void stone::Attacked(int damage) {
    HP -= damage;
    draw_hp();
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
        // ����Ѫ��
        float percentage = HP / fullHP;
        Brush->setScaleX(0.02f * percentage);
    
}

void stone1::draw_stone() {
    // ���� Sprite
    stone_s = cocos2d::Sprite::create("balloon.png");

    // ��ȡ��Ļ�ɼ�����Ĵ�С
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // ����λ��
   // stone_s->setPosition(cocos2d::Director::getInstance()->getVisibleSize() / 2);
    stone_s->setPosition(6*75+40,6*75+20);

    // ���þ����ʼ��С
    stone_s->setScale(0.15f); // ��СΪԭ���ı���

    // �ڳ�ʼ�������д������ξ���
    Brush = cocos2d::Sprite::create("brush.png");
    Brush->setAnchorPoint(cocos2d::Vec2(0, 0.5)); // ����ê�����������
    Brush->setPosition(6 * 75 + 40 - 20, 6 * 75 + 20+ 80); // ����λ��
    // ���þ����ʼ��С
    Brush->setScale(0.02f); // ��СΪԭ���ı���

   
}

void stone2::draw_stone() {
    // ���� Sprite
    stone_s = cocos2d::Sprite::create("ball.png");

    // ��ȡ��Ļ�ɼ�����Ĵ�С
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // ����λ��
    stone_s->setPosition(5*75,4*75+60);

    // ���þ����ʼ��С
    stone_s->setScale(0.08f); // ��СΪԭ���ı���

    // �ڳ�ʼ�������д������ξ���
    Brush = cocos2d::Sprite::create("brush.png");
    Brush->setAnchorPoint(cocos2d::Vec2(0, 0.5)); // ����ê�����������
    Brush->setPosition(cocos2d::Vec2(5 * 75-20, 4 * 75 + 60+50)); // ����λ��
    // ���þ����ʼ��С
    Brush->setScale(0.02f); // ��СΪԭ���ı���

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
    Brush->setPosition(cocos2d::Vec2(4 * 75-20, 6 * 75+70)); // ����λ��
    // ���þ����ʼ��С
    Brush->setScale(0.02f); // ��СΪԭ���ı���

  
}

void stone4::draw_stone() {
    // ���� Sprite
    stone_s = cocos2d::Sprite::create("rainbow.png");

    // ��ȡ��Ļ�ɼ�����Ĵ�С
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // ����λ��
    stone_s->setPosition(6*75+20,2*75+45);

    // ���þ����ʼ��С
    stone_s->setScale(0.085f); // ��СΪԭ���ı���

    // �ڳ�ʼ�������д������ξ���
    Brush = cocos2d::Sprite::create("brush.png");
    Brush->setAnchorPoint(cocos2d::Vec2(0, 0.5)); // ����ê�����������
    Brush->setPosition(cocos2d::Vec2(6 * 75 + 20-20, 2 * 75 + 45+60)); // ����λ��
    // ���þ����ʼ��С
    Brush->setScale(0.02f); // ��СΪԭ���ı���

   
}

void stone5::draw_stone() {
    // ���� Sprite
    stone_s = cocos2d::Sprite::create("box.png");

    // ��ȡ��Ļ�ɼ�����Ĵ�С
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // ����λ��
    stone_s->setPosition(6*75+30,1*75+25);

    // ���þ����ʼ��С
    stone_s->setScale(0.09f); // ��СΪԭ���ı���

    // �ڳ�ʼ�������д������ξ���
    Brush = cocos2d::Sprite::create("brush.png");
    Brush->setAnchorPoint(cocos2d::Vec2(0, 0.5)); // ����ê�����������
    Brush->setPosition(cocos2d::Vec2(6 * 75 + 30-20, 1 * 75 + 25+60)); // ����λ��
    // ���þ����ʼ��С
    Brush->setScale(0.02f); // ��СΪԭ���ı���

  
}

void stone6::draw_stone() {
    // ���� Sprite
    stone_s = cocos2d::Sprite::create("ball.png");

    // ��ȡ��Ļ�ɼ�����Ĵ�С
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // ����λ��
    stone_s->setPosition(8 * 75, 4 * 75 + 60);

    // ���þ����ʼ��С
    stone_s->setScale(0.08f); // ��СΪԭ���ı���

    // �ڳ�ʼ�������д������ξ���
    Brush = cocos2d::Sprite::create("brush.png");
    Brush->setAnchorPoint(cocos2d::Vec2(0, 0.5)); // ����ê�����������
    Brush->setPosition(cocos2d::Vec2(8 * 75-20, 4 * 75 + 60+50)); // ����λ��
    // ���þ����ʼ��С
    Brush->setScale(0.02f); // ��СΪԭ���ı���

}

void stone7::draw_stone() {
    // ���� Sprite
    stone_s = cocos2d::Sprite::create("cloud.png");

    // ��ȡ��Ļ�ɼ�����Ĵ�С
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // ����λ��
    stone_s->setPosition(9 * 75, 6 * 75 );

    // ���þ����ʼ��С
    stone_s->setScale(0.1f); // ��СΪԭ���ı���

    // �ڳ�ʼ�������д������ξ���
    Brush = cocos2d::Sprite::create("brush.png");
    Brush->setAnchorPoint(cocos2d::Vec2(0, 0.5)); // ����ê�����������
    Brush->setPosition(cocos2d::Vec2(9 * 75-20, 6 * 75+70)); // ����λ��
    // ���þ����ʼ��С
    Brush->setScale(0.02f); // ��СΪԭ���ı���

}

void stone8::draw_stone() {
    // ���� Sprite
    stone_s = cocos2d::Sprite::create("cloud.png");

    // ��ȡ��Ļ�ɼ�����Ĵ�С
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // ����λ��
    stone_s->setPosition(3* 75, 3 * 75 +40);

    // ���þ����ʼ��С
    stone_s->setScale(0.05f); // ��СΪԭ���ı���

    // �ڳ�ʼ�������д������ξ���
    Brush = cocos2d::Sprite::create("brush.png");
    Brush->setAnchorPoint(cocos2d::Vec2(0, 0.5)); // ����ê�����������
    Brush->setPosition(cocos2d::Vec2(3 * 75-20, 3 * 75 + 40+40)); // ����λ��
    // ���þ����ʼ��С
    Brush->setScale(0.02f); // ��СΪԭ���ı���
}

void stone9::draw_stone() {
    // ���� Sprite
    stone_s = cocos2d::Sprite::create("cloud.png");

    // ��ȡ��Ļ�ɼ�����Ĵ�С
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // ����λ��
    stone_s->setPosition(10 * 75, 3 * 75 + 40);

    // ���þ����ʼ��С
    stone_s->setScale(0.05f); // ��СΪԭ���ı���

    // �ڳ�ʼ�������д������ξ���
    Brush = cocos2d::Sprite::create("brush.png");
    Brush->setAnchorPoint(cocos2d::Vec2(0, 0.5)); // ����ê�����������
    Brush->setPosition(cocos2d::Vec2(10 * 75-20, 3 * 75 + 40+40)); // ����λ��
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

    mouse_click();

    this->addChild(Brush);

    // ��ӵ�����
    this->addChild(stone_s);

    return true;
}