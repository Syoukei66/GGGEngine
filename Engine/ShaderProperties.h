#pragma once

#include <string>
#include "NativeShader.h"

class ShaderProperty
{
public:
  virtual void Apply(INativeShader* shader, const std::string& property_name) = 0;
  virtual ShaderProperty* Clone() = 0;
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
  void Apply(INativeShader* shader, const std::string& property_name) override
  {
    shader->SetBool(property_name.c_str(), this->value_);
  }
  ShaderProperty* Clone() override
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
  void Apply(INativeShader* shader, const std::string& property_name) override
  {
    shader->SetInt(property_name.c_str(), this->value_);
  }
  ShaderProperty* Clone() override
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
  void Apply(INativeShader* shader, const std::string& property_name) override
  {
    shader->SetFloat(property_name.c_str(), this->value_);
  }
  ShaderProperty* Clone() override
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
  operator T&()
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
  void Apply(INativeShader* shader, const std::string& property_name) override
  {
    shader->SetVec2f(property_name.c_str(), this->value_);
  }
  ShaderProperty* Clone() override
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
  void Apply(INativeShader* shader, const std::string& property_name) override
  {
    shader->SetVec3f(property_name.c_str(), this->value_);
  }
  ShaderProperty* Clone() override
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
  void Apply(INativeShader* shader, const std::string& property_name) override
  {
    shader->SetVec4f(property_name.c_str(), this->value_);
  }
  ShaderProperty* Clone() override
  {
    ShaderProperty_vec4f* ret = new ShaderProperty_vec4f();
    ret->value_ = this->value_;
    return ret;
  }
};

class ShaderProperty_color : public ShaderProperty_struct<Color4F>
{
public:
  const ShaderProperty_color& operator = (const Color4F& b)
  {
    ShaderProperty_struct::operator=(b);
    return *this;
  }
public:
  void Apply(INativeShader* shader, const std::string& property_name) override
  {
    shader->SetColor(property_name.c_str(), this->value_);
  }
  ShaderProperty* Clone() override
  {
    ShaderProperty_color* ret = new ShaderProperty_color();
    ret->value_ = this->value_;
    return ret;
  }
};

// =================================================================
// object
// =================================================================
template<typename T>
class ShaderProperty_native : public ShaderProperty
{
public:
  ShaderProperty_native()
    : value_()
  {}

public:
  operator const T*&()
  {
    return this->value_;
  }

  const T* operator = (const T* b)
  {
    this->value_ = b;
    return b;
  }

public:
  inline void SetValue(const T* value)
  {
    this->value_ = value;
  }
  inline const T* GetValue() const
  {
    return this->value_;
  }

protected:
  const T* value_;
};

class ShaderProperty_matrix : public ShaderProperty_native<INativeMatrix>
{
public:
  const ShaderProperty_matrix& operator = (const INativeMatrix* b)
  {
    ShaderProperty_native::operator=(b);
    return *this;
  }
public:
  void Apply(INativeShader* shader, const std::string& property_name) override
  {
    if (!this->value_)
    {
      return;
    }
    shader->SetMatrix(property_name.c_str(), this->value_->GetNativeInstance());
  }
  ShaderProperty* Clone() override
  {
    ShaderProperty_matrix* ret = new ShaderProperty_matrix();
    ret->value_ = this->value_;
    return ret;
  }
};

class ShaderProperty_texture : public ShaderProperty_native<INativeTexture>
{
public:
  const ShaderProperty_texture& operator = (const INativeTexture* b)
  {
    ShaderProperty_native::operator=(b);
    return *this;
  }
public:
  void Apply(INativeShader* shader, const std::string& property_name) override
  {
    if (!this->value_)
    {
      return;
    }
    shader->SetTexture(property_name.c_str(), this->value_->GetNativeInstance());
  }
  ShaderProperty* Clone() override
  {
    ShaderProperty_texture* ret = new ShaderProperty_texture();
    ret->value_ = this->value_;
    return ret;
  }
};

