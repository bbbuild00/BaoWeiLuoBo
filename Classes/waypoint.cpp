#include"waypoint.h"

waypoint::waypoint(cocos2d::Vec2 m_pos) {
	p = m_pos;
	nextp = NULL;
}

bool crash(cocos2d::Vec2 a, cocos2d::Vec2 b) {//Åö×²¼ì²â
	float x = a.x - b.x;
    float y = a.y - b.y;
    float s = x * x + y * y;//¼ÆËãÅ·ÊÏ¾àÀëµÄÆ½·½
	if (s <= 100) {
		return true;
	}
	return false;
}

void addWayPoint1(cocos2d::Vector<waypoint*>& m_waypointList, cocos2d::Sprite* monster) {
    waypoint* waypoint1 = new waypoint(cocos2d::Vec2(2 * 75 - 10, 5 * 75));
    m_waypointList.pushBack(waypoint1);

    waypoint* waypoint2 = new waypoint(cocos2d::Vec2(2 * 75 - 10, 4 * 75));
    waypoint1->setNext(waypoint2);
    m_waypointList.pushBack(waypoint2);

    waypoint* waypoint3 = new waypoint(cocos2d::Vec2(2 * 75 - 10, 3 * 75));
    waypoint2->setNext(waypoint3);
    m_waypointList.pushBack(waypoint3);

    waypoint* waypoint4 = new waypoint(cocos2d::Vec2(3 * 75 - 10, 3 * 75));
    waypoint3->setNext(waypoint4);
    m_waypointList.pushBack(waypoint4);

    waypoint* waypoint5 = new waypoint(cocos2d::Vec2(4 * 75 - 10, 3 * 75));
    waypoint4->setNext(waypoint5);
    m_waypointList.pushBack(waypoint5);

    waypoint* waypoint6 = new waypoint(cocos2d::Vec2(5 * 75 - 10, 3 * 75));
    waypoint5->setNext(waypoint6);
    m_waypointList.pushBack(waypoint6);

    waypoint* waypoint7 = new waypoint(cocos2d::Vec2(5 * 75 - 10, 4 * 75));
    waypoint6->setNext(waypoint7);
    m_waypointList.pushBack(waypoint7);

    waypoint* waypoint8 = new waypoint(cocos2d::Vec2(6 * 75 - 10, 4 * 75));
    waypoint7->setNext(waypoint8);
    m_waypointList.pushBack(waypoint8);

    waypoint* waypoint9 = new waypoint(cocos2d::Vec2(7 * 75 - 10, 4 * 75));
    waypoint8->setNext(waypoint9);
    m_waypointList.pushBack(waypoint9);

    waypoint* waypoint10 = new waypoint(cocos2d::Vec2(8 * 75 - 10, 4 * 75));
    waypoint9->setNext(waypoint10);
    m_waypointList.pushBack(waypoint10);

    waypoint* waypoint11 = new waypoint(cocos2d::Vec2(8 * 75 - 10, 3 * 75));
    waypoint10->setNext(waypoint11);
    m_waypointList.pushBack(waypoint11);

    waypoint* waypoint12 = new waypoint(cocos2d::Vec2(9 * 75 - 10, 3 * 75));
    waypoint11->setNext(waypoint12);
    m_waypointList.pushBack(waypoint12);

    waypoint* waypoint13 = new waypoint(cocos2d::Vec2(10 * 75 - 10, 3 * 75));
    waypoint12->setNext(waypoint13);
    m_waypointList.pushBack(waypoint13);

    waypoint* waypoint14 = new waypoint(cocos2d::Vec2(11 * 75 - 10, 3 * 75));
    waypoint13->setNext(waypoint14);
    m_waypointList.pushBack(waypoint14);

    waypoint* waypoint15 = new waypoint(cocos2d::Vec2(11 * 75 - 10, 4 * 75));
    waypoint14->setNext(waypoint15);
    m_waypointList.pushBack(waypoint15);

    waypoint* waypoint16 = new waypoint(cocos2d::Vec2(11 * 75 - 10, 5 * 75));
    waypoint15->setNext(waypoint16);
    m_waypointList.pushBack(waypoint16);

    waypoint* waypoint17 = new waypoint(cocos2d::Vec2(11 * 75 - 10, 6 * 75));
    waypoint16->setNext(waypoint17);
    m_waypointList.pushBack(waypoint17);
}

void addWayPoint2(cocos2d::Vector<waypoint*>& m_waypointList, cocos2d::Sprite* monster) {
    waypoint* waypoint1 = new waypoint(cocos2d::Vec2(4 * 75 - 10, 6* 75));
    m_waypointList.pushBack(waypoint1);

    waypoint* waypoint2 = new waypoint(cocos2d::Vec2(5 * 75 - 10, 6 * 75));
    waypoint1->setNext(waypoint2);
    m_waypointList.pushBack(waypoint2);

    waypoint* waypoint3 = new waypoint(cocos2d::Vec2(6* 75 - 10, 6 * 75));
    waypoint2->setNext(waypoint3);
    m_waypointList.pushBack(waypoint3);

    waypoint* waypoint4 = new waypoint(cocos2d::Vec2(7 * 75 - 10, 6 * 75));
    waypoint3->setNext(waypoint4);
    m_waypointList.pushBack(waypoint4);

    waypoint* waypoint5 = new waypoint(cocos2d::Vec2(8 * 75 - 10, 6 * 75));
    waypoint4->setNext(waypoint5);
    m_waypointList.pushBack(waypoint5);

    waypoint* waypoint6 = new waypoint(cocos2d::Vec2(9* 75 +60, 6 * 75));
    waypoint5->setNext(waypoint6);
    m_waypointList.pushBack(waypoint6);

    

    waypoint* waypoint7 = new waypoint(cocos2d::Vec2(9 * 75 + 60, 5 * 75));
    waypoint6->setNext(waypoint7);
    m_waypointList.pushBack(waypoint7);

    waypoint* waypoint8 = new waypoint(cocos2d::Vec2(9 * 75 + 60, 4 * 75));
    waypoint7->setNext(waypoint8);
    m_waypointList.pushBack(waypoint8);

    waypoint* waypoint9 = new waypoint(cocos2d::Vec2(8 * 75 -10, 4* 75));
    waypoint8->setNext(waypoint9);
    m_waypointList.pushBack(waypoint9);

    waypoint* waypoint10 = new waypoint(cocos2d::Vec2(7 * 75 - 10, 4* 75));
    waypoint9->setNext(waypoint10);
    m_waypointList.pushBack(waypoint10);

    waypoint* waypoint11 = new waypoint(cocos2d::Vec2(6* 75 - 10, 4 * 75));
    waypoint10->setNext(waypoint11);
    m_waypointList.pushBack(waypoint11);

    waypoint* waypoint12 = new waypoint(cocos2d::Vec2(5* 75 - 10, 4 * 75));
    waypoint11->setNext(waypoint12);
    m_waypointList.pushBack(waypoint12);

    waypoint* waypoint13 = new waypoint(cocos2d::Vec2(4 * 75 - 10, 4 * 75));
    waypoint12->setNext(waypoint13);
    m_waypointList.pushBack(waypoint13);

    waypoint* waypoint14 = new waypoint(cocos2d::Vec2(3 * 75 - 10, 4* 75));
    waypoint13->setNext(waypoint14);
    m_waypointList.pushBack(waypoint14);

    waypoint* waypoint15 = new waypoint(cocos2d::Vec2(2 * 75 +60, 4 * 75));
    waypoint14->setNext(waypoint15);
    m_waypointList.pushBack(waypoint15);

    waypoint* waypoint16 = new waypoint(cocos2d::Vec2(2 * 75 + 60, 3* 75));
    waypoint15->setNext(waypoint16);
    m_waypointList.pushBack(waypoint16);

    waypoint* waypoint17 = new waypoint(cocos2d::Vec2(2 * 75 + 60, 2 * 75));
    waypoint16->setNext(waypoint17);
    m_waypointList.pushBack(waypoint17);

    waypoint* waypoint18 = new waypoint(cocos2d::Vec2(3 * 75 - 10, 2* 75));
    waypoint17->setNext(waypoint18);
    m_waypointList.pushBack(waypoint18);

    waypoint* waypoint19 = new waypoint(cocos2d::Vec2(4 * 75 - 10, 2* 75));
    waypoint18->setNext(waypoint19);
    m_waypointList.pushBack(waypoint19);

    waypoint* waypoint20 = new waypoint(cocos2d::Vec2(5 * 75 - 10, 2* 75));
    waypoint19->setNext(waypoint20);
    m_waypointList.pushBack(waypoint20);

    waypoint* waypoint21 = new waypoint(cocos2d::Vec2(7 * 75 - 10, 2* 75));
    waypoint20->setNext(waypoint21);
    m_waypointList.pushBack(waypoint21);

    waypoint* waypoint22 = new waypoint(cocos2d::Vec2(9 * 75 +20, 2* 75));
    waypoint21->setNext(waypoint22);
    m_waypointList.pushBack(waypoint22);
}