//
// Created by liuqian8 on 2018/10/24.
//

#pragma once
#include "vec2.hpp"

//cocos2dx是以坐下角为锚点使用（OpenGL标准坐标系）右手坐标系（为了在2D方面计算的简洁快速性，采用以左下角为锚点）
// urho3d是以左上角为锚点，并且其是（DX坐标系）左手坐标系(为了在PC端使用DX9与DX11而遵循的一种坐标系标准)
//OGRE采用的是（DX坐标系）左手坐标系，是以左上角为锚点(为了在PC端使用DX9与DX11而遵循的一种坐标系标准)
//我采用以中心点为锚点，使用（OpenGL标准坐标系）右手坐标系（2D到3D的快速切换，从而采用以中心点为锚点）
//代码风格类似于ogre，不同于谷歌的风格

/// Intersection test result.
enum Intersection
{
    OUTSIDE,//外部
    INTERSECTS,//交叉
    INSIDE//内部
};

class Rect
{
    //使用该类时一定要注意我所规定的标准，我是以OpenGL标准的右手坐标系为基准，max最大是右上角，min最小是左下角
public:
    //默认构造器，其初始化值都为0
    Rect():min_(),
            max_()
    {
    }

    Rect(const glm::vec2& min,const glm::vec2& max):
            min_(min),
            max_(max)
    {
    }

    Rect(float left,float top,float right,float bottom):
            max_(right,top),
            min_(left,bottom)
    {
    }
    //使用数组来初始化的时候，要严格遵循，left top right bottom排列顺序
    Rect(const float* data):
            min_(data[0],data[3]),
            max_(data[2],data[1])
    {
    }

    Rect(const Rect& rect):
            min_(rect.min_),
            max_(rect.max_)
    {
    }

    Rect& operator =(const Rect& rhs)
    {
        min_ = rhs.min_;
        max_ = rhs.max_;
        return *this;
    }

    /// Test for equality with another rect.
    bool operator ==(const Rect& rhs) const
    {
        return min_ == rhs.min_ && max_ == rhs.max_;
    }

    /// Test for inequality with another rect.
    bool operator !=(const Rect& rhs) const
    {
        return min_ != rhs.min_ || max_ != rhs.max_;
    }

    /// Add another rect to this one inplace.
    Rect& operator +=(const Rect& rhs)
    {
        min_ += rhs.min_;
        max_ += rhs.max_;
        return *this;
    }

    /// Subtract another rect from this one inplace.
    Rect& operator -=(const Rect& rhs)
    {
        min_ -= rhs.min_;
        max_ -= rhs.max_;
        return *this;
    }

    /// Divide by scalar inplace.
    Rect& operator /=(float value)
    {
        min_ /= value;
        max_ /= value;
        return *this;
    }

    /// Multiply by scalar inplace.
    Rect& operator *=(float value)
    {
        min_ *= value;
        max_ *= value;
        return *this;
    }

    /// Divide by scalar.
    Rect operator /(float value) const
    {
        return Rect(min_ / value, max_ / value);
    }

    /// Multiply by scalar.
    Rect operator *(float value) const
    {
        return Rect(min_ * value, max_ * value);
    }

    /// Add another rect.
    Rect operator +(const Rect& rhs) const
    {
        return Rect(min_ + rhs.min_, max_ + rhs.max_);
    }

    /// Subtract another rect.
    Rect operator -(const Rect& rhs) const
    {
        return Rect(min_ - rhs.min_, max_ - rhs.max_);
    }

    /// Test whether a point is inside.
    Intersection isInside(const glm::vec2& point) const
    {
        if (point.x < min_.x || point.y < min_.y || point.x > max_.x || point.y > max_.y)
            return OUTSIDE;
        else
            return INSIDE;
    }

    /// Test if another rect is inside, outside or intersects.
    Intersection isInside(const Rect& rect) const
    {
        if (rect.max_.x < min_.x || rect.min_.x > max_.x || rect.max_.y < min_.y || rect.min_.y > max_.y)
            return OUTSIDE;
        else if (rect.min_.x < min_.x || rect.max_.x > max_.x || rect.min_.y < min_.y || rect.max_.y > max_.y)
            return INTERSECTS;
        else
            return INSIDE;
    }

    /// Return left-top corner position.
    glm::vec2 min() const
    {
        return min_;
    }

    /// Return right-bottom corner position.
    glm::vec2 max() const
    {
        return max_;
    }

    /// Return left coordinate.
    float left() const
    {
        return min_.x;
    }

    /// Return top coordinate.
    float top() const
    {
        return max_.y;
    }

    /// Return right coordinate.
    float right() const
    {
        return max_.x;
    }

    /// Return bottom coordinate.
    float bottom() const
    {
        return min_.y;
    }

    glm::vec2 min_;
    glm::vec2 max_;

    /// Rect in the range (-1, -1) - (1, 1)
    static const Rect FULL;
    /// Rect in the range (0, 0) - (1, 1)
    static const Rect POSITIVE;
    /// Zero-sized rect.
    static const Rect ZERO;
};
