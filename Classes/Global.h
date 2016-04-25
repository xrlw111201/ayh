//
//  Global.h
//  ayh
//
//  Created by liuhui on 16/4/18.
//
//

#ifndef __ayh__Global__
#define __ayh__Global__

// Prev scene
#define REG_SCENE    1
#define ML_SCENE     2

// Login scene
#define LOGIN        100
#define EDITBOX      101
#define BUTTON       102
#define LBLREGISTER  103
#define LBLCONVT     104
#define LOGIN_MOBILE 105

// Register scene
#define REGISTER    200
#define GOBACK      201
#define PETNAME     202
#define PACCOUNT    203
#define REGRESET    204
#define PPWD        205
#define REG         206
#define PICKIMG     207

// Convert account scene
#define CONVERTACCOUNT  301
#define CONV_GOBACK     302
#define CONV_PACCOUNT   303
#define CONV_RESET1     304
#define CONV_PPWD       305
#define CONV_RESET2     306
#define CONV_LONGIN     307
#define CONV_LBLLOGIN   308
#define CONV_USEMSG     309

// MsgLogin scene
#define MSGLOGIN        400
#define ML_GOBACK       401
#define MOBILE_NO       402
#define ML_RESET        403
#define ML_NEXT         404

// MsgCheck scene
#define MSGCHECK        500
#define MC_GOBACK       501
#define MC_MOBILE       502
#define CHECK_CODE      503
#define CHECK_CODE_LEN  6       //验证码长度
#define MC_BUTTON       504

#include <cocos2d.h>
#include <string>
#include <vector>
USING_NS_CC;

class Global{
public:
    static int g_nPrevScene;
    static std::string g_fileName;
    static std::vector<std::string> g_vecAlbum;
    
    static void init();
    static void cleanAlbumVector();
};

class Tools{
public:
    static bool checkMobile(const char*);
    static bool checkPwd(const char*);
    static bool checkInfo(const char*, const char*);
    static bool checkMsg(const char*);
    static long getCurTime();
};

class MyToast{
public:
    static LayerColor* s_ly;
    static Label* s_lbl;
    static void showMsg(Node*, const std::string, const float);
    static void delMsg();
};
#endif /* defined(__ayh__Global__) */
