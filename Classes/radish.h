#pragma once
#include "cocos2d.h"
#include <cmath>
#define size_of_radish 120  //������ʾ�ĳ��Ϳ�
#define ALLHP 10
#define UPMONEY 1500  //����һ�ε�Ǯ������һ����һ����
#define size_of_up 50  //����С��ʶ�ĳ��Ϳ�
#define size_of_blood 40  //����С��ʶ�ĳ��Ϳ�
class GameScene;
class radish:public cocos2d::Layer
{
public:
	radish(cocos2d::Vec2& a,GameScene* b);
	static radish* create(cocos2d::Vec2& a, GameScene* b);
	virtual bool init();
	int change_HP(int a);  //������������ֵΪ1ʱ���Ѿ����ˣ���ϷҪ����
	//void if_money();
	~radish() {
		this->unschedule("ShootScheduler");
	}
	//void cartoon(float dt);
private:
	cocos2d::Vec2 rpoint; //�ӵ��տ�ʼ��λ��
	int grade; //�ȼ�
	int HP;    //ʣ�����
	cocos2d::Sprite* MySprite = NULL;
	cocos2d::Sprite* upSprite = NULL;
	cocos2d::Label* label = NULL;
	GameScene* scene = NULL;
};
