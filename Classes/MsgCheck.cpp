//
//  MsgCheck.cpp
//  ayh
//
//  Created by liuhui on 16/4/20.
//
//
#include "MsgLogin.h"
#include "MsgCheck.h"
#include "Register.h"
#include "Global.h"

Scene* MsgCheck::createScene()
{
    auto scene = Scene::create();
    auto layer = MsgCheck::create();
    scene->addChild(layer);
    return scene;
}

bool MsgCheck::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    auto keyboardlistener = EventListenerKeyboard::create();
    keyboardlistener->onKeyReleased = CC_CALLBACK_2(MsgCheck::onKeyReleased, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardlistener, this);
#endif
    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(MsgCheck::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(MsgCheck::onTouchEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    initUI();
    
    return true;
}

void MsgCheck::initUI(){
    Size visibleSize = Director::getInstance()->getVisibleSize();

    Sprite* bg = Sprite::create("msg_check.png");
    bg->setPosition(visibleSize/2);
    bg->setTag(MSGCHECK);
    addChild(bg);
    
    Sprite* go_back = Sprite::create("go_back.png");
    go_back->setPosition(visibleSize.width*0.0781, visibleSize.height*0.9561);
    go_back->setTag(MC_GOBACK);
    addChild(go_back);
    
    Label* lbl_mobile = Label::create();
    lbl_mobile->setString("18648713587");
    lbl_mobile->setTextColor(Color4B::BLACK);
    lbl_mobile->setSystemFontSize(40.00);
    lbl_mobile->setHorizontalAlignment(TextHAlignment::CENTER);
    lbl_mobile->setPosition(visibleSize.width*0.5703, visibleSize.height*0.6631);
    lbl_mobile->setTag(MC_MOBILE);
    addChild(lbl_mobile);
    
    //editbox
    ui::Scale9Sprite* petname = ui::Scale9Sprite::create("eb.png");
    float sx = petname->getContentSize().width*0.8000;
    float sy = petname->getContentSize().height;
    
    ui::EditBox* cc = ui::EditBox::create(Size(sx, sy), petname);
    cc->setPosition(Vec2(visibleSize.width*0.5500, visibleSize.height*0.5475));
    cc->setTag(CHECK_CODE);
    cc->setFontSize(23);
    cc->setPlaceholderFontSize(23);
    cc->setFontColor(Color3B::BLACK);
    cc->setPlaceholderFontColor (Color3B::GRAY);
    cc->setInputMode(ui::EditBox::InputMode::NUMERIC);
    cc->setPlaceHolder("请输入验证码");
    cc->setMaxLength(CHECK_CODE_LEN);
    cc->setDelegate(this);
    addChild(cc);
    
    Sprite* btnNext = Sprite::create("button.png");
    btnNext->setPosition(visibleSize.width*0.5000, visibleSize.height*0.4050);
    btnNext->setTag(MC_BUTTON);
    addChild(btnNext);
    
    Label* lblNext = Label::create();
    lblNext->setString("下一步");
    lblNext->setTextColor(Color4B::WHITE);
    lblNext->setSystemFontSize(40.00);
    lblNext->setHorizontalAlignment(TextHAlignment::CENTER);
    lblNext->setPosition(visibleSize.width*0.5000, visibleSize.height*0.4050);
    addChild(lblNext);
}

bool MsgCheck::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event){
    
    return true;
}

void MsgCheck::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event){
    Vec2 touchLocation = convertTouchToNodeSpace(touch);
    
    if(getChildByTag(MC_GOBACK)->getBoundingBox().containsPoint(touchLocation)){
        goBack();
    }
    if(getChildByTag(MC_BUTTON)->getBoundingBox().containsPoint(touchLocation)){
        // todo: 校验验证码
        ui::EditBox* eb = (ui::EditBox*)getChildByTag(CHECK_CODE);
        if(!Tools::checkMsg(eb->getText())){
            MyToast::showMsg(this, "验证码是6位数字", 2.0f);
        }else{
            
        }
    }
}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void MsgCheck::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event){
    
    goBack();
}
#endif
void MsgCheck::editBoxReturn(ui::EditBox *editBox){}

void MsgCheck::goBack(){
    Scene* trans = NULL;
    switch(Global::g_nPrevScene){
        case REG_SCENE:{trans = TransitionMoveInL::create(0.5, Register::createScene()); break;}
        case ML_SCENE:{trans = TransitionMoveInL::create(0.5, MsgLogin::createScene()); break;}
        default: break;
    }
    Director::getInstance()->replaceScene(trans);
}
