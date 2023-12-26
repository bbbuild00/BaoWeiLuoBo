#include "GameScene.h"
//#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include<string>


USING_NS_CC;
int ifSpeedUp;//1为二倍速
int ifPause;//1为暂停
char gameMap[7][12] = { {0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,9,0,0,0,0,0,0,0,0,9,0},
                        {0,9,0,0,0,0,0,0,0,0,9,0},
                        {0,9,0,0,9,9,9,9,0,0,9,0}, 
                        {0,9,9,9,9,0,0,9,9,9,9,0},
                        {9,9,0,0,0,0,0,0,0,0,9,9},
                        {9,9,9,9,0,0,0,0,0,9,9,9} };//地图框架,0为空，1-3为炮塔，4为障碍物、9为路或不可移动障碍



struct mapPos {
    int x;
    int y;
};

//把框框坐标转换为通用位置坐标（待调整）
static Vec2 gridToPosition(int x, int y) {
    Vec2 vec;
    vec.x = 35 + x * 75;
    vec.y = 465 - y * 75;
    return vec;
}
//把通用位置坐标转换为框框坐标,在框内返回1
bool positionToGrid(const Vec2& position, struct mapPos& grid) {
    if (position.x < 35 || position.x>35 + 12 * 75 || position.y < 465 - 6 * 75 || position.y>465 + 75) {
        return false;
    }
    grid.x = static_cast<int>((position.x - 35) / 75);
    grid.y = static_cast<int>((465 - position.y) / 75 + 1);
    if (gameMap[grid.y][grid.x] != 0) {
        return false;
    }
    return true;
}

Scene* GameScene::createGameScene() {
	return GameScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
}

bool GameScene::init() {
    if (!Scene::init())
    {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    //初始一倍速运行
    ifSpeedUp = 0;
    ifPause = 0;

    //背景
    createBackground();

    log("GameScene's Address: %p", this);

    //金币
    MoneyLayer* money = dynamic_cast<MoneyLayer*>(MoneyLayer::createLayer(this));
    this->addChild(money);
    money->setTag(TagMoney);
    log("MoneyLayer's Address: %p", this->getChildByTag(TagMoney));

    //菜单
    MenuLayer* Menu = dynamic_cast<MenuLayer*>(MenuLayer::createMenuLayer(this));
    this->addChild(Menu);
    Menu->setTag(TagMenu);
    log("MenuLayer's Address: %p", this->getChildByTag(TagMenu));

    //怪兽层
    MonsterLayer* monsterLayer = dynamic_cast<MonsterLayer*>(MonsterLayer::createLayer(this));
    this->addChild(monsterLayer);
    monsterLayer->setTag(TagMonster);
    log("MonsterLayer's Address: %p", this->getChildByTag(TagMonster));

    //炮塔层
    TowerLayer* towerLayer = dynamic_cast<TowerLayer*>(TowerLayer::createLayer(this));
    this->addChild(towerLayer);
    towerLayer->setTag(TagTower);
    log("TowerLayer's Address: %p", this->getChildByTag(TagTower));

    //障碍物层
    StoneLayer* stoneLayer = dynamic_cast<StoneLayer*>(StoneLayer::createLayer(this));
    this->addChild(stoneLayer);
    stoneLayer->setTag(TagStone);
    log("StoneLayer's Address1: %p", stoneLayer);
    log("StoneLayer's Address2: %p", this->getChildByTag(TagStone));
    
    //倒计时
    countToStart();

    return true;

}

void GameScene::createBackground() {

    log("Create GameScene Background.");
    auto spriteBG = Sprite::create();//合成背景
    auto spriteBackground = Sprite::create("/game/BG1-hd.png");//蓝色背景
    if (spriteBackground == nullptr)
    {
        problemLoading("'/game/BG1-hd.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        spriteBackground->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

        // add the sprite as a child to this layer
        spriteBG->addChild(spriteBackground);
    }
    auto spriteRoad = Sprite::create("/game/BG-hd.png");//小路
    if (spriteRoad == nullptr)
    {
        problemLoading("'/game/BG-hd.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        spriteRoad->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 80));

        // add the sprite as a child to this layer
        spriteBG->addChild(spriteRoad);
    }
    this->addChild(spriteBG);
}

void GameScene::countToStart() {
    log("Start Counting.");
    ifPause = 1;
    auto timeLayer = Layer::create();
    this->addChild(timeLayer);

    //屏蔽触摸事件
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch* touch, Event* event) {
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, timeLayer);

    //倒计时背景盘
    auto timeBG = Sprite::create("/game/Items02-hd_165.PNG");
    timeBG->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    timeLayer->addChild(timeBG);
    //倒计时数字3
    auto number = Sprite::create("/game/Items02-hd_68.PNG");
    number->setPosition(Vec2(origin.x + visibleSize.width / 2 + 5,
        origin.y + visibleSize.height / 2));
    timeLayer->addChild(number);
    //倒计时转圈
    auto circle = Sprite::create("/game/Items02-hd_50.PNG");
    circle->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    timeLayer->addChild(circle);
    circle->runAction(Sequence::create(Repeat::create(RotateBy::create(1.0f, -360), 3), FadeOut::create(0.1), nullptr));
    timeBG->runAction(Sequence::create(DelayTime::create(3.6), FadeOut::create(0.1), nullptr));


    //倒计时数字
    Vector<SpriteFrame*> spriteFrameVecCount;
    spriteFrameVecCount.pushBack(SpriteFrame::create("/game/Items02-hd_68.PNG", Rect(0, 0, number->getContentSize().width, number->getContentSize().height)));
    spriteFrameVecCount.pushBack(SpriteFrame::create("/game/Items02-hd_92.PNG", Rect(0, 0, number->getContentSize().width, number->getContentSize().height)));
    spriteFrameVecCount.pushBack(SpriteFrame::create("/game/Items02-hd_88.PNG", Rect(0, 0, number->getContentSize().width, number->getContentSize().height)));
    Animation* ani = Animation::createWithSpriteFrames(spriteFrameVecCount, 1);
    Animate* animate = Animate::create(ani);
    number->runAction(Sequence::create(animate, FadeOut::create(0.1), nullptr));

    //倒计时GO
    auto* fadeIn = FadeIn::create(0.1f);//出现
    auto rotate = RotateBy::create(0.2f, 360);
    auto scaleUp = ScaleTo::create(0.15f, 1.5f);
    auto scaleDown = ScaleTo::create(0.15f, 1.0f);
    auto* fadeOut = FadeOut::create(0.1f);
    Sequence* sequence = Sequence::create(DelayTime::create(3), fadeIn, rotate, scaleUp, scaleDown, fadeOut, nullptr);
    auto spriteGo = Sprite::create("/game/ItemsGo-hd.PNG");
    spriteGo->setOpacity(0);//初始不可见
    spriteGo->setPosition(number->getPosition());
    timeLayer->addChild(spriteGo);
    spriteGo->runAction(sequence);
    
    auto removeCallBack = CallFunc::create([=]() {
        this->removeChild(timeLayer);
        });
    timeLayer->runAction(Sequence::create(DelayTime::create(3.6), removeCallBack, nullptr));
    ifPause = 1;
}


cocos2d::Layer* MoneyLayer::createLayer(GameScene* pScene)
{
    MoneyLayer* layer = dynamic_cast<MoneyLayer*>(MoneyLayer::create());
    layer->_pGameScene = pScene;
    return layer;
}

bool MoneyLayer::init() {
    if (!Layer::init())
    {
        return false;
    }
    //金币栏
    log("Create MoneyLabel.");
    MoneyLabel = Label::createWithTTF(StringUtils::toString(getMoney()), "/fonts/Marker Felt.ttf", 32);
    if (!MoneyLabel) {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    MoneyLabel->setPosition(Vec2(origin.x + MoneyLabel->getContentSize().width * 2, origin.y + visibleSize.height - MoneyLabel->getContentSize().height * 1.5));
    
    this->addChild(MoneyLabel);
    //MoneyLabel->setString(StringUtils::toString(666));//非常匪夷所思，不知道为什么换不了
    return true;
}

void MoneyLayer::updateMoney(const int& changedCoins) {
    coins += changedCoins;
    //同步更改分数显示栏
    auto LabelPos = MoneyLabel->getPosition();
    MoneyLabel->removeFromParent();
    MoneyLabel = Label::createWithTTF(StringUtils::toString(getMoney()), "/fonts/Marker Felt.ttf", 32);
    MoneyLabel->setPosition(LabelPos);
    this->addChild(MoneyLabel);    
}

int MoneyLayer::getMoney() {
    return coins;
}

cocos2d::Layer* MenuLayer::createMenuLayer(GameScene* pScene)
{
    MenuLayer* layer = dynamic_cast<MenuLayer*>(MenuLayer::create());
    layer->_pGameScene = pScene;
    return layer;
}
bool MenuLayer::init() {
    if (!Layer::init())
    {
        return false;
    }

    
    //注册触摸事件监听器
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(MenuLayer::touchBegan, this);
    //touchListener->onTouchMoved = CC_CALLBACK_2(TouchLayer::onTouchMoved, this);
    //touchListener->onTouchEnded = CC_CALLBACK_2(TouchLayer::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    

    //格子测试
    //Sprite* grid[7][12];
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 12; j++) {
            if (gameMap[i][j] != RODE) {
                grid[i][j] = Sprite::create();
                grid[i][j]->setTexture("/game/StartSprite.png");
                grid[i][j]->setScale(0.9);
                Vec2 vec = gridToPosition(j, i);
                //grid[i][j]->setAnchorPoint(Vec2(0, 0));
                grid[i][j]->setPosition(vec.x, vec.y);
                this->addChild(grid[i][j]);
                grid[i][j]->setVisible(false);
            }
            
        }
    }
    return true;
}

void MenuLayer::buildTower(int row, int col) {
    auto layerBuild = Layer::create();
    layerBuild->setName("layerBuild");//Menu layer中的一个层，后面用名字来调用
    //框框
    gridBuiding = grid[row][col];
    if (gridBuiding) {
        gridBuiding->setTexture("/game/Grid.png");
        gridBuiding->setVisible(true);
        
    }
    //炮塔选项
    auto greenBottle = Sprite::create();
    greenBottle->setName("greenBottle");
    auto shit = Sprite::create();
    shit->setName("shit");

    //和炮塔层通讯
    TowerLayer* pTower = dynamic_cast<TowerLayer*>(_pGameScene->getChildByTag(TagTower));
    //绿瓶子
    if (!(pTower->ifAvailable(GREEN_BOTTLE))) {
        greenBottle->setTexture("/game/green_CanClick0.PNG");
    }
    else {
        greenBottle->setTexture("/game/green_CanClick1.PNG");
    }
    Vec2 vec = gridToPosition(col, row);
    greenBottle->setPosition(Vec2(vec.x - greenBottle->getContentSize().width / 2 + 40, vec.y + greenBottle->getContentSize().height + 40));
    layerBuild->addChild(greenBottle);
    //便便
    if (!(pTower->ifAvailable(SHIT))) {
        shit->setTexture("/game/shit_CanClick0.PNG");
    }
    else {
        shit->setTexture("/game/shit_CanClick1.PNG");
    }
    shit->setPosition(Vec2(vec.x + shit->getContentSize().width / 2 + 40,
        vec.y + shit->getContentSize().height + 40));
    layerBuild->addChild(shit);
    this->addChild(layerBuild);

}
bool MenuLayer::touchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    //获取点击位置
    auto touchLocation = this->convertToNodeSpace(touch->getLocation());
    //选中空地的处理
    mapPos gridPosition;

    //和炮塔层通讯
    TowerLayer* pTower = dynamic_cast<TowerLayer*>(_pGameScene->getChildByTag(TagTower));

    if (positionToGrid(touchLocation, gridPosition)) {
        //弹出建塔圈圈
        if (!ifBuildLayer) {
            buildTower(gridPosition.y, gridPosition.x);
            ifBuildLayer = 1;//当前处于选择建塔状态
        }
        //建塔或取消建塔圈圈
        else {
            //获取建炮塔层
            auto buildTower = this->getChildByName("layerBuild");
            auto towerGreen = buildTower->getChildByName("greenBottle");
            auto towerShit = buildTower->getChildByName("shit");

            //判断点击位置是否在炮塔选项图标内
            if (towerGreen->getBoundingBox().containsPoint(touchLocation)){
                if (pTower->ifAvailable(GREEN_BOTTLE)) {
                    pTower->buidTower(GREEN_BOTTLE, gridBuiding);
                    gameMap[gridPosition.y][gridPosition.x] = TOWER1;
                }
            }
            else if (towerShit->getBoundingBox().containsPoint(touchLocation)){
                if (pTower->ifAvailable(SHIT)) {
                    pTower->buidTower(SHIT, gridBuiding);
                    gameMap[gridPosition.y][gridPosition.x] = TOWER1;
                }
            }
            this->removeChildByName("layerBuild");//移除菜单
            gridBuiding->setVisible(false);//隐藏特殊框
            gridBuiding = nullptr;
            ifBuildLayer = 0;//回到非建塔状态
        }
    }
    //选到小路、背景、障碍上还得显示禁区图标，但是要注意和怪兽的冲突处理
    return true;
}

cocos2d::Layer* TowerLayer::createLayer(GameScene* pScene)
{
    TowerLayer* layer = dynamic_cast<TowerLayer*>(TowerLayer::create());
    layer->_pGameScene = pScene;
    return layer;
}

bool TowerLayer::init() {
    if (!Layer::init())
    {
        return false;
    }

    return true;
}

bool TowerLayer::ifAvailable(int Type) {

    //和金币层通讯
    MoneyLayer* pMoney = dynamic_cast<MoneyLayer*>(_pGameScene->getChildByTag(TagMoney));
    switch (Type)
    {
        case GREEN_BOTTLE:
            if (pMoney->getMoney() >= 100)//这里有问题 引发了异常: 读取访问权限冲突。this->_pTower->_pMoney 是 0xDDDDDDDD。
                //pMoney->update(-120);
                return true;
            else
                return false;
            break;
        case SHIT:
            if (pMoney->getMoney() >= 130)
                return true;
            else
                return false;
            break;
        default:
            return false;
            break;
    }
}

void TowerLayer::buidTower(int Type, cocos2d::Sprite* gridBuiding) {

    if (!gridBuiding)return;

    Vec2 position0 = gridBuiding->getPosition();
    Vec2 position =  Vec2(position0.x+75/2,position0.y+75/2);

    //tower newTower;
    if (Type == GREEN_BOTTLE) {
        /*建tower1
        auto newTower = tower_1::create(position, _pGameScene);//还是改成传GameScene指针
        */
        //测试
        auto newTower = Sprite::create("tower1-1.png");
        newTower->setPosition(position);
        this->addChild(newTower);
        //TowerLayer* ptower = dynamic_cast<TowerLayer*>(newTower->getParent());
        //ptower->removeTower(this);
    }
    else if (Type == SHIT) {
        /*建tower2
        auto newTower = tower_2::create(position, _pGameScene);
        */
        //测试
        auto newTower2 = Sprite::create("tower3-1.png");
        newTower2->setPosition(position);
        this->addChild(newTower2);
    }
}

bool TowerLayer::removeTower(tower* Tower) {
    if (!Tower) {
        return false;
    }
    /*从层上移掉塔
    removeChild(dynamic_cast<Layer*>(Tower));
    */
    MonsterLayer* pMonster = dynamic_cast<MonsterLayer*>(_pGameScene->getChildByTag(TagMonster));
    return true;
}

cocos2d::Layer* MonsterLayer::createLayer(GameScene* pScene)
{
    MonsterLayer* layer = dynamic_cast<MonsterLayer*>(MonsterLayer::create());
    layer->_pGameScene = pScene;
    return layer;
}

bool MonsterLayer::init() {
    if (!Layer::init())
    {
        return false;
    }

    return true;
}

bool MonsterLayer::removeMonster(enemy* Enemy) {
    if (!Enemy) {
        return false;
    }
    //removeChild(dynamic_cast<Layer*>(Enemy));//有定义后可以直接指
    return true;
}

cocos2d::Layer* StoneLayer::createLayer(GameScene* pScene)
{
    StoneLayer* layer = dynamic_cast<StoneLayer*>(StoneLayer::create());
    layer->_pGameScene = pScene;

    return layer;
}

bool StoneLayer::init() {
    if (!Layer::init())
    {
        return false;
    }

    return true;
}

bool StoneLayer::removeStone(stone* Stone) {
    if (!Stone) {
        return false;
    }
    //removeChild(dynamic_cast<Layer*>(Stone));//有定义后可以直接指
    return true;
}
