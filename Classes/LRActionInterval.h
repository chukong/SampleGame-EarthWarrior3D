//
//  PublicApi.h
//  Moon3d
//
//  Created by Hao Wu on 2/27/14.
//
//

#ifndef __Moon3d__EnemyManager__
#define __Moon3d__EnemyManager__

#include "CCActionInterval.h"
using namespace cocos2d;
// 定义一个结构来包含确定椭圆的参数
typedef struct _lrTuoyuanConfig
{
    //中心点坐标
    CCPoint centerPosition;
    //椭圆a长，三角斜边
    float aLength;
    //椭圆c长，三角底边
    float cLength;
} lrTuoyuanConfig;

class LRTuoyuanBy : public CCActionInterval
{
public:
    //用“动作持续时间”和“椭圆控制参数”初始化动作
    bool initWithDuration(ccTime t, const lrTuoyuanConfig& c);
    virtual void update(ccTime time);//利用update函数来不断的设定坐标
public:
    //用“动作持续时间”和“椭圆控制参数”创建动作
    static LRTuoyuanBy *actionWithDuration(ccTime t, const lrTuoyuanConfig& c);
    
protected:
    lrTuoyuanConfig m_sConfig;
    CCPoint m_startPosition;
    CCPoint s_startPosition;
};

#endif /* defined(__Moon3d__PublicApi__) */