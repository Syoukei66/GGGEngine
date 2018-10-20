#pragma once

#include <string>
#include "Shader.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

class ShaderProperty
{
public:
  virtual ~ShaderProperty() {}

public:
  virtual void Apply(const SharedRef<rcShader>& shader, const std::string& property_name) const = 0;
  virtual ShaderProperty* Clone() const = 0;
};

// =================================================================
// primitive
// =================================================================
template<typename T>
class ShaderProperty_primitive : public ShaderProperty
{
public:
  ShaderProperty_primitive()
    : value_()
  {}

public:
  operator T&()
  {
    return this->value_;
  }
  
  ShaderProperty_primitive<T>& operator = (T b)
  {
    this->value_ = b;
    return *this;
  }

public:
  inline void SetValue(T value)
  {
    this->value_ = value;
  }
  inline T GetValue() const
  {
    return this->value_;
  }

protected:
  T value_;
};

class ShaderProperty_bool : public ShaderProperty_primitive<bool>
{
public:
  ShaderProperty_bool& operator = (bool b)
  {
    ShaderProperty_primitive::operator=(b);
    return *this;
  }

public:
  void Apply(const SharedRef<rcShader>& shader, const std::string& property_name) const override
  {
    shader->SetBool(property_name, this->value_);
  }
  ShaderProperty* Clone() const override
  {
    ShaderProperty_bool* ret = new ShaderProperty_bool();
    ret->value_ = this->value_;
    return ret;
  }
};

class ShaderProperty_int : public ShaderProperty_primitive<T_INT32>
{
public:
  ShaderProperty_int& operator = (T_INT32 b)
  {
    ShaderProperty_primitive::operator=(b);
    return *this;
  }

public:
  void Apply(const SharedRef<rcShader>& shader, const std::string& property_name) const override
  {
    shader->SetInt(property_name, this->value_);
  }
  ShaderProperty* Clone() const override
  {
    ShaderProperty_int* ret = new ShaderProperty_int();
    ret->value_ = this->value_;
    return ret;
  }
};

class ShaderProperty_float : public ShaderProperty_primitive<T_FLOAT>
{
public:
  ShaderProperty_float& operator = (T_FLOAT b)
  {
    ShaderProperty_primitive::operator=(b);
    return *this;
  }

public:
  void Apply(const SharedRef<rcShader>& shader, const std::string& property_name) const override
  {
    shader->SetFloat(property_name, this->value_);
  }
  ShaderProperty* Clone() const override
  {
    ShaderProperty_float* ret = new ShaderProperty_float();
    ret->value_ = this->value_;
    return ret;
  }
};

// =================================================================
// struct
// =================================================================
template<typename T>
class ShaderProperty_struct : public ShaderProperty
{
public:
  ShaderProperty_struct()
    : value_()
  {}

public:
  operator T&() const
  {
    return this->value_;
  }

  ShaderProperty_struct<T>& operator = (const T& b)
  {
    this->value_ = b;
    return *this;
  }

public:
  inline void SetValue(const T& value)
  {
    this->value_ = value;
  }
  inline const T& GetValue() const
  {
    return this->value_;
  }

protected:
  T value_;
};

class ShaderProperty_vec2f : public ShaderProperty_struct<TVec2f>
{
public:
  const ShaderProperty_vec2f& operator = (const TVec2f& b)
  {
    ShaderProperty_struct::operator=(b);
    return *this;
  }
public:
  void Apply(const SharedRef<rcShader>& shader, const std::string& property_name) const override
  {
    shader->SetVec2f(property_name, this->value_);
  }
  ShaderProperty* Clone() const override
  {
    ShaderProperty_vec2f* ret = new ShaderProperty_vec2f();
    ret->value_ = this->value_;
    return ret;
  }
};

class ShaderProperty_vec3f : public ShaderProperty_struct<TVec3f>
{
public:
  const ShaderProperty_vec3f& operator = (const TVec3f& b)
  {
    ShaderProperty_struct::operator=(b);
    return *this;
  }
public:
  void Apply(const SharedRef<rcShader>& shader, const std::string& property_name) const override
  {
    shader->SetVec3f(property_name, this->value_);
  }
  ShaderProperty* Clone() const override
  {
    ShaderProperty_vec3f* ret = new ShaderProperty_vec3f();
    ret->value_ = this->value_;
    return ret;
  }
};

class ShaderProperty_vec4f : public ShaderProperty_struct<TVec4f>
{
public:
  const ShaderProperty_vec4f& operator = (const TVec4f& b)
  {
    ShaderProperty_struct::operator=(b);
    return *this;
  }
public:
  void Apply(const SharedRef<rcShader>& shader, const std::string& property_name) const override
  {
    shader->SetVec4f(property_name, this->value_);
  }
  ShaderProperty* Clone() const override
  {
    ShaderProperty_vec4f* ret = new ShaderProperty_vec4f();
    ret->value_ = this->value_;
    return ret;
  }
};

class ShaderProperty_color : public ShaderProperty_struct<TColor>
{
public:
  const ShaderProperty_color& operator = (const TColor& b)
  {
    ShaderProperty_struct::operator=(b);
    return *this;
  }
public:
  void Apply(const SharedRef<rcShader>& shader, const std::string& property_name) const override
  {
    shader->SetColor(property_name, this->value_);
  }
  ShaderProperty* Clone() const override
  {
    ShaderProperty_color* ret = new ShaderProperty_color();
    ret->value_ = this->value_;
    return ret;
  }
};

class ShaderProperty_matrix : public ShaderProperty_struct<Matrix4x4>
{
public:
  const ShaderProperty_matrix& operator = (const Matrix4x4& b)
  {
    ShaderProperty_struct::operator=(b);
    return *this;
  }
public:
  void Apply(const SharedRef<rcShader>& shader, const std::string& property_name) const override
  {
    if (!this->value_)
    {
      return;
    }
    shader->SetMatrix(property_name, this->value_);
  }
  ShaderProperty* Clone() const override
  {
    ShaderProperty_matrix* ret = new ShaderProperty_matrix();
    ret->value_ = this->value_;
    return ret;
  }
};

// =================================================================
// resource
// =================================================================
template<typename T>
class ShaderProperty_resource : public ShaderProperty
{
public:
  ShaderProperty_resource()
    : value_()
  {}
  
public:
  operator SharedRef<const T>() const
  {
    return this->value_;
  }

  const SharedRef<const T>& operator = (const SharedRef<const T>& b)
  {
    this->SetValue(b);
    return b;
  }

public:
  inline void SetValue(const SharedRef<const T>& value)
  {
    this->value_ = value;
  }
  inline SharedRef<const T> GetValue() const
  {
    return this->value_;
  }

protected:
  SharedRef<const T> value_;
};

class ShaderProperty_texture : public ShaderProperty_resource<rcTexture>
{
public:
  const ShaderProperty_texture& operator = (const SharedRef<const rcTexture>& b)
  {
    ShaderProperty_resource::operator=(b);
    return *this;
  }
public:
  void Apply(const SharedRef<rcShader>& shader, const std::string& property_name) const override
  {
    if (!this->value_)
    {
      return;
    }
    shader->SetTexture(property_name, this->value_);
  }
  ShaderProperty* Clone() const override
  {
    ShaderProperty_texture* ret = new ShaderProperty_texture();
    ret->value_ = this->value_;
    return ret;
  }
};

