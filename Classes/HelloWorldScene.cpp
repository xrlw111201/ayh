#include "HelloWorldScene.h"
#include "Register.h"
#include "ConvertAccount.h"
#include "Global.h"
#include <regex>

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    auto keyboardlistener = EventListenerKeyboard::create();
    keyboardlistener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardlistener, this);
#endif
    
    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    initUI();

//    auto fu = FileUtils::getInstance();
//    FIle* f = fopen(fu->fullPathFromRelativeFile("myfile", fu->getWritablePath()).c_str(), "w");
//    fprintf(f, "hello, liuzixi");
//    fclose(f);

    return true;
}

void HelloWorld::initUI(){
    
    m_keyTime = 0;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    Sprite* bg = Sprite::create("login.png");
    bg->setPosition(visibleSize/2);
    bg->setTag(LOGIN);
    addChild(bg);
    
    // 已保存的账户名
    Label* lbl_account = Label::create();
    lbl_account->setString("13807861265");
    lbl_account->setTextColor(Color4B::BLACK);
    lbl_account->setSystemFontSize(40.00);
    lbl_account->setHorizontalAlignment(TextHAlignment::CENTER);
    lbl_account->setPosition(visibleSize.width*0.5000, visibleSize.height*0.5511);
    lbl_account->setTag(LOGIN_MOBILE);
    addChild(lbl_account);
    
   
    
    //editbox
    ui::Scale9Sprite* ss = ui::Scale9Sprite::create("eb.png");
    float sx = ss->getContentSize().width;
    float sy = ss->getContentSize().height;

    ui::EditBox* peb = ui::EditBox::create(Size(sx, sy), ss);
    peb->setPosition(Vec2(visibleSize.width*0.5000, visibleSize.height*0.4736));
    peb->setTag(EDITBOX);
    peb->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
    peb->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
    peb->setFontSize(23);
    peb->setPlaceholderFontSize(23);
    peb->setFontColor(Color3B::BLACK);
    peb->setPlaceholderFontColor (Color3B::GRAY);
    peb->setPlaceHolder("请填写密码");
    peb->setMaxLength(20);
    peb->setDelegate(this);
    addChild(peb);
    
    Sprite* btn_login = Sprite::create("button.png");
    btn_login->setPosition(visibleSize.width*0.5000, visibleSize.height*0.3495);
    btn_login->setTag(BUTTON);
    addChild(btn_login);
    
    Label* lbl_login = Label::create();
    lbl_login->setString("登录");
    lbl_login->setTextColor(Color4B::WHITE);
    lbl_login->setSystemFontSize(40.00);
    lbl_login->setHorizontalAlignment(TextHAlignment::CENTER);
    lbl_login->setPosition(visibleSize.width*0.5000, visibleSize.height*0.3495);
    addChild(lbl_login);
    
    Label* lbl_register = Label::create();
    lbl_register->setString("注册");
    lbl_register->setTextColor(Color4B::BLUE);
    lbl_register->setSystemFontSize(40.00);
    lbl_register->setHorizontalAlignment(TextHAlignment::CENTER);
    lbl_register->setPosition(visibleSize.width*0.3531, visibleSize.height*0.2315);
    lbl_register->setTag(LBLREGISTER);
    addChild(lbl_register);
    
    Label* lbl_convt = Label::create();
    lbl_convt->setString("切换账户");
    lbl_convt->setTextColor(Color4B::BLUE);
    lbl_convt->setSystemFontSize(40.00);
    lbl_convt->setHorizontalAlignment(TextHAlignment::CENTER);
    lbl_convt->setPosition(visibleSize.width*0.6766, visibleSize.height*0.2315);
    lbl_convt->setTag(LBLCONVT);
    addChild(lbl_convt);
/*

    float w = visibleSize.width;
    float h = visibleSize.height;

    Rect drawArea = Rect(100, 100, 100, 100);
    Image* img = new Image();
    
    img->initWithImageFile("shenfenzheng.png");
    log("%d, %d", img->getWidth(), img->getHeight());

    float x = img->getWidth()/2-w/6;
    x = x<0? 0: x;
    float y = img->getHeight()/2-h/10;
    y = y<0? 0: y;
    float xw = w/3;
    xw = xw>img->getWidth()? img->getWidth(): xw;
    float yh = h/5;
    yh = yh>img->getHeight()? img->getHeight(): yh;
    Rect requied = Rect(x, y, xw, yh);
    
    
    Texture2D* t = new Texture2D();
    t->initWithImage(img);
    img->release();
    
    Sprite* s = Sprite::createWithTexture(t, requied);
//    s->setAnchorPoint(Point(0, 0));
//    s->setScale(drawArea.size.width/requied.size.width);
    s->setTag(999);
    s->setPosition(visibleSize/2);
    log("%.2f, %.2f", s->getContentSize().width, s->getContentSize().height);
    
    addChild(s);
*/
}

bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event){

    /*
    ui::EditBox* tf = (ui::EditBox*)getChildByTag(EDITBOX);
    if(tf->getBoundingBox().containsPoint(touchLocation)){
        tf->attachWithIME();
    }else{
        tf->detachWithIME();
    }
    */
    return true;
}

void HelloWorld::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event){
    Vec2 touchLocation = convertTouchToNodeSpace(touch);
    if(getChildByTag(LBLREGISTER)->getBoundingBox().containsPoint(touchLocation)){
        auto trans = TransitionMoveInR::create(0.5, Register::createScene());
        Director::getInstance()->replaceScene(trans);
    }
    if(getChildByTag(LBLCONVT)->getBoundingBox().containsPoint(touchLocation)){
        auto trans = TransitionMoveInR::create(0.5, ConvertAccount::createScene());
        Director::getInstance()->replaceScene(trans);
    }
    if(getChildByTag(BUTTON)->getBoundingBox().containsPoint(touchLocation)){
        
        ui::EditBox* ebPwd = (ui::EditBox*)getChildByTag(EDITBOX);
        const char* pwd = ebPwd->getText();
        
        if(!Tools::checkPwd(pwd)){
            MyToast::showMsg(this, "密码是6-10位字符\n不允许特殊字符", 2.5f);
        }
    }
}

void HelloWorld::editBoxReturn(ui::EditBox *editBox){}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event){
    

    if(EventKeyboard::KeyCode::KEY_ESCAPE == keyCode){

        long curTime = Tools::getCurTime();
        if(curTime - m_keyTime > 2000){
            m_keyTime = curTime;
            MyToast::showMsg(this, "再按一次退出爱运好", 2.0f);
        }else{
            Director::getInstance()->end();
            exit(0);
        }
    }
}
#endif

/*
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
*/