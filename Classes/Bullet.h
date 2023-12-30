#pragma once
#include "cocos2d.h"
#include "tower.h"

#define size_of_Bullet 15  //�ӵ�ͼƬ��С
#define size_of_Moneyup 20  //�ӵ�ͼƬ��С

class enemy;
class Widget;
class tower;
class QTimer;
class stone;
class tower_1;

class Bullet:public cocos2d::Layer
{
public:
	Bullet(cocos2d::Vec2 p1, cocos2d::Vec2 p2, tower* t, enemy* e);
	Bullet(cocos2d::Vec2 p1, cocos2d::Vec2 p2, tower* t, stone* e);
	void move();
	virtual void hittarget() = 0;
protected:
	cocos2d::Vec2 start_point; //�ӵ��տ�ʼ��λ��
	cocos2d::Vec2 target_point; //�ӵ�Ҫȥ�ĵط�
	
	int damage;
	int run_time; //�ӵ��˶���ʱ��
	tower* Tower; //�������ӵ�������
	enemy* attack_enemy = NULL; //��ѡ�еĵ���
	stone* attack_stone = NULL; //��ѡ�е��ϰ���
	cocos2d::Sprite* my_picture = NULL;    //�������Ӧ��ͼƬ�ľ���
};



class Bullet_1 :public Bullet
{
public:
	Bullet_1(cocos2d::Vec2 p1, cocos2d::Vec2 p2, tower* t, enemy* e) :Bullet(p1, p2, t, e) {};
	static Bullet_1* create(cocos2d::Vec2 p1, cocos2d::Vec2 p2, tower* t, enemy* e) {
		Bullet_1* layer = new Bullet_1(p1, p2, t, e);
		if (layer && layer->init()) {
			layer->autorelease();
			return layer;
		}
		CC_SAFE_DELETE(layer);
		return nullptr;
	}
	virtual bool init() override {
		if (!Layer::init()) {
			return false;
		}
		// ��������и���ĳ�ʼ������
		my_picture = cocos2d::Sprite::create("bullet-1.png");
		my_picture->setPosition(start_point);
		my_picture->setContentSize(cocos2d::Size(size_of_Bullet, size_of_Bullet));
		this->addChild(my_picture);
		move();
		
		return true;
	}

	Bullet_1(cocos2d::Vec2 p1, cocos2d::Vec2 p2, tower* t, stone* e) :Bullet(p1, p2, t, e) {};
	static Bullet_1* create(cocos2d::Vec2 p1, cocos2d::Vec2 p2, tower* t, stone* e) {
		Bullet_1* layer = new Bullet_1(p1, p2, t, e);
		if (layer && layer->init()) {
			layer->autorelease();
			return layer;
		}
		CC_SAFE_DELETE(layer);
		return nullptr;
	}

	virtual void hittarget();
};


class Bullet_2 :public Bullet
{
public:
	Bullet_2(cocos2d::Vec2 p1, cocos2d::Vec2 p2, tower* t, enemy* e) :Bullet(p1, p2, t, e) {};
	static Bullet_2* create(cocos2d::Vec2 p1, cocos2d::Vec2 p2, tower* t, enemy* e) {
		Bullet_2* layer = new Bullet_2(p1, p2, t, e);
		if (layer && layer->init()) {
			layer->autorelease();
			return layer;
		}
		CC_SAFE_DELETE(layer);
		return nullptr;
	}
	virtual bool init() override {
		if (!Layer::init()) {
			return false;
		}
		// ��������и���ĳ�ʼ������
		my_picture = cocos2d::Sprite::create("bullet-2.png");
		my_picture->setPosition(start_point);
		my_picture->setContentSize(cocos2d::Size(size_of_Bullet, size_of_Bullet));
		this->addChild(my_picture);
		move();

		return true;
	}

	Bullet_2(cocos2d::Vec2 p1, cocos2d::Vec2 p2, tower* t, stone* e) :Bullet(p1, p2, t, e) {};
	static Bullet_2* create(cocos2d::Vec2 p1, cocos2d::Vec2 p2, tower* t, stone* e) {
		Bullet_2* layer = new Bullet_2(p1, p2, t, e);
		if (layer && layer->init()) {
			layer->autorelease();
			return layer;
		}
		CC_SAFE_DELETE(layer);
		return nullptr;
	}

	virtual void hittarget();
};


class Bullet_3 :public Bullet
{
public:
	Bullet_3(cocos2d::Vec2 p1, cocos2d::Vec2 p2, tower* t, enemy* e) :Bullet(p1, p2, t, e) {};
	static Bullet_3* create(cocos2d::Vec2 p1, cocos2d::Vec2 p2, tower* t, enemy* e) {
		Bullet_3* layer = new Bullet_3(p1, p2, t, e);
		if (layer && layer->init()) {
			layer->autorelease();
			return layer;
		}
		CC_SAFE_DELETE(layer);
		return nullptr;
	}
	virtual bool init() override {
		if (!Layer::init()) {
			return false;
		}
		// ��������и���ĳ�ʼ������
		my_picture = cocos2d::Sprite::create("bullet-3.png");
		my_picture->setPosition(start_point);
		my_picture->setContentSize(cocos2d::Size(size_of_Bullet, size_of_Bullet));
		this->addChild(my_picture);
		move();

		return true;
	}

	Bullet_3(cocos2d::Vec2 p1, cocos2d::Vec2 p2, tower* t, stone* e) :Bullet(p1, p2, t, e) {};
	static Bullet_3* create(cocos2d::Vec2 p1, cocos2d::Vec2 p2, tower* t, stone* e) {
		Bullet_3* layer = new Bullet_3(p1, p2, t, e);
		if (layer && layer->init()) {
			layer->autorelease();
			return layer;
		}
		CC_SAFE_DELETE(layer);
		return nullptr;
	}

	virtual void hittarget();
};