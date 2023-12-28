#pragma once
#include "cocos2d.h"
#include <cmath>


#define size_of_tower 75  //炮塔显示的长和宽
#define size_of_up 60  //炮塔升级和删除图标显示的长和宽


class enemy;
class Widget;
class Bullet;
class QTimer;
class stone;
class GameScene;

const float internal_time = 1.0;   //炮塔两次攻击之间的间隔时间

const int range_all = 500; //炮塔的攻击范围
const int damage_1[3] = { 10,20,40 };//第一种炮塔的伤害
const int cost_money_1[3] = { 100,150,250 };
const int get_money_1[3] = { 60,150,300 };


const int damage_2[3] = { 10,20,40 };//第二种炮塔的伤害
const int cost_money_2[3] = { 150,250,350 };
const int get_money_2[3] = { 90,240,450 };


const int damage_3[3] = { 10,20,40 };//第三种炮塔的伤害
const int cost_money_3[3] = { 130,239,300 };
const int get_money_3[3] = { 78,216,396 };

//炮塔类
class tower :public cocos2d::Layer
{  
public:
	void set_rotation(double angle);  //将炮塔对应的精灵进行旋转，要求传入一个角度来。该函数由成员函数rotation进行调用
	virtual void upgrade() = 0;  //负责炮塔的升级,纯虚函数，在基类中实现
	void rotation(); //如果有被选定的攻击对象，调用该函数会发生旋转 
	void get_stone(stone* a);  //选中障碍物   未解之谜函数  传进一个stone*来，我就可以选中目标攻击对象
	void get_enemy(enemy* a);
	bool check_if_in_range(cocos2d::Vec2 p);  //判断障碍物是否在我的攻击范围内
	virtual void shoot() = 0;  //负责开弹
	void enemy_killed();  //敌人死了以后指针处理
	void stone_killed();
	void enemy_out();  //敌人走出炮塔的攻击范围以后的处理
	enemy* get_enemy();  //得到我目前的攻击敌人
	void check_enemy_in(); //我来选择出我目标攻击的敌人是谁，目前还没实现
	void removed();  //去还没有实现，功能是想拆除炮塔
	int get_damage(); //向子弹类传伤害值
	bool if_continue(int a); //由子弹类来调用，判断能否扣血
	void add_money(); //由子弹类调用

protected:
	cocos2d::Sprite* turretSprite = NULL;    //用来存炮塔对应的图片的精灵
	enemy* attack_enemy = NULL; //被选中的敌人
	stone* attack_stone = NULL; //被选中的障碍物
	int grade = 0;  //等级
	int range = range_all; //这个炮塔的攻击范围
	int damage; //这个炮塔造成的伤害
	int internal =  internal_time;
	cocos2d::Vec2 point; //炮塔的坐标
	cocos2d::Vec2 enemy_point; //要攻击的坐标
	bool stop = false;  //暂停
	GameScene* scene = NULL;
};


class tower_1 : public tower  //第一个炮塔
{
public:
	tower_1(cocos2d::Vec2& a,GameScene* b);    //构造函数，要求传进一个位置来
	virtual void upgrade();
	virtual void shoot();  
	static tower_1* create(cocos2d::Vec2& a, GameScene* b) {
		tower_1* layer = new tower_1(a, b);
		if (layer && layer->init()) {
			layer->autorelease();
			return layer;
		}
		CC_SAFE_DELETE(layer);
		return nullptr;
	}
	virtual bool init() override;
	tower_1::~tower_1(){
		this->unschedule("ShootScheduler1");
		this->unschedule("ShootScheduler2");
	}
};


class tower_2 : public tower  //第二个炮塔
{
public:
	tower_2(cocos2d::Vec2& a,GameScene* b);    //构造函数，要求传进一个位置来
	virtual void upgrade();
	virtual void shoot();  
	static tower_2* create(cocos2d::Vec2& a, GameScene* b) {
		tower_2* layer = new tower_2(a, b);
		if (layer && layer->init()) {
			layer->autorelease();
			return layer;
		}
		CC_SAFE_DELETE(layer);
		return nullptr;
	}
	virtual bool init() override;
	~tower_2(){
		this->unschedule("ShootScheduler1");
		this->unschedule("ShootScheduler2");
	}
};


class tower_3 : public tower  //第二个炮塔
{
public:
	tower_3(cocos2d::Vec2& a,GameScene* b);    //构造函数，要求传进一个位置来
	virtual void upgrade();
	virtual void shoot();  
	static tower_3* create(cocos2d::Vec2& a, GameScene* b) {
		tower_3* layer = new tower_3(a, b);
		if (layer && layer->init()) {
			layer->autorelease();
			return layer;
		}
		CC_SAFE_DELETE(layer);
		return nullptr;
	}
	virtual bool init() override;
	~tower_3(){
		this->unschedule("ShootScheduler1");
		this->unschedule("ShootScheduler2");
	}
};