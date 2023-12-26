#pragma once

#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#include "cocos2d.h"
#include"GameScene.h"

class WelcomeScene : public cocos2d::Layer
{
public:
    //����������static˵��������ת�����ͷ��ٸ�ֵ��
    static cocos2d::Scene* createWelcomeScene();
    //��ʼ��
    virtual bool init();

    //�˳���Ϸ�Ļص�
    void menuCloseCallback(cocos2d::Ref* pSender);

    //ð��ģʽ�Ļص�
    void adventureCallback(cocos2d::Ref* pSender);

    //�����ѵĻص�
    void nestCallback(cocos2d::Ref* pSender) {};

    //�������ĵĻص�
    void optionsCallback(cocos2d::Ref* pSender) {};

    //�������ĵĻص�
    void helperCallback(cocos2d::Ref* pSender) {};

    CREATE_FUNC(WelcomeScene);
};

#endif // __WELCOME_SCENE_H__
