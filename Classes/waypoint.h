#pragma once//��Ҫд����
#include "cocos/math/Vec2.h"
#include "cocos2d.h"
#include "cocos/2d/CCDrawNode.h"
#include<cmath>

bool crash(cocos2d::Vec2 a, cocos2d::Vec2 b);//�ж������Ƿ���ײ

class waypoint :public cocos2d::Ref {
public:
	waypoint(cocos2d::Vec2 m_pos);//���ú���λ��
	const cocos2d::Vec2 getpos() {return p;}//�õ���ǰ�����λ��
	void setNext(waypoint* m_next) { nextp = m_next; }//�����¸������ָ��
	waypoint* getNext() { return nextp; }//�õ��¸�����ָ��

	void addWayPoint1(cocos2d::Vector<waypoint*>& m_waypointList, cocos2d::Sprite* monster);//��ӳ�ʼ�����еĺ���

protected:
	cocos2d::Vec2 p;//��ά����
	waypoint* nextp;//��һ����
};