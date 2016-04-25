//
//  ShortMsg.h
//  ayh
//
//  Created by liuhui on 16/4/19.
//
//

#ifndef __ayh__ShortMsg__
#define __ayh__ShortMsg__

#include "cocos2d.h"
#include <ui/CocosGUI.h>
USING_NS_CC;

class MsgLogin: public cocos2d::Layer, public ui::EditBoxDelegate
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(MsgLogin);
    
    virtual void editBoxReturn(ui::EditBox*);
    virtual void editBoxEditingDidBegin(ui::EditBox*);
    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
    
private:
    
    
    void initUI();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
public:
    void onKeyReleased(EventKeyboard::KeyCode, Event*);
#endif
};

#endif /* defined(__ayh__ShortMsg__) */
