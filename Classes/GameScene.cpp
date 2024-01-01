#include "GameScene.h"
#include"GameSelectionScene.h"
#include<string>
#include"tower.h"
#include"enemy.h"
#include"stone.h"
#include"radish.h"

int ifSpeedUp;//1为二倍速
int ifPause;//1为暂停
char gameMap[7][12];
char gameMap1[7][12] = {{0,0,4,4,4,4,4,4,4,4,0,0},
                        {0,9,4,4,4,4,4,4,4,4,9,0},
                        {0,9,0,0,4,0,0,4,0,0,9,0},
                        {0,9,4,0,9,9,9,9,0,4,9,0}, 
                        {0,9,9,9,9,4,4,9,9,9,9,0},
                        {9,9,0,0,0,4,4,0,0,0,9,9},
                        {9,9,9,9,0,4,4,0,0,9,9,9} };//地图框架,0为空，1-3为炮塔，4为障碍物、9为路或不可移动障碍

char gameMap2[7][12] = {{0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,9,9,9,9,9,9,0,0},
                        {0,0,0,0,0,0,0,0,0,9,0,0},
                        {0,0,9,9,9,9,9,9,9,9,0,0},
                        {0,0,9,0,0,0,0,0,0,0,0,0},
                        {9,0,9,9,9,9,9,9,9,0,0,9},
                        {9,9,9,0,0,0,0,0,0,0,9,9} };//地图框架,0为空，1-3为炮塔，4为障碍物、9为路或不可移动障碍



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
//把通用位置坐标转换为框框坐标,在地图内返回1
bool positionToGrid(const Vec2& position, struct mapPos& grid) {
    if (position.x < 35 || position.x>35 + 12 * 75 || position.y < 465 - 6 * 75 || position.y>465 + 75) {
        return false;//地图外，返回false
    }
    grid.x = static_cast<int>((position.x - 35) / 75);
    grid.y = static_cast<int>((465 - position.y) / 75 + 1);
    //log("gameMap[%d][%d] = %d", grid.y, grid.x, (int)gameMap[grid.y][grid.x]);
    return true;
}

Scene* GameScene::createGameScene(int level) {
    GameScene* scene = new GameScene(level);
    if (scene && scene->init(level)) {
        scene->autorelease();
        return scene;
    }
    else {
        delete scene;
        return nullptr;
    }
}


static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
}


bool GameScene::init(int level) {
    if (!Scene::init())
    {
        return false;
    }
    log("Level: %d", m_level);

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    //初始一倍速运行
    ifSpeedUp = 0;
    ifPause = 0;

    //地图
    if (m_level == 1) {
        memcpy(gameMap, gameMap1, sizeof(gameMap));
    }
    else if (m_level == 2) {
        memcpy(gameMap, gameMap2, sizeof(gameMap));
    }

    //更新背景音乐和音效
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    experimental::AudioEngine::preload("/radish/carrot2.mp3");

    //背景
    createBackground();

    log("GameScene's Address: %p", this);

    //金币
    log("MoneyLayer::createLayer(this) : %p", this);
    MoneyLayer* money = dynamic_cast<MoneyLayer*>(MoneyLayer::createLayer(this));
    this->addChild(money);
    money->setTag(TagMoney);
    log("MoneyLayer's Address: %p", this->getChildByTag(TagMoney));


    //障碍物层
    if (m_level == 1) {
        StoneLayer* stoneLayer = dynamic_cast<StoneLayer*>(StoneLayer::createLayer(this));
        this->addChild(stoneLayer);
        stoneLayer->setTag(TagStone);
    }
    
    //菜单
    MenuLayer* Menu = dynamic_cast<MenuLayer*>(MenuLayer::createMenuLayer(this));
    this->addChild(Menu);
    Menu->setTag(TagMenu);
    
    //炮塔层
    TowerLayer* towerLayer = dynamic_cast<TowerLayer*>(TowerLayer::createLayer(this));
    this->addChild(towerLayer);
    towerLayer->setTag(TagTower);
    //log("TowerLayer's Address: %p", this->getChildByTag(TagTower));

    //怪兽层
    MonsterLayer* monsterLayer = dynamic_cast<MonsterLayer*>(MonsterLayer::createLayer(this));
    this->addChild(monsterLayer);
    monsterLayer->setTag(TagMonster);
    //log("MonsterLayer's Address: %p", this->getChildByTag(TagMonster));


    //萝卜层
    Vec2 vec = Vec2(11 * 75, 6 * 75);
    if (m_level == 2) {
        vec = Vec2(9 * 75, 2 * 75);
    }
    radish* Radish = dynamic_cast<radish*>(radish::create(vec,this));
    this->addChild(Radish);
    Radish->setTag(TagRadish);

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
    if (m_level == 2) {
        spriteRoad->setTexture("/game/BG-hd2.png");
    }
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
    auto header = Sprite::create("/game/touming-hd.pvr_13.PNG");
    header->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - header->getContentSize().height / 2));
    spriteBG->addChild(header);

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

void GameScene::winGame() {
    UserDefault::getInstance()->setBoolForKey("Level_1", true);
    UserDefault::getInstance()->flush();
    //切换到选关场景
    cocos2d::Director::getInstance()->replaceScene(GameSelectionScene::createScene());
}

cocos2d::Layer* MoneyLayer::createLayer(GameScene* pScene)
{
    MoneyLayer* scene = new MoneyLayer(pScene);
    if (scene && scene->init()) {
        scene->autorelease();
        return scene;
    }
    else {
        delete scene;
        return nullptr;
    }
}

bool MoneyLayer::init() {
    if (!Layer::init())
    {
        return false;
    }
    //金币栏
    if (_pGameScene->getLevel() == 1) {
        coins = 1450;
    }
    else if (_pGameScene->getLevel() == 2) {
        coins = 2000;
    }
    MoneyLabel = Label::createWithTTF(StringUtils::toString(getMoney()), "/fonts/Marker Felt.ttf", 32);
    if (!MoneyLabel) {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    MoneyLabel->setPosition(Vec2(origin.x + MoneyLabel->getContentSize().width * 3, origin.y + visibleSize.height - MoneyLabel->getContentSize().height * 1.2));
    
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
    //touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(MenuLayer::touchBegan, this);
    
    //touchListener->onTouchMoved = CC_CALLBACK_2(TouchLayer::onTouchMoved, this);
    //touchListener->onTouchEnded = CC_CALLBACK_2(TouchLayer::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    

    //格子测试
    //Sprite* grid[7][12];
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 12; j++) {
            if (gameMap[i][j] != RODE) {
                grid[i][j].x = j;
                grid[i][j].y = i;
                grid[i][j].spriteGrid = Sprite::create();
                grid[i][j].spriteGrid->setTexture("/game/StartSprite.png");
                grid[i][j].spriteGrid->setScale(0.9);
                Vec2 vec = gridToPosition(j, i);
                grid[i][j].spriteGrid->setAnchorPoint(Vec2(0, 0));
                grid[i][j].spriteGrid->setPosition(vec.x, vec.y);
                this->addChild(grid[i][j].spriteGrid);
                grid[i][j].spriteGrid->setVisible(false);
            }
            
        }
    }
    return true;
}

void MenuLayer::buildTower(int row, int col) {
    auto layerBuild = Layer::create();
    layerBuild->setName("layerBuild");//Menu layer中的一个层，后面用名字来调用
    //框框
    gridBuiding = &grid[row][col];
    if (gridBuiding) {
        Grid grid = *gridBuiding;
        if (grid.spriteGrid) {
            grid.spriteGrid->setTexture("/game/Grid.png");
            grid.spriteGrid->setVisible(true);
        }
        
        
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
    //第一第二关的第二个道具不一样
    int level = _pGameScene->getLevel();
    if (level == 1) {
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
    }
    else if (level == 2) {
        //蓝冰冻
        if (!(pTower->ifAvailable(ICE))) {
            shit->setTexture("/game/frozen_CanClick0.PNG");
        }
        else {
            shit->setTexture("/game/frozen_CanClick1.PNG");
        }
        shit->setPosition(Vec2(vec.x + shit->getContentSize().width / 2 + 40,
            vec.y + shit->getContentSize().height + 40));
        layerBuild->addChild(shit);
    }
   
    this->addChild(layerBuild);

}
bool MenuLayer::touchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    //获取点击位置
    auto touchLocation = this->convertToNodeSpace(touch->getLocation());
    mapPos gridPosition;
    //点击位置在地图外，不处理
    if (!positionToGrid(touchLocation, gridPosition)) {
        return true;
    }

    //点击位置在地图内的处理

    //和炮塔层通讯
    TowerLayer* pTower = dynamic_cast<TowerLayer*>(_pGameScene->getChildByTag(TagTower));

    if (!ifBuildLayer) {
        //选中空地则弹出建塔圈圈
        if (gameMap[gridPosition.y][gridPosition.x] == 0) {
            //log("build layer: gameMap[%d][%d] = %d", gridPosition.y, gridPosition.x, (int)gameMap[gridPosition.y][gridPosition.x]);
            buildTower(gridPosition.y, gridPosition.x);
            ifBuildLayer = 1;//当前处于选择建塔状态
        }
    }
    else {//建塔或取消建塔圈圈
        //获取建炮塔层
        auto buildTower = this->getChildByName("layerBuild");
        auto towerGreen = buildTower->getChildByName("greenBottle");
        auto towerShit = buildTower->getChildByName("shit");
        //获取当前建塔框
        Grid grid = *gridBuiding;
        //log("build tower: gameMap[%d][%d] = %d", grid.y, grid.x, (int)gameMap[grid.y][grid.x]);
        //判断点击位置是否在炮塔选项图标内
        if (towerGreen->getBoundingBox().containsPoint(touchLocation)) {
            if (pTower->ifAvailable(GREEN_BOTTLE)) {
                pTower->buidTower(GREEN_BOTTLE, grid.x, grid.y);
            }
        }
        else if (towerShit->getBoundingBox().containsPoint(touchLocation)) {
            //第一第二关不一样
            int level = _pGameScene->getLevel();
            if (level == 1) {
                if (pTower->ifAvailable(SHIT)) {
                    pTower->buidTower(SHIT, grid.x, grid.y);
                }
            }
            else if (level == 2) {
                if (pTower->ifAvailable(ICE)) {
                    pTower->buidTower(ICE, grid.x, grid.y);
                }
            }
        }
        this->removeChildByName("layerBuild");//移除菜单
        grid.spriteGrid->setVisible(false);//隐藏特殊框
        gridBuiding = nullptr;
        ifBuildLayer = 0;//回到非建塔状态
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
            if (pMoney->getMoney() >= 100)
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
        case ICE:
            if (pMoney->getMoney() >= 200)
                return true;
            else
                return false;
            break;
        default:
            return false;
            break;
    }
}

void TowerLayer::buidTower(int Type, int gridx, int gridy) {

    Vec2 position0 = gridToPosition(gridx, gridy);
    Vec2 position = Vec2(position0.x + 75 / 2, position0.y + 75 / 2);
    log("build tower position : (%fl, %fl)", position.x, position.y);
    //tower newTower;
    if (Type == GREEN_BOTTLE) {
        //建tower1
        auto newTower = tower_1::create(position, _pGameScene);
        this->addChild(newTower);
        //TowerLayer* ptower = dynamic_cast<TowerLayer*>(newTower->getParent());
        //ptower->removeTower(this);
    }
    else if (Type == SHIT) {
        //建tower3
        auto newTower = tower_3::create(position, _pGameScene);
        this->addChild(newTower);
    }
    else if (Type == ICE) {
        //建tower2
        auto newTower = tower_2::create(position, _pGameScene);
        this->addChild(newTower);
    }
    gameMap[gridy][gridx] = TOWER1;
}

bool TowerLayer::removeTower(tower* Tower) {
    if (!Tower) {
        return false;
    }
    
    Vec2 position0 = Tower->getpos();
    mapPos mappos;
    positionToGrid(position0, mappos);
    log("gameMap[mappos.y][mappos.x] : (%d, %d)", mappos.y, mappos.x);
    gameMap[mappos.y][mappos.x] = 0;
    
    
    //从层上移掉塔
    removeChild(dynamic_cast<Layer*>(Tower));

    /*
    //内存释放测试
    Tower->release();
    removeChild(dynamic_cast<Layer*>(Tower));
    log("removeTower: released? %p", Tower);
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
    this->scheduleOnce([this](float dt) { 
        schedule(schedule_selector(MonsterLayer::spawnMonster), 3.0f); // 每3秒生成一个怪物
	    schedule(schedule_selector(MonsterLayer::moveMonster), 22.0f); // 每22秒移动一个怪物 
        }, 5.0f, "uniqueKeyForThisSchedule"); // 注意：3.0f 是延迟时间（秒），"uniqueKeyForThisSchedule" 是这个调度的唯一标识符
	
	return true;
}

void MonsterLayer::spawnMonster(float dt)
{
	enemy* monster = nullptr;
    int mType = _pGameScene->getLevel();
    if (mType != 1 && mType != 2)return;

	switch (monsterSpawnIndex % 3)
	{ // 使用模运算来循环怪物类型
		case 0: monster = enemy1::create(_pGameScene, mType);
			break;
		case 1:
			monster = enemy2::create(_pGameScene, mType);
			break;
		case 2: 
            monster = enemy3::create(_pGameScene, mType);
            break;
	} this->addChild(monster); monsterQueue.push(monster); monsterSpawnIndex++; // 增加索引以便下次生成不同的怪物 
}

void MonsterLayer::moveMonster(float dt)
{
	if (!monsterQueue.empty())
	{
		enemy* firstMonster = monsterQueue.front();
		firstMonster->move(); monsterQueue.pop(); // 移除已经移动的怪物
	}
}

bool MonsterLayer::removeMonster(enemy* Enemy, int coins) {
    if (!Enemy) {
        return false;
    }
    //Enemy->release();
    removeChild(dynamic_cast<Layer*>(Enemy));
    //log("removeMonster: released? %p", Enemy);
    //和金币层通讯
    MoneyLayer* pMoney = dynamic_cast<MoneyLayer*>(_pGameScene->getChildByTag(TagMoney));
    pMoney->updateMoney(coins);
    
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
    auto stone1 = stone1::create(Vec2(0,0),_pGameScene);
    auto stone2 = stone2::create(Vec2(0, 0), _pGameScene);
    auto stone3 = stone3::create(Vec2(0, 0), _pGameScene);
    auto stone4 = stone4::create(Vec2(0, 0), _pGameScene);
    auto stone5 = stone5::create(Vec2(0, 0), _pGameScene);
    auto stone6 = stone6::create(Vec2(0, 0), _pGameScene);
    auto stone7 = stone7::create(Vec2(0, 0), _pGameScene);
    auto stone8 = stone8::create(Vec2(0, 0), _pGameScene);
    auto stone9 = stone9::create(Vec2(0, 0), _pGameScene);
    this->addChild(stone1);
    this->addChild(stone2);
    this->addChild(stone3);
    this->addChild(stone4);
    this->addChild(stone5);
    this->addChild(stone6);
    this->addChild(stone7);
    this->addChild(stone8);
    this->addChild(stone9);

    return true;
}

bool StoneLayer::removeStone(stone* Stone, int coins) {
    if (!Stone) {
        return false;
    }
    removeChild(dynamic_cast<Layer*>(Stone));

    //和金币层通讯
    MoneyLayer* pMoney = dynamic_cast<MoneyLayer*>(_pGameScene->getChildByTag(TagMoney));
    pMoney->updateMoney(coins);
    return true;
}


