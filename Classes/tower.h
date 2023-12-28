#pragma once
#include "cocos2d.h"
#include <cmath>


#define size_of_tower 75  //������ʾ�ĳ��Ϳ�
#define size_of_up 60  //����������ɾ��ͼ����ʾ�ĳ��Ϳ�


class enemy;
class Widget;
class Bullet;
class QTimer;
class stone;
class GameScene;

const float internal_time = 1.0;   //�������ι���֮��ļ��ʱ��

const int range_all = 500; //�����Ĺ�����Χ
const int damage_1[3] = { 10,20,40 };//��һ���������˺�
const int cost_money_1[3] = { 100,150,250 };
const int get_money_1[3] = { 60,150,300 };


const int damage_2[3] = { 10,20,40 };//�ڶ����������˺�
const int cost_money_2[3] = { 150,250,350 };
const int get_money_2[3] = { 90,240,450 };


const int damage_3[3] = { 10,20,40 };//�������������˺�
const int cost_money_3[3] = { 130,239,300 };
const int get_money_3[3] = { 78,216,396 };

//������
class tower :public cocos2d::Layer
{  
public:
	void set_rotation(double angle);  //��������Ӧ�ľ��������ת��Ҫ����һ���Ƕ������ú����ɳ�Ա����rotation���е���
	virtual void upgrade() = 0;  //��������������,���麯�����ڻ�����ʵ��
	void rotation(); //����б�ѡ���Ĺ������󣬵��øú����ᷢ����ת 
	void get_stone(stone* a);  //ѡ���ϰ���   δ��֮�պ���  ����һ��stone*�����ҾͿ���ѡ��Ŀ�깥������
	void get_enemy(enemy* a);
	bool check_if_in_range(cocos2d::Vec2 p);  //�ж��ϰ����Ƿ����ҵĹ�����Χ��
	virtual void shoot() = 0;  //���𿪵�
	void enemy_killed();  //���������Ժ�ָ�봦��
	void stone_killed();
	void enemy_out();  //�����߳������Ĺ�����Χ�Ժ�Ĵ���
	enemy* get_enemy();  //�õ���Ŀǰ�Ĺ�������
	void check_enemy_in(); //����ѡ�����Ŀ�깥���ĵ�����˭��Ŀǰ��ûʵ��
	void removed();  //ȥ��û��ʵ�֣���������������
	int get_damage(); //���ӵ��ഫ�˺�ֵ
	bool if_continue(int a); //���ӵ��������ã��ж��ܷ��Ѫ
	void add_money(); //���ӵ������

protected:
	cocos2d::Sprite* turretSprite = NULL;    //������������Ӧ��ͼƬ�ľ���
	enemy* attack_enemy = NULL; //��ѡ�еĵ���
	stone* attack_stone = NULL; //��ѡ�е��ϰ���
	int grade = 0;  //�ȼ�
	int range = range_all; //��������Ĺ�����Χ
	int damage; //���������ɵ��˺�
	int internal =  internal_time;
	cocos2d::Vec2 point; //����������
	cocos2d::Vec2 enemy_point; //Ҫ����������
	bool stop = false;  //��ͣ
	GameScene* scene = NULL;
};


class tower_1 : public tower  //��һ������
{
public:
	tower_1(cocos2d::Vec2& a,GameScene* b);    //���캯����Ҫ�󴫽�һ��λ����
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


class tower_2 : public tower  //�ڶ�������
{
public:
	tower_2(cocos2d::Vec2& a,GameScene* b);    //���캯����Ҫ�󴫽�һ��λ����
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


class tower_3 : public tower  //�ڶ�������
{
public:
	tower_3(cocos2d::Vec2& a,GameScene* b);    //���캯����Ҫ�󴫽�һ��λ����
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