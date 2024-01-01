#pragma once
#ifndef __GameSelection_SCENE_H__
#define __GameSelection_SCENE_H__
#include"WelcomeScene.h"
#include "cocos2d.h"
#include "cocos/ui/UIWidget.h"
#include"ui/CocosGUI.h"


class GameSelectionScene : public cocos2d::Scene
{
public:
    
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameSelectionScene);
};

//���ѡ��
class SkyLayer :public cocos2d::Layer
{
public:

    static cocos2d::Layer* createLayer();
    virtual bool init();
    CREATE_FUNC(SkyLayer);
    //ѡ���1С��
    void game1(Ref* psender, ui::Widget::TouchEventType type);
    //ѡ���2С��
    void game2(Ref* psender, ui::Widget::TouchEventType type);

    //������һ��
    void return_to_welcome(Ref* pSender)
    {
        auto scene = WelcomeScene::createWelcomeScene();
        cocos2d::Director::getInstance()->replaceScene(scene);
    }
};
#endif // __GameSelection_SCENE_H__
