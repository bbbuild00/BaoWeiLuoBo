#pragma once//还要写两关
#include "cocos/math/Vec2.h"
#include "cocos2d.h"
#include "cocos/2d/CCDrawNode.h"
#include<cmath>

class waypoint ;

bool crash(cocos2d::Vec2 a, cocos2d::Vec2 b);//判断两点是否相撞

void addWayPoint1(cocos2d::Vector<waypoint*>& m_waypointList, cocos2d::Sprite* monster);//添加初始化所有的航点

class waypoint :public cocos2d::Ref {
public:
	//waypoint();//设置航点位置
	waypoint(cocos2d::Vec2 m_pos);//设置航点位置
	const cocos2d::Vec2 getpos() {return p;}//得到当前航点的位置
	void setNext(waypoint* m_next) { nextp = m_next; }//设置下个航点的指针
	waypoint* getNext() { return nextp; }//得到下个航点指针

	

protected:
	cocos2d::Vec2 p;//二维坐标
	waypoint* nextp;//下一航点
};