#pragma once

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
//111
#define RODE 9
#define BARRIER 4
#define TOWER1 1//1����
#define TOWER2 2//2����
#define TOWER3 3//������
#define GREEN_BOTTLE 1
#define SHIT 2
#define TagMenu 1
#define TagTower 2
#define TagMonster 3
#define TagMoney 4
#define TagStone 5

class GameScene : public cocos2d::Scene
{
public:
    //����������static˵��������ת�����ͷ��ٸ�ֵ��
    static cocos2d::Scene* createGameScene();

    //��ʼ��
    virtual bool init();
    void createBackground();//��ӱ���ͼ
    void countToStart();//����ʱ

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
    GameScene* _pGameScene = nullptr;//ͨ��������ͨѶ��ʽ
};

class TowerLayer;
class MonsterLayer;
class StoneLayer;
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
    //�����¼�
    bool touchBegan(cocos2d::Touch* touch, cocos2d::Event* event);


private:
    
    Grid grid[7][12] = { 0 };//�����
    Grid* gridBuiding = nullptr;//ָ����ʾ�����Ŀ���ָ��
    bool ifBuildLayer = 0;//�Ƿ���ѡ����״̬
    GameScene* _pGameScene = nullptr;//ͨ��������ͨѶ��ʽ
};

//������������MonsterLayer
//��������create
//�洢���˵�list
class enemy;
class MonsterLayer : public cocos2d::Layer
{
public:
    static cocos2d::Layer* createLayer(GameScene* pScene);
    virtual bool init();
    CREATE_FUNC(MonsterLayer);
    void createMonster();//����С����
    bool removeMonster(enemy* Enemy, int coins);//�Ƶ�С���ޣ����ӽ��

private:
    GameScene* _pGameScene = nullptr;//ͨ��������ͨѶ��ʽ
};

//�������������TowerLayer
//�ҵ��õ�static tower_1* create(cocos2d::Vec2& a, GameScene* b);
//��д��bool removeTower(tower* Tower)
class tower;
class TowerLayer : public cocos2d::Layer
{
public:
    static cocos2d::Layer* createLayer(GameScene* pScene);
    virtual bool init();
    bool ifAvailable(int Type);//�ж��Ƿ�Ǯ
    void buidTower(int Type, int gridx, int gridy);//����tower�������յؽ���
    bool removeTower(tower* Tower);
    CREATE_FUNC(TowerLayer);

private:
    GameScene* _pGameScene = nullptr;//ͨ��������ͨѶ��ʽ
};


//�����ϰ�������StoneLayer
//��д��bool removeStone(stone* Stone)
//�ҵ��õ�create
class stone;
class StoneLayer : public cocos2d::Layer
{
public:
    static cocos2d::Layer* createLayer(GameScene* pScene);
    virtual bool init();
    CREATE_FUNC(StoneLayer);
    bool removeStone(stone* Stone, int coins);

private:
    GameScene* _pGameScene = nullptr;//ͨ��������ͨѶ��ʽ
};
#endif // __GAME_SCENE_H__
