#include "LRTuoyuanBy.h"

static inline float tuoyuanXat( float a, float bx, float c, ccTime t )//返回X坐标
{
    //参数方程
    return -a*cos(2*3.1415926*t)+a;
}
static inline float tuoyuanYat( float a, float by, float c, ccTime t )//返回Y坐标
{
    float b = sqrt(powf(a, 2) - powf(c, 2));//因为之前定义的参数是焦距c而不是短半轴b，所以需要计算出b
    //参数方程
    return b*sin(2*3.1415926*t);
}


//
//TuoyuanBy
//
LRTuoyuanBy* LRTuoyuanBy::actionWithDuration(ccTime t, const lrTuoyuanConfig& c)//利用之前定义的椭圆的三个参数初始化椭圆
{
    LRTuoyuanBy *pTuoyuanBy = new LRTuoyuanBy();
    pTuoyuanBy->initWithDuration(t, c);
    pTuoyuanBy->autorelease();
    
    return pTuoyuanBy;
}

bool LRTuoyuanBy::initWithDuration(ccTime t, const lrTuoyuanConfig& c)
{
    if (CCActionInterval::initWithDuration(t))
    {
        m_sConfig = c;
        return true;
    }
    
    return false;
}
void LRTuoyuanBy::update(ccTime time)
{
    if (m_pTarget)
    {
        CCPoint s_startPosition =m_sConfig.centerPosition;//中心点坐标
        float a = m_sConfig.aLength;
        float bx = m_sConfig.centerPosition.x;
        float by = m_sConfig.centerPosition.y;
        float c = m_sConfig.cLength;
        float x = tuoyuanXat(a, bx, c, time);//调用之前的坐标计算函数来计算出坐标值
        float y = tuoyuanYat(a, by, c, time);
        m_pTarget->setPosition(ccpAdd(s_startPosition, ccp(x-a, y)));//由于我们画计算出的椭圆你做值是以原点为中心的，所以需要加上我们设定的中心点坐标
    }
}