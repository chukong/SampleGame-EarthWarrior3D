#ifndef __MY_ANALYTICS_H__
#define __MY_ANALYTICS_H__

#include "AgentManager.h"
#include "string.h"
#include <sstream>
using namespace anysdk::framework;
using namespace std;
class Analytics
{
public:
    static Analytics* getInstance();
    static void purge();


    //统计系统
        void startSession();

        void stopSession();

        void setSessionContinueMillis(long millis);
    	void setCaptureUncaughtException(bool isEnabled);
    	void logError(string errorId, string message);
    	void logEvent(string eventId);
    	void logEvent(string eventId, map<string, string> paramMap);
    	void logTimedEventBegin(string eventId);
    	void logTimedEventEnd(string eventId);

    	void setAccount();
    	void onChargeRequest();
    	void onChargeOnlySuccess();
    	void onChargeSuccess();
    	void onChargeFail();
    	void onPurchase();
    	void onUse();
    	void onReward();
    	void startLevel();
    	void finishLevel();
    	void failLevel();
    	void startTask();
    	void finishTask();
    	void failTask();

    	bool isFunctionSupported(string functionName);
    	template <class T>
    	static std::string ConvertToString(T value) {
    		std::stringstream ss;
    		ss << value;
    		return ss.str();
    	}


private:
    	Analytics();
    virtual ~Analytics();

    static Analytics* _pInstance;

};

#endif
