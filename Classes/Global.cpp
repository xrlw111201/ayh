//
//  Global.cpp
//  ayh
//
//  Created by liuhui on 16/4/18.
//
//

#include "Global.h"
#include <cocos2d.h>
#include <regex>
USING_NS_CC;

std::string Global::g_fileName = "";
std::vector<std::string> Global::g_vecAlbum;
int Global::g_nPrevScene = 0;

LayerColor* MyToast::s_ly = NULL;
Label* MyToast::s_lbl = NULL;

void Global::init(){
    FileUtils* fu = FileUtils::getInstance();
    std::string path = fu->getWritablePath();
    g_fileName = fu->fullPathFromRelativeFile("ayh_7670943822e01e", path);
}

void Global::cleanAlbumVector(){
    g_vecAlbum.clear();
    std::vector<std::string>().swap(g_vecAlbum);
}


// 校验手机账号、密码
bool Tools::checkInfo(const char* sAccount, const char* sPwd){
    
    bool rt = true;
    
    // 校验账号（手机号码）
    std::regex pattern("1[345678]\\d{9}");
    if(!regex_match(sAccount, pattern)){
        rt = false;
    }
    // 校验密码
    pattern.assign("[\\w-]{6,10}");
    if(!regex_match(sPwd, pattern)){
        rt = false;
    }
    return rt;
}

// 校验手机账号
bool Tools::checkMobile(const char* sAccount){

    std::regex pattern("1[345678]\\d{9}");
    return regex_match(sAccount, pattern);
}

// 校验密码
bool Tools::checkPwd(const char* pwd){
    
    std::regex pattern("[\\w-]{6,10}");
    return regex_match(pwd, pattern);
}

// 校验验证码
bool Tools::checkMsg(const char* msg){
    std::regex pattern("[\\d]{6}");
    return regex_match(msg, pattern);
}

void MyToast::showMsg(cocos2d::Node* node, const std::string msg, const float time){
    
    delMsg();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    s_lbl = Label::create();
    s_lbl->ignoreAnchorPointForPosition(false);
    s_lbl->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    s_lbl->setString(msg);
    s_lbl->setTextColor(Color4B::BLACK);
    s_lbl->setSystemFontSize(40.00);
    s_lbl->setHorizontalAlignment(TextHAlignment::CENTER);
    
    s_ly = LayerColor::create(Color4B::WHITE);
    s_ly->ignoreAnchorPointForPosition(false);
    s_ly->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    s_ly->setContentSize(s_lbl->getContentSize() + Size(80, 35));

    node->addChild(s_ly);
    node->addChild(s_lbl);
    
    s_ly->setPosition(Vec2(visibleSize.width/2, visibleSize.height/7));
    s_lbl->setPosition(s_ly->getPosition());
    auto seq = Sequence::create(FadeIn::create(time/5),
                                 DelayTime::create(time/5*1.5),
                                 FadeOut::create(time/5*2.5),
                                 CallFunc::create(MyToast::delMsg),
                                 NULL);

    auto action = Repeat::create(seq, 1);
    s_ly->runAction(action);
    s_lbl->runAction(action->clone());

}

void MyToast::delMsg(){
    if(NULL != s_lbl){s_lbl->removeFromParentAndCleanup(true); s_lbl = NULL;}
    if(NULL != s_ly){s_ly->removeFromParentAndCleanup(true); s_ly = NULL;}
}

long Tools::getCurTime(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

