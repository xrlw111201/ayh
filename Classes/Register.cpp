//
//  Login.cpp
//  ayh
//
//  Created by liuhui on 16/4/18.
//
//
#include "Register.h"
#include "MsgCheck.h"
#include "HelloWorldScene.h"
#include "AlbumLayer.h"
#include "Global.h"
#include <regex>


Scene* Register::createScene()
{
    auto scene = Scene::create();
    auto layer = Register::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool Register::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Global::cleanAlbumVector();
    Conn2Java::getAlbum(this);
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    auto keyboardlistener = EventListenerKeyboard::create();
    keyboardlistener->onKeyReleased = CC_CALLBACK_2(Register::onKeyReleased, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardlistener, this);
#endif
    
    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(Register::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(Register::onTouchEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    initUI();
    
    return true;
}

void Register::initUI(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    Sprite* bg = Sprite::create("register.png");
    bg->setPosition(visibleSize/2);
    bg->setTag(REGISTER);
    addChild(bg);
    
    Sprite* go_back = Sprite::create("go_back.png");
    go_back->setPosition(visibleSize.width*0.0781, visibleSize.height*0.9561);
    go_back->setTag(GOBACK);
    addChild(go_back);
    
    Sprite* camera = Sprite::create("camera.png");
    camera->setPosition(visibleSize.width*0.8063, visibleSize.height*0.7513);
    camera->setTag(PICKIMG);
    addChild(camera);
    
    //editbox
    ui::Scale9Sprite* petname = ui::Scale9Sprite::create("eb.png");
    float sx = petname->getContentSize().width*0.7023;
    float sy = petname->getContentSize().height;
    
    ui::EditBox* pPetname = ui::EditBox::create(Size(sx, sy), petname);
    pPetname->setPosition(Vec2(visibleSize.width*0.4281, visibleSize.height*0.7350));
    pPetname->setTag(PETNAME);
    pPetname->setFontSize(23);
    pPetname->setPlaceholderFontSize(23);
    pPetname->setFontColor(Color3B::BLACK);
    pPetname->setPlaceholderFontColor (Color3B::GRAY);
    pPetname->setPlaceHolder("例如：陈晨");
    pPetname->setMaxLength(10);
    pPetname->setDelegate(this);
    addChild(pPetname);
    
    ui::Scale9Sprite* account = ui::Scale9Sprite::create("eb.png");
    sx = account->getContentSize().width*0.8000;
    sy = account->getContentSize().height;
    
    // 账号
    ui::EditBox* pAccount = ui::EditBox::create(Size(sx, sy), account);
    pAccount->setPosition(Vec2(visibleSize.width*0.5078, visibleSize.height*0.5053));
    pAccount->setTag(PACCOUNT);
    pAccount->setFontSize(23);
    pAccount->setPlaceholderFontSize(23);
    pAccount->setFontColor(Color3B::BLACK);
    pAccount->setPlaceholderFontColor (Color3B::GRAY);
    pAccount->setInputMode(ui::EditBox::InputMode::PHONE_NUMBER);
    pAccount->setPlaceHolder("填写手机号");
    pAccount->setMaxLength(11);
    pAccount->setDelegate(this);
    addChild(pAccount);
    
    Sprite* reset = Sprite::create("reset.png");
    reset->setPosition(visibleSize.width*0.8781, visibleSize.height*0.5094);
    reset->setTag(REGRESET);
    reset->setVisible(false);
    addChild(reset);
    
    // 密码
    ui::Scale9Sprite* pwd = ui::Scale9Sprite::create("eb.png");
    sx = pwd->getContentSize().width*0.8000;
    sy = pwd->getContentSize().height;
    
    ui::EditBox* pPwd = ui::EditBox::create(Size(sx, sy), pwd);
    pPwd->setPosition(Vec2(visibleSize.width*0.5078, visibleSize.height*0.3979));
    pPwd->setTag(PPWD);
    pPwd->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
    pPwd->setFontSize(23);
    pPwd->setPlaceholderFontSize(23);
    pPwd->setFontColor(Color3B::BLACK);
    pPwd->setPlaceholderFontColor (Color3B::GRAY);
    pPwd->setPlaceHolder("填写密码");
    pPwd->setMaxLength(15);
    pPwd->setDelegate(this);
    addChild(pPwd);
    
    Sprite* reg = Sprite::create("button.png");
    reg->setPosition(visibleSize.width*0.5000, visibleSize.height*0.2500);
    reg->setTag(REG);
    addChild(reg);
    
    Label* lbl_reg = Label::create();
    lbl_reg->setString("注册");
    lbl_reg->setTextColor(Color4B::WHITE);
    lbl_reg->setSystemFontSize(40.00);
    lbl_reg->setHorizontalAlignment(TextHAlignment::CENTER);
    lbl_reg->setPosition(visibleSize.width*0.5000, visibleSize.height*0.2494);
    addChild(lbl_reg);
}

bool Register::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event){
    
    return true;
}

void Register::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event){
    Vec2 touchLocation = convertTouchToNodeSpace(touch);
    
    if(getChildByTag(GOBACK)->getBoundingBox().containsPoint(touchLocation)){
        auto trans = TransitionMoveInL::create(0.5, HelloWorld::createScene());
        Director::getInstance()->replaceScene(trans);
    }
    if(getChildByTag(REGRESET)->getBoundingBox().containsPoint(touchLocation)){
        ui::EditBox* account = (ui::EditBox*)getChildByTag(PACCOUNT);
        account->setText("");
    }
    if(getChildByTag(REG)->getBoundingBox().containsPoint(touchLocation)){
        
        ui::EditBox* account = (ui::EditBox*)getChildByTag(PACCOUNT);
        ui::EditBox* pwd = (ui::EditBox*)getChildByTag(PPWD);
        ui::EditBox* petName = (ui::EditBox*)getChildByTag(PETNAME);
        const char* sAccount = account->getText();
        const char* sPwd = pwd->getText();
        const char* sPetName = petName->getText();
        
        // 校验输入信息
        if(!Tools::checkInfo(sAccount, sPwd)){
            MyToast::showMsg(this, "手机号码是11位数字\n密码是6-10位字母或数字\n不允许特殊字符", 2.5f);
        }else{
            Global::g_nPrevScene = REG_SCENE;
            auto trans = TransitionMoveInR::create(0.5, MsgCheck::createScene());
            Director::getInstance()->replaceScene(trans);
        }
        
        // todo: 发送POST请求注册
    }
    // 调用本地相册，获取所有照片路径
    if(getChildByTag(PICKIMG)->getBoundingBox().containsPoint(touchLocation)){
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        auto trans = TransitionMoveInR::create(0.5, AlbumLayer::createScene());
        Director::getInstance()->replaceScene(trans);
#endif
        
    }
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void Register::finishGetAlbum(){
    
    unsigned long count = Global::g_vecAlbum.size();
    std::vector<std::string>::iterator it;
    for(it=Global::g_vecAlbum.begin(); it!=Global::g_vecAlbum.end(); it++){
        log("%ld == %s", count, (*it).c_str());
    }
}
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void Register::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event){

    auto trans = TransitionMoveInL::create(0.5, HelloWorld::createScene());
    Director::getInstance()->replaceScene(trans);
}
#endif

void Register::editBoxReturn(ui::EditBox *editBox){}
void Register::editBoxEditingDidBegin(ui::EditBox* eb){
    ui::EditBox* account = (ui::EditBox*)getChildByTag(PACCOUNT);
    if(account == eb){
        Sprite* reset = (Sprite*)getChildByTag(REGRESET);
        reset->setVisible(true);
    }
}
/*
void* Register::sendQuery(void* args){
    
    log("thread.");
    Size visibleSize = Director::getInstance()->getVisibleSize();
    float m_width = visibleSize.width;
    float m_height = visibleSize.height;
    
    Global::g_vecSprite.clear();
    std::vector<Sprite*>().swap(Global::g_vecSprite);
    
    Image* img = NULL;
    Sprite* s = NULL;
    std::vector<std::string>::iterator it;
    for(it=Global::g_vecAlbum.begin(); it!=Global::g_vecAlbum.end(); it++){
        img = new Image();
        img->initWithImageFile(*it);
        float x = img->getWidth()/2 - m_width/6;
        x = x<0? 0: x;
        
        float y = img->getHeight()/2 - m_height/10;
        y = y<0? 0: y;
        
        float width = m_width/3;
        width = width>img->getWidth()? img->getWidth(): width;
        
        float height = m_height/5;
        height = height>img->getHeight()? img->getHeight(): height;
        
        Rect requied = Rect(x, y, width, height);
        
        Texture2D* t = new Texture2D();
        t->initWithImage(img);
        t->autorelease();
        delete img;
        s = Sprite::createWithTexture(t, requied);
        Global::g_vecSprite.push_back(s);
    }
    return NULL;
}*/