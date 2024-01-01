#include "tower.h"
#include "Bullet.h"
#include "GameScene.h"
#include <string>
#include "stone.h"
#include "enemy.h"



void tower::add_money()
{
	MoneyLayer* pMoney = dynamic_cast<MoneyLayer*>(scene->getChildByTag(TagMoney));
	pMoney->updateMoney((grade + 1) * 5);
}

void tower::removed()
{
	TowerLayer* ptower = dynamic_cast<TowerLayer*>(this->getParent());
	ptower->removeTower(this);
}

void tower::set_rotation(double angle)   //��������Ӧ�ľ��������ת��Ҫ����һ���Ƕ���
{
	auto rotateTo = cocos2d::RotateTo::create(0.05, angle);  //��0.05s����ת��angle�Ƕ�
	turretSprite->runAction(rotateTo);
}

void tower::rotation()
{
	if ((attack_enemy != NULL) || (attack_stone != NULL)) {     //����ָ���Ĺ������˻�����
		if (attack_enemy != NULL) {
			enemy_point = attack_enemy->getpos();
		}
		else if (attack_stone != NULL) {
			enemy_point = attack_stone->getpos();
		}
		double x = point.x - enemy_point.x;
		double y = point.y - enemy_point.y;
		double resultDegrees;
		if (x > 0 && y > 0) {
			double result = atan(y / x);
			resultDegrees = -(result * 180.0 / M_PI + 90);
		}
		else if (x < 0 && y < 0) {
			double result = atan(x / y);
			resultDegrees = result * 180.0 / M_PI;
		}
		else if (x > 0 && y < 0) {
			double result = atan(x / (-y));
			resultDegrees = -(result * 180.0 / M_PI);
		}
		else if (x < 0 && y>0) {
			double result = atan(y / (-x));
			resultDegrees = result * 180.0 / M_PI + 90;
		}
		else if (x == 0 && y <= 0) {
			resultDegrees = 0;
		}
		else if (x == 0 && y > 0) {
			resultDegrees = 180;
		}
		else if (x > 0 && y == 0) {
			resultDegrees = -90;
		}
		else {
			resultDegrees = 90;
		}
		set_rotation(resultDegrees);
	}
}

bool tower::check_if_in_range(cocos2d::Vec2 p) {
	double dx = p.x - point.x;
	double dy = p.y - point.y;
	if (dx * dx + dy * dy <= range * range) {
		return true;
	}
	return false;
}

void tower::get_stone(stone* a)  //δ��֮�պ���
{
	attack_stone = a;
	enemy_point = a->getpos();
	attack_stone->addtower(this);  //���Ӧ���ϰ������ӵ�˭�ڹ����� //˭Ҫɱ���ң�������ɱ��˭��
	attack_enemy == NULL;
}

void tower::get_enemy(enemy* a)  //δ��֮�պ���
{
	attack_enemy = a;
	enemy_point = a->getpos();
	attack_enemy->addtower(this);  //���Ӧ���ϰ������ӵ�˭�ڹ����� //˭Ҫɱ���ң�������ɱ��˭��
}


void tower::enemy_killed()
{
	if (attack_enemy != NULL) {
		attack_enemy = NULL;
	}
	Vector<Node*> bulletsToRemove;
	for (auto child : this->getChildren()) {
		if (Bullet* bullet = dynamic_cast<Bullet*>(child)) {
			bulletsToRemove.pushBack(bullet);
		}
	}
	for (auto bullet : bulletsToRemove) {
		this->removeChild(bullet);
	}

}

void tower::stone_killed()
{
	if (attack_stone != NULL) {
		attack_stone = NULL;
	}
	Vector<Node*> bulletsToRemove;
	for (auto child : this->getChildren()) {
		if (Bullet* bullet = dynamic_cast<Bullet*>(child)) {
			bulletsToRemove.pushBack(bullet);
		}
	}
	for (auto bullet : bulletsToRemove) {
		this->removeChild(bullet);
	}
}

void tower::enemy_out()
{
	if (attack_enemy != NULL) {
		attack_enemy->getout(this);
		attack_enemy = NULL;
	}
}

enemy* tower::get_enemy()
{
	return attack_enemy;
}

void tower::check_enemy_in()  //��δʵ��
{
	if (rotate)
		rotation();
	if (attack_stone != NULL); //�����attack_stone�Ļ������ý��к������
	else if (attack_enemy != NULL) {
		enemy_point = attack_enemy->getpos();  //�õ�Ҫ�����ĵ��˵�λ������
		double dx = point.x - enemy_point.x;
		double dy = point.y - enemy_point.y;
		double dis = sqrt(dx * dx + dy * dy);  //���㹥�����˺�����֮��ľ���
		if (dis >= range) {                    //��������Ѿ��߳����ҵĹ�����Χ���ҾͰ����Ƴ�ȥ
			enemy_out();
		}
	}
	else {
		MonsterLayer* pMonster = dynamic_cast<MonsterLayer*>(scene->getChildByTag(TagMonster));
		for (Node* child : pMonster->getChildren()) {
			if (enemy* e = dynamic_cast<enemy*>(child)) {
				bool a = check_if_in_range(e->getpos());
				if (a) {
					get_enemy(e);
					break;
				}
			}
		}
	}
}

int tower::get_damage()
{
	return damage;
}
/*
bool tower::if_continue(int a)
{
	if ((a == 1 && attack_stone != NULL) || (a == 2 && attack_enemy != NULL))
		return true;
	return false;
}
*/
tower_1::tower_1(cocos2d::Vec2& a, GameScene* b)
{
	rotate = true;
	point = a;
	grade = 0;
	damage = damage_1[0];
	scene = b;
	MoneyLayer* pMoney = dynamic_cast<MoneyLayer*>(scene->getChildByTag(TagMoney));
	pMoney->updateMoney(-cost_money_1[0]);
}

void tower_1::upgrade()
{
	if (grade == 0) {
		turretSprite->setTexture("tower1-2.png");
		turretSprite->setContentSize(cocos2d::Size(size_of_tower, size_of_tower));
		damage = damage_1[1];
		MoneyLayer* pMoney = dynamic_cast<MoneyLayer*>(scene->getChildByTag(TagMoney));
		pMoney->updateMoney(-cost_money_1[1]);
	}
	else if (grade == 1) {
		turretSprite->setTexture("tower1-3.png");
		turretSprite->setContentSize(cocos2d::Size(size_of_tower, size_of_tower));
		damage = damage_1[2];
		MoneyLayer* pMoney = dynamic_cast<MoneyLayer*>(scene->getChildByTag(TagMoney));
		pMoney->updateMoney(-cost_money_1[2]);
	}
	grade++;
}

void tower_1::shoot()
{
	if (attack_stone != NULL) {    //����Ҫ�������ϰ���
		Bullet* bullet = Bullet_1::create(point, enemy_point, this, attack_stone); //������һ���ӵ��ࣿ
		this->addChild(bullet);
		bullet->move();  //���ӵ�������

	}
	if (attack_enemy != NULL) {    //����Ҫ�����ĵ���
		Bullet* bullet = Bullet_1::create(point, enemy_point, this, attack_enemy); //������һ���ӵ��ࣿ
		this->addChild(bullet);
		bullet->move();  //���ӵ�������

	}
}

bool tower_1::init()
{
	if (!Layer::init()) {
		return false;
	}
	// ��������и���ĳ�ʼ������
	turretSprite = cocos2d::Sprite::create("tower1-1.png");
	turretSprite->setPosition(point);
	turretSprite->setContentSize(cocos2d::Size(size_of_tower, size_of_tower));
	this->addChild(turretSprite);
	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	//��һ���������� �����������������������ͼƬ
	
	listener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event){
		auto touchlocation = this->convertToNodeSpace(touch->getLocation());
		// �������Ƿ�������
		if (turretSprite->getBoundingBox().containsPoint(touchlocation)) {
			// ���������ִ������Ҫ�Ĳ���
			listener->setSwallowTouches(true);
			MoneyLayer* pMoney = dynamic_cast<MoneyLayer*>(scene->getChildByTag(TagMoney));
			int allmoney = pMoney->getMoney();
			auto upSprite = cocos2d::Sprite::create();
			if (allmoney >= cost_money_1[1] && grade == 0)
				upSprite->setTexture("tower1-1-a.png");
			else if (allmoney >= cost_money_1[2] && grade == 1)
				upSprite->setTexture("tower1-2-a.png");
			else if (grade == 0)
				upSprite->setTexture("tower1-1-b.png");
			else if(grade==1)
				upSprite->setTexture("tower1-2-b.png");
			else 
				upSprite->setTexture("tower1-3-a.png");
			upSprite->setPosition(cocos2d::Vec2(point.x, point.y + (size_of_tower / 2) + (size_of_up / 2)));
			upSprite->setContentSize(cocos2d::Size(size_of_up, size_of_up));
			this->addChild(upSprite);

			auto downSprite = cocos2d::Sprite::create();
			if (grade == 0)
				downSprite->setTexture("tower1-1-c.png");
			else if (grade == 1)
				downSprite->setTexture("tower1-2-c.png");
			else 
				downSprite->setTexture("tower1-3-b.png");
			downSprite->setPosition(cocos2d::Vec2(point.x, point.y - (size_of_tower / 2) - (size_of_up / 2)));
			downSprite->setContentSize(cocos2d::Size(size_of_up, size_of_up));
			this->addChild(downSprite);

			//��һ����������
			auto listene = cocos2d::EventListenerTouchOneByOne::create();
			listene->setSwallowTouches(true);
			listene->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
				auto touchLocation = this->convertToNodeSpace(touch->getLocation());
				// ������������������Ǯ�㹻
				if (upSprite->getBoundingBox().containsPoint(touchLocation) && ((allmoney >= cost_money_1[1] && grade == 0) || (allmoney >= cost_money_1[2] && grade == 1))) {
					upgrade();   //����
					listener->setSwallowTouches(true);
				}
				//�����������ٲ��ҵȼ�Ϊ0
				else if (downSprite->getBoundingBox().containsPoint(touchLocation) && grade == 0) {
					MoneyLayer* pMoney = dynamic_cast<MoneyLayer*>(scene->getChildByTag(TagMoney));
					pMoney->updateMoney(get_money_1[0]);
					removed();
					listener->setSwallowTouches(true);
				}
				//�����������ٲ��ҵȼ�Ϊ1
				else if (downSprite->getBoundingBox().containsPoint(touchLocation) && grade == 1) {
					MoneyLayer* pMoney = dynamic_cast<MoneyLayer*>(scene->getChildByTag(TagMoney));
					pMoney->updateMoney(get_money_1[1]);
					removed();
					listener->setSwallowTouches(true);
				}
				//�����������ٲ��ҵȼ�Ϊ2
				else if (downSprite->getBoundingBox().containsPoint(touchLocation) && grade == 2) {
					MoneyLayer* pMoney = dynamic_cast<MoneyLayer*>(scene->getChildByTag(TagMoney));
					pMoney->updateMoney(get_money_1[2]);
					removed();
					listener->setSwallowTouches(true);
				}
				else {
					listener->setSwallowTouches(false);
				}
				if (upSprite != NULL)
					this->removeChild(upSprite);  //���������ժ���
				if (downSprite != NULL)
					this->removeChild(downSprite);
				return false;
			};
			// ע�������
			_eventDispatcher->addEventListenerWithSceneGraphPriority(listene, upSprite);

		}
		
		return true;
	};

	// ע�������
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, turretSprite);


	//��ʱ��
	this->schedule([this](float dt) {
		this->shoot();
		}, internal, "ShootScheduler1"); //1.0fΪ���ʱ�䣬"ShootScheduler"Ϊ�������ı�ǩ��

	this->schedule([this](float dt) {
		this->check_enemy_in();
		}, 0.1, "ShootScheduler2"); //1.0fΪ���ʱ�䣬"ShootScheduler"Ϊ�������ı�ǩ��

	return true;

}



tower_2::tower_2(cocos2d::Vec2& a, GameScene* b)
{
	rotate = true;
	point = a;
	grade = 0;
	damage = damage_2[0];
	scene = b;
	MoneyLayer* pMoney = dynamic_cast<MoneyLayer*>(scene->getChildByTag(TagMoney));
	pMoney->updateMoney(-cost_money_2[0]);
}
void tower_2::upgrade()
{
	if (grade == 0) {
		turretSprite->setTexture("tower2-2.png");
		turretSprite->setContentSize(cocos2d::Size(size_of_tower, size_of_tower));
		damage = damage_2[1];
		MoneyLayer* pMoney = dynamic_cast<MoneyLayer*>(scene->getChildByTag(TagMoney));
		pMoney->updateMoney(-cost_money_2[1]);
	}
	else if (grade == 1) {
		turretSprite->setTexture("tower2-3.png");
		turretSprite->setContentSize(cocos2d::Size(size_of_tower, size_of_tower));
		damage = damage_2[2];
		MoneyLayer* pMoney = dynamic_cast<MoneyLayer*>(scene->getChildByTag(TagMoney));
		pMoney->updateMoney(-cost_money_2[2]);
	}
	grade++;
}
void tower_2::shoot()
{
	if (attack_stone != NULL) {    //����Ҫ�������ϰ���
		Bullet* bullet = Bullet_2::create(point, enemy_point, this, attack_stone); //������һ���ӵ��ࣿ
		this->addChild(bullet);
		bullet->move();  //���ӵ�������

	}
	if (attack_enemy != NULL) {    //����Ҫ�����ĵ���
		Bullet* bullet = Bullet_2::create(point, enemy_point, this, attack_enemy); //������һ���ӵ��ࣿ
		this->addChild(bullet);
		bullet->move();  //���ӵ�������

	}
}
bool tower_2::init()
{
	if (!Layer::init()) {
		return false;
	}
	// ��������и���ĳ�ʼ������
	turretSprite = cocos2d::Sprite::create("tower2-1.png");
	turretSprite->setPosition(point);
	turretSprite->setContentSize(cocos2d::Size(size_of_tower, size_of_tower));
	this->addChild(turretSprite);
	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	
	//��һ���������� �����������������������ͼƬ
	listener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event){
		auto touchLocation = this->convertToNodeSpace(touch->getLocation());
		// �������Ƿ�������
		if (turretSprite->getBoundingBox().containsPoint(touchLocation)) {
			// ���������ִ������Ҫ�Ĳ���
			listener->setSwallowTouches(true);
			MoneyLayer* pMoney = dynamic_cast<MoneyLayer*>(scene->getChildByTag(TagMoney));
			int allmoney = pMoney->getMoney();
			auto upSprite = cocos2d::Sprite::create();
			if (allmoney >= cost_money_2[1] && grade == 0)
				upSprite->setTexture("tower2-1-a.png");
			else if (allmoney >= cost_money_2[2] && grade == 1)
				upSprite->setTexture("tower2-2-a.png");
			else if (grade == 0)
				upSprite->setTexture("tower2-1-b.png");
			else if(grade==1)
				upSprite->setTexture("tower2-2-b.png");
			else 
				upSprite->setTexture("tower2-3-a.png");
			upSprite->setPosition(cocos2d::Vec2(point.x, point.y + (size_of_tower / 2) + (size_of_up / 2)));
			upSprite->setContentSize(cocos2d::Size(size_of_up, size_of_up));
			this->addChild(upSprite);

			auto downSprite = cocos2d::Sprite::create();
			if (grade == 0)
				downSprite->setTexture("tower2-1-c.png");
			else if (grade == 1)
				downSprite->setTexture("tower2-2-c.png");
			else 
				downSprite->setTexture("tower2-3-a.png");
			downSprite->setPosition(cocos2d::Vec2(point.x, point.y - (size_of_tower / 2) - (size_of_up / 2)));
			downSprite->setContentSize(cocos2d::Size(size_of_up, size_of_up));
			this->addChild(downSprite);

			//��һ����������
			auto listene = cocos2d::EventListenerTouchOneByOne::create();
			listene->setSwallowTouches(true);
			listene->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
				auto touchlocation = this->convertToNodeSpace(touch->getLocation());
				// ������������������Ǯ�㹻
				if (upSprite->getBoundingBox().containsPoint(touchlocation) && ((allmoney >= cost_money_2[1] && grade == 0) || (allmoney >= cost_money_2[2] && grade == 1))) {
					upgrade();   //����
					listener->setSwallowTouches(true);
				}
				//�����������ٲ��ҵȼ�Ϊ0
				else if (downSprite->getBoundingBox().containsPoint(touchlocation) && grade == 0) {
					MoneyLayer* pMoney = dynamic_cast<MoneyLayer*>(scene->getChildByTag(TagMoney));
					pMoney->updateMoney(get_money_2[0]);
					removed();
					listener->setSwallowTouches(true);
				}
				//�����������ٲ��ҵȼ�Ϊ1
				else if (downSprite->getBoundingBox().containsPoint(touchlocation) && grade == 1) {
					MoneyLayer* pMoney = dynamic_cast<MoneyLayer*>(scene->getChildByTag(TagMoney));
					pMoney->updateMoney(get_money_2[1]);
					removed();
					listener->setSwallowTouches(true);
				}
				//�����������ٲ��ҵȼ�Ϊ2
				else if (downSprite->getBoundingBox().containsPoint(touchlocation) && grade == 2) {
					MoneyLayer* pMoney = dynamic_cast<MoneyLayer*>(scene->getChildByTag(TagMoney));
					pMoney->updateMoney(get_money_2[2]);
					removed();
					listener->setSwallowTouches(true);
				}
				else
					listener->setSwallowTouches(false);
				if (upSprite != NULL)
					this->removeChild(upSprite);  //���������ժ���
				if (downSprite != NULL)
					this->removeChild(downSprite);
				return false;
			};
			// ע�������
			_eventDispatcher->addEventListenerWithSceneGraphPriority(listene, upSprite);

		}
		return true;
	};

	// ע�������
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, turretSprite);


	//��ʱ��
	this->schedule([this](float dt) {
		this->shoot();
		}, internal, "ShootScheduler1"); //1.0fΪ���ʱ�䣬"ShootScheduler"Ϊ�������ı�ǩ��

	this->schedule([this](float dt) {
		this->check_enemy_in();
		}, 0.1, "ShootScheduler2"); //1.0fΪ���ʱ�䣬"ShootScheduler"Ϊ�������ı�ǩ��

	return true;

}



tower_3::tower_3(cocos2d::Vec2& a, GameScene* b)
{
	rotate = false;
	point = a;
	grade = 0;
	damage = damage_3[0];
	scene = b;
	MoneyLayer* pMoney = dynamic_cast<MoneyLayer*>(scene->getChildByTag(TagMoney));
	pMoney->updateMoney(-cost_money_3[0]);
}
void tower_3::upgrade()
{
	if (grade == 0) {
		turretSprite->setTexture("tower3-2.png");
		turretSprite->setContentSize(cocos2d::Size(size_of_tower, size_of_tower));
		damage = damage_3[1];
		MoneyLayer* pMoney = dynamic_cast<MoneyLayer*>(scene->getChildByTag(TagMoney));
		pMoney->updateMoney(-cost_money_3[1]);
	}
	else if (grade == 1) {
		turretSprite->setTexture("tower3-3.png");
		turretSprite->setContentSize(cocos2d::Size(size_of_tower, size_of_tower));
		damage = damage_3[2];
		MoneyLayer* pMoney = dynamic_cast<MoneyLayer*>(scene->getChildByTag(TagMoney));
		pMoney->updateMoney(-cost_money_3[2]);
	}
	grade++;
}
void tower_3::shoot()
{
	if (attack_stone != NULL) {    //����Ҫ�������ϰ���
		Bullet* bullet = Bullet_3::create(point, enemy_point, this, attack_stone); //������һ���ӵ��ࣿ
		this->addChild(bullet);
		bullet->move();  //���ӵ�������

	}
	if (attack_enemy != NULL) {    //����Ҫ�����ĵ���
		Bullet* bullet = Bullet_3::create(point, enemy_point, this, attack_enemy); //������һ���ӵ��ࣿ
		this->addChild(bullet);
		bullet->move();  //���ӵ�������

	}
}

bool tower_3::init()
{
	if (!Layer::init()) {
		return false;
	}
	// ��������и���ĳ�ʼ������
	turretSprite = cocos2d::Sprite::create("tower3-1.png");
	turretSprite->setPosition(point);
	turretSprite->setContentSize(cocos2d::Size(size_of_tower, size_of_tower));
	//turretSprite->setLocalZOrder(5);
	this->addChild(turretSprite);

	auto listener = cocos2d::EventListenerTouchOneByOne::create();

	//��һ���������� �����������������������ͼƬ
	listener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event){
		//��ȡ���λ��
		auto touchlocation = this->convertToNodeSpace(touch->getLocation());
		// �������Ƿ�������
		if (turretSprite->getBoundingBox().containsPoint(touchlocation)) {
			// ���������ִ������Ҫ�Ĳ���
			listener->setSwallowTouches(true);
			MoneyLayer* pMoney = dynamic_cast<MoneyLayer*>(scene->getChildByTag(TagMoney));
			int allmoney = pMoney->getMoney();
			auto upSprite = cocos2d::Sprite::create();
			if (allmoney >= cost_money_3[1] && grade == 0)
				upSprite->setTexture("tower3-1-a.png");
			else if (allmoney >= cost_money_3[2] && grade == 1)
				upSprite->setTexture("tower3-2-a.png");
			else if (grade == 0)
				upSprite->setTexture("tower3-1-b.png");
			else if(grade==1)
				upSprite->setTexture("tower3-2-b.png");
			else 
				upSprite->setTexture("tower3-3-a.png");
			upSprite->setPosition(cocos2d::Vec2(point.x, point.y + (size_of_tower / 2) + (size_of_up / 2)));
			upSprite->setContentSize(cocos2d::Size(size_of_up, size_of_up));
			//upSprite->setLocalZOrder(-1);
			this->addChild(upSprite);

			auto downSprite = cocos2d::Sprite::create();
			if (grade == 0)
				downSprite->setTexture("tower3-1-c.png");
			else if (grade == 1)
				downSprite->setTexture("tower3-2-c.png");
			else 
				downSprite->setTexture("tower3-3-a.png");
			downSprite->setPosition(cocos2d::Vec2(point.x, point.y - (size_of_tower / 2) - (size_of_up / 2)));
			downSprite->setContentSize(cocos2d::Size(size_of_up, size_of_up));
			//downSprite->setLocalZOrder(-1);
			this->addChild(downSprite);

			//��һ����������
			auto listene = cocos2d::EventListenerTouchOneByOne::create();
			listene->setSwallowTouches(true);
			listene->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
				auto touchLocation = this->convertToNodeSpace(touch->getLocation());
				// ������������������Ǯ�㹻
				if (upSprite->getBoundingBox().containsPoint(touchLocation) && ((allmoney >= cost_money_3[1] && grade == 0) || (allmoney >= cost_money_3[2] && grade == 1))) {
					upgrade();   //����
					listener->setSwallowTouches(true);
				}
				//�����������ٲ��ҵȼ�Ϊ0
				else if (downSprite->getBoundingBox().containsPoint(touchLocation) && grade == 0) {
					MoneyLayer* pMoney = dynamic_cast<MoneyLayer*>(scene->getChildByTag(TagMoney));
					pMoney->updateMoney(get_money_3[0]);
					removed();
					listener->setSwallowTouches(true);
				}
				//�����������ٲ��ҵȼ�Ϊ1
				else if (downSprite->getBoundingBox().containsPoint(touchLocation) && grade == 1) {
					MoneyLayer* pMoney = dynamic_cast<MoneyLayer*>(scene->getChildByTag(TagMoney));
					pMoney->updateMoney(get_money_3[1]);
					removed();
					listener->setSwallowTouches(true);
				}
				//�����������ٲ��ҵȼ�Ϊ2
				else if (downSprite->getBoundingBox().containsPoint(touchLocation) && grade == 2) {
					MoneyLayer* pMoney = dynamic_cast<MoneyLayer*>(scene->getChildByTag(TagMoney));
					pMoney->updateMoney(get_money_3[2]);
					removed();
					listener->setSwallowTouches(true);
				}
				else
					listener->setSwallowTouches(true);
				if (upSprite != NULL)
					this->removeChild(upSprite);  //���������ժ���
				if (downSprite != NULL)
					this->removeChild(downSprite);
				return false;
			};
			// ע�������
			_eventDispatcher->addEventListenerWithSceneGraphPriority(listene, upSprite);

		}
		return true;
	};

	// ע�������
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, turretSprite);


	//��ʱ��
	this->schedule([this](float dt) {
		this->shoot();
		}, internal, "ShootScheduler1"); //1.0fΪ���ʱ�䣬"ShootScheduler"Ϊ�������ı�ǩ��

	this->schedule([this](float dt) {
		this->check_enemy_in();
		}, 0.1, "ShootScheduler2"); //1.0fΪ���ʱ�䣬"ShootScheduler"Ϊ�������ı�ǩ��

	return true;

}