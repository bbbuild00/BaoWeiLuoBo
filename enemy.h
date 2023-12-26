#pragma once
#include "cocos2d.h"
#include "cocos/math/Vec2.h"//包含cocos2d::Size和二维向量
#include "cocos/2d/CCDrawNode.h"
#include "cocos/platform/CCImage.h"
#include"waypoint.h"

class enemy :public cocos2d::Layer
{
public:
	//enemy(waypoint* st, MonsterLayer* lay);
	//virtual ~enemy();
	//static enemy* create(waypoint* st, MonsterLayer* lay);
	virtual bool init() override;// 初始化函数

	virtual void draw_enemy() = 0;//纯虚函数//绘制小怪兽
	virtual void cartoon(float dt) = 0;//在冰冻攻击后变换图片
	virtual void slowdown() = 0;//判断速度（被减速）//关关或刘姐姐调用

	void move();//小怪兽的移动

	void Attackedby(tower* mtower);//受到炮塔攻击

	void Attacked(int damage);//被攻击时的伤害
	int getHP() { return HP; }//获取当前血量
	int getmoney() { return money; }//获取打败小怪兽奖励的金币
	bool Attacackable() { return active; }//判断小怪兽是否可以被攻击,是否消失
	void getout(tower* tower);//小怪兽脱离炮塔攻击范围
	void beremoved();//小怪兽被移除
	void doublespeed() { speed *= 2; }
	void normalspeed() { speed /= 2; }

	cocos2d::Vec2 getpos() { return mpos; }//获得当前位置

protected:
	int HP;//血量
	int fullHP;//满血
	double speed;//速度
	bool stop;//暂停

	cocos2d::Sprite* monster = NULL;//小怪兽
	cocos2d::Sprite* brush;//血条

	GameScene* w;
	bool slowice;//是否被冰块攻击
	bool active;//是否移动
	cocos2d::Vec2 mpos;//当前位置
	waypoint* walktowards;//走向的航点
	int money; //打败小怪兽奖励的金币

	cocos2d::Vector<waypoint*>m_waypointList;//走向的航点

	//记录有哪些炮塔在攻击它，当小怪兽死去后，到对应的炮塔里，把炮塔对应的该攻击对象删除
	//cocos2d::Vector<tower*>Attacktower;

};

class enemy1 :public enemy {
public:
	enemy1(waypoint* st, GameScene* lay);
	void draw_enemy();
	virtual void draw_enemy();//纯虚函数//绘制小怪兽
	virtual void cartoon(float dt);//在冰冻攻击后变换图片
	void slowdown();//判断速度（被减速）//关关或刘姐姐调用
	virtual ~enemy1();
};

class enemy2 :public enemy {
public:
	enemy2(waypoint* st, GameScene* lay);
	void draw_enemy();
	virtual void draw_enemy();//纯虚函数//绘制小怪兽
	virtual void cartoon(float dt);//在冰冻攻击后变换图片
	void slowdown();//判断速度（被减速）//关关或刘姐姐调用
	virtual ~enemy2();
};

class enemy3 :public enemy {
public:
	enemy3(waypoint* st, GameScene* lay);
	void draw_enemy();
	virtual void draw_enemy();//纯虚函数//绘制小怪兽
	virtual void cartoon(float dt);//在冰冻攻击后变换图片
	void slowdown();//判断速度（被减速）//关关或刘姐姐调用
	virtual ~enemy3();
};