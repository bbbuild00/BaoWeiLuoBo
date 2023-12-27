#include "Bullet.h"
#include "stone.h"
#include "enemy.h"


//Bullet类的成员函数
Bullet::Bullet(cocos2d::Vec2 p1, cocos2d::Vec2 p2, tower* t, enemy* e)
{
	start_point = p1;
	target_point = p2;
	attack_enemy = e;
	Tower = t;
	damage = t->get_damage();
}

Bullet::Bullet(cocos2d::Vec2 p1, cocos2d::Vec2 p2, tower* t, stone* e)
{
	start_point = p1;
	target_point = p2;
	attack_stone = e;
	Tower = t;
	damage = t->get_damage();
}

void Bullet::move()
{
	double dx = start_point.x - target_point.x;
	double dy = start_point.y - target_point.y;
	double dis = sqrt(dx * dx + dy * dy);  //计算攻击敌人和炮塔之间的距离
	auto moveTo = cocos2d::MoveTo::create(time_bei * dis, target_point);//在规定时间内子弹发射到敌人的位置进行攻击
	auto callFunc = cocos2d::CallFunc::create([=](){
		hittarget();
		});
	auto sequence = cocos2d::Sequence::create(moveTo, callFunc, nullptr);
	my_picture->runAction(sequence);
}



//Bullet_1类的成员函数
void Bullet_1::hittarget()  //第一种炮塔没有这个冰冻效果，所以不必考虑这个；第二种炮塔有冰冻效果的时候，还得调用对方敌人一个函数
{
	if (attack_stone != NULL) { 
		bool a = Tower->if_continue(1);
		if (a) {
			attack_stone->Attacked(damage);   //让障碍物减血条
		}
	}
	if (attack_enemy != NULL ) {  
		bool a = Tower->if_continue(2);
		if (a) {
			attack_enemy->Attacked(damage);   //让敌人减血条
		}
		
	}
	this->removeChild(my_picture);
}


//Bullet_2类的成员函数
void Bullet_2::hittarget()  //第一种炮塔没有这个冰冻效果，所以不必考虑这个；第二种炮塔有冰冻效果的时候，还得调用对方敌人一个函数
{
	if (attack_stone != NULL) { 
		bool a = Tower->if_continue(1);
		if (a) {
			attack_stone->Attacked(damage);   //让障碍物减血条
		}
	}
	if (attack_enemy != NULL ) {  
		bool a = Tower->if_continue(2);
		if (a) {
			attack_enemy->Attacked(damage);   //让敌人减血条
			attack_enemy->slowdown();         //让敌人运动变慢
		}

	}
	this->removeChild(my_picture);
}


//Bullet_3类的成员函数
void Bullet_3::hittarget()  //第一种炮塔没有这个冰冻效果，所以不必考虑这个；第二种炮塔有冰冻效果的时候，还得调用对方敌人一个函数
{
	if (attack_stone != NULL) { 
		bool a = Tower->if_continue(1);
		if (a) {
			attack_stone->Attacked(damage);   //让障碍物减血条
			Tower->add_money();
		}
	}
	if (attack_enemy != NULL ) {  
		bool a = Tower->if_continue(2);
		if (a) {
			attack_enemy->Attacked(damage);   //让敌人减血条
			Tower->add_money();
		}

	}
	this->removeChild(my_picture);
}