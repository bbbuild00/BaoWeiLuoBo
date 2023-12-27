#include "GameScene.h"
//#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include<string>
#include"tower.h"
#include"enemy.h"
#include"stone.h"


USING_NS_CC;
int ifSpeedUp;//1Ϊ������
int ifPause;//1Ϊ��ͣ
char gameMap[7][12] = { {0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,9,0,0,0,0,0,0,0,0,9,0},
                        {0,9,0,0,0,0,0,0,0,0,9,0},
                        {0,9,0,0,9,9,9,9,0,0,9,0}, 
                        {0,9,9,9,9,0,0,9,9,9,9,0},
                        {9,9,0,0,0,0,0,0,0,0,9,9},
                        {9,9,9,9,0,0,0,0,0,9,9,9} };//��ͼ���,0Ϊ�գ�1-3Ϊ������4Ϊ�ϰ��9Ϊ·�򲻿��ƶ��ϰ�



struct mapPos {
    int x;
    int y;
};

//�ѿ������ת��Ϊͨ��λ�����꣨��������
static Vec2 gridToPosition(int x, int y) {
    Vec2 vec;
    vec.x = 35 + x * 75;
    vec.y = 465 - y * 75;
    return vec;
}
//��ͨ��λ������ת��Ϊ�������,�ڵ�ͼ�ڷ���1
bool positionToGrid(const Vec2& position, struct mapPos& grid) {
    if (position.x < 35 || position.x>35 + 12 * 75 || position.y < 465 - 6 * 75 || position.y>465 + 75) {
        return false;//��ͼ�⣬����false
    }
    grid.x = static_cast<int>((position.x - 35) / 75);
    grid.y = static_cast<int>((465 - position.y) / 75 + 1);
    //log("gameMap[%d][%d] = %d", grid.y, grid.x, (int)gameMap[grid.y][grid.x]);
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
    
    //��ʼһ��������
    ifSpeedUp = 0;
    ifPause = 0;

    //����
    createBackground();

    log("GameScene's Address: %p", this);

    //���
    MoneyLayer* money = dynamic_cast<MoneyLayer*>(MoneyLayer::createLayer(this));
    this->addChild(money);
    money->setTag(TagMoney);
    log("MoneyLayer's Address: %p", this->getChildByTag(TagMoney));

    //�˵�
    MenuLayer* Menu = dynamic_cast<MenuLayer*>(MenuLayer::createMenuLayer(this));
    this->addChild(Menu);
    Menu->setTag(TagMenu);
    log("MenuLayer's Address: %p", this->getChildByTag(TagMenu));

    //���޲�
    MonsterLayer* monsterLayer = dynamic_cast<MonsterLayer*>(MonsterLayer::createLayer(this));
    this->addChild(monsterLayer);
    monsterLayer->setTag(TagMonster);
    log("MonsterLayer's Address: %p", this->getChildByTag(TagMonster));

    //������
    TowerLayer* towerLayer = dynamic_cast<TowerLayer*>(TowerLayer::createLayer(this));
    this->addChild(towerLayer);
    towerLayer->setTag(TagTower);
    log("TowerLayer's Address: %p", this->getChildByTag(TagTower));

    //�ϰ����
    StoneLayer* stoneLayer = dynamic_cast<StoneLayer*>(StoneLayer::createLayer(this));
    this->addChild(stoneLayer);
    stoneLayer->setTag(TagStone);
    log("StoneLayer's Address1: %p", stoneLayer);
    log("StoneLayer's Address2: %p", this->getChildByTag(TagStone));
    
    //����ʱ
    countToStart();

    return true;

}

void GameScene::createBackground() {

    log("Create GameScene Background.");
    auto spriteBG = Sprite::create();//�ϳɱ���
    auto spriteBackground = Sprite::create("/game/BG1-hd.png");//��ɫ����
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
    auto spriteRoad = Sprite::create("/game/BG-hd.png");//С·
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

    //���δ����¼�
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch* touch, Event* event) {
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, timeLayer);

    //����ʱ������
    auto timeBG = Sprite::create("/game/Items02-hd_165.PNG");
    timeBG->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    timeLayer->addChild(timeBG);
    //����ʱ����3
    auto number = Sprite::create("/game/Items02-hd_68.PNG");
    number->setPosition(Vec2(origin.x + visibleSize.width / 2 + 5,
        origin.y + visibleSize.height / 2));
    timeLayer->addChild(number);
    //����ʱתȦ
    auto circle = Sprite::create("/game/Items02-hd_50.PNG");
    circle->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    timeLayer->addChild(circle);
    circle->runAction(Sequence::create(Repeat::create(RotateBy::create(1.0f, -360), 3), FadeOut::create(0.1), nullptr));
    timeBG->runAction(Sequence::create(DelayTime::create(3.6), FadeOut::create(0.1), nullptr));


    //����ʱ����
    Vector<SpriteFrame*> spriteFrameVecCount;
    spriteFrameVecCount.pushBack(SpriteFrame::create("/game/Items02-hd_68.PNG", Rect(0, 0, number->getContentSize().width, number->getContentSize().height)));
    spriteFrameVecCount.pushBack(SpriteFrame::create("/game/Items02-hd_92.PNG", Rect(0, 0, number->getContentSize().width, number->getContentSize().height)));
    spriteFrameVecCount.pushBack(SpriteFrame::create("/game/Items02-hd_88.PNG", Rect(0, 0, number->getContentSize().width, number->getContentSize().height)));
    Animation* ani = Animation::createWithSpriteFrames(spriteFrameVecCount, 1);
    Animate* animate = Animate::create(ani);
    number->runAction(Sequence::create(animate, FadeOut::create(0.1), nullptr));

    //����ʱGO
    auto* fadeIn = FadeIn::create(0.1f);//����
    auto rotate = RotateBy::create(0.2f, 360);
    auto scaleUp = ScaleTo::create(0.15f, 1.5f);
    auto scaleDown = ScaleTo::create(0.15f, 1.0f);
    auto* fadeOut = FadeOut::create(0.1f);
    Sequence* sequence = Sequence::create(DelayTime::create(3), fadeIn, rotate, scaleUp, scaleDown, fadeOut, nullptr);
    auto spriteGo = Sprite::create("/game/ItemsGo-hd.PNG");
    spriteGo->setOpacity(0);//��ʼ���ɼ�
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
    //�����
    log("Create MoneyLabel.");
    MoneyLabel = Label::createWithTTF(StringUtils::toString(getMoney()), "/fonts/Marker Felt.ttf", 32);
    if (!MoneyLabel) {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    MoneyLabel->setPosition(Vec2(origin.x + MoneyLabel->getContentSize().width * 2, origin.y + visibleSize.height - MoneyLabel->getContentSize().height * 1.5));
    
    this->addChild(MoneyLabel);
    //MoneyLabel->setString(StringUtils::toString(666));//�ǳ�������˼����֪��Ϊʲô������
    return true;
}

void MoneyLayer::updateMoney(const int& changedCoins) {
    coins += changedCoins;
    //ͬ�����ķ�����ʾ��
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

    
    //ע�ᴥ���¼�������
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(MenuLayer::touchBegan, this);
    
    //touchListener->onTouchMoved = CC_CALLBACK_2(TouchLayer::onTouchMoved, this);
    //touchListener->onTouchEnded = CC_CALLBACK_2(TouchLayer::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    

    //���Ӳ���
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
    layerBuild->setName("layerBuild");//Menu layer�е�һ���㣬����������������
    //���
    gridBuiding = &grid[row][col];
    if (gridBuiding) {
        Grid grid = *gridBuiding;
        grid.spriteGrid->setTexture("/game/Grid.png");
        grid.spriteGrid->setVisible(true);
        
    }
    //����ѡ��
    auto greenBottle = Sprite::create();
    greenBottle->setName("greenBottle");
    auto shit = Sprite::create();
    shit->setName("shit");

    //��������ͨѶ
    TowerLayer* pTower = dynamic_cast<TowerLayer*>(_pGameScene->getChildByTag(TagTower));
    //��ƿ��
    if (!(pTower->ifAvailable(GREEN_BOTTLE))) {
        greenBottle->setTexture("/game/green_CanClick0.PNG");
    }
    else {
        greenBottle->setTexture("/game/green_CanClick1.PNG");
    }
    Vec2 vec = gridToPosition(col, row);
    greenBottle->setPosition(Vec2(vec.x - greenBottle->getContentSize().width / 2 + 40, vec.y + greenBottle->getContentSize().height + 40));
    layerBuild->addChild(greenBottle);
    //���
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
    //��ȡ���λ��
    auto touchLocation = this->convertToNodeSpace(touch->getLocation());
    mapPos gridPosition;
    //���λ���ڵ�ͼ�⣬������
    if (!positionToGrid(touchLocation, gridPosition)) {
        return true;
    }

    //���λ���ڵ�ͼ�ڵĴ���

    //��������ͨѶ
    TowerLayer* pTower = dynamic_cast<TowerLayer*>(_pGameScene->getChildByTag(TagTower));

    if (!ifBuildLayer) {
        //ѡ�пյ��򵯳�����ȦȦ
        if (gameMap[gridPosition.y][gridPosition.x] == 0) {
            //log("build layer: gameMap[%d][%d] = %d", gridPosition.y, gridPosition.x, (int)gameMap[gridPosition.y][gridPosition.x]);
            buildTower(gridPosition.y, gridPosition.x);
            ifBuildLayer = 1;//��ǰ����ѡ����״̬
        }
    }
    else {//������ȡ������ȦȦ
        //��ȡ��������
        auto buildTower = this->getChildByName("layerBuild");
        auto towerGreen = buildTower->getChildByName("greenBottle");
        auto towerShit = buildTower->getChildByName("shit");
        //��ȡ��ǰ������
        Grid grid = *gridBuiding;
        //log("build tower: gameMap[%d][%d] = %d", grid.y, grid.x, (int)gameMap[grid.y][grid.x]);
        //�жϵ��λ���Ƿ�������ѡ��ͼ����
        if (towerGreen->getBoundingBox().containsPoint(touchLocation)) {
            if (pTower->ifAvailable(GREEN_BOTTLE)) {
                pTower->buidTower(GREEN_BOTTLE, grid.x, grid.y);
            }
        }
        else if (towerShit->getBoundingBox().containsPoint(touchLocation)) {
            if (pTower->ifAvailable(SHIT)) {
                pTower->buidTower(SHIT, grid.x, grid.y);
            }
        }
        this->removeChildByName("layerBuild");//�Ƴ��˵�
        grid.spriteGrid->setVisible(false);//���������
        gridBuiding = nullptr;
        ifBuildLayer = 0;//�ص��ǽ���״̬
    }
    //ѡ��С·���������ϰ��ϻ�����ʾ����ͼ�꣬����Ҫע��͹��޵ĳ�ͻ����
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

    //�ͽ�Ҳ�ͨѶ
    MoneyLayer* pMoney = dynamic_cast<MoneyLayer*>(_pGameScene->getChildByTag(TagMoney));
    switch (Type)
    {
        case GREEN_BOTTLE:
            if (pMoney->getMoney() >= 100)//���������� �������쳣: ��ȡ����Ȩ�޳�ͻ��this->_pTower->_pMoney �� 0xDDDDDDDD��
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

void TowerLayer::buidTower(int Type, int gridx, int gridy) {

    Vec2 position0 = gridToPosition(gridx, gridy);
    Vec2 position = Vec2(position0.x + 75 / 2, position0.y + 75 / 2);
    log("build tower position : (%fl, %fl)", position.x, position.y);
    //tower newTower;
    if (Type == GREEN_BOTTLE) {
        //��tower1
        auto newTower = tower_1::create(position, _pGameScene);
        this->addChild(newTower);
        //TowerLayer* ptower = dynamic_cast<TowerLayer*>(newTower->getParent());
        //ptower->removeTower(this);
    }
    else if (Type == SHIT) {
        //��tower3
        auto newTower = tower_3::create(position, _pGameScene);
        this->addChild(newTower);
    }
    gameMap[gridy][gridx] = TOWER1;
}

bool TowerLayer::removeTower(tower* Tower) {
    if (!Tower) {
        return false;
    }
   
    /*��Ч��getposition
    Vec2 position0 = Tower->getPosition();
    Vec2 position = Vec2(position0.x - 75 / 2, position0.y - 75 / 2);
    log("remove tower position : (% d, % d)", position0.x, position0.y);
    mapPos mappos;
    positionToGrid(position, mappos);
    gameMap[mappos.y][mappos.x] = 0;*/
    
    
    //�Ӳ����Ƶ���
    removeChild(dynamic_cast<Layer*>(Tower));
    
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
    removeChild(dynamic_cast<Layer*>(Enemy));//�ж�������ֱ��ָ
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
    removeChild(dynamic_cast<Layer*>(Stone));//�ж�������ֱ��ָ
    return true;
}
