#include "tower.h"
#include "Bullet.h"
#include "TowerLayer.h"
#include <string>
#include "stone.h"
#include "enemy.h"


void tower::add_money()
{
	scene->_pMoney->updateMoney((grade + 1) * 5);
}

void tower::removed()
{
	scene->removeTower(this);
}

void tower::set_rotation(double angle)   //��������Ӧ�ľ��������ת��Ҫ����һ���Ƕ���
{
	auto rotateTo = cocos2d::RotateTo::create(1.0f, angle);  //��1s����ת��angle�Ƕ�
	turretSprite->runAction(rotateTo);
}

void tower::rotation()  
{
	if ((attack_enemy != NULL) || (attack_stone != NULL)) {     //����ָ���Ĺ������˻�����
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
}

void tower::stone_killed()
{
	if (attack_stone != NULL) {
		attack_stone = NULL;
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
	rotation();
	if (attack_stone != NULL); //�����attack_stone�Ļ������ý��к������
	else if (attack_enemy) {
		enemy_point = attack_enemy->getpos();  //�õ�Ҫ�����ĵ��˵�λ������
		double dx = point.x - enemy_point.x;
		double dy = point.y - enemy_point.y;
		double dis = sqrt(dx * dx + dy * dy);  //���㹥�����˺�����֮��ľ���
		if (dis >= range) {                    //��������Ѿ��߳����ҵĹ�����Χ���ҾͰ����Ƴ�ȥ
			enemy_out();
		}
	}
	else {  
		for (enemy* child : scene->_pMonsters->getChildren()) {
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

bool tower::if_continue(int a)
{
	if ((a == 1 && attack_stone != NULL) || (a == 2 && attack_enemy != NULL))
		return true;
	return false;
}

tower_1::tower_1(cocos2d::Vec2& a,TowerLayer* b)
{
	point = a;
	grade = 0;
	damage = damage_1[0];
	scene = b;
	scene->_pMoney->updateMoney(-cost_money_1[0]);
}

void tower_1::upgrade()
{
	if (grade == 0) {
		turretSprite->setTexture("tower1-2.png");
		turretSprite->setContentSize(cocos2d::Size(size_of_tower, size_of_tower));
		damage = damage_1[1];
		scene->_pMoney->updateMoney(-cost_money_1[1]);
	}
	else if (grade == 1) {
		turretSprite->setTexture("tower1-3.png");
		turretSprite->setContentSize(cocos2d::Size(size_of_tower, size_of_tower));
		damage = damage_1[2];
		scene->_pMoney->updateMoney(-cost_money_1[2]);
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
	auto listener = cocos2d::EventListenerMouse::create(); 
	//��һ����������
	listener->onMouseDown = [=](cocos2d::Event *event){
		auto e = static_cast<cocos2d::EventMouse*>(event);
		float x = e->getCursorX();
		float y = e->getCursorY();
		// �������Ƿ�������
		if( turretSprite ->getBoundingBox().containsPoint(cocos2d::Vec2(x, y))) {
			// ���������ִ������Ҫ�Ĳ���
			//��һ�¹ع���ô��1-a��1-bһֱ��ʾ��

			int allmoney = scene->_pMoney->getMoney();
			//��������������ֵĶ������͹ع�����һ���������ˣ�
			if (grade == 0 || grade == 1) {  
				if ((allmoney >= cost_money_1[1] && grade == 0) || (allmoney >= cost_money_1[2] && grade == 1)) {   //����㹻�����Ļ�
					std::string pic_1;
					if (grade == 0) {
						pic_1 = "tower1-1-a.png";
					}
					else {
						pic_1 = "tower1-2-a.png";
					}
					auto upSprite = cocos2d::Sprite::create(pic_1);
					upSprite->setPosition(cocos2d::Vec2(point.x, point.y + (size_of_tower / 2) + (size_of_up / 2)));
					upSprite->setContentSize(cocos2d::Size(size_of_up, size_of_up));
					this->addChild(upSprite);

					std::string pic_2;
					if (grade == 0) {
						pic_2 = "tower1-1-c.png";
					}
					else {
						pic_2 = "tower1-2-c.png";
					}
					auto downSprite = cocos2d::Sprite::create(pic_2);
					downSprite->setPosition(cocos2d::Vec2(point.x, point.y - (size_of_tower / 2) - (size_of_up / 2)));
					downSprite->setContentSize(cocos2d::Size(size_of_up, size_of_up));
					this->addChild(downSprite);


					//��һ����������
					auto listene = cocos2d::EventListenerMouse::create(); 
					listene->onMouseDown = [=](cocos2d::Event *event){
						auto ee = static_cast<cocos2d::EventMouse*>(event);
						float ex = ee->getCursorX();
						float ey = ee->getCursorY();
						// �������Ƿ�������
						if( upSprite ->getBoundingBox().containsPoint(cocos2d::Vec2(ex, ey))) {
							upgrade();   //����
							this->removeChild(upSprite);  //���������ժ���
							this->removeChild(downSprite);
						}
					};
					// ע�������
					_eventDispatcher->addEventListenerWithSceneGraphPriority(listene,  upSprite);


					
					//��һ����������
					auto listen = cocos2d::EventListenerMouse::create(); 
					listen->onMouseDown = [=](cocos2d::Event *event){
						auto ee = static_cast<cocos2d::EventMouse*>(event);
						float ex = ee->getCursorX();
						float ey = ee->getCursorY();
						// �������Ƿ�������
						if( downSprite ->getBoundingBox().containsPoint(cocos2d::Vec2(ex, ey))) {
							// ���������ִ������Ҫ�Ĳ���
							//��û��ȫ���
							if (grade == 0) {
								scene->_pMoney->updateMoney( get_money_1[0]);
							}
							else {
								scene->_pMoney->updateMoney( get_money_1[1]);
							}
							this->removeChild(upSprite);  //���������ժ���
							this->removeChild(downSprite);
							removed();
							
						}
					};
					// ע�������
					_eventDispatcher->addEventListenerWithSceneGraphPriority(listen,  downSprite);

				}
				else {  //Ǯ����������
					std::string pic_1;
					if (grade == 0) {
						pic_1 = "tower1-1-b.png";
					}
					else {
						pic_1 = "tower1-2-b.png";
					}
					auto upSprite = cocos2d::Sprite::create(pic_1);
					upSprite->setPosition(cocos2d::Vec2(point.x, point.y + (size_of_tower / 2) + (size_of_up / 2)));
					upSprite->setContentSize(cocos2d::Size(size_of_up, size_of_up));
					this->addChild(upSprite);


					std::string pic_2;
					if (grade == 0) {
						pic_2 = "tower1-1-c.png";
					}
					else {
						pic_2 = "tower1-2-c.png";
					}
					auto downSprite = cocos2d::Sprite::create(pic_2);
					downSprite->setPosition(cocos2d::Vec2(point.x, point.y - (size_of_tower / 2) - (size_of_up / 2)));
					downSprite->setContentSize(cocos2d::Size(size_of_up, size_of_up));
					this->addChild(downSprite);
					//��һ����������
					auto listen = cocos2d::EventListenerMouse::create(); 
					listen->onMouseDown = [=](cocos2d::Event *event){
						auto ee = static_cast<cocos2d::EventMouse*>(event);
						float ex = ee->getCursorX();
						float ey = ee->getCursorY();
						// �������Ƿ�������
						if( downSprite ->getBoundingBox().containsPoint(cocos2d::Vec2(ex, ey))) {
							// ���������ִ������Ҫ�Ĳ���
							//��û��ȫ���
							if (grade == 0) {
								scene->_pMoney->updateMoney( get_money_1[0]);
							}
							else {
								scene->_pMoney->updateMoney( get_money_1[1]);
							}
							this->removeChild(upSprite);  //���������ժ���
							this->removeChild(downSprite);
							removed();
							
						}
					};
					// ע�������
					_eventDispatcher->addEventListenerWithSceneGraphPriority(listen,  downSprite);


				}
			}
			else {  //�Ѿ�������߼�
				auto upSprite = cocos2d::Sprite::create("tower1-3-a.png");
				upSprite->setPosition(cocos2d::Vec2(point.x, point.y + (size_of_tower / 2) + (size_of_up / 2)));
				upSprite->setContentSize(cocos2d::Size(size_of_up, size_of_up));
				this->addChild(upSprite);
				auto downSprite = cocos2d::Sprite::create("tower1-3-b.png");
				downSprite->setPosition(cocos2d::Vec2(point.x, point.y - (size_of_tower / 2) - (size_of_up / 2)));
				downSprite->setContentSize(cocos2d::Size(size_of_up, size_of_up));
				this->addChild(downSprite);

				//��һ����������
				auto listen = cocos2d::EventListenerMouse::create(); 
				listen->onMouseDown = [=](cocos2d::Event *event){
					auto ee = static_cast<cocos2d::EventMouse*>(event);
					float ex = ee->getCursorX();
					float ey = ee->getCursorY();
					// �������Ƿ�������
					if( downSprite ->getBoundingBox().containsPoint(cocos2d::Vec2(ex, ey))) {
						// ���������ִ������Ҫ�Ĳ���
						//��û��ȫ���
						
							scene->_pMoney->updateMoney( get_money_1[2]);
							this->removeChild(upSprite);  //���������ժ���
							this->removeChild(downSprite);
							removed();
					

						
					}
				};
				// ע�������
				_eventDispatcher->addEventListenerWithSceneGraphPriority(listen,  downSprite);

			}



		}
	};

	// ע�������
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,  turretSprite );



	//��ʱ��
	this->schedule([this](float dt) {
		this->shoot();
		},  internal, "ShootScheduler"); //1.0fΪ���ʱ�䣬"ShootScheduler"Ϊ�������ı�ǩ��

	this->schedule([this](float dt) {
		this->check_enemy_in();
		},  0.01, "ShootScheduler"); //1.0fΪ���ʱ�䣬"ShootScheduler"Ϊ�������ı�ǩ��

	return true;
		
}



tower_2::tower_2(cocos2d::Vec2& a,TowerLayer*  b)
{
	point = a;
	grade = 0;
	damage = damage_2[0];
	scene = b;
	scene->_pMoney->updateMoney(-cost_money_2[0]);
}
void tower_2::upgrade()
{
	if (grade == 0) {
		turretSprite->setTexture("tower2-2.png");
		turretSprite->setContentSize(cocos2d::Size(size_of_tower, size_of_tower));
		damage = damage_2[1];
		scene->_pMoney->updateMoney(-cost_money_2[1]);
	}
	else if (grade == 1) {
		turretSprite->setTexture("tower2-3.png");
		turretSprite->setContentSize(cocos2d::Size(size_of_tower, size_of_tower));
		damage = damage_2[2];
		scene->_pMoney->updateMoney(-cost_money_2[2]);
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
	auto listener = cocos2d::EventListenerMouse::create(); 
	//��һ����������
	listener->onMouseDown = [=](cocos2d::Event *event){
		auto e = static_cast<cocos2d::EventMouse*>(event);
		float x = e->getCursorX();
		float y = e->getCursorY();
		// �������Ƿ�������
		if( turretSprite ->getBoundingBox().containsPoint(cocos2d::Vec2(x, y))) {
			// ���������ִ������Ҫ�Ĳ���
			//��һ�¹ع���ô��1-a��1-bһֱ��ʾ��

			int allmoney = scene->_pMoney->getMoney();
			//��������������ֵĶ������͹ع�����һ���������ˣ�
			if (grade == 0 || grade == 1) {  
				if ((allmoney >= cost_money_2[1] && grade == 0) || (allmoney >= cost_money_2[2] && grade == 1)) {   //����㹻�����Ļ�
					std::string pic_1;
					if (grade == 0) {
						pic_1 = "tower2-1-a.png";
					}
					else {
						pic_1 = "tower2-2-a.png";
					}
					auto upSprite = cocos2d::Sprite::create(pic_1);
					upSprite->setPosition(cocos2d::Vec2(point.x, point.y + (size_of_tower / 2) + (size_of_up / 2)));
					upSprite->setContentSize(cocos2d::Size(size_of_up, size_of_up));
					this->addChild(upSprite);

					std::string pic_2;
					if (grade == 0) {
						pic_2 = "tower2-1-c.png";
					}
					else {
						pic_2 = "tower2-2-c.png";
					}
					auto downSprite = cocos2d::Sprite::create(pic_2);
					downSprite->setPosition(cocos2d::Vec2(point.x, point.y - (size_of_tower / 2) - (size_of_up / 2)));
					downSprite->setContentSize(cocos2d::Size(size_of_up, size_of_up));
					this->addChild(downSprite);


					//��һ����������
					auto listene = cocos2d::EventListenerMouse::create(); 
					listene->onMouseDown = [=](cocos2d::Event *event){
						auto ee = static_cast<cocos2d::EventMouse*>(event);
						float ex = ee->getCursorX();
						float ey = ee->getCursorY();
						// �������Ƿ�������
						if( upSprite ->getBoundingBox().containsPoint(cocos2d::Vec2(ex, ey))) {
							upgrade();   //����
							this->removeChild(upSprite);  //���������ժ���
							this->removeChild(downSprite);
						}
					};
					// ע�������
					_eventDispatcher->addEventListenerWithSceneGraphPriority(listene,  upSprite);



					//��һ����������
					auto listen = cocos2d::EventListenerMouse::create(); 
					listen->onMouseDown = [=](cocos2d::Event *event){
						auto ee = static_cast<cocos2d::EventMouse*>(event);
						float ex = ee->getCursorX();
						float ey = ee->getCursorY();
						// �������Ƿ�������
						if( downSprite ->getBoundingBox().containsPoint(cocos2d::Vec2(ex, ey))) {
							// ���������ִ������Ҫ�Ĳ���
							//��û��ȫ���
							if (grade == 0) {
								scene->_pMoney->updateMoney( get_money_2[0]);
							}
							else {
								scene->_pMoney->updateMoney( get_money_2[1]);
							}
							this->removeChild(upSprite);  //���������ժ���
							this->removeChild(downSprite);
							removed();

						}
					};
					// ע�������
					_eventDispatcher->addEventListenerWithSceneGraphPriority(listen,  downSprite);

				}
				else {  //Ǯ����������
					std::string pic_1;
					if (grade == 0) {
						pic_1 = "tower2-1-b.png";
					}
					else {
						pic_1 = "tower2-2-b.png";
					}
					auto upSprite = cocos2d::Sprite::create(pic_1);
					upSprite->setPosition(cocos2d::Vec2(point.x, point.y + (size_of_tower / 2) + (size_of_up / 2)));
					upSprite->setContentSize(cocos2d::Size(size_of_up, size_of_up));
					this->addChild(upSprite);


					std::string pic_2;
					if (grade == 0) {
						pic_2 = "tower2-1-c.png";
					}
					else {
						pic_2 = "tower2-2-c.png";
					}
					auto downSprite = cocos2d::Sprite::create(pic_2);
					downSprite->setPosition(cocos2d::Vec2(point.x, point.y - (size_of_tower / 2) - (size_of_up / 2)));
					downSprite->setContentSize(cocos2d::Size(size_of_up, size_of_up));
					this->addChild(downSprite);
					//��һ����������
					auto listen = cocos2d::EventListenerMouse::create(); 
					listen->onMouseDown = [=](cocos2d::Event *event){
						auto ee = static_cast<cocos2d::EventMouse*>(event);
						float ex = ee->getCursorX();
						float ey = ee->getCursorY();
						// �������Ƿ�������
						if( downSprite ->getBoundingBox().containsPoint(cocos2d::Vec2(ex, ey))) {
							// ���������ִ������Ҫ�Ĳ���
							//��û��ȫ���
							if (grade == 0) {
								scene->_pMoney->updateMoney( get_money_2[0]);
							}
							else {
								scene->_pMoney->updateMoney( get_money_2[1]);
							}
							this->removeChild(upSprite);  //���������ժ���
							this->removeChild(downSprite);
							removed();

						}
					};
					// ע�������
					_eventDispatcher->addEventListenerWithSceneGraphPriority(listen,  downSprite);


				}
			}
			else {  //�Ѿ�������߼�
				auto upSprite = cocos2d::Sprite::create("tower2-3-a.png");
				upSprite->setPosition(cocos2d::Vec2(point.x, point.y + (size_of_tower / 2) + (size_of_up / 2)));
				upSprite->setContentSize(cocos2d::Size(size_of_up, size_of_up));
				this->addChild(upSprite);
				auto downSprite = cocos2d::Sprite::create("tower2-3-b.png");
				downSprite->setPosition(cocos2d::Vec2(point.x, point.y - (size_of_tower / 2) - (size_of_up / 2)));
				downSprite->setContentSize(cocos2d::Size(size_of_up, size_of_up));
				this->addChild(downSprite);

				//��һ����������
				auto listen = cocos2d::EventListenerMouse::create(); 
				listen->onMouseDown = [=](cocos2d::Event *event){
					auto ee = static_cast<cocos2d::EventMouse*>(event);
					float ex = ee->getCursorX();
					float ey = ee->getCursorY();
					// �������Ƿ�������
					if( downSprite ->getBoundingBox().containsPoint(cocos2d::Vec2(ex, ey))) {
						// ���������ִ������Ҫ�Ĳ���
						//��û��ȫ���
						scene->_pMoney->updateMoney(get_money_2[2]);
						this->removeChild(upSprite);  //���������ժ���
						this->removeChild(downSprite);
						removed();

					}
				};
				// ע�������
				_eventDispatcher->addEventListenerWithSceneGraphPriority(listen,  downSprite);

			}



		}
	};

	// ע�������
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,  turretSprite );



	//��ʱ��
	this->schedule([this](float dt) {
		this->shoot();
		},  internal, "ShootScheduler"); //1.0fΪ���ʱ�䣬"ShootScheduler"Ϊ�������ı�ǩ��

	this->schedule([this](float dt) {
		this->check_enemy_in();
		},  0.01, "ShootScheduler"); //1.0fΪ���ʱ�䣬"ShootScheduler"Ϊ�������ı�ǩ��

	return true;

}






tower_3::tower_3(cocos2d::Vec2& a,TowerLayer*  b)
{
	point = a;
	grade = 0;
	damage = damage_3[0];
	scene = b;
	scene->_pMoney->updateMoney(-cost_money_3[0]);
}
void tower_3::upgrade()
{
	if (grade == 0) {
		turretSprite->setTexture("tower3-2.png");
		turretSprite->setContentSize(cocos2d::Size(size_of_tower, size_of_tower));
		damage = damage_3[1];
		scene->_pMoney->updateMoney(-cost_money_3[1]);
	}
	else if (grade == 1) {
		turretSprite->setTexture("tower3-3.png");
		turretSprite->setContentSize(cocos2d::Size(size_of_tower, size_of_tower));
		damage = damage_3[2];
		scene->_pMoney->updateMoney(-cost_money_3[2]);
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
	this->addChild(turretSprite);
	auto listener = cocos2d::EventListenerMouse::create(); 
	//��һ����������
	listener->onMouseDown = [=](cocos2d::Event *event){
		auto e = static_cast<cocos2d::EventMouse*>(event);
		float x = e->getCursorX();
		float y = e->getCursorY();
		// �������Ƿ�������
		if( turretSprite ->getBoundingBox().containsPoint(cocos2d::Vec2(x, y))) {
			// ���������ִ������Ҫ�Ĳ���
			//��һ�¹ع���ô��1-a��1-bһֱ��ʾ
			int allmoney = scene->_pMoney->getMoney();
			//��������������ֵĶ������͹ع�����һ���������ˣ�
			if (grade == 0 || grade == 1) {  
				if ((allmoney >= cost_money_3[1] && grade == 0) || (allmoney >= cost_money_3[2] && grade == 1)) {   //����㹻�����Ļ�
					std::string pic_1;
					if (grade == 0) {
						pic_1 = "tower3-1-a.png";
					}
					else {
						pic_1 = "tower3-2-a.png";
					}
					auto upSprite = cocos2d::Sprite::create(pic_1);
					upSprite->setPosition(cocos2d::Vec2(point.x, point.y + (size_of_tower / 2) + (size_of_up / 2)));
					upSprite->setContentSize(cocos2d::Size(size_of_up, size_of_up));
					this->addChild(upSprite);

					std::string pic_2;
					if (grade == 0) {
						pic_2 = "tower3-1-c.png";
					}
					else {
						pic_2 = "tower3-2-c.png";
					}
					auto downSprite = cocos2d::Sprite::create(pic_2);
					downSprite->setPosition(cocos2d::Vec2(point.x, point.y - (size_of_tower / 2) - (size_of_up / 2)));
					downSprite->setContentSize(cocos2d::Size(size_of_up, size_of_up));
					this->addChild(downSprite);


					//��һ����������
					auto listene = cocos2d::EventListenerMouse::create(); 
					listene->onMouseDown = [=](cocos2d::Event *event){
						auto ee = static_cast<cocos2d::EventMouse*>(event);
						float ex = ee->getCursorX();
						float ey = ee->getCursorY();
						// �������Ƿ�������
						if( upSprite ->getBoundingBox().containsPoint(cocos2d::Vec2(ex, ey))) {
							upgrade();   //����
							this->removeChild(upSprite);  //���������ժ���
							this->removeChild(downSprite);
						}
					};
					// ע�������
					_eventDispatcher->addEventListenerWithSceneGraphPriority(listene,  upSprite);



					//��һ����������
					auto listen = cocos2d::EventListenerMouse::create(); 
					listen->onMouseDown = [=](cocos2d::Event *event){
						auto ee = static_cast<cocos2d::EventMouse*>(event);
						float ex = ee->getCursorX();
						float ey = ee->getCursorY();
						// �������Ƿ�������
						if( downSprite ->getBoundingBox().containsPoint(cocos2d::Vec2(ex, ey))) {
							// ���������ִ������Ҫ�Ĳ���
							//��û��ȫ���
							if (grade == 0) {
								scene->_pMoney->updateMoney( get_money_3[0]);
							}
							else {
								scene->_pMoney->updateMoney( get_money_3[1]);
							}
							this->removeChild(upSprite);  //���������ժ���
							this->removeChild(downSprite);
							removed();

						}
					};
					// ע�������
					_eventDispatcher->addEventListenerWithSceneGraphPriority(listen,  downSprite);

				}
				else {  //Ǯ����������
					std::string pic_1;
					if (grade == 0) {
						pic_1 = "tower3-1-b.png";
					}
					else {
						pic_1 = "tower3-2-b.png";
					}
					auto upSprite = cocos2d::Sprite::create(pic_1);
					upSprite->setPosition(cocos2d::Vec2(point.x, point.y + (size_of_tower / 2) + (size_of_up / 2)));
					upSprite->setContentSize(cocos2d::Size(size_of_up, size_of_up));
					this->addChild(upSprite);


					std::string pic_2;
					if (grade == 0) {
						pic_2 = "tower3-1-c.png";
					}
					else {
						pic_2 = "tower3-2-c.png";
					}
					auto downSprite = cocos2d::Sprite::create(pic_2);
					downSprite->setPosition(cocos2d::Vec2(point.x, point.y - (size_of_tower / 2) - (size_of_up / 2)));
					downSprite->setContentSize(cocos2d::Size(size_of_up, size_of_up));
					this->addChild(downSprite);

					//��һ����������
					auto listene = cocos2d::EventListenerMouse::create(); 
					listene->onMouseDown = [=](cocos2d::Event *event){
						auto ee = static_cast<cocos2d::EventMouse*>(event);
						float ex = ee->getCursorX();
						float ey = ee->getCursorY();
						// �������Ƿ�������
						if( upSprite ->getBoundingBox().containsPoint(cocos2d::Vec2(ex, ey))) {
							this->removeChild(upSprite);  //���������ժ���
							this->removeChild(downSprite);
						}
					};
					// ע�������
					_eventDispatcher->addEventListenerWithSceneGraphPriority(listene,  upSprite);

					//��һ����������
					auto listen = cocos2d::EventListenerMouse::create(); 
					listen->onMouseDown = [=](cocos2d::Event *event){
						auto ee = static_cast<cocos2d::EventMouse*>(event);
						float ex = ee->getCursorX();
						float ey = ee->getCursorY();
						// �������Ƿ�������
						if( downSprite ->getBoundingBox().containsPoint(cocos2d::Vec2(ex, ey))) {
							// ���������ִ������Ҫ�Ĳ���
							//��û��ȫ���
							if (grade == 0) {
								scene->_pMoney->updateMoney( get_money_3[0]);
							}
							else {
								scene->_pMoney->updateMoney( get_money_3[1]);
							}
							this->removeChild(upSprite);  //���������ժ���
							this->removeChild(downSprite);
							removed();

						}
					};
					// ע�������
					_eventDispatcher->addEventListenerWithSceneGraphPriority(listen,  downSprite);


				}
			}
			else {  //�Ѿ�������߼�
				auto upSprite = cocos2d::Sprite::create("tower3-3-a.png");
				upSprite->setPosition(cocos2d::Vec2(point.x, point.y + (size_of_tower / 2) + (size_of_up / 2)));
				upSprite->setContentSize(cocos2d::Size(size_of_up, size_of_up));
				this->addChild(upSprite);
				auto downSprite = cocos2d::Sprite::create("tower3-3-b.png");
				downSprite->setPosition(cocos2d::Vec2(point.x, point.y - (size_of_tower / 2) - (size_of_up / 2)));
				downSprite->setContentSize(cocos2d::Size(size_of_up, size_of_up));
				this->addChild(downSprite);


				//��һ����������
				auto listene = cocos2d::EventListenerMouse::create(); 
				listene->onMouseDown = [=](cocos2d::Event *event){
					auto ee = static_cast<cocos2d::EventMouse*>(event);
					float ex = ee->getCursorX();
					float ey = ee->getCursorY();
					// �������Ƿ�������
					if( upSprite ->getBoundingBox().containsPoint(cocos2d::Vec2(ex, ey))) {
						this->removeChild(upSprite);  //���������ժ���
						this->removeChild(downSprite);
					}
				};

				//��һ����������
				auto listen = cocos2d::EventListenerMouse::create(); 
				listen->onMouseDown = [=](cocos2d::Event *event){
					auto ee = static_cast<cocos2d::EventMouse*>(event);
					float ex = ee->getCursorX();
					float ey = ee->getCursorY();
					// �������Ƿ�������
					if( downSprite ->getBoundingBox().containsPoint(cocos2d::Vec2(ex, ey))) {
						// ���������ִ������Ҫ�Ĳ���
						//��û��ȫ���
						
						scene->_pMoney->updateMoney(get_money_3[2]);
					
						this->removeChild(upSprite);  //���������ժ���
						this->removeChild(downSprite);
						removed();

					}
				};
				// ע�������
				_eventDispatcher->addEventListenerWithSceneGraphPriority(listen,  downSprite);

			}



		}
	};

	// ע�������
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,  turretSprite );



	//��ʱ��
	this->schedule([this](float dt) {
		this->shoot();
		},  internal, "ShootScheduler"); //1.0fΪ���ʱ�䣬"ShootScheduler"Ϊ�������ı�ǩ��

	this->schedule([this](float dt) {
		this->check_enemy_in();
		},  0.01, "ShootScheduler"); //1.0fΪ���ʱ�䣬"ShootScheduler"Ϊ�������ı�ǩ��


	return true;
}

