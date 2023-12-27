#include"stone.h"
#include"GameScene.h"

void stone::Attacked(int damage) {
    HP -= damage;
    if (HP <= 0) {
        //���ú���������ʯͷ���������Ϳ���̨������ӽ�ң�
        //��������ͨѶ
        TowerLayer* pTower = dynamic_cast<TowerLayer*>(w->getChildByTag(TagTower));

        StoneLayer* pStone = dynamic_cast<StoneLayer*>(w->getChildByTag(TagStone));
        //���ú���������ʯͷ���������Ϳ���̨������ӽ�ң�
        pStone->removeStone(this);

        //pTower->enemy_killed();
        //�ͽ�Ҳ�ͨѶ
        StoneLayer* pMoney = dynamic_cast<StoneLayer*>(w->getChildByTag(TagStone));
        pMoney->update(getmoney());
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

stone3*stone3:: create(cocos2d::Vec2 po, GameScene* lay) {
    stone3* layer = new stone3(po, lay);
    if (layer && layer->init()) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

stone4*stone4:: create(cocos2d::Vec2 po, GameScene* lay) {
    stone4* layer = new stone4(po, lay);
    if (layer && layer->init()) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

stone5*stone5:: create(cocos2d::Vec2 po, GameScene* lay) {
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
    stone_1 = cocos2d::Sprite::create("balloon.png");

    // ��ȡ��Ļ�ɼ�����Ĵ�С
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // ����λ��
    stone_1->setPosition(cocos2d::Director::getInstance()->getVisibleSize() / 2);

    // ���þ����ʼ��С
    stone_1->setScale(0.1f); // ��СΪԭ���ı���

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
    stone_1 = cocos2d::Sprite::create("ball.png");

    // ��ȡ��Ļ�ɼ�����Ĵ�С
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // ����λ��
    stone_1->setPosition(cocos2d::Director::getInstance()->getVisibleSize() / 2);

    // ���þ����ʼ��С
    stone_1->setScale(0.1f); // ��СΪԭ���ı���

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
    stone_1 = cocos2d::Sprite::create("cloud.png");

    // ��ȡ��Ļ�ɼ�����Ĵ�С
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // ����λ��
    stone_1->setPosition(cocos2d::Director::getInstance()->getVisibleSize() / 2);

    // ���þ����ʼ��С
    stone_1->setScale(0.1f); // ��СΪԭ���ı���

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
    stone_1 = cocos2d::Sprite::create("rainbow.png");

    // ��ȡ��Ļ�ɼ�����Ĵ�С
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // ����λ��
    stone_1->setPosition(cocos2d::Director::getInstance()->getVisibleSize() / 2);

    // ���þ����ʼ��С
    stone_1->setScale(0.1f); // ��СΪԭ���ı���

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
    stone_1 = cocos2d::Sprite::create("box.png");

    // ��ȡ��Ļ�ɼ�����Ĵ�С
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // ����λ��
    stone_1->setPosition(cocos2d::Director::getInstance()->getVisibleSize() / 2);

    // ���þ����ʼ��С
    stone_1->setScale(0.1f); // ��СΪԭ���ı���

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
bool stone::init(){
    if (!Layer::init()) {
        return false;
    }

    draw_stone();

    this->addChild(Brush);

    // ��ӵ�����
    this->addChild(stone_1);

    return true;
}