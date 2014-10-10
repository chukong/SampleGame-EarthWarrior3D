//
//  PluginChannel.cpp
//  EarthWarrior3D
//
//  Created by daisy on 14-10-9.
//
//


#include <jni.h>
#include <android/log.h>
#include "PluginJniHelper.h"
#include "PluginChannel.h"

using namespace anysdk::framework;

#define  LOG_TAG    "PluginChannel"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG,__VA_ARGS__);
extern "C"
{
    
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_wrapper_nativeInitPlugins(JNIEnv*  env, jobject thiz)
    {
        PluginChannel::getInstance()->loadPlugins();
    }
    
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_wrapper_nativeUnLoadPlugins(JNIEnv*  env, jobject thiz)
    {
        PluginChannel::purge();
    }
}
PluginChannel* PluginChannel::_pInstance = NULL;

PluginChannel::PluginChannel()
{
	
    
}

PluginChannel::~PluginChannel()
{
    unloadPlugins();
}

PluginChannel* PluginChannel::getInstance()
{
    if (_pInstance == NULL) {
        _pInstance = new PluginChannel();
    }
    return _pInstance;
}

void PluginChannel::purge()
{
    if (_pInstance)
    {
        delete _pInstance;
        _pInstance = NULL;
    }
}


void PluginChannel::loadPlugins()
{
    LOGD("Load plugins invoked");
    /**
     * appKey、appSecret、privateKey不能使用Sample中的值，需要从打包工具中游戏管理界面获取，替换
     * oauthLoginServer参数是游戏服务提供的用来做登陆验证转发的接口地址。
     */
    std::string oauthLoginServer = "http://oauth.qudao.info/api/OauthLoginDemo/Login.php";
	std::string appKey = "0914CB16-BAEE-790E-808E-3A37B8FFBE3F";
	std::string appSecret = "62bee0ddb86bdeccb8acd959765041cc";
	std::string privateKey = "96C273AB03E1A798BA1AD0C38004871F";
    
    AgentManager::getInstance()->init(appKey,appSecret,privateKey,oauthLoginServer);
    
    //使用框架中代理类进行插件初始化
    AgentManager::getInstance()->loadALLPlugin();
    
    //对用户系统设置监听类
    if(AgentManager::getInstance()->getUserPlugin())
    {
		AgentManager::getInstance()->getUserPlugin()->setDebugMode(true);
    	AgentManager::getInstance()->getUserPlugin()->setActionListener(this);
    }
    
    
}

void PluginChannel::unloadPlugins()
{
    LOGD("Unload plugins invoked");
    AgentManager::getInstance()->unloadALLPlugin();
}




void PluginChannel::login()
{
	if(AgentManager::getInstance()->getUserPlugin())
	{
		AgentManager::getInstance()->getUserPlugin()->login();
	}
}

bool PluginChannel::isLogined()
{
	if(AgentManager::getInstance()->getUserPlugin())
	{
		return AgentManager::getInstance()->getUserPlugin()->isLogined();
	}
    return false;
}

void PluginChannel::onActionResult(ProtocolUser* pPlugin, UserActionResultCode code, const char* msg)
{
	LOGD("onActionResult%d%s",code,msg);
	switch(code)
	{
        case kInitSuccess://初始化SDK成功回调
            break;
        case kInitFail://初始化SDK失败回调
            break;
        case kLoginSuccess://登陆成功回调
            break;
        case kLoginNetworkError://登陆失败回调
        case kLoginCancel://登陆取消回调
        case kLoginFail://登陆失败回调
            break;
        case kLogoutSuccess://登出成功回调
            break;
        case kLogoutFail://登出失败回调
            break;
        case kPlatformEnter://平台中心进入回调
            break;
        case kPlatformBack://平台中心退出回调
            break;
        case kPausePage://暂停界面回调
            break;
        case kExitPage://退出游戏回调
            break;
        case kAntiAddictionQuery://防沉迷查询回调
            break;
        case kRealNameRegister://实名注册回调
            break;
        case kAccountSwitchSuccess://切换账号成功回调
            break;
        case kAccountSwitchFail://切换账号成功回调
            break;
        default:
            break;
	}
    
}

std::string PluginChannel::getUserId()
{
	if(AgentManager::getInstance()->getUserPlugin())
	{
        
        
		return AgentManager::getInstance()->getUserPlugin()->getUserID();
	}
}