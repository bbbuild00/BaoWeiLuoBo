#pragma once
#include "cocos2d.h"
#include "cocos/math/Vec2.h"//����cocos2d::Size�Ͷ�ά����
#include "cocos/2d/CCDrawNode.h"
#include "cocos/platform/CCImage.h"

class stone :public cocos2d::Layer {
public:
   // stone(cocos2d::Vec2 p, StoneLayer* lay);
    virtual void draw_stone()=0;//���ϰ���
   // static stone* create(cocos2d::Vec2 po��StoneLayer* lay);
    virtual bool init() override; // ��ʼ������
    cocos2d::Vec2 getpos() { return point; }
    int getmoney() { return money; }
    void addtower(tower*tw){towerlist.push_back(tw);}
    void stone::Attacked(int damage);

protected:
    cocos2d::Sprite* stone_1 = NULL;//�ϰ���1
    cocos2d::Sprite* Brush;//Ѫ��
    int q;
    int HP;
    int fullHP;
    cocos2d::Vec2 point;//ʵ��λ��
    int money;

    StoneLayer *w;
	cocos2d::Vector<tower*>towerlist;
};

class stone1 :public stone {
public:
    stone1(cocos2d::Vec2 p, StoneLayer* lay);
    virtual void draw_stone();
};

class stone2 :public stone {
public:
    stone2(cocos2d::Vec2 p, StoneLayer* lay);
    virtual void draw_stone();
};

class stone3 :public stone {
public:
    stone3(cocos2d::Vec2 p, StoneLayer* lay);
    virtual void draw_stone();
};

class stone4 :public stone {
public:
    stone4(cocos2d::Vec2 p, StoneLayer* lay);
    virtual void draw_stone();
};

class stone5 :public stone {
public:
    stone5(cocos2d::Vec2 p, StoneLayer* lay);
    virtual void draw_stone();
};