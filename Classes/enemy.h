#pragma once
#include "cocos2d.h"
#include "cocos/math/Vec2.h"//����cocos2d::Size�Ͷ�ά����
#include "cocos/2d/CCDrawNode.h"
#include "cocos/platform/CCImage.h"
#include"waypoint.h"

class enemy :public cocos2d::Layer
{
public:
	//enemy(waypoint* st, MonsterLayer* lay);
	//virtual ~enemy();
	//static enemy* create(waypoint* st, MonsterLayer* lay);
	virtual bool init() override;// ��ʼ������

	virtual void draw_enemy() = 0;//���麯��//����С����
	virtual void cartoon(float dt) = 0;//�ڱ���������任ͼƬ
	virtual void slowdown() = 0;//�ж��ٶȣ������٣�//�عػ���������

	void move();//С���޵��ƶ�

	void Attackedby(tower* mtower);//�ܵ���������

	void Attacked(int damage);//������ʱ���˺�
	int getHP() { return HP; }//��ȡ��ǰѪ��
	int getmoney() { return money; }//��ȡ���С���޽����Ľ��
	bool Attacackable() { return active; }//�ж�С�����Ƿ���Ա�����,�Ƿ���ʧ
	void getout(tower* tower);//С������������������Χ
	void beremoved();//С���ޱ��Ƴ�
	void doublespeed() { speed *= 2; }
	void normalspeed() { speed /= 2; }

	cocos2d::Vec2 getpos() { return mpos; }//��õ�ǰλ��

protected:
	int HP;//Ѫ��
	int fullHP;//��Ѫ
	double speed;//�ٶ�
	bool stop;//��ͣ

	cocos2d::Sprite* monster = NULL;//С����
	cocos2d::Sprite* brush;//Ѫ��

	GameScene* w;
	bool slowice;//�Ƿ񱻱��鹥��
	bool active;//�Ƿ��ƶ�
	cocos2d::Vec2 mpos;//��ǰλ��
	waypoint* walktowards;//����ĺ���
	int money; //���С���޽����Ľ��

	cocos2d::Vector<waypoint*>m_waypointList;//����ĺ���

	//��¼����Щ�����ڹ���������С������ȥ�󣬵���Ӧ���������������Ӧ�ĸù�������ɾ��
	//cocos2d::Vector<tower*>Attacktower;

};

class enemy1 :public enemy {
public:
	enemy1(waypoint* st, GameScene* lay);
	void draw_enemy();
	virtual void draw_enemy();//���麯��//����С����
	virtual void cartoon(float dt);//�ڱ���������任ͼƬ
	void slowdown();//�ж��ٶȣ������٣�//�عػ���������
	virtual ~enemy1();
};

class enemy2 :public enemy {
public:
	enemy2(waypoint* st, GameScene* lay);
	void draw_enemy();
	virtual void draw_enemy();//���麯��//����С����
	virtual void cartoon(float dt);//�ڱ���������任ͼƬ
	void slowdown();//�ж��ٶȣ������٣�//�عػ���������
	virtual ~enemy2();
};

class enemy3 :public enemy {
public:
	enemy3(waypoint* st, GameScene* lay);
	void draw_enemy();
	virtual void draw_enemy();//���麯��//����С����
	virtual void cartoon(float dt);//�ڱ���������任ͼƬ
	void slowdown();//�ж��ٶȣ������٣�//�عػ���������
	virtual ~enemy3();
};