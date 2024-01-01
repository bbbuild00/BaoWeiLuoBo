#include"GameScene.h"
#include "GameSelectionScene.h"
#include"ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;


static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
}


Scene* GameSelectionScene::createScene()
{
    return GameSelectionScene::create();
}
/*初始化*/
bool GameSelectionScene::init()
{
    /*初始化场景*/
    if (!Scene::init())
    {
        return false;
    }
    //获取屏幕大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //背景
    auto background_image = Sprite::create("/selection/stages_bg-hd_0.PNG");
    background_image->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    this->addChild(background_image);

    auto SkyLayer = SkyLayer::createLayer();//选关层
    this->addChild(SkyLayer);


    return true;
}


cocos2d::Layer* SkyLayer::createLayer()
{
    return SkyLayer::create();
}
//初始化
bool SkyLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    //获取屏幕大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //菜单
    auto menu = Menu::create();
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    //返回welcomescene
    auto return_btn = MenuItemImage::create("/selection/stages_bg-hd_41.PNG", "/selection/stages_bg-hd_40.PNG",
        CC_CALLBACK_1(SkyLayer::return_to_welcome, this));
    return_btn->setPosition(Vec2(origin.x + visibleSize.width * 0.1,
        origin.y + visibleSize.height * 0.9));
    menu->addChild(return_btn);

    //背景
    auto bg_1 = Sprite::create("/selection/BG_Left.PNG");
    bg_1->setPosition(Vec2(origin.x + bg_1->getContentSize().width / 2,
        origin.y + bg_1->getContentSize().height / 2));
    this->addChild(bg_1);

    auto bg_2 = Sprite::create("/selection/BG_Right.PNG");
    bg_2->setPosition(Vec2(origin.x + +visibleSize.width - bg_2->getContentSize().width / 2,
        origin.y + bg_2->getContentSize().height / 2));
    this->addChild(bg_2);

    //2个关卡
    //关卡1
    auto game1_image = Sprite::create("/selection/Level_1.PNG");
    game1_image->setScale(0.8);
    game1_image->setPosition(Vec2(origin.x + visibleSize.width / 4 + 20,
        origin.y + visibleSize.height * 0.54));
    this->addChild(game1_image);

    auto level_1_btn = Button::create("/selection/stages_bg-hd_30.PNG", "/GameSelectionScene/stages_bg-hd_28.PNG",
        "/selection/stages_bg-hd_39.PNG");
    level_1_btn->addTouchEventListener(CC_CALLBACK_2(SkyLayer::game1, this));
    level_1_btn->setPosition(Vec2(origin.x + visibleSize.width / 4 + 20,
        origin.y + visibleSize.height * 0.1));
    this->addChild(level_1_btn);

    if (UserDefault::getInstance()->getBoolForKey("Level_1") == true) {
        auto win_image = Sprite::create("/selection/golden_radish.png");
        win_image->setScale(0.8);
        win_image->setPosition(Vec2(origin.x + visibleSize.width / 2 - 30,
            origin.y + visibleSize.height * 0.4));
        this->addChild(win_image);
    }//金萝卜！
    

    //关卡game2
    auto game2_image = Sprite::create("/selection/Level_2.PNG");
    game2_image->setScale(0.8);
    game2_image->setPosition(Vec2(origin.x + visibleSize.width * 0.75 - 40,
        origin.y + visibleSize.height * 0.54));
    this->addChild(game2_image);
    if (UserDefault::getInstance()->getBoolForKey("Level_1") == false) {
        auto game2_lock = Sprite::create("/selection/stages_bg-hd_31.PNG");
        game2_lock->setPosition(Vec2(origin.x + visibleSize.width * 1.64,
            origin.y + visibleSize.height * 0.4));
        this->addChild(game2_lock);
    }

    auto level_2_btn = Button::create("/selection/stages_bg-hd_30.PNG", "/selection/stages_bg-hd_28.PNG",
        "/selection/stages_bg-hd_39.PNG");
    level_2_btn->addTouchEventListener(CC_CALLBACK_2(SkyLayer::game2, this));
    if (UserDefault::getInstance()->getBoolForKey("Level_1") == false){
        level_2_btn->setEnabled(false);
    }
    else {
        level_2_btn->setEnabled(true);
    }
    level_2_btn->setPosition(Vec2(origin.x + visibleSize.width * 0.75 - 20,
        origin.y + visibleSize.height * 0.1));
    this->addChild(level_2_btn);

    if (UserDefault::getInstance()->getBoolForKey("Level_2") == true) {
        auto win_image = Sprite::create("/selection/golden_radish.png");
        win_image->setScale(0.8);
        win_image->setPosition(Vec2(origin.x + visibleSize.width - 30,
            origin.y + visibleSize.height * 0.4));
        this->addChild(win_image);
    }//金萝卜！

    return true;
}

//天际第1关
void SkyLayer::game1(Ref* psender, Widget::TouchEventType type)
{
    Scene* game_scene = nullptr;
    //按钮回调函数
    switch (type) {
        case Widget::TouchEventType::ENDED:
            game_scene = GameScene::createGameScene(1);
            Director::getInstance()->replaceScene(game_scene);
            break;
        default:
            break;
    }
}
//天际第2关
void SkyLayer::game2(Ref* psender, Widget::TouchEventType type)
{
    Scene* game_scene = nullptr;
    //按钮回调函数
    switch (type) {
        case Widget::TouchEventType::ENDED:
            game_scene = GameScene::createGameScene(2);
            Director::getInstance()->replaceScene(game_scene);
            break;
        default:
            break;
    }
}

