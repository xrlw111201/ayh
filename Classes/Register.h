//
//  Login.h
//  ayh
//
//  Created by liuhui on 16/4/18.
//
//

#ifndef __ayh__Login__
#define __ayh__Login__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../proj.android/jni/hellocpp/JavaDelegate.h"
#endif

#include "cocos2d.h"
#include <ui/CocosGUI.h>
USING_NS_CC;

class Register : public cocos2d::Layer, public ui::EditBoxDelegate

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
, public LayerDelegate
#endif

{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(Register);
    
    virtual void editBoxReturn(ui::EditBox*);
    virtual void editBoxEditingDidBegin(ui::EditBox*);
    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);

private:
    void initUI();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
public:
    void finishGetAlbum();
    void onKeyReleased(EventKeyboard::KeyCode, Event*);
#endif
};

#endif /* defined(__ayh__Login__) */
