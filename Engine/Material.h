#pragma once

#include "Color.h"
#include "Texture.h"
#include "ShaderResource.h"
#include "BlendFunction.h"

class Material
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Material();
  ~Material();

  // =================================================================
  // delegate to shader
  // =================================================================
public:
  inline void Begin()
  {
    this->shader_->Begin();
  }
  inline void End()
  {
    this->shader_->End();
  }

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
  inline void SetMatrix(const char* property_name, const INativeMatrix& matrix)
  {
    this->
    this->shader_->SetMatrix(property_name, matrix.GetNativeInstance());
  }
  inline void SetTexture(const char* property_name, const INativeTexture& texture)
  {
    this->shader_->SetTexture(property_name, texture.GetNativeInstance());
  }

  inline void GetBool(const char* property_name, bool* dest)
  {
    this->shader_->GetBool(property_name, dest);
  }
  inline void GetInt(const char* property_name, T_INT32* dest)
  {
    this->shader_->GetInt(property_name, dest);
  }
  inline void GetFloat(const char* property_name, T_FLOAT* dest)
  {
    this->shader_->GetFloat(property_name, dest);
  }
  inline void GetVec2f(const char* property_name, TVec2f* dest)
  {
    this->shader_->GetVec2f(property_name, dest);
  }
  inline void GetVec3f(const char* property_name, TVec3f* dest)
  {
    this->shader_->GetVec3f(property_name, dest);
  }
  inline void GetVec4f(const char* property_name, TVec4f* dest)
  {
    this->shader_->GetVec4f(property_name, dest);
  }
  inline void GetColor(const char* property_name, Color4F* dest)
  {
    this->shader_->GetColor(property_name, dest);
  }
  inline void GetMatrix(const char* property_name, INativeMatrix* dest)
  {
    this->shader_->GetMatrix(property_name, dest);
  }
  inline void GetTexture(const char* property_name, INativeTexture* dest)
  {
    this->shader_->GetTexture(property_name, dest);
  }

  // =================================================================
  // setter/getter
  // =================================================================
  inline void SetShader(INativeShader* shader)
  {
    this->shader_ = shader;
  }

  inline INativeShader* GetShader()
  {
    return this->shader_;
  }

  inline void SetColor(const Color4F& color)
  {
    this->color_ = color;
  }
  inline void SetColor(T_FLOAT r, T_FLOAT g, T_FLOAT b)
  {
    this->color_.SetColor(r, g, b);
  }
  inline void SetColor(T_FLOAT r, T_FLOAT g, T_FLOAT b, T_FLOAT a)
  {
    this->color_.SetColor(r, g, b, a);
  }
  inline const Color4F& GetColor() const
  {
    return this->color_;
  }
  inline void SetRed(T_FLOAT r)
  {
    this->color_.SetRed(r);
  }
  inline T_FLOAT GetRed() const
  {
    return this->color_.GetRed();
  }
  inline void SetGreen(T_FLOAT g)
  {
    this->color_.SetGreen(g);
  }
  inline T_FLOAT GetGreen() const
  {
    return this->color_.GetGreen();
  }
  inline void SetBlue(T_FLOAT b)
  {
    this->color_.SetBlue(b);
  }
  inline T_FLOAT GetBlue() const
  {
    return this->color_.GetBlue();
  }
  inline void SetAlpha(T_FLOAT a)
  {
    this->color_.SetAlpha(a);
  }
  inline T_FLOAT GetAlpha() const
  {
    return this->color_.GetAlpha();
  }

  inline void SetBlendFunction(BlendFunction::BlendMode src, BlendFunction::BlendMode dst)
  {
    this->blend_function_src_ = src;
    this->blend_function_dst_ = dst;
  }
  inline void SetBlendFunctionSource(BlendFunction::BlendMode src)
  {
    this->blend_function_src_ = src;
  }
  inline BlendFunction::BlendMode GetBlendFunctionSource() const
  {
    return this->blend_function_src_;
  }
  inline void SetBlendFunctionDestination(BlendFunction::BlendMode dst)
  {
    this->blend_function_dst_ = dst;
  }
  inline BlendFunction::BlendMode GetBlendFunctionDestination() const
  {
    return this->blend_function_dst_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  std::map<std::string, bool> bool_values_;
  std::map<std::string, T_INT32> int_values_;
  std::map<std::string, T_FLOAT> float_values_;
  std::map<std::string, TVec2f> vec2_values_;
  std::map<std::string, TVec3f> vec3_values_;
  std::map<std::string, TVec4f> vec4_values_;
  std::map<std::string, Color4F> color_values_;
  std::map<std::string, NativeMatrixInstance> matrix_values_;
  std::map<std::string, NativeTextureInstance> texture_values_;

  INativeShader* shader_;
  Texture* texture_;
  Color4F color_;

  BlendFunction::BlendMode blend_function_src_;
  BlendFunction::BlendMode blend_function_dst_;
};
