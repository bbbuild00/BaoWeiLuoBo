#pragma once

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

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
    
    cocos2d::Sprite* grid[7][12] = { 0 };//�����
    cocos2d::Sprite* gridBuiding = nullptr;//ָ����ʾ�����Ŀ���ָ��
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
    bool removeMonster(enemy* Enemy);

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
    void buidTower(int Type, cocos2d::Sprite* gridBuiding);//����tower�������յؽ���
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
    bool removeStone(stone* Stone);

private:
    GameScene* _pGameScene = nullptr;//ͨ��������ͨѶ��ʽ
};
#endif // __GAME_SCENE_H__
