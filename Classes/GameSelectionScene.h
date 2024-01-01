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

//天际选关
class SkyLayer :public cocos2d::Layer
{
public:

    static cocos2d::Layer* createLayer();
    virtual bool init();
    CREATE_FUNC(SkyLayer);
    //选择第1小关
    void game1(Ref* psender, ui::Widget::TouchEventType type);
    //选择第2小关
    void game2(Ref* psender, ui::Widget::TouchEventType type);

    //返回上一层
    void return_to_welcome(Ref* pSender)
    {
        auto scene = WelcomeScene::createWelcomeScene();
        cocos2d::Director::getInstance()->replaceScene(scene);
    }
};
#endif // __GameSelection_SCENE_H__
