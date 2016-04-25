//
//  ConvertAccount.cpp
//  ayh
//
//  Created by liuhui on 16/4/18.
//
//

#include "ConvertAccount.h"
#include "HelloWorldScene.h"
#include "Global.h"
#include "MsgLogin.h"

Scene* ConvertAccount::createScene()
{
    auto scene = Scene::create();
    auto layer = ConvertAccount::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool ConvertAccount::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    auto keyboardlistener = EventListenerKeyboard::create();
    keyboardlistener->onKeyReleased = CC_CALLBACK_2(ConvertAccount::onKeyReleased, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardlistener, this);
#endif
    
    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(ConvertAccount::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(ConvertAccount::onTouchEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    initUI();
    
    return true;
}

void ConvertAccount::initUI(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    Sprite* bg = Sprite::create("convert_user.png");
    bg->setPosition(visibleSize/2);
    bg->setTag(CONVERTACCOUNT);
    addChild(bg);
    
    Sprite* go_back = Sprite::create("go_back.png");
    go_back->setPosition(visibleSize.width*0.0781, visibleSize.height*0.9561);
    go_back->setTag(CONV_GOBACK);
    addChild(go_back);
    
    // 账号
    ui::Scale9Sprite* account = ui::Scale9Sprite::create("eb.png");
    float sx = account->getContentSize().width*0.8000;
    float sy = account->getContentSize().height;
    
    ui::EditBox* pAccount = ui::EditBox::create(Size(sx, sy), account);
    pAccount->setPosition(Vec2(visibleSize.width*0.5031, visibleSize.height*0.6558));
    pAccount->setTag(CONV_PACCOUNT);
    pAccount->setFontSize(23);
    pAccount->setPlaceholderFontSize(23);
    pAccount->setFontColor(Color3B::BLACK);
    pAccount->setPlaceholderFontColor (Color3B::GRAY);
    pAccount->setInputMode(ui::EditBox::InputMode::PHONE_NUMBER);
    pAccount->setPlaceHolder("用户名/手机号");
    pAccount->setMaxLength(11);
    pAccount->setDelegate(this);
    addChild(pAccount);
    
    Sprite* reset1 = Sprite::create("reset.png");
    reset1->setPosition(visibleSize.width*0.8766, visibleSize.height*0.6590);
    reset1->setTag(CONV_RESET1);
    reset1->setVisible(false);
    addChild(reset1);
    
    // 密码
    ui::Scale9Sprite* pwd = ui::Scale9Sprite::create("eb.png");
    sx = pwd->getContentSize().width*0.8000;
    sy = pwd->getContentSize().height;
    
    ui::EditBox* pPwd = ui::EditBox::create(Size(sx, sy), pwd);
    pPwd->setPosition(Vec2(visibleSize.width*0.5031, visibleSize.height*0.5546));
    pPwd->setTag(CONV_PPWD);
    pPwd->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
    pPwd->setFontSize(23);
    pPwd->setPlaceholderFontSize(23);
    pPwd->setFontColor(Color3B::BLACK);
    pPwd->setPlaceholderFontColor (Color3B::GRAY);
    pPwd->setPlaceHolder("填写密码");
    pPwd->setMaxLength(15);
    pPwd->setDelegate(this);
    addChild(pPwd);
    
    Sprite* reset2 = Sprite::create("reset.png");
    reset2->setPosition(visibleSize.width*0.8766, visibleSize.height*0.5560);
    reset2->setTag(CONV_RESET2);
    reset2->setVisible(false);
    addChild(reset2);
    
    Sprite* login = Sprite::create("button.png");
    login->setPosition(visibleSize.width*0.5000, visibleSize.height*0.4085);
    login->setTag(CONV_LONGIN);
    addChild(login);
    
    Label* lbl_login = Label::create();
    lbl_login->setString("登录");
    lbl_login->setTextColor(Color4B::WHITE);
    lbl_login->setSystemFontSize(40.00);
    lbl_login->setHorizontalAlignment(TextHAlignment::CENTER);
    lbl_login->setPosition(visibleSize.width*0.5000, visibleSize.height*0.4085);
    lbl_login->setTag(CONV_LBLLOGIN);
    addChild(lbl_login);
    
    Label* lbl_useMsg = Label::create();
    lbl_useMsg->setString("使用短信验证码登录");
    lbl_useMsg->setTextColor(Color4B::BLUE);
    lbl_useMsg->setSystemFontSize(40.00);
    lbl_useMsg->setHorizontalAlignment(TextHAlignment::CENTER);
    lbl_useMsg->setPosition(visibleSize.width*0.5000, visibleSize.height*0.3180);
    lbl_useMsg->setTag(CONV_USEMSG);
    addChild(lbl_useMsg);
}

bool ConvertAccount::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event){

    return true;
}

void ConvertAccount::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event){
    Vec2 touchLocation = convertTouchToNodeSpace(touch);
    
    if(getChildByTag(CONV_GOBACK)->getBoundingBox().containsPoint(touchLocation)){
        auto trans = TransitionMoveInL::create(0.5, HelloWorld::createScene());
        Director::getInstance()->replaceScene(trans);
    }
    if(getChildByTag(CONV_USEMSG)->getBoundingBox().containsPoint(touchLocation)){
        auto trans = TransitionMoveInR::create(0.5, MsgLogin::createScene());
        Director::getInstance()->replaceScene(trans);
    }
    if(getChildByTag(CONV_LONGIN)->getBoundingBox().containsPoint(touchLocation)){
        
        ui::EditBox* ebAccount = (ui::EditBox*)getChildByTag(CONV_PACCOUNT);
        ui::EditBox* ebPwd = (ui::EditBox*)getChildByTag(CONV_PPWD);
        const char* sAccount = ebAccount->getText();
        const char* sPwd = ebPwd->getText();
        
        if(!Tools::checkInfo(sAccount, sPwd)){
            MyToast::showMsg(this, "手机号码是11位数字\n密码是6-10位字母或数字\n不允许特殊字符", 2.5f);
        }else{
            
        }
    }
    if(getChildByTag(CONV_RESET1)->getBoundingBox().containsPoint(touchLocation)){
        ui::EditBox* ebAccount = (ui::EditBox*)getChildByTag(CONV_PACCOUNT);
        ebAccount->setText("");
    }
    if(getChildByTag(CONV_RESET2)->getBoundingBox().containsPoint(touchLocation)){
        ui::EditBox* ebPwd = (ui::EditBox*)getChildByTag(CONV_PPWD);
        ebPwd->setText("");
    }
}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void ConvertAccount::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event){
    
    auto trans = TransitionMoveInL::create(0.5, HelloWorld::createScene());
    Director::getInstance()->replaceScene(trans);
}
#endif

void ConvertAccount::editBoxReturn(ui::EditBox *editBox){}

void ConvertAccount::editBoxEditingDidBegin(ui::EditBox* eb){
    
    ui::EditBox* account = (ui::EditBox*)getChildByTag(CONV_PACCOUNT);
    ui::EditBox* pwd = (ui::EditBox*)getChildByTag(CONV_PPWD);
    Sprite* reset1 = (Sprite*)getChildByTag(CONV_RESET1);
    Sprite* reset2 = (Sprite*)getChildByTag(CONV_RESET2);
    if(eb == account){
        reset1->setVisible(true);
    }
    if(eb == pwd){
        reset2->setVisible(true);
    }
    
}