#include "Bullet.h"
#include "stone.h"
#include "enemy.h"


//Bullet��ĳ�Ա����
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
	auto moveTo = cocos2d::MoveTo::create(0.8,target_point);//�ڹ涨ʱ�����ӵ����䵽���˵�λ�ý��й���
	auto callFunc = cocos2d::CallFunc::create([=](){
		hittarget();
		});
	auto sequence = cocos2d::Sequence::create(moveTo, callFunc, nullptr);
	my_picture->runAction(sequence);
}



//Bullet_1��ĳ�Ա����
void Bullet_1::hittarget()  //��һ������û���������Ч�������Բ��ؿ���������ڶ��������б���Ч����ʱ�򣬻��õ��öԷ�����һ������
{
	if (attack_stone != NULL) { 
		bool a = Tower->if_continue(1);
		if (a) {
			attack_stone->Attacked(damage);   //���ϰ����Ѫ��
		}
	}
	if (attack_enemy != NULL ) {  
		bool a = Tower->if_continue(2);
		if (a) {
			attack_enemy->Attacked(damage);   //�õ��˼�Ѫ��
		}
		
	}
	this->removeChild(my_picture);
	auto sprite = Sprite::create("moneyupup.png");
	sprite->setPosition(target_point);
	my_picture->setContentSize(cocos2d::Size(size_of_Moneyup, size_of_Moneyup));
	this->addChild(my_picture);
	this->addChild(sprite);
	this->scheduleOnce([sprite](float delta) {
		sprite->setVisible(false);
		}, 1, "hideSprite_key");
}


//Bullet_2��ĳ�Ա����
void Bullet_2::hittarget()  //��һ������û���������Ч�������Բ��ؿ���������ڶ��������б���Ч����ʱ�򣬻��õ��öԷ�����һ������
{
	if (attack_stone != NULL) { 
		bool a = Tower->if_continue(1);
		if (a) {
			attack_stone->Attacked(damage);   //���ϰ����Ѫ��
		}
	}
	if (attack_enemy != NULL ) {  
		bool a = Tower->if_continue(2);
		if (a) {
			attack_enemy->Attacked(damage);   //�õ��˼�Ѫ��
			attack_enemy->slowdown();         //�õ����˶�����
		}

	}
	this->removeChild(my_picture);
	auto sprite = Sprite::create("moneyupup.png");
	sprite->setPosition(target_point);
	my_picture->setContentSize(cocos2d::Size(size_of_Moneyup, size_of_Moneyup));
	this->addChild(my_picture);
	this->addChild(sprite);
	this->scheduleOnce([sprite](float delta) {
		sprite->setVisible(false);
		}, 1, "hideSprite_key");
}


//Bullet_3��ĳ�Ա����
void Bullet_3::hittarget()  //��һ������û���������Ч�������Բ��ؿ���������ڶ��������б���Ч����ʱ�򣬻��õ��öԷ�����һ������
{
	if (attack_stone != NULL) { 
		bool a = Tower->if_continue(1);
		if (a) {
			attack_stone->Attacked(damage);   //���ϰ����Ѫ��
			Tower->add_money();
		}
	}
	if (attack_enemy != NULL ) {  
		bool a = Tower->if_continue(2);
		if (a) {
			attack_enemy->Attacked(damage);   //�õ��˼�Ѫ��
			Tower->add_money();
		}

	}
	this->removeChild(my_picture);
	auto sprite = Sprite::create("moneyupup.png");
	sprite->setPosition(target_point);
	my_picture->setContentSize(cocos2d::Size(size_of_Moneyup, size_of_Moneyup));
	this->addChild(my_picture);
	this->addChild(sprite);
	this->scheduleOnce([sprite](float delta) {
		sprite->setVisible(false);
		}, 1, "hideSprite_key");
}