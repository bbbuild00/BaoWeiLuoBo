#include"enemy.h"

class waypoint;

enemy1::enemy1(waypoint* st,MonsterLayer* lay) {
    mpos = st->getpos();
    stop = false;
    slowice = false;
    active = false;
    w = lay;
    //mpos=st->getpos();
}

enemy2::enemy2(waypoint* st, MonsterLayer* lay) {
    mpos = st->getpos();
    stop = false;
    slowice = false;
    active = false;
    w = lay;
    //mpos=st->getpos();
}

enemy3::enemy3(waypoint* st, MonsterLayer* lay) {
    mpos = st->getpos();
    stop = false;
    slowice = false;
    active = false;
    w = lay;
    //mpos=st->getpos();
}

static enemy* create(waypoint* st, MonsterLayer* lay) {
    enemy* layer = new enemy1(st,lay);
    enemy* layer = new enemy2(st, lay);
    enemy* layer = new enemy3(st, lay);
    if (layer && layer->init()) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

// ��ʼ������
bool enemy::init(){
    if (!Layer::init()) {
        return false;
    }

    draw_enemy();

    //����¼�

    move();

    this->addChild(brush);

    // ���ӵ�����
    this->addChild(monster);

    return true;
}

void enemy1::cartoon(float dt) {
    // ����һ�����ڴ洢����֡������
    cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;
    animFrames.reserve(2);

    // ��ȡ��������
    auto textureCache = cocos2d::Director::getInstance()->getTextureCache();
        // ����ͼƬ����
        cocos2d::Texture2D* texture = textureCache->addImage("monster1_1.png");

        // ��ȡ�����Ŀ��Ⱥ͸߶�
        float width_1 = texture->getContentSize().width;
        float height_1 = texture->getContentSize().height;

        // ��ȡ��������
        textureCache = cocos2d::Director::getInstance()->getTextureCache();

        // ����ͼƬ����
        texture = textureCache->addImage("monster1_2.png");

        // ��ȡ�����Ŀ��Ⱥ͸߶�
        float width_2 = texture->getContentSize().width;
        float height_2 = texture->getContentSize().height;

        // ����ͬ����ľ���֡���ӵ�������
        animFrames.pushBack(cocos2d::SpriteFrame::create("monster1_1.png", cocos2d::Rect(0, 0, width_1, height_1)));
        animFrames.pushBack(cocos2d::SpriteFrame::create("monster1_2.png", cocos2d::Rect(0, 0, width_2, height_2)));

        // ʹ�þ���֡��������һ����������ÿһ֡���Ϊ 0.2 ��
        cocos2d::Animation* animation = cocos2d::Animation::createWithSpriteFrames(animFrames, dt);

        // ʹ�ö������󴴽�һ����������
        cocos2d::Animate* animate = cocos2d::Animate::create(animation);

        // �������������ӵ������ϣ���ʹ�������ظ�����
        monster->runAction(cocos2d::RepeatForever::create(animate));
}

void enemy1::draw_enemy() {
    // ���� Sprite
    monster = cocos2d::Sprite::create("monster1_1.png");

    // ��ȡ��Ļ�ɼ�����Ĵ�С
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // ��ȡ��Ļ�ɼ������ԭ������
   // cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    // ����λ��
   // monster->setPosition(cocos2d::Director::getInstance()->getVisibleSize() / 2);
   // monster->setPosition(cocos2d::Vec2(40,275));
    monster->setPosition(cocos2d::Vec2(2 * 75 - 10, 6 * 75));

    // ���þ����ʼ��С
    monster->setScale(0.05f); // ��СΪԭ���ı���

	cartoon(0.2f);//������֡����

    // �ڳ�ʼ�������д������ξ���
    brush = cocos2d::Sprite::create("brush.png");
    brush->setAnchorPoint(cocos2d::Vec2(0, 0.5)); // ����ê�����������
    brush->setPosition(cocos2d::Vec2(2 * 75 - 30, 6 * 75 + 40)); // ����λ��
    // ���þ����ʼ��С
    brush->setScale(0.02f); // ��СΪԭ���ı���

    // ����Ѫ��
    int percentage = HP / fullHP;
    brush->setScaleX(0.02f * percentage);
}

void enemy2::cartoon(float dt) {
    // ����һ�����ڴ洢����֡������
    cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;
    animFrames.reserve(2);

        // ��ȡ��������
        auto textureCache = cocos2d::Director::getInstance()->getTextureCache();

        // ����ͼƬ����
        cocos2d::Texture2D* texture = textureCache->addImage("monster2_1.png");

        // ��ȡ�����Ŀ��Ⱥ͸߶�
        float width_1 = texture->getContentSize().width;
        float height_1 = texture->getContentSize().height;

        // ��ȡ��������
        textureCache = cocos2d::Director::getInstance()->getTextureCache();

        // ����ͼƬ����
        texture = textureCache->addImage("monster2_2.png");

        // ��ȡ�����Ŀ��Ⱥ͸߶�
        float width_2 = texture->getContentSize().width;
        float height_2 = texture->getContentSize().height;

        // ����ͬ����ľ���֡���ӵ�������
        animFrames.pushBack(cocos2d::SpriteFrame::create("monster2_1.png", cocos2d::Rect(0, 0, width_1, height_1)));
        animFrames.pushBack(cocos2d::SpriteFrame::create("monster2_2.png", cocos2d::Rect(0, 0, width_2, height_2)));

        // ʹ�þ���֡��������һ����������ÿһ֡���Ϊ 0.2 ��
        cocos2d::Animation* animation = cocos2d::Animation::createWithSpriteFrames(animFrames,dt);

        // ʹ�ö������󴴽�һ����������
        cocos2d::Animate* animate = cocos2d::Animate::create(animation);

        // �������������ӵ������ϣ���ʹ�������ظ�����
        monster->runAction(cocos2d::RepeatForever::create(animate));
}

void enemy2::draw_enemy() {
    // ���� Sprite
    monster = cocos2d::Sprite::create("monster2_1.png");

    // ��ȡ��Ļ�ɼ�����Ĵ�С
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // ��ȡ��Ļ�ɼ������ԭ������
   // cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    // ����λ��
   // monster->setPosition(cocos2d::Director::getInstance()->getVisibleSize() / 2);
   // monster->setPosition(cocos2d::Vec2(40,275));
    monster->setPosition(cocos2d::Vec2(2 * 75 - 10, 6 * 75));

    // ���þ����ʼ��С
    monster->setScale(0.05f); // ��СΪԭ���ı���

    cartoon(0.2f);//������֡����

    // �ڳ�ʼ�������д������ξ���
    brush = cocos2d::Sprite::create("brush.png");
    brush->setAnchorPoint(cocos2d::Vec2(0, 0.5)); // ����ê�����������
    brush->setPosition(cocos2d::Vec2(2 * 75 - 30, 6 * 75 + 40)); // ����λ��
    // ���þ����ʼ��С
    brush->setScale(0.02f); // ��СΪԭ���ı���

    // ����Ѫ��
    int percentage = HP / fullHP;
    brush->setScaleX(0.02f * percentage);
}

void enemy3::cartoon(float dt) {
    // ����һ�����ڴ洢����֡������
    cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;
    animFrames.reserve(2);

    
        // ��ȡ��������
        auto textureCache = cocos2d::Director::getInstance()->getTextureCache();

        // ����ͼƬ����
        cocos2d::Texture2D* texture = textureCache->addImage("monster3_1.png");

        // ��ȡ�����Ŀ��Ⱥ͸߶�
        float width_1 = texture->getContentSize().width;
        float height_1 = texture->getContentSize().height;

        // ��ȡ��������
        textureCache = cocos2d::Director::getInstance()->getTextureCache();

        // ����ͼƬ����
        texture = textureCache->addImage("monster3_2.png");

        // ��ȡ�����Ŀ��Ⱥ͸߶�
        float width_2 = texture->getContentSize().width;
        float height_2 = texture->getContentSize().height;

        // ����ͬ����ľ���֡���ӵ�������
        animFrames.pushBack(cocos2d::SpriteFrame::create("monster3_1.png", cocos2d::Rect(0, 0, width_1, height_1)));
        animFrames.pushBack(cocos2d::SpriteFrame::create("monster3_2.png", cocos2d::Rect(0, 0, width_2, height_2)));

        // ʹ�þ���֡��������һ����������ÿһ֡���Ϊ 0.2 ��
        cocos2d::Animation* animation = cocos2d::Animation::createWithSpriteFrames(animFrames, dt);

        // ʹ�ö������󴴽�һ����������
        cocos2d::Animate* animate = cocos2d::Animate::create(animation);

        // �������������ӵ������ϣ���ʹ�������ظ�����
        monster->runAction(cocos2d::RepeatForever::create(animate));
   
}

void enemy3::draw_enemy() {
    // ���� Sprite
    monster = cocos2d::Sprite::create("monster3_1.png");

    // ��ȡ��Ļ�ɼ�����Ĵ�С
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // ��ȡ��Ļ�ɼ������ԭ������
   // cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    // ����λ��
   // monster->setPosition(cocos2d::Director::getInstance()->getVisibleSize() / 2);
   // monster->setPosition(cocos2d::Vec2(40,275));
    monster->setPosition(cocos2d::Vec2(2 * 75 - 10, 6 * 75));

    // ���þ����ʼ��С
    monster->setScale(0.05f); // ��СΪԭ���ı���

    cartoon(0.2f);//������֡����

    // �ڳ�ʼ�������д������ξ���
    brush = cocos2d::Sprite::create("brush.png");
    brush->setAnchorPoint(cocos2d::Vec2(0, 0.5)); // ����ê�����������
    brush->setPosition(cocos2d::Vec2(2 * 75 - 30, 6 * 75 + 40)); // ����λ��
    // ���þ����ʼ��С
    brush->setScale(0.02f); // ��СΪԭ���ı���

    // ����Ѫ��
    int percentage = HP / fullHP;
    brush->setScaleX(0.02f * percentage);
}

void enemy::move() {
addWayPoint1(m_waypointList, monster);//����ĺ���
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

        // ����һ���յĶ�������
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

        // ����һ���յĶ�������
        auto sequence1 = cocos2d::Sequence::create(moveTo1, moveTo2, moveTo3, moveTo4, moveTo5, moveTo6, moveTo7, moveTo8, moveTo9, moveTo10, moveTo11, moveTo12, moveTo13, moveTo14,
            moveTo15, moveTo16, moveTo17, NULL);
        auto sequence2 = cocos2d::Sequence::create(moveTo1b, moveTo2b, moveTo3b, moveTo4b, moveTo5b, moveTo6b, moveTo7b, moveTo8b, moveTo9b, moveTo10b, moveTo11b, moveTo12b, moveTo13b, moveTo14b,
            moveTo15b, moveTo16b, moveTo17b, NULL);

        monster->runAction(sequence1);
        brush->runAction(sequence2);
    }
}

enemy1::~enemy1() {
    Attacktower.clear();
}
enemy2::~enemy2() {
    Attacktower.clear();
}
enemy3::~enemy3() {
    Attacktower.clear();
}



void enemy1::slowdown() {

    // �л�����֡����

    // ����ͼƬ����
     // ����һ�����ڴ洢����֡������
    cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;
    animFrames.reserve(2);

    // ��ȡ��������
    auto textureCache = cocos2d::Director::getInstance()->getTextureCache();
    cocos2d::Texture2D* texture = textureCache->addImage("ice1_1.png");


    // ��ȡ�����Ŀ��Ⱥ͸߶�
    float width_1 = texture->getContentSize().width;
    float height_1 = texture->getContentSize().height;

    // ��ȡ��������
    textureCache = cocos2d::Director::getInstance()->getTextureCache();

    // ����ͼƬ����
    texture = textureCache->addImage("ice1_2.png");

    // ��ȡ�����Ŀ��Ⱥ͸߶�
    float width_2 = texture->getContentSize().width;
    float height_2 = texture->getContentSize().height;

    // ����ͬ����ľ���֡���ӵ�������
    animFrames.pushBack(cocos2d::SpriteFrame::create("ice1_1.png", cocos2d::Rect(0, 0, width_1, height_1)));
    animFrames.pushBack(cocos2d::SpriteFrame::create("ice1_2.png", cocos2d::Rect(0, 0, width_2, height_2)));

    // ʹ�þ���֡��������һ����������ÿһ֡���Ϊ 0.2 ��
    cocos2d::Animation* animation = cocos2d::Animation::createWithSpriteFrames(animFrames, 0.2f);

    animation->setDelayPerUnit(1.0f);//ֻ�л�1��

    // ʹ�ö������󴴽�һ����������
    cocos2d::Animate* animate = cocos2d::Animate::create(animation);

    // �������������ӵ������ϣ���ʹ�������ظ�����
    monster->runAction(cocos2d::RepeatForever::create(animate));

	this->scheduleOnce(schedule_selector(enemy1::cartoon), 2.0f);  // 2���ִ��

    speed *= 0.75;
    slowice = true;
}

void enemy2::slowdown() {

    // �л�����֡����

    // ����ͼƬ����
     // ����һ�����ڴ洢����֡������
    cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;
    animFrames.reserve(2);

    // ��ȡ��������
    auto textureCache = cocos2d::Director::getInstance()->getTextureCache();
    cocos2d::Texture2D* texture = textureCache->addImage("ice2_1.png");


    // ��ȡ�����Ŀ��Ⱥ͸߶�
    float width_1 = texture->getContentSize().width;
    float height_1 = texture->getContentSize().height;

    // ��ȡ��������
    textureCache = cocos2d::Director::getInstance()->getTextureCache();

    // ����ͼƬ����
    texture = textureCache->addImage("ice2_2.png");

    // ��ȡ�����Ŀ��Ⱥ͸߶�
    float width_2 = texture->getContentSize().width;
    float height_2 = texture->getContentSize().height;

    // ����ͬ����ľ���֡���ӵ�������
    animFrames.pushBack(cocos2d::SpriteFrame::create("ice2_1.png", cocos2d::Rect(0, 0, width_1, height_1)));
    animFrames.pushBack(cocos2d::SpriteFrame::create("ice2_2.png", cocos2d::Rect(0, 0, width_2, height_2)));

    // ʹ�þ���֡��������һ����������ÿһ֡���Ϊ 0.2 ��
    cocos2d::Animation* animation = cocos2d::Animation::createWithSpriteFrames(animFrames, 0.2f);

    animation->setDelayPerUnit(1.0f);//ֻ�л�1��

    // ʹ�ö������󴴽�һ����������
    cocos2d::Animate* animate = cocos2d::Animate::create(animation);

    // �������������ӵ������ϣ���ʹ�������ظ�����
    monster->runAction(cocos2d::RepeatForever::create(animate));

    this->scheduleOnce(schedule_selector(enemy1::cartoon), 2.0f);  // 2���ִ��

    speed *= 0.75;
    slowice = true;
}

void enemy3::slowdown() {

    // �л�����֡����

    // ����ͼƬ����
     // ����һ�����ڴ洢����֡������
    cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;
    animFrames.reserve(2);

    // ��ȡ��������
    auto textureCache = cocos2d::Director::getInstance()->getTextureCache();
    cocos2d::Texture2D* texture = textureCache->addImage("ice3_1.png");


    // ��ȡ�����Ŀ��Ⱥ͸߶�
    float width_1 = texture->getContentSize().width;
    float height_1 = texture->getContentSize().height;

    // ��ȡ��������
    textureCache = cocos2d::Director::getInstance()->getTextureCache();

    // ����ͼƬ����
    texture = textureCache->addImage("ice3_2.png");

    // ��ȡ�����Ŀ��Ⱥ͸߶�
    float width_2 = texture->getContentSize().width;
    float height_2 = texture->getContentSize().height;

    // ����ͬ����ľ���֡���ӵ�������
    animFrames.pushBack(cocos2d::SpriteFrame::create("ice3_1.png", cocos2d::Rect(0, 0, width_1, height_1)));
    animFrames.pushBack(cocos2d::SpriteFrame::create("ice3_2.png", cocos2d::Rect(0, 0, width_2, height_2)));

    // ʹ�þ���֡��������һ����������ÿһ֡���Ϊ 0.2 ��
    cocos2d::Animation* animation = cocos2d::Animation::createWithSpriteFrames(animFrames, 0.2f);

    animation->setDelayPerUnit(1.0f);//ֻ�л�1��

    // ʹ�ö������󴴽�һ����������
    cocos2d::Animate* animate = cocos2d::Animate::create(animation);

    // �������������ӵ������ϣ���ʹ�������ظ�����
    monster->runAction(cocos2d::RepeatForever::create(animate));

    this->scheduleOnce(schedule_selector(enemy1::cartoon), 2.0f);  // 2���ִ��

    speed *= 0.75;
    slowice = true;
}


void enemy::Attacked(int damage) {
    HP -= damage;
    if (HP <= 0) {
        //���ú���������ʯͷ���������Ϳ���̨�������ӽ�ң�
        w->removeMonster(enemy);
        w->_pTower->enemy_killed();
        w->_pMoney->updateMoney(getmoney());
    }
}
//���ӹ����ҵ�����
//ɾ�������ҵ�����

/*void enemy::move() {
    if (!active) {//�����ƶ�ʱֱ�ӷ���
        return;
    }
    if (crash(mpos, walktowards->getpos())) {//�ж��Ƿ񵽴ﺽ��
        if (walktowards->getNext()) {//������һ���㣬��Ŀ�껻����һ��
            mpos = walktowards->getpos();
            walktowards = walktowards->getNext();
        }
        else {//��������һ�����㣬��ζ�ųԵ��ܲ�
           // w->reducelife();
         //   w->removeenemy(this);
            active = false;
            return;
        }
    }
    else {
        cocos2d::Vec2 target= walktowards->getpos();
        double m_speed = speed;
        //��ȡ�����·�߲��ƶ�
        cocos2d::Vec2 normailized(target - mpos);
      //  normailized.normailize();
      //  mpos += (normailized.toPoint()*m_speed);
    }
}*/