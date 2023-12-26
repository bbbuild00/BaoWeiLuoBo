#pragma once

#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#include "cocos2d.h"
#include"GameScene.h"

class WelcomeScene : public cocos2d::Layer
{
public:
    //创建场景（static说明场景的转换是释放再赋值）
    static cocos2d::Scene* createWelcomeScene();
    //初始化
    virtual bool init();

    //退出游戏的回调
    void menuCloseCallback(cocos2d::Ref* pSender);

    //冒险模式的回调
    void adventureCallback(cocos2d::Ref* pSender);

    //怪物窝的回调
    void nestCallback(cocos2d::Ref* pSender) {};

    //设置中心的回调
    void optionsCallback(cocos2d::Ref* pSender) {};

    //帮助中心的回调
    void helperCallback(cocos2d::Ref* pSender) {};

    CREATE_FUNC(WelcomeScene);
};

#endif // __WELCOME_SCENE_H__
