//
//  Star.h
//  SolarSystem
//
//  Created by 欧长坤 on 14/12/16.
//  Copyright (c) 2014年 Changkun Ou. All rights reserved.
//

#ifndef SolarSystem_BallDefinition_h
#define SolarSystem_BallDefinition_h

#include <GLUT/glut.h>

// 数组type
typedef GLfloat (Float2)[2];
typedef GLfloat (Float3)[3];
typedef GLfloat Float;
typedef GLfloat (Float4)[4];

// 对数组进行操作的宏
//#define Float(name, value) (name)=(value)
#define Float2(name, value0, value1) ((name)[0])=(value0), ((name)[1])=(value1)
#define Float3(name, value0, value1, value2) ((name)[0])=(value0), \
((name)[1])=(value1), ((name)[2])=(value2)
#define Float4(name, value0, value1, value2, value3) ((name)[0])=(value0), \
((name)[1])=(value1), ((name)[2])=(value2), ((name)[3])=(value3)

// 对数组进行操作的宏
//#define Float(name) (name)
#define RFloat2(name) ((name)[0]), ((name)[1])
#define RFloat3(name) ((name)[0]), ((name)[1]), ((name)[2])
#define RFloat4(name) ((name)[0]), ((name)[1]), ((name)[2]), ((name)[3])


// 对于具体星球而言，有以下属性：
// 颜色color
// 半径radius
// 自传速度selfspeed
// 公转速度speed
// 距离太阳中心距离distance
// 绕行星球parentball
// 当前自转角度alphaself
// 当前公转角度alpha

// 描述普通能够自传并且绕某个点公转的球(classBall)
// 描述具有材质属性的球(classMatBall)
// 描述具有发光属性的球(classLightBall)
// 每个星球类独立的处理自己的运动
// 类中实现draw和update用户绘制和更新星球
// draw 处理自己绕行点(parentball)的关系, 对于星球属性需要按一定比例调整以符合观看需要

class Ball {
public:
    Float4 Color;
    Float Radius;
    Float SelfSpeed;
    Float Speed;
    
    // ParentBall是本球绕行的球
    // Center是本球的中心点，当有ParentBall和Distance的时候可以不使用
    // Distance是本球中心与ParentBall中心的距离
    // Center暂时没有使用
    //Float2 Center;
    Float Distance;
    Ball * ParentBall;
    
    virtual void Draw() { DrawBall(); }
    virtual void Update(long TimeSpan);
    
    Ball(Float Radius, Float Distance, Float Speed, Float SelfSpeed, Ball * Parent);
    
    // 对普通的球体进行移动和旋转
    void DrawBall();
    
protected:
    Float AlphaSelf, Alpha;
};

class MatBall : public Ball {
public:
    virtual void Draw() { DrawMat(); DrawBall(); }
    
    MatBall(Float Radius, Float Distance, Float Speed, Float SelfSpeed,
            Ball * Parent, Float3 color);
    
    // 对材质进行设置
    void DrawMat();
};

class LightBall : public MatBall {
public:
    virtual void Draw() { DrawLight(); DrawMat(); DrawBall(); }
    
    LightBall(Float Radius, Float Distance, Float Speed, Float SelfSpeed,
              Ball * Parent, Float3 color);
    
    // 对光源进行设置
    void DrawLight();
};

#endif
