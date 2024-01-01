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
	this->removeChild(my_picture);
	if (attack_stone != NULL) { 
			attack_stone->Attacked(damage);   //���ϰ����Ѫ��
	}
	else if (attack_enemy != NULL ) { 
		log("attack_enemy->Attacked(damage) %p", attack_enemy);
		attack_enemy->Attacked(damage);   //�õ��˼�Ѫ��
	}

}


//Bullet_2��ĳ�Ա����
void Bullet_2::hittarget()  //��һ������û���������Ч�������Բ��ؿ���������ڶ��������б���Ч����ʱ�򣬻��õ��öԷ�����һ������
{
	this->removeChild(my_picture);
	if (attack_stone != NULL) { 
			attack_stone->Attacked(damage);   //���ϰ����Ѫ��
	}
	else if (attack_enemy != NULL ) {
			attack_enemy->slowdown();         //�õ����˶�����
			attack_enemy->Attacked(damage);   //�õ��˼�Ѫ�������治�ܼӶ�����this��û������ô���ã���
	}
	
}


//Bullet_3��ĳ�Ա����
void Bullet_3::hittarget()  //��һ������û���������Ч�������Բ��ؿ���������ڶ��������б���Ч����ʱ�򣬻��õ��öԷ�����һ������
{
	this->removeChild(my_picture);
	if (attack_stone != NULL) { 
			attack_stone->Attacked(damage);   //���ϰ����Ѫ��
	}
	else if (attack_enemy != NULL ) {
			//���еļӽ����Ч
			Tower->add_money();
			auto sprite = cocos2d::Sprite::create("moneyupup.png");
			sprite->setPosition(cocos2d::Vec2(1 * 75, 7 * 75 + 50));
			sprite->setContentSize(cocos2d::Size(size_of_Moneyup, size_of_Moneyup));
			this->addChild(sprite);
			this->scheduleOnce([sprite](float delta) {
				sprite->setVisible(false);
				}, 1, "hideSprite_key");

			attack_enemy->Attacked(damage);   //�õ��˼�Ѫ��
	}
}