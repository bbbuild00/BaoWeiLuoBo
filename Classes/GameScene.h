#pragma once
#include "SimpleAudioEngine.h"
#include "audio/include/AudioEngine.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
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
#define ICE 3
#define TagMenu 1
#define TagTower 2
#define TagMonster 3
#define TagMoney 4
#define TagStone 5
#define TagRadish 6

#define LEVEL1 1
#define LEVEL2 2

class GameScene : public cocos2d::Scene
{
public:
    //���캯��������������
    GameScene(int level) : m_level(level) {}
   
    //����������static˵��������ת�����ͷ��ٸ�ֵ��
    static cocos2d::Scene* createGameScene(int level);

    //��ʼ��
    virtual bool init(int level);
    void createBackground();//��ӱ���ͼ
    void countToStart();//����ʱ
    
    int getLevel() { return m_level; }

    void winGame();//Ӯ��
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    int m_level;
};

class MoneyLayer : public cocos2d::Layer
{
public:
    //���캯��
    MoneyLayer(GameScene* pScene) : _pGameScene(pScene) {
    }
    static cocos2d::Layer* createLayer(GameScene* pScene);
    virtual bool init();
    void updateMoney(const int& changedCoins);
    int getMoney();

private:
    int coins;
    cocos2d::Label* MoneyLabel = nullptr;
    GameScene* _pGameScene = nullptr;//ͨ��������ͨѶ��ʽ
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
    MenuLayer(GameScene* pScene) : _pGameScene(pScene) {}
    static cocos2d::Layer* createMenuLayer(GameScene* pScene);
    virtual bool init();
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
class enemy;
class MonsterLayer : public cocos2d::Layer
{
public:
    //���캯��
    MonsterLayer(GameScene* pScene) : _pGameScene(pScene) {
    }
    static cocos2d::Layer* createLayer(GameScene* pScene);
    virtual bool init();
    bool removeMonster(enemy* Enemy, int coins);//�Ƶ�С���ޣ����ӽ��
    void spawnMonster(float dt);//����С����
    //void moveMonster(float dt);
private:
    GameScene* _pGameScene = nullptr;//ͨ��������ͨѶ��ʽ
    std::list<enemy*> monsterQueue;//�м�Ĺ��޻ᱻ���𣬻��ǲ�Ҫ�ö�����
    int monsterSpawnIndex = 0; // ���ڸ�����һ��Ҫ���ɵĹ�������
    int monsterNum = 20;
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
    void createStones();
private:
    GameScene* _pGameScene = nullptr;//ͨ��������ͨѶ��ʽ
};


#endif // __GAME_SCENE_H__


