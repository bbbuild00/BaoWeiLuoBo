#pragma once

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
//111
#define RODE 9
#define BARRIER 4
#define TOWER1 1//1级塔
#define TOWER2 2//2级塔
#define TOWER3 3//顶级塔
#define GREEN_BOTTLE 1
#define SHIT 2
#define TagMenu 1
#define TagTower 2
#define TagMonster 3
#define TagMoney 4
#define TagStone 5
#define TagRadish 5

class GameScene : public cocos2d::Scene
{
public:
    //创建场景（static说明场景的转换是释放再赋值）
    static cocos2d::Scene* createGameScene();

    //初始化
    virtual bool init();
    void createBackground();//添加背景图
    void countToStart();//倒计时

    CREATE_FUNC(GameScene);

private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
};

class MoneyLayer : public cocos2d::Layer
{
public:
    static cocos2d::Layer* createLayer(GameScene* pScene);
    virtual bool init();
    CREATE_FUNC(MoneyLayer);
    void updateMoney(const int& changedCoins);
    int getMoney();

private:
    int coins = 450;
    cocos2d::Label* MoneyLabel = nullptr;
    GameScene* _pGameScene = nullptr;//通过场景的通讯方式
};

class TowerLayer;
class MonsterLayer;
class StoneLayer;
class RadishLayer;
struct Grid
{
    cocos2d::Sprite* spriteGrid = nullptr;
    int x;
    int y;
};
class MenuLayer : public cocos2d::Layer
{
public:
    static cocos2d::Layer* createMenuLayer(GameScene* pScene);
    virtual bool init();
    CREATE_FUNC(MenuLayer);
    void buildTower(int row, int col);
    //触摸事件
    bool touchBegan(cocos2d::Touch* touch, cocos2d::Event* event);


private:
    
    Grid grid[7][12] = { 0 };//框框结点
    Grid* gridBuiding = nullptr;//指向显示建塔的框框的指针
    bool ifBuildLayer = 0;//是否在选择建塔状态
    GameScene* _pGameScene = nullptr;//通过场景的通讯方式
};

//创建怪物管理层MonsterLayer
//创建函数create
//存储敌人的list
class enemy;
class MonsterLayer : public cocos2d::Layer
{
public:
    static cocos2d::Layer* createLayer(GameScene* pScene);
    virtual bool init();
    CREATE_FUNC(MonsterLayer);
    void createMonster();//生成小怪兽
    bool removeMonster(enemy* Enemy, int coins);//移掉小怪兽，增加金币
    void spawnMonster(float dt);
    void moveMonster(float dt);
private:
    GameScene* _pGameScene = nullptr;//通过场景的通讯方式
    std::queue<enemy*> monsterQueue;
};

//创建炮塔管理层TowerLayer
//我调用的static tower_1* create(cocos2d::Vec2& a, GameScene* b);
//我写的bool removeTower(tower* Tower)
class tower;
class TowerLayer : public cocos2d::Layer
{
public:
    static cocos2d::Layer* createLayer(GameScene* pScene);
    virtual bool init();
    bool ifAvailable(int Type);//判断是否够钱
    void buidTower(int Type, int gridx, int gridy);//调用tower函数，空地建塔
    bool removeTower(tower* Tower);
    CREATE_FUNC(TowerLayer);

private:
    GameScene* _pGameScene = nullptr;//通过场景的通讯方式
};


//创建障碍物管理层StoneLayer
//我写的bool removeStone(stone* Stone)
//我调用的create
class stone;
class StoneLayer : public cocos2d::Layer
{
public:
    static cocos2d::Layer* createLayer(GameScene* pScene);
    virtual bool init();
    CREATE_FUNC(StoneLayer);
    bool removeStone(stone* Stone, int coins);

private:
    GameScene* _pGameScene = nullptr;//通过场景的通讯方式
};

//创建萝卜管理层StoneLayer
//刘文美和闫雯晴写的bool removeStone(stone* Stone)
//刘文美和闫雯晴调用的create
class radish;
class RadishLayer : public cocos2d::Layer
{
public:
    static cocos2d::Layer* createLayer(GameScene* pScene);
    virtual bool init();
    CREATE_FUNC(RadishLayer);

private:
    GameScene* _pGameScene = nullptr;//通过场景的通讯方式
};


#endif // __GAME_SCENE_H__


