//
// Created by liuqian8 on 2018/10/17.
//
#pragma once
#include "vec4.hpp"
#include "vec2.hpp"

enum VariantType
{
    VAR_NONE = 0,
    VAR_INT,
    VAR_BOOL,
    VAR_FLOAT,
    VAR_VECTOR2,
    VAR_VECTOR4,
    VAR_RECT,
    VAR_INT64,
    VAR_DOUBLE,
    MAX_VAR_TYPES
};

union VariantValue
{
    int int_;
    bool bool_;
    float float_;
    double double_;
    long long int64_;
    glm::vec2 vector2_;
    glm::vec4 vector4_;
    /// Construct uninitialized.
    VariantValue() { }      // NOLINT(modernize-use-equals-default)
    /// Non-copyable.
    VariantValue(const VariantValue& value) = delete;
    /// Destruct.
    ~VariantValue() { }     // NOLINT(modernize-use-equals-default)
};

class Variant
{
public:
    Variant() = default;


    Variant(int value)
    {
        *this = value;
    }

    /// Construct from a float.
    Variant(float value)                // NOLINT(google-explicit-constructor)
    {
        *this = value;
    }

    /// Construct from a double.
    Variant(double value)               // NOLINT(google-explicit-constructor)
    {
        *this = value;
    }

    /// Construct from a Vector2.
    Variant(const glm::vec2& value)       // NOLINT(google-explicit-constructor)
    {
        *this = value;
    }

    /// Construct from a Vector4.
    Variant(const glm::vec4& value)       // NOLINT(google-explicit-constructor)
    {
        *this = value;
    }

    VariantType getType() const
    {
        return type_;
    }

/// Destruct.
    ~Variant()
    {
        setType(VAR_NONE);
    }

    /// Assign from an integer.
    Variant& operator =(int rhs)
    {
        setType(VAR_INT);
        value_.int_ = rhs;
        return *this;
    }

    /// Assign from an unsigned integer.
    Variant& operator =(unsigned rhs)
    {
        setType(VAR_INT);
        value_.int_ = (int)rhs;
        return *this;
    }

    /// Assign from a bool.
    Variant& operator =(bool rhs)
    {
        setType(VAR_BOOL);
        value_.bool_ = rhs;
        return *this;
    }

    /// Assign from a float.
    Variant& operator =(float rhs)
    {
        setType(VAR_FLOAT);
        value_.float_ = rhs;
        return *this;
    }

    /// Assign from a double.
    Variant& operator =(double rhs)
    {
        setType(VAR_DOUBLE);
        value_.double_ = rhs;
        return *this;
    }

    /// Assign from a Vector2.
    Variant& operator =(const glm::vec2& rhs)
    {
        setType(VAR_VECTOR2);
        value_.vector2_ = rhs;
        return *this;
    }

    /// Assign from a Vector4.
    Variant& operator =(const glm::vec4& rhs)
    {
        setType(VAR_VECTOR4);
        value_.vector4_ = rhs;
        return *this;
    }

    /// Test for equality with an integer. To return true, both the type and value must match.
    bool operator ==(int rhs) const
    {
        return type_ == VAR_INT ? value_.int_ == rhs : false;
    }

    /// Test for equality with an unsigned 64 bit integer. To return true, both the type and value must match.
    bool operator ==(unsigned rhs) const
    {
        return type_ == VAR_INT ? value_.int_ == static_cast<int>(rhs) : false;
    }

    /// Test for equality with a bool. To return true, both the type and value must match.
    bool operator ==(bool rhs) const
    {
        return type_ == VAR_BOOL ? value_.bool_ == rhs : false;
    }

    /// Test for equality with a float. To return true, both the type and value must match.
    bool operator ==(float rhs) const
    {
        return type_ == VAR_FLOAT ? value_.float_ == rhs : false;
    }

    /// Test for equality with a double. To return true, both the type and value must match.
    bool operator ==(double rhs) const
    {
        return type_ == VAR_DOUBLE ? value_.double_ == rhs : false;
    }

    /// Test for equality with a Vector2. To return true, both the type and value must match.
    bool operator ==(const glm::vec2& rhs) const
    {
        return type_ == VAR_VECTOR2 ? value_.vector2_ == rhs : false;
    }

    /// Test for equality with a Vector4. To return true, both the type and value must match.
    bool operator ==(const glm::vec4& rhs) const
    {
        return type_ == VAR_VECTOR4 ? value_.vector4_ == rhs : false;
    }

    /// Test for inequality with an integer.
    bool operator !=(int rhs) const
    {
        return !(*this == rhs);
    }

    /// Test for inequality with an unsigned integer.
    bool operator !=(unsigned rhs) const
    {
        return !(*this == rhs);
    }

    /// Test for inequality with a bool.
    bool operator !=(bool rhs) const
    {
        return !(*this == rhs);
    }

    /// Test for inequality with a float.
    bool operator !=(float rhs) const
    {
        return !(*this == rhs);
    }

    /// Test for inequality with a double.
    bool operator !=(double rhs) const
    {
        return !(*this == rhs);
    }

    /// Test for inequality with a Vector2.
    bool operator !=(const glm::vec2& rhs) const
    {
        return !(*this == rhs);
    }

    /// Test for inequality with an Vector4.
    bool operator !=(const glm::vec4& rhs) const
    {
        return !(*this == rhs);
    }

    /// Return int or zero on type mismatch. Floats and doubles are converted.
    int GetInt() const
    {
        if (type_ == VAR_INT)
            return value_.int_;
        else if (type_ == VAR_FLOAT)
            return static_cast<int>(value_.float_);
        else if (type_ == VAR_DOUBLE)
            return static_cast<int>(value_.double_);
        else
            return 0;
    }

    /// Return unsigned int or zero on type mismatch. Floats and doubles are converted.
    unsigned GetUInt() const
    {
        if (type_ == VAR_INT)
            return static_cast<unsigned>(value_.int_);
        else if (type_ == VAR_FLOAT)
            return static_cast<unsigned>(value_.float_);
        else if (type_ == VAR_DOUBLE)
            return static_cast<unsigned>(value_.double_);
        else
            return 0;
    }

    /// Return 64 bit int or zero on type mismatch. Floats and doubles are converted.
    long long GetInt64() const
    {
        if (type_ == VAR_INT64)
            return value_.int64_;
        else if (type_ == VAR_INT)
            return value_.int_;
        else if (type_ == VAR_FLOAT)
            return static_cast<long long>(value_.float_);
        else if (type_ == VAR_DOUBLE)
            return static_cast<long long>(value_.double_);
        else
            return 0;
    }

    /// Return bool or false on type mismatch.
    bool GetBool() const
    {
        return type_ == VAR_BOOL ? value_.bool_ : false;
    }

    /// Return float or zero on type mismatch. Ints and doubles are converted.
    float GetFloat() const
    {
        if (type_ == VAR_FLOAT)
            return value_.float_;
        else if (type_ == VAR_DOUBLE)
            return static_cast<float>(value_.double_);
        else if (type_ == VAR_INT)
            return static_cast<float>(value_.int_);
        else if (type_ == VAR_INT64)
            return static_cast<float>(value_.int64_);
        else
            return 0.0f;
    }

    /// Return double or zero on type mismatch. Ints and floats are converted.
    double GetDouble() const
    {
        if (type_ == VAR_DOUBLE)
            return value_.double_;
        else if (type_ == VAR_FLOAT)
            return value_.float_;
        else if (type_ == VAR_INT)
            return static_cast<double>(value_.int_);
        else if (type_ == VAR_INT64)
            return static_cast<double>(value_.int64_);
        else
            return 0.0;
    }

    /// Return Vector2 or zero on type mismatch.
    const glm::vec2& GetVector2() const
    {
        return type_ == VAR_VECTOR2 ? value_.vector2_ : glm::vec2();
    }

    /// Return Vector4 or zero on type mismatch.
    const glm::vec4& GetVector4() const
    {
        return type_ == VAR_VECTOR4 ? value_.vector4_ : glm::vec4();
    }

    /// Return the value, template version.
    template <class T> T Get() const;
private:
    void setType(VariantType newType);

    /// Variant type.
    VariantType type_ = VAR_NONE;
    /// Variant value.
    VariantValue value_;
};

/// Return variant type from type.
template <typename T> VariantType GetVariantType();

// Return variant type from concrete types
template <> inline VariantType GetVariantType<int>(){return VAR_INT;}

template <> inline VariantType GetVariantType<unsigned>(){return VAR_INT;}

template <> inline VariantType GetVariantType<long long>() {return VAR_INT64;}

template <> inline VariantType GetVariantType<bool>() { return VAR_BOOL; }

template <> inline VariantType GetVariantType<float>() { return VAR_FLOAT; }

template <> inline VariantType GetVariantType<double>() { return VAR_DOUBLE; }

template <> inline VariantType GetVariantType<glm::vec2>() { return VAR_VECTOR2; }

template <> inline VariantType GetVariantType<glm::vec4>() { return VAR_VECTOR4; }


// Specializations of Variant::Get<T>
template <> int Variant::Get<int>() const;

template <> unsigned Variant::Get<unsigned>() const;

template <> long long Variant::Get<long long>() const;

template <> bool Variant::Get<bool>() const;

template <> float Variant::Get<float>() const;

template <> double Variant::Get<double>() const;

template <> const glm::vec2& Variant::Get<const glm::vec2&>() const;

template <> const glm::vec4& Variant::Get<const glm::vec4&>() const;

template <> glm::vec2 Variant::Get<glm::vec2>() const;

template <> glm::vec4 Variant::Get<glm::vec4>() const;
