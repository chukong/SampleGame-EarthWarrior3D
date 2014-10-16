#include "Analytics.h"
#include <jni.h>
#include <android/log.h>
#include "PluginJniHelper.h"
using namespace anysdk::framework;

#define  LOG_TAG    "Analytics"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG,__VA_ARGS__);
extern "C"{
JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_wrapper_nativeStartSession(JNIEnv*  env, jobject thiz)
{
	Analytics::getInstance()->startSession();
}

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_wrapper_nativeStopSession(JNIEnv*  env, jobject thiz)
{
	Analytics::getInstance()->stopSession();
}
}


Analytics* Analytics::_pInstance = NULL;

Analytics::Analytics()
{
	if(AgentManager::getInstance()->getAnalyticsPlugin())
		{
			AgentManager::getInstance()->getAnalyticsPlugin()->setDebugMode(true);
		}
}

Analytics::~Analytics()
{

}

Analytics* Analytics::getInstance()
{
    if (_pInstance == NULL) {
        _pInstance = new Analytics();
    }
    return _pInstance;
}

void Analytics::purge()
{
    if (_pInstance)
    {
        delete _pInstance;
        _pInstance = NULL;
    }
}
void Analytics::startSession()
{
	if(AgentManager::getInstance()->getAnalyticsPlugin())
	{
		AgentManager::getInstance()->getAnalyticsPlugin()->startSession();
	}

}

void Analytics::stopSession()
{
	if(AgentManager::getInstance()->getAnalyticsPlugin())
	{
		AgentManager::getInstance()->getAnalyticsPlugin()->stopSession();
	}

}

void Analytics::setSessionContinueMillis(long millis)
{
	if(AgentManager::getInstance()->getAnalyticsPlugin())
	{
		AgentManager::getInstance()->getAnalyticsPlugin()->setSessionContinueMillis(millis);
	}

}
void Analytics::setCaptureUncaughtException(bool isEnabled)
{
	if(AgentManager::getInstance()->getAnalyticsPlugin())
	{
		AgentManager::getInstance()->getAnalyticsPlugin()->setCaptureUncaughtException(true);
	}

}
void Analytics::logError(string errorId, string message)
{
	if(AgentManager::getInstance()->getAnalyticsPlugin())
	{
		AgentManager::getInstance()->getAnalyticsPlugin()->logError(errorId.c_str(),message.c_str());
	}

}
void Analytics::logEvent(string eventId)
{
	if(AgentManager::getInstance()->getAnalyticsPlugin())
	{
		AgentManager::getInstance()->getAnalyticsPlugin()->logEvent(eventId.c_str());
	}

}
void Analytics::logEvent(string eventId, map<string, string> paramMap)
{
	if(AgentManager::getInstance()->getAnalyticsPlugin())
	{
		AgentManager::getInstance()->getAnalyticsPlugin()->logEvent(eventId.c_str(), &paramMap);
	}

}
void Analytics::logTimedEventBegin(string eventId)
{
	if(AgentManager::getInstance()->getAnalyticsPlugin())
	{
		AgentManager::getInstance()->getAnalyticsPlugin()->logTimedEventBegin("logTimedEventBegin");
	}

}
void Analytics::logTimedEventEnd(string eventId)
{
	if(AgentManager::getInstance()->getAnalyticsPlugin())
	{
		AgentManager::getInstance()->getAnalyticsPlugin()->logTimedEventEnd(eventId.c_str());
	}

}

void Analytics::setAccount()
{
	ProtocolAnalytics* plugin = AgentManager::getInstance()->getAnalyticsPlugin();
	if(plugin && isFunctionSupported("setAccount"))
	{
		map<string, string> paramMap;
		paramMap["Account_Id"] = "123456";
		paramMap["Account_Name"] = "test";
		paramMap["Account_Type"] = Analytics::ConvertToString(ANONYMOUS);
		paramMap["Account_Level"] = "1";
		paramMap["Account_Age"] = "1";
		paramMap["Account_Operate"] = Analytics::ConvertToString(LOGIN);
		paramMap["Account_Gender"] = Analytics::ConvertToString(MALE);
		paramMap["Server_Id"] = "1";

		PluginParam data(paramMap);
		plugin->callFuncWithParam("setAccount",&data, NULL);

	}
}

void Analytics::onChargeRequest()
{
	ProtocolAnalytics* plugin = AgentManager::getInstance()->getAnalyticsPlugin();
	if(plugin && isFunctionSupported("onChargeRequest"))
	{
		map<string, string> paramMap;
		paramMap["Order_Id"] = "123456";
		paramMap["Product_Name"] = "test";
		paramMap["Currency_Amount"] = Analytics::ConvertToString(2.0);
		paramMap["Currency_Type"] = "1";
		paramMap["Payment_Type"] = "1";
		paramMap["Virtual_Currency_Amount"] = Analytics::ConvertToString(100);

		PluginParam data(paramMap);
		plugin->callFuncWithParam("onChargeRequest",&data, NULL);

	}
}
void Analytics::onChargeOnlySuccess()
{
	ProtocolAnalytics* plugin = AgentManager::getInstance()->getAnalyticsPlugin();
	if(plugin && isFunctionSupported("onChargeOnlySuccess"))
	{
		map<string, string> paramMap;
		paramMap["Order_Id"] = "123456";
		paramMap["Product_Name"] = "test";
		paramMap["Currency_Amount"] = Analytics::ConvertToString(2.0);
		paramMap["Currency_Type"] = "1";
		paramMap["Payment_Type"] = "1";
		paramMap["Virtual_Currency_Amount"] = Analytics::ConvertToString(100);
		PluginParam data(paramMap);
		plugin->callFuncWithParam("onChargeOnlySuccess",&data, NULL);

	}
}
void Analytics::onChargeSuccess()
{
	ProtocolAnalytics* plugin = AgentManager::getInstance()->getAnalyticsPlugin();
	if(plugin && isFunctionSupported("onChargeSuccess"))
	{
		PluginParam data("123456");
		plugin->callFuncWithParam("onChargeSuccess",&data, NULL);

	}
}

void Analytics::onChargeFail()
{
	ProtocolAnalytics* plugin = AgentManager::getInstance()->getAnalyticsPlugin();
	if(plugin && isFunctionSupported("onChargeFail"))
	{
		map<string, string> paramMap;
		paramMap["Order_Id"] = "123456";
		paramMap["Fail_Reason"] = "test";
		PluginParam data(paramMap);
		plugin->callFuncWithParam("onChargeFail",&data, NULL);

	}
}
void Analytics::onPurchase()
{
	ProtocolAnalytics* plugin = AgentManager::getInstance()->getAnalyticsPlugin();
	if(plugin && isFunctionSupported("onPurchase"))
	{
		map<string, string> paramMap;
		paramMap["Item_Id"] = "123456";
		paramMap["Item_Type"] = "test";
		paramMap["Item_Count"] = Analytics::ConvertToString(2);
		paramMap["Vitural_Currency"] = "1";
		paramMap["Currency_Type"] = AgentManager::getInstance()->getChannelId();
		PluginParam data(paramMap);
		plugin->callFuncWithParam("onPurchase",&data, NULL);

	}
}
void Analytics::onUse()
{
	ProtocolAnalytics* plugin = AgentManager::getInstance()->getAnalyticsPlugin();
	if(plugin && isFunctionSupported("onUse"))
	{
		map<string, string> paramMap;
		paramMap["Item_Id"] = "123456";
		paramMap["Item_Type"] = "test";
		paramMap["Item_Count"] = Analytics::ConvertToString(2);
		paramMap["Use_Reason"] = "1";
		PluginParam data(paramMap);
		plugin->callFuncWithParam("onUse",&data, NULL);

	}
}
void Analytics::onReward()
{
	ProtocolAnalytics* plugin = AgentManager::getInstance()->getAnalyticsPlugin();
	if(plugin && isFunctionSupported("onReward"))
	{
		map<string, string> paramMap;
		paramMap["Item_Id"] = "123456";
		paramMap["Item_Type"] = "test";
		paramMap["Item_Count"] = Analytics::ConvertToString(2);
		paramMap["Use_Reason"] = "1";
		PluginParam data(paramMap);
		plugin->callFuncWithParam("onReward",&data, NULL);

	}
}
void Analytics::startLevel()
{
	ProtocolAnalytics* plugin = AgentManager::getInstance()->getAnalyticsPlugin();
	if(plugin && isFunctionSupported("startLevel"))
	{
		map<string, string> paramMap;
		paramMap["Level_Id"] = "123456";
		paramMap["Seq_Num"] = "1";
		PluginParam data(paramMap);
		plugin->callFuncWithParam("startLevel",&data, NULL);

	}
}

void Analytics::finishLevel()
{
	ProtocolAnalytics* plugin = AgentManager::getInstance()->getAnalyticsPlugin();
	if(plugin && isFunctionSupported("finishLevel"))
	{
		PluginParam data("123456");
		plugin->callFuncWithParam("finishLevel",&data, NULL);

	}
}
void Analytics::failLevel()
{
	ProtocolAnalytics* plugin = AgentManager::getInstance()->getAnalyticsPlugin();
	if(plugin && isFunctionSupported("failLevel"))
	{
		map<string, string> paramMap;
		paramMap["Level_Id"] = "123456";
		paramMap["Fail_Reason"] = "test";
		PluginParam data(paramMap);
		plugin->callFuncWithParam("failLevel",&data, NULL);

	}
}
void Analytics::startTask()
{
	ProtocolAnalytics* plugin = AgentManager::getInstance()->getAnalyticsPlugin();
	if(plugin && isFunctionSupported("startTask"))
	{
		map<string, string> paramMap;
		paramMap["Task_Id"] = "123456";
		paramMap["Task_Type"] = Analytics::ConvertToString(GUIDE_LINE);
		PluginParam data(paramMap);
		plugin->callFuncWithParam("startTask",&data, NULL);

	}
}
void Analytics::finishTask()
{
	ProtocolAnalytics* plugin = AgentManager::getInstance()->getAnalyticsPlugin();
	if(plugin && isFunctionSupported("finishTask"))
	{
		PluginParam data("123456");
		plugin->callFuncWithParam("finishTask",&data, NULL);

	}
}
void Analytics::failTask()
{
	ProtocolAnalytics* plugin = AgentManager::getInstance()->getAnalyticsPlugin();
	if(plugin && isFunctionSupported("failTask"))
	{
		map<string, string> paramMap;
		paramMap["Task_Id"] = "123456";
		paramMap["Fail_Reason"] = "test";
		PluginParam data(paramMap);
		plugin->callFuncWithParam("failTask",&data, NULL);

	}

}

bool Analytics::isFunctionSupported(string functionName)
{
	ProtocolAnalytics* plugin = AgentManager::getInstance()->getAnalyticsPlugin();
	if(plugin)
	{
		return plugin->isFunctionSupported(functionName);

	}
	return false;
}
