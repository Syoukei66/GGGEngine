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
  virtual void Begin();
  virtual void End();

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
protected:
  INativeShader* shader_;
  Texture* texture_;
  Color4F color_;

  BlendFunction::BlendMode blend_function_src_;
  BlendFunction::BlendMode blend_function_dst_;
};
