#include "WelcomeScene.h"
#include "SimpleAudioEngine.h"
#include"GameSelectionScene.h"

USING_NS_CC;
//using namespace CocosDenshion;
Scene* WelcomeScene::createWelcomeScene()
{
    //����һ����WelcomeScene��LayerΪ����Scene������������ֱ�Ӵ���scene��һ�㣿��

    auto scene = Scene::create();
    auto layerWelcome = WelcomeScene::create();

    scene->addChild(layerWelcome);

    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    //printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in WelcomeScene.cpp\n");
}


bool WelcomeScene::init()
{

    if (!Layer::init())
    {
        return false;
    }
    /*��������*/
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("/welcome/BGMusic.mp3", true);
    

    //��ȡ��ǰlayer��С
    auto wndSize = getContentSize();
    //��ȡ��Ļ��С
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    /***����***/
    auto spriteBackground = Sprite::create("/welcome/MainBG.PNG");
    if (spriteBackground == nullptr)
    {
        problemLoading("'/welcome/MainBG.PNG'");
    }
    else
    {
        // position the sprite on the center of the screen
        spriteBackground->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

        // add the sprite as a child to this layer
        this->addChild(spriteBackground);
    }

    /***��***/
    auto cloud = Sprite::create();
    //��1
    auto cloud1 = Sprite::create("/welcome/Cloud.PNG");
    if (cloud1 == nullptr)
    {
        problemLoading("'Cloud.PNG'");
    }
    else
    {
        cloud1->setPosition(Vec2(origin.x - cloud1->getContentSize().width,
            origin.y + visibleSize.height * 0.75));
        cloud1->setScale(1.5);
        cloud1->setOpacity(150);//͸����
        cloud1->setColor(Color3B::WHITE);
        cloud->addChild(cloud1);
    }
    //��2
    auto cloud2 = Sprite::create("/welcome/Cloud2.PNG");
    if (cloud2 == nullptr)
    {
        problemLoading("'Cloud2.PNG'");
    }
    else
    {
        cloud2->setPosition(Vec2(origin.x + visibleSize.width + cloud2->getContentSize().width,
            origin.y + visibleSize.height * 0.7));
        cloud2->setScale(2);
        cloud2->setOpacity(200);
        cloud->addChild(cloud2);
    }
    //�ƶ���(����С���ٶȻ���̫һ��...)
    // MoveTo::create(float duration, const Vec2& position);
    //��1�������ң�ͣ�٣���������ͣ��
    auto cloud1_moveto_right = MoveTo::create(30.0f, Vec2(origin.x + visibleSize.width + cloud1->getContentSize().width, origin.y + visibleSize.height * 0.75));
    auto cloud1_moveto_left = MoveTo::create(30.0f, Vec2(origin.x - cloud1->getContentSize().width, origin.y + visibleSize.height * 0.75));
    auto cloud1_sequence = Sequence::create(cloud1_moveto_right, DelayTime::create(4), cloud1_moveto_left, DelayTime::create(4), nullptr);
    //ѭ������
    cloud1->runAction(RepeatForever::create(cloud1_sequence));
    //��2����������ͣ�٣��������ң�ͣ��
    auto cloud2_moveto_left = MoveTo::create(20.0f, Vec2(origin.x - cloud2->getContentSize().width, origin.y + visibleSize.height * 0.7));
    auto cloud2_moveto_right = MoveTo::create(20.0f, Vec2(origin.x + visibleSize.width + cloud2->getContentSize().width, origin.y + visibleSize.height * 0.7));
    auto cloud2_sequence = Sequence::create(cloud2_moveto_left, DelayTime::create(4), cloud2_moveto_right, DelayTime::create(4), nullptr);
    //ѭ������
    cloud2->runAction(RepeatForever::create(cloud2_sequence));

    this->addChild(cloud);


    /****���й�***/
    auto flyMonster = Sprite::create("/welcome/FlyMonster.PNG");
    if (flyMonster == nullptr) {
        problemLoading("'FlyMonster.PNG'");
    }
    else {
        flyMonster->setPosition(Vec2(origin.x + visibleSize.width / 4, origin.y + visibleSize.height * 0.8));
        //���������ϣ�������moveby�����λ�ã�
        auto monster_moveup = MoveBy::create(1.2f, Vec2(0, flyMonster->getContentSize().height / 3));
        flyMonster->runAction(RepeatForever::create(Sequence::create(monster_moveup, monster_moveup->reverse(), NULL)));

        this->addChild(flyMonster);
    }

    /***�ܲ�***/
    auto carrot = Sprite::create();
    carrot->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 4));
    //�ܲ�Ҷ��(˳���ܲ����ӵ�Ҷ�ӣ�
    auto carrot_leaf1 = Sprite::create("/welcome/Leaf1.PNG");
    if (carrot_leaf1 == nullptr)
    {
        problemLoading("'Leaf1.PNG'");
    }
    else
    {
        carrot_leaf1->setPosition(Vec2(origin.x - carrot_leaf1->getContentSize().width / 2,
            origin.y + visibleSize.height / 4 + carrot_leaf1->getContentSize().height * 1.2));
        carrot->addChild(carrot_leaf1);
    }

    auto carrot_leaf2 = Sprite::create("/welcome/Leaf2.PNG");
    if (carrot_leaf2 == nullptr)
    {
        problemLoading("'Leaf2.PNG'");
    }
    else
    {
        carrot_leaf2->setPosition(Vec2(origin.x + carrot_leaf2->getContentSize().width * 0.6,
            origin.y + visibleSize.height / 4 + carrot_leaf2->getContentSize().height * 1.3));
        carrot_leaf2->setName("Leaf2");
        carrot->addChild(carrot_leaf2);
    }

    auto carrot_leaf3 = Sprite::create("/welcome/Leaf3.PNG");
    if (carrot_leaf3 == nullptr)
    {
        problemLoading("'Leaf3.PNG'");
    }
    else
    {
        carrot_leaf3->setPosition(Vec2(origin.x,
            origin.y + visibleSize.height / 4 + carrot_leaf3->getContentSize().height * 1.1));
        carrot_leaf3->setName("Leaf3");
        carrot->addChild(carrot_leaf3);
    }

    //�ܲ�����
    auto carrot_body = Sprite::create("/welcome/CarrotBody.PNG");
    if (carrot_body == nullptr)
    {
        problemLoading("'CarrotBody.PNG'");
    }
    else
    {
        carrot_body->setPosition(Vec2(origin.x,
            origin.y + visibleSize.height / 4 + carrot_body->getContentSize().height / 4));

        carrot->addChild(carrot_body);
    }

    this->addChild(carrot);
    //�ܲ��������
    carrot->setScale(0.1);
    //ÿ���л������˵�ʱ���ܲ��ĳ���ͨ�����Ŷ�����ʵ��
    auto carrot_start_scale = ScaleTo::create(0.3, 1);
    carrot->runAction(carrot_start_scale);
    //Ҷ�ӻζ�
    auto pRotate = RotateBy::create(0.06f, 15);
    auto pDelay = DelayTime::create(2);
    //�ұ�Ҷ�ӵĻζ�
    carrot_leaf2->runAction(RepeatForever::create(Sequence::create(pRotate, pRotate->reverse(), pRotate, pRotate->reverse(), pDelay, NULL)));
    //�м�Ҷ�ӵĻζ�
    carrot_leaf3->runAction(RepeatForever::create(Sequence::create(pDelay, pRotate, pRotate->reverse(), pRotate, pRotate->reverse(), pDelay, NULL)));


    /***����***/
    auto title = Sprite::create("/welcome/MainTitle.PNG");
    if (title == nullptr) {
        problemLoading("'MainTitle.PNG'");
    }
    else {
        title->setPosition(Vec2(origin.x + visibleSize.width / 2 + title->getContentSize().width / 20,
            origin.y + visibleSize.height / 2 - title->getContentSize().height / 6));
        this->addChild(title);
    }

    /**�˵�**/
    auto menu = Menu::create();
    menu->setPosition(Vec2(0, 0));
    //�˳���Ϸ��ť
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",//����ʱ
        "CloseSelected.png",//���ʱ
        CC_CALLBACK_1(WelcomeScene::menuCloseCallback, this));

    if (closeItem == nullptr || closeItem->getContentSize().width <= 0 || closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2, origin.y + closeItem->getContentSize().height / 2));
        menu->addChild(closeItem);
    }

    //���ð�ť
    auto options_item = MenuItemImage::create("/welcome/Btn_Set.PNG", "/welcome/Btn_SetLight.PNG", CC_CALLBACK_1(WelcomeScene::optionsCallback, this));
    if (options_item == nullptr) {
        problemLoading("'options_item'");
    }
    else {
        options_item->setPosition(Vec2(origin.x + visibleSize.width * 0.2,
            origin.y + visibleSize.height / 3));
        menu->addChild(options_item);
    }
    //������ť
    auto helper_item = MenuItemImage::create("/welcome/Btn_Help.PNG", "/welcome/Btn_HelpLight.PNG", CC_CALLBACK_1(WelcomeScene::helperCallback, this));
    if (helper_item == nullptr) {
        problemLoading("'helper_item'");
    }
    else {
        helper_item->setPosition(Vec2(origin.x + visibleSize.width * 0.8,
            origin.y + visibleSize.height / 3));
        menu->addChild(helper_item);
    }
    //ð��ģʽ
    auto adventure_item = MenuItemImage::create("/welcome/Btn_NormalModle.PNG", "/welcome/Btn_NormalModleLight.PNG", CC_CALLBACK_1(WelcomeScene::adventureCallback, this));
    if (adventure_item == nullptr) {
        problemLoading("'adventure_item'");
    }
    else {
        adventure_item->setScale(0.9f);
        adventure_item->setPosition(Vec2(origin.x + visibleSize.width / 2 - adventure_item->getContentSize().width,
            origin.y + visibleSize.height / 8));
        menu->addChild(adventure_item);
    }
    //BOSSģʽ����������������
    auto boss_item = MenuItemImage::create("/welcome/Btn_Boss.PNG", "/welcome/Btn_BossLight.PNG");
    if (boss_item == nullptr) {
        problemLoading("'boss_item'");
    }
    else {
        boss_item->setScale(0.9f);
        boss_item->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height / 8));
        auto boss_lock = Sprite::create("/welcome/lock.png");
        if (boss_lock == nullptr) {
            problemLoading("'lock.png'");
        }
        else {
            boss_lock->setScale(1.4);
            boss_lock->setPosition(Vec2(origin.x + visibleSize.width / 2 + boss_item->getContentSize().width * 0.41,
                origin.y + visibleSize.height / 8 - boss_item->getContentSize().height / 5));
            this->addChild(boss_lock, 1);
        }
        menu->addChild(boss_item);
    }
    //�����ѣ�����������ʱ������
    auto nest_item = MenuItemImage::create("/welcome/Btn_MonsterNest.PNG", "/welcome/Btn_MonsterNestLight.PNG", CC_CALLBACK_1(WelcomeScene::nestCallback, this));
    if (nest_item == nullptr) {
        problemLoading("'nest_item'");
    }
    else {
        nest_item->setScale(0.9f);
        nest_item->setPosition(Vec2(origin.x + visibleSize.width / 2 + nest_item->getContentSize().width,
            origin.y + visibleSize.height / 8));
        
        auto nest_lock = Sprite::create("/welcome/lock.png");
        if (nest_lock == nullptr) {
            problemLoading("'lock.png'");
        }
        else {
            nest_lock->setName("nest_lock");
            nest_lock->setScale(1.4);
            nest_lock->setPosition(Vec2(origin.x + visibleSize.width / 2 + nest_item->getContentSize().width * 1.44,
                origin.y + visibleSize.height / 8 - nest_item->getContentSize().height / 5));
            this->addChild(nest_lock, 2);
        }
    }
    menu->addChild(nest_item);
    this->addChild(menu);

    return true;
}

void WelcomeScene::adventureCallback(Ref* pSender)
{
    //auto scene = GameScene::createGameScene(2);
    auto scene = GameSelectionScene::createScene();
    
    Director::getInstance()->replaceScene(scene);
}

void WelcomeScene::menuCloseCallback(Ref* pSender)
{
    //ֹͣ��������
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    Director::getInstance()->end();//��ת���������������������������

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}