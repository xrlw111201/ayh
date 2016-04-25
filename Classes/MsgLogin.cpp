//
//  ShortMsg.cpp
//  ayh
//
//  Created by liuhui on 16/4/19.
//
//

#include "MsgLogin.h"
#include "MsgCheck.h"
#include "Global.h"
#include "ConvertAccount.h"

Scene* MsgLogin::createScene()
{
    auto scene = Scene::create();
    auto layer = MsgLogin::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool MsgLogin::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    auto keyboardlistener = EventListenerKeyboard::create();
    keyboardlistener->onKeyReleased = CC_CALLBACK_2(MsgLogin::onKeyReleased, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardlistener, this);
#endif
    
    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(MsgLogin::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(MsgLogin::onTouchEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    initUI();
    
    return true;
}

void MsgLogin::initUI(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite* bg = Sprite::create("msg_login.png");
    bg->setPosition(visibleSize/2);
    bg->setTag(MSGLOGIN);
    addChild(bg);
    
    Sprite* go_back = Sprite::create("go_back.png");
    go_back->setPosition(visibleSize.width*0.0781, visibleSize.height*0.9561);
    go_back->setTag(ML_GOBACK);
    addChild(go_back);
    
    Sprite* next = Sprite::create("next.png");
    next->setPosition(visibleSize.width*0.8719, visibleSize.height*0.9596);
    next->setTag(ML_NEXT);
    addChild(next);
    
    //editbox
    ui::Scale9Sprite* petname = ui::Scale9Sprite::create("eb.png");
    float sx = petname->getContentSize().width*0.8000;
    float sy = petname->getContentSize().height;
    
    ui::EditBox* mobile = ui::EditBox::create(Size(sx, sy), petname);
    mobile->setPosition(Vec2(visibleSize.width*0.5031, visibleSize.height*0.6585));
    mobile->setTag(MOBILE_NO);
    mobile->setFontSize(23);
    mobile->setPlaceholderFontSize(23);
    mobile->setFontColor(Color3B::BLACK);
    mobile->setPlaceholderFontColor (Color3B::GRAY);
    mobile->setInputMode(ui::EditBox::InputMode::PHONE_NUMBER);
    mobile->setPlaceHolder("你的手机号码");
    mobile->setMaxLength(11);
    mobile->setDelegate(this);
    addChild(mobile);
    
    Sprite* reset = Sprite::create("reset.png");
    reset->setPosition(visibleSize.width*0.8547, visibleSize.height*0.6661);
    reset->setTag(ML_RESET);
    addChild(reset);
}

bool MsgLogin::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event){
    
    return true;
}

void MsgLogin::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event){
    Vec2 touchLocation = convertTouchToNodeSpace(touch);

    if(getChildByTag(ML_RESET)->getBoundingBox().containsPoint(touchLocation)){
        ui::EditBox* mobile = (ui::EditBox*)getChildByTag(MOBILE_NO);
        mobile->setText("");
    }
    
    if(getChildByTag(ML_GOBACK)->getBoundingBox().containsPoint(touchLocation)){
        auto trans = TransitionMoveInL::create(0.5, ConvertAccount::createScene());
        Director::getInstance()->replaceScene(trans);
    }
    if(getChildByTag(ML_NEXT)->getBoundingBox().containsPoint(touchLocation)){

        ui::EditBox* eb = (ui::EditBox*)getChildByTag(MOBILE_NO);
        
        if(!Tools::checkMobile(eb->getText())){
            MyToast::showMsg(this, "请输入正确的手机号码", 2.5f);
        }else{
            Global::g_nPrevScene = ML_SCENE;
            auto trans = TransitionMoveInR::create(0.5, MsgCheck::createScene());
            Director::getInstance()->replaceScene(trans);
        }
    }
}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void MsgLogin::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event){
    
    auto trans = TransitionMoveInL::create(0.5, ConvertAccount::createScene());
    Director::getInstance()->replaceScene(trans);
}
#endif
void MsgLogin::editBoxReturn(ui::EditBox *editBox){}

void MsgLogin::editBoxEditingDidBegin(ui::EditBox* eb){
    Sprite* reset = (Sprite*)getChildByTag(ML_RESET);
    reset->setVisible(true);
}

