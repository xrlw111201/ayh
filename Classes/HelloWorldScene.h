#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__



#include "cocos2d.h"
#include <ui/CocosGUI.h>
USING_NS_CC;

class HelloWorld : public cocos2d::Layer, public ui::EditBoxDelegate
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    //void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(HelloWorld);
    virtual void editBoxReturn(ui::EditBox*);
    
    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
public:
    void onKeyReleased(EventKeyboard::KeyCode, Event*);
#endif
    
private:
    int m_keyTime;
    void initUI();
};

#endif // __HELLOWORLD_SCENE_H__
