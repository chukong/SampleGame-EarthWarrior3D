//
//  PluginChannel.h
//  EarthWarrior3D
//
//  Created by daisy on 14-10-9.
//
//

#ifndef EarthWarrior3D_PluginChannel_h
#define EarthWarrior3D_PluginChannel_h



#endif
#include "AgentManager.h"
#include "string"
using namespace std;
using namespace anysdk::framework;

class PluginChannel: public UserActionListener
{
public:
    static PluginChannel* getInstance();
    static void purge();
    
    void loadPlugins();
    
    void unloadPlugins();
    
    void login();
    
    bool isLogined();
    
    
    virtual void onActionResult(ProtocolUser* pPlugin, UserActionResultCode code, const char* msg);
    
    //获取用户唯一标识符，进行游戏端登陆
    std::string getUserId();

    
private:
    PluginChannel();
    virtual ~ PluginChannel();
    static PluginChannel* _pInstance;
    
    
    
};