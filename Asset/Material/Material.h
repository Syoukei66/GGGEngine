#pragma once

#include "ShaderProperties.h"

struct MaterialData
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SERIALIZABLE(MaterialData)
  {
    archive(shader_unique_id_);
    archive(main_tex_unique_id_);
    archive(color_);
    archive(tiling_);
    archive(tiling_offset_);
    archive(billbording_);

    archive(bool_properties_);
    archive(int_properties_);
    archive(float_properties_);
    archive(vec2_properties_);
    archive(vec3_properties_);
    archive(vec4_properties_);
    archive(color_properties_);
    archive(matrix_properties_);
    archive(texture_properties_);
  }

  // =================================================================
  // Data Member
  // =================================================================
public:
  T_FIXED_UINT32 shader_unique_id_;
  T_FIXED_UINT32 main_tex_unique_id_;
  TColor color_;
  TVec2f tiling_;
  TVec2f tiling_offset_;
  bool billbording_;

  std::unordered_map<std::string, bool> bool_properties_;
  std::unordered_map<std::string, T_FIXED_INT32> int_properties_;
  std::unordered_map<std::string, T_FIXED_FLOAT> float_properties_;
  std::unordered_map<std::string, TVec2f> vec2_properties_;
  std::unordered_map<std::string, TVec3f> vec3_properties_;
  std::unordered_map<std::string, TVec4f> vec4_properties_;
  std::unordered_map<std::string, TColor> color_properties_;
  std::unordered_map<std::string, Matrix4x4> matrix_properties_;
  std::unordered_map<std::string, T_FIXED_UINT32> texture_properties_;
};

/*!
 * @brief マテリアル
 * シェーダーへのプロパティの受け渡しを担うクラス
 */
class rcMaterial : public GGAssetObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_ASSET(rcMaterial, MaterialData);
  GG_LOAD_FUNC(rcMaterial, SharedRef<rcShader>);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  virtual ~rcMaterial();

  // =================================================================
  // Methods
  // =================================================================
public:
  UniqueRef<rcMaterial> Clone() const;
  UniqueRef<rcMaterial> InitialClone() const;

public:
  void SetProperties(const SharedRef<rcShader>& shader) const;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  void SetShader(const SharedRef<rcShader>& shader);
  GG_INLINE SharedRef<rcShader> GetShader() const
  {
    return this->shader_;
  }

  GG_INLINE void SetTechnique(const std::string& technique)
  {
    this->technique_ = technique;
  }
  GG_INLINE const std::string& GetTechnique() const
  {
    return this->technique_;
  }

  GG_INLINE void SetRenderQueue(Graphics::RenderQueue queue)
  {
    this->queue_ = queue;
  }
  GG_INLINE Graphics::RenderQueue GetRenderQueue() const
  {
    return this->queue_;
  }

  void SetMainTexture(const SharedRef<const rcTexture>& texture);
  GG_INLINE SharedRef<const rcTexture> GetMainTexture() const
  {
    return this->texture_;
  }

  GG_INLINE void SetTiling(const TVec2f& tiling)
  {
    this->tiling_ = tiling;
  }
  GG_INLINE const TVec2f& GetTiling() const
  {
    return this->tiling_;
  }

  GG_INLINE void SetTilingOffset(const TVec2f& offset)
  {
    this->tiling_offset_ = offset;
  }
  GG_INLINE const TVec2f& GetTilingOffset() const
  {
    return this->tiling_offset_;
  }

  GG_INLINE void SetMainColor(const TColor& color)
  {
    this->color_ = color;
  }
  GG_INLINE void SetMainColor(T_FLOAT r, T_FLOAT g, T_FLOAT b)
  {
    this->color_.r = r;
    this->color_.g = g;
    this->color_.b = b;
  }
  GG_INLINE void SetMainColor(T_FLOAT r, T_FLOAT g, T_FLOAT b, T_FLOAT a)
  {
    this->color_.r = r;
    this->color_.g = g;
    this->color_.b = b;
    this->color_.a = a;
  }
  GG_INLINE TColor& GetMainColor()
  {
    return this->color_;
  }
  GG_INLINE const TColor& GetMainColor() const
  {
    return this->color_;
  }

  GG_INLINE void SetBillboardingFlag(bool billboarding)
  {
    this->billbording_ = billboarding;
  }

  GG_INLINE bool IsBillboard() const
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

  GG_INLINE ShaderProperty_bool& BoolProperty(const std::string& property_name)
  {
    return this->GetShaderProperty<ShaderProperty_bool>(property_name);
  }
  GG_INLINE const ShaderProperty_bool& BoolProperty(const std::string& property_name) const
  {
    return this->GetShaderProperty<ShaderProperty_bool>(property_name);
  }

  GG_INLINE ShaderProperty_int& IntProperty(const std::string& property_name)
  {
    return this->GetShaderProperty<ShaderProperty_int>(property_name);
  }
  GG_INLINE const ShaderProperty_int& IntProperty(const std::string& property_name) const
  {
    return this->GetShaderProperty<ShaderProperty_int>(property_name);
  }

  GG_INLINE ShaderProperty_float& FloatProperty(const std::string& property_name)
  {
    return this->GetShaderProperty<ShaderProperty_float>(property_name);
  }
  GG_INLINE const ShaderProperty_float& FloatProperty(const std::string& property_name) const
  {
    return this->GetShaderProperty<ShaderProperty_float>(property_name);
  }

  GG_INLINE ShaderProperty_vec2f& Vec2fProperty(const std::string& property_name)
  {
    return this->GetShaderProperty<ShaderProperty_vec2f>(property_name);
  }
  GG_INLINE const ShaderProperty_vec2f& Vec2fProperty(const std::string& property_name) const
  {
    return this->GetShaderProperty<ShaderProperty_vec2f>(property_name);
  }

  GG_INLINE ShaderProperty_vec3f& Vec3fProperty(const std::string& property_name)
  {
    return this->GetShaderProperty<ShaderProperty_vec3f>(property_name);
  }
  GG_INLINE const ShaderProperty_vec3f& Vec3fProperty(const std::string& property_name) const
  {
    return this->GetShaderProperty<ShaderProperty_vec3f>(property_name);
  }

  GG_INLINE ShaderProperty_vec4f& Vec4fProperty(const std::string& property_name)
  {
    return this->GetShaderProperty<ShaderProperty_vec4f>(property_name);
  }
  GG_INLINE const ShaderProperty_vec4f& Vec4fProperty(const std::string& property_name) const
  {
    return this->GetShaderProperty<ShaderProperty_vec4f>(property_name);
  }

  GG_INLINE ShaderProperty_color& ColorProperty(const std::string& property_name)
  {
    return this->GetShaderProperty<ShaderProperty_color>(property_name);
  }
  GG_INLINE const ShaderProperty_color& ColorProperty(const std::string& property_name) const
  {
    return this->GetShaderProperty<ShaderProperty_color>(property_name);
  }

  GG_INLINE ShaderProperty_matrix& MatrixProperty(const std::string& property_name)
  {
    return this->GetShaderProperty<ShaderProperty_matrix>(property_name);
  }
  GG_INLINE const ShaderProperty_matrix& MatrixProperty(const std::string& property_name) const
  {
    return this->GetShaderProperty<ShaderProperty_matrix>(property_name);
  }

  GG_INLINE ShaderProperty_texture& TextureProperty(const std::string& property_name)
  {
    return this->GetShaderProperty<ShaderProperty_texture>(property_name);
  }
  GG_INLINE const ShaderProperty_texture& TextureProperty(const std::string& property_name) const
  {
    return this->GetShaderProperty<ShaderProperty_texture>(property_name);
  }

  // =================================================================
  // Data Member
  // =================================================================
protected:
  SharedRef<rcShader> shader_;
  std::string technique_;

  Graphics::RenderQueue queue_;
  std::unordered_map<std::string, ShaderProperty*> properties_;

  SharedRef<const rcTexture> texture_;
  TVec2f tiling_;
  TVec2f tiling_offset_;
  TColor color_;
  bool billbording_;

};