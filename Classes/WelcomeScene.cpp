#include "WelcomeScene.h"
#include "SimpleAudioEngine.h"
#include"GameSelectionScene.h"

USING_NS_CC;
//using namespace CocosDenshion;
Scene* WelcomeScene::createWelcomeScene()
{
    //创建一个以WelcomeScene的Layer为结点的Scene（可能这样比直接创建scene好一点？）

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
    /*播放音乐*/
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("/welcome/BGMusic.mp3", true);
    

    //获取当前layer大小
    auto wndSize = getContentSize();
    //获取屏幕大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    /***背景***/
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

    /***云***/
    auto cloud = Sprite::create();
    //云1
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
        cloud1->setOpacity(150);//透明度
        cloud1->setColor(Color3B::WHITE);
        cloud->addChild(cloud1);
    }
    //云2
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
    //云动画(大云小云速度还不太一样...)
    // MoveTo::create(float duration, const Vec2& position);
    //云1，从左到右，停顿，从右向左，停顿
    auto cloud1_moveto_right = MoveTo::create(30.0f, Vec2(origin.x + visibleSize.width + cloud1->getContentSize().width, origin.y + visibleSize.height * 0.75));
    auto cloud1_moveto_left = MoveTo::create(30.0f, Vec2(origin.x - cloud1->getContentSize().width, origin.y + visibleSize.height * 0.75));
    auto cloud1_sequence = Sequence::create(cloud1_moveto_right, DelayTime::create(4), cloud1_moveto_left, DelayTime::create(4), nullptr);
    //循环播放
    cloud1->runAction(RepeatForever::create(cloud1_sequence));
    //云2，从右向左，停顿，从左向右，停顿
    auto cloud2_moveto_left = MoveTo::create(20.0f, Vec2(origin.x - cloud2->getContentSize().width, origin.y + visibleSize.height * 0.7));
    auto cloud2_moveto_right = MoveTo::create(20.0f, Vec2(origin.x + visibleSize.width + cloud2->getContentSize().width, origin.y + visibleSize.height * 0.7));
    auto cloud2_sequence = Sequence::create(cloud2_moveto_left, DelayTime::create(4), cloud2_moveto_right, DelayTime::create(4), nullptr);
    //循环播放
    cloud2->runAction(RepeatForever::create(cloud2_sequence));

    this->addChild(cloud);


    /****飞行怪***/
    auto flyMonster = Sprite::create("/welcome/FlyMonster.PNG");
    if (flyMonster == nullptr) {
        problemLoading("'FlyMonster.PNG'");
    }
    else {
        flyMonster->setPosition(Vec2(origin.x + visibleSize.width / 4, origin.y + visibleSize.height * 0.8));
        //动画，向上，回来（moveby是相对位置）
        auto monster_moveup = MoveBy::create(1.2f, Vec2(0, flyMonster->getContentSize().height / 3));
        flyMonster->runAction(RepeatForever::create(Sequence::create(monster_moveup, monster_moveup->reverse(), NULL)));

        this->addChild(flyMonster);
    }

    /***萝卜***/
    auto carrot = Sprite::create();
    carrot->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 4));
    //萝卜叶子(顺序，萝卜身子挡叶子）
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

    //萝卜身子
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
    //萝卜动画添加
    carrot->setScale(0.1);
    //每次切换到主菜单时，萝卜蹦出，通过缩放动画来实现
    auto carrot_start_scale = ScaleTo::create(0.3, 1);
    carrot->runAction(carrot_start_scale);
    //叶子晃动
    auto pRotate = RotateBy::create(0.06f, 15);
    auto pDelay = DelayTime::create(2);
    //右边叶子的晃动
    carrot_leaf2->runAction(RepeatForever::create(Sequence::create(pRotate, pRotate->reverse(), pRotate, pRotate->reverse(), pDelay, NULL)));
    //中间叶子的晃动
    carrot_leaf3->runAction(RepeatForever::create(Sequence::create(pDelay, pRotate, pRotate->reverse(), pRotate, pRotate->reverse(), pDelay, NULL)));


    /***标题***/
    auto title = Sprite::create("/welcome/MainTitle.PNG");
    if (title == nullptr) {
        problemLoading("'MainTitle.PNG'");
    }
    else {
        title->setPosition(Vec2(origin.x + visibleSize.width / 2 + title->getContentSize().width / 20,
            origin.y + visibleSize.height / 2 - title->getContentSize().height / 6));
        this->addChild(title);
    }

    /**菜单**/
    auto menu = Menu::create();
    menu->setPosition(Vec2(0, 0));
    //退出游戏按钮
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",//正常时
        "CloseSelected.png",//点击时
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

    //设置按钮
    auto options_item = MenuItemImage::create("/welcome/Btn_Set.PNG", "/welcome/Btn_SetLight.PNG", CC_CALLBACK_1(WelcomeScene::optionsCallback, this));
    if (options_item == nullptr) {
        problemLoading("'options_item'");
    }
    else {
        options_item->setPosition(Vec2(origin.x + visibleSize.width * 0.2,
            origin.y + visibleSize.height / 3));
        menu->addChild(options_item);
    }
    //帮助按钮
    auto helper_item = MenuItemImage::create("/welcome/Btn_Help.PNG", "/welcome/Btn_HelpLight.PNG", CC_CALLBACK_1(WelcomeScene::helperCallback, this));
    if (helper_item == nullptr) {
        problemLoading("'helper_item'");
    }
    else {
        helper_item->setPosition(Vec2(origin.x + visibleSize.width * 0.8,
            origin.y + visibleSize.height / 3));
        menu->addChild(helper_item);
    }
    //冒险模式
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
    //BOSS模式，锁定啦，不搞啦
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
    //怪物窝，锁定啦，暂时不搞啦
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
    //停止背景音乐
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    Director::getInstance()->end();//跳转到“结束”场景（即程序结束）

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}