#pragma once

#include "Material.h"

class ModifiableMaterial : public Material
{

public:
  inline void SetBool(const char* property_name, bool val)
  {
    this->bool_values_[property_name] = val;
  }
  inline void SetInt(const char* property_name, T_INT32 val)
  {
    this->int_values_[property_name] = val;
  }
  inline void SetFloat(const char* property_name, T_FLOAT val)
  {
    this->float_values_[property_name] = val;
  }
  inline void SetVec2f(const char* property_name, const TVec2f& vec)
  {
    this->vec2_values_[property_name] = vec;
  }
  inline void SetVec3f(const char* property_name, const TVec3f& vec)
  {
    this->vec3_values_[property_name] = vec;
  }
  inline void SetVec4f(const char* property_name, const TVec4f& vec)
  {
    this->vec4_values_[property_name] = vec;
  }
  inline void SetColor(const char* property_name, const Color4F& color)
  {
    this->color_values_[property_name] = color;
  }
  inline void SetMatrix(const char* property_name, const INativeMatrix* matrix)
  {
    this->matrix_values_[property_name] = matrix;
  }
  inline void SetTexture(const char* property_name, const INativeTexture* texture)
  {
    this->texture_values_[property_name] = texture;
  }

  inline bool GetBool(const char* property_name)
  {
    return this->bool_values_[property_name];
  }
  inline T_INT32 GetInt(const char* property_name)
  {
    return this->int_values_[property_name];
  }
  inline T_FLOAT GetFloat(const char* property_name)
  {
    return this->float_values_[property_name];
  }
  inline const TVec2f& GetVec2f(const char* property_name)
  {
    return this->vec2_values_[property_name];
  }
  inline const TVec3f& GetVec3f(const char* property_name)
  {
    return this->vec3_values_[property_name];
  }
  inline const TVec4f& GetVec4f(const char* property_name)
  {
    return this->vec4_values_[property_name];
  }
  inline const Color4F& GetColor(const char* property_name)
  {
    return this->color_values_[property_name];
  }
  inline const INativeMatrix* GetMatrix(const char* property_name)
  {
    return this->matrix_values_[property_name];
  }
  inline const INativeTexture* GetTexture(const char* property_name)
  {
    return this->texture_values_[property_name];
  }

private:
  std::map<std::string, bool> bool_values_;
  std::map<std::string, T_INT32> int_values_;
  std::map<std::string, T_FLOAT> float_values_;
  std::map<std::string, TVec2f> vec2_values_;
  std::map<std::string, TVec3f> vec3_values_;
  std::map<std::string, TVec4f> vec4_values_;
  std::map<std::string, Color4F> color_values_;
  std::map<std::string, const INativeMatrix*> matrix_values_;
  std::map<std::string, const INativeTexture*> texture_values_;

};