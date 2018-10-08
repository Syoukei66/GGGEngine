#pragma once

#include <vector>
#include <unordered_map>
#include "Shader.h"
#include "ShaderProperties.h"
#include "GraphicsConstants.h"
#include "MaterialData.h"

class rcMaterial : public Resource
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static rcMaterial* CreateFromFile(const char* path);
  static rcMaterial* Create(rcShader* resource);
  static rcMaterial* Create(const MaterialData* data);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  rcMaterial(rcShader* shader);
  virtual ~rcMaterial();

  // =================================================================
  // Methods
  // =================================================================
public:
  rcMaterial* Clone() const;
  rcMaterial* InitialClone() const;

public:
  void SetProperties(rcShader* shader) const;

  // =================================================================
  // setter/getter
  // =================================================================
public:
  void SetShader(rcShader* shader);
  inline rcShader* GetShader() const
  {
    return this->shader_;
  }

  inline void SetTechnique(const std::string& technique)
  {
    this->technique_ = technique;
  }
  inline const std::string& GetTechnique() const
  {
    return this->technique_;
  }

  inline void SetRenderQueue(Graphics::RenderQueue queue)
  {
    this->queue_ = queue;
  }
  inline Graphics::RenderQueue GetRenderQueue() const
  {
    return this->queue_;
  }

  void SetMainTexture(const rcTexture* texture);
  inline const rcTexture* GetMainTexture() const
  {
    return this->texture_;
  }

  inline void SetTiling(const TVec2f& tiling)
  {
    this->tiling_ = tiling;
  }
  inline const TVec2f& GetTiling() const
  {
    return this->tiling_;
  }

  inline void SetTilingOffset(const TVec2f& offset)
  {
    this->tiling_offset_ = offset;
  }
  inline const TVec2f& GetTilingOffset() const
  {
    return this->tiling_offset_;
  }

  inline void SetMainColor(const TColor& color)
  {
    this->color_ = color;
  }
  inline void SetMainColor(T_FLOAT r, T_FLOAT g, T_FLOAT b)
  {
    this->color_.r = r;
    this->color_.g = g;
    this->color_.b = b;
  }
  inline void SetMainColor(T_FLOAT r, T_FLOAT g, T_FLOAT b, T_FLOAT a)
  {
    this->color_.r = r;
    this->color_.g = g;
    this->color_.b = b;
    this->color_.a = a;
  }
  inline TColor& GetMainColor()
  {
    return this->color_;
  }
  inline const TColor& GetMainColor() const
  {
    return this->color_;
  }

  inline void SetBillboardingFlag(bool billboarding)
  {
    this->billbording_ = billboarding;
  }

  inline bool IsBillboard() const
  {
    return this->billbording_;
  }

  template <class T>
  T& GetShaderProperty(const std::string& property_name)
  {
    T* ret = (T*)this->properties_[property_name];
    if (!ret)
    {
      ret = new T();
      this->properties_[property_name] = ret;
    }
    return *ret;
  }

  template <class T>
  const T& GetShaderProperty(const std::string& property_name) const
  {
    T* ret = (T*)const_cast<rcMaterial*>(this)->properties_[property_name];
    if (!ret)
    {
      ret = new T();
      const_cast<rcMaterial*>(this)->properties_[property_name] = ret;
    }
    return *ret;
  }

  inline ShaderProperty_bool& BoolProperty(const std::string& property_name)
  {
    return this->GetShaderProperty<ShaderProperty_bool>(property_name);
  }
  inline const ShaderProperty_bool& BoolProperty(const std::string& property_name) const
  {
    return this->GetShaderProperty<ShaderProperty_bool>(property_name);
  }

  inline ShaderProperty_int& IntProperty(const std::string& property_name)
  {
    return this->GetShaderProperty<ShaderProperty_int>(property_name);
  }
  inline const ShaderProperty_int& IntProperty(const std::string& property_name) const
  {
    return this->GetShaderProperty<ShaderProperty_int>(property_name);
  }

  inline ShaderProperty_float& FloatProperty(const std::string& property_name)
  {
    return this->GetShaderProperty<ShaderProperty_float>(property_name);
  }
  inline const ShaderProperty_float& FloatProperty(const std::string& property_name) const
  {
    return this->GetShaderProperty<ShaderProperty_float>(property_name);
  }

  inline ShaderProperty_vec2f& Vec2fProperty(const std::string& property_name)
  {
    return this->GetShaderProperty<ShaderProperty_vec2f>(property_name);
  }
  inline const ShaderProperty_vec2f& Vec2fProperty(const std::string& property_name) const
  {
    return this->GetShaderProperty<ShaderProperty_vec2f>(property_name);
  }

  inline ShaderProperty_vec3f& Vec3fProperty(const std::string& property_name)
  {
    return this->GetShaderProperty<ShaderProperty_vec3f>(property_name);
  }
  inline const ShaderProperty_vec3f& Vec3fProperty(const std::string& property_name) const
  {
    return this->GetShaderProperty<ShaderProperty_vec3f>(property_name);
  }

  inline ShaderProperty_vec4f& Vec4fProperty(const std::string& property_name)
  {
    return this->GetShaderProperty<ShaderProperty_vec4f>(property_name);
  }
  inline const ShaderProperty_vec4f& Vec4fProperty(const std::string& property_name) const
  {
    return this->GetShaderProperty<ShaderProperty_vec4f>(property_name);
  }

  inline ShaderProperty_color& ColorProperty(const std::string& property_name)
  {
    return this->GetShaderProperty<ShaderProperty_color>(property_name);
  }
  inline const ShaderProperty_color& ColorProperty(const std::string& property_name) const
  {
    return this->GetShaderProperty<ShaderProperty_color>(property_name);
  }

  inline ShaderProperty_matrix& MatrixProperty(const std::string& property_name)
  {
    return this->GetShaderProperty<ShaderProperty_matrix>(property_name);
  }
  inline const ShaderProperty_matrix& MatrixProperty(const std::string& property_name) const
  {
    return this->GetShaderProperty<ShaderProperty_matrix>(property_name);
  }

  inline ShaderProperty_texture& TextureProperty(const std::string& property_name)
  {
    return this->GetShaderProperty<ShaderProperty_texture>(property_name);
  }
  inline const ShaderProperty_texture& TextureProperty(const std::string& property_name) const
  {
    return this->GetShaderProperty<ShaderProperty_texture>(property_name);
  }

  // =================================================================
  // Data Member
  // =================================================================
protected:
  rcShader* shader_;
  std::string technique_;

  Graphics::RenderQueue queue_;
  std::unordered_map<std::string, ShaderProperty*> properties_;

  const rcTexture* texture_;
  TVec2f tiling_;
  TVec2f tiling_offset_;
  TColor color_;
  bool billbording_;

};