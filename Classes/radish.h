#pragma once
#include "cocos2d.h"
#include <cmath>
#define size_of_radish 120  //炮塔显示的长和宽
#define ALLHP 10
#define UPMONEY 1500  //升级一次的钱，升级一次涨一次命
#define size_of_up 50  //升级小标识的长和宽
#define size_of_blood 40  //升级小标识的长和宽
class GameScene;
class radish:public cocos2d::Layer
{
public:
	radish(cocos2d::Vec2& a,GameScene* b);
	static radish* create(cocos2d::Vec2& a, GameScene* b);
	virtual bool init();
	int change_HP(int a);  //改命，当返回值为1时，已经死了，游戏要结束
	//void if_money();
	~radish() {
		this->unschedule("ShootScheduler");
	}
	//void cartoon(float dt);
private:
	cocos2d::Vec2 rpoint; //子弹刚开始的位置
	int grade; //等级
	int HP;    //剩余的命
	cocos2d::Sprite* MySprite = NULL;
	cocos2d::Sprite* upSprite = NULL;
	cocos2d::Label* label = NULL;
	GameScene* scene = NULL;
};
