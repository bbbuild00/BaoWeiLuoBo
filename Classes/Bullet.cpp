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
	auto moveTo = cocos2d::MoveTo::create(0.8,target_point);//在规定时间内子弹发射到敌人的位置进行攻击
	auto callFunc = cocos2d::CallFunc::create([=](){
		hittarget();
		});
	auto sequence = cocos2d::Sequence::create(moveTo, callFunc, nullptr);
	my_picture->runAction(sequence);
}



//Bullet_1类的成员函数
void Bullet_1::hittarget()  //第一种炮塔没有这个冰冻效果，所以不必考虑这个；第二种炮塔有冰冻效果的时候，还得调用对方敌人一个函数
{
	this->removeChild(my_picture);
	if (attack_stone != NULL) { 
			attack_stone->Attacked(damage);   //让障碍物减血条
	}
	else if (attack_enemy != NULL ) { 
		log("attack_enemy->Attacked(damage) %p", attack_enemy);
		attack_enemy->Attacked(damage);   //让敌人减血条
	}

}


//Bullet_2类的成员函数
void Bullet_2::hittarget()  //第一种炮塔没有这个冰冻效果，所以不必考虑这个；第二种炮塔有冰冻效果的时候，还得调用对方敌人一个函数
{
	this->removeChild(my_picture);
	if (attack_stone != NULL) { 
			attack_stone->Attacked(damage);   //让障碍物减血条
	}
	else if (attack_enemy != NULL ) {
			attack_enemy->slowdown();         //让敌人运动变慢
			attack_enemy->Attacked(damage);   //让敌人减血条（后面不能加东西！this都没啦还怎么调用！）
	}
	
}


//Bullet_3类的成员函数
void Bullet_3::hittarget()  //第一种炮塔没有这个冰冻效果，所以不必考虑这个；第二种炮塔有冰冻效果的时候，还得调用对方敌人一个函数
{
	this->removeChild(my_picture);
	if (attack_stone != NULL) { 
			attack_stone->Attacked(damage);   //让障碍物减血条
	}
	else if (attack_enemy != NULL ) {
			//特有的加金币特效
			Tower->add_money();
			auto sprite = cocos2d::Sprite::create("moneyupup.png");
			sprite->setPosition(cocos2d::Vec2(1 * 75, 7 * 75 + 50));
			sprite->setContentSize(cocos2d::Size(size_of_Moneyup, size_of_Moneyup));
			this->addChild(sprite);
			this->scheduleOnce([sprite](float delta) {
				sprite->setVisible(false);
				}, 1, "hideSprite_key");

			attack_enemy->Attacked(damage);   //让敌人减血条
	}
}