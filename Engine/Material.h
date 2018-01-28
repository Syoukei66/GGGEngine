#pragma once

#include <unordered_map>

#include "NativeAssert.h"
#include "Color.h"
#include "ShaderResource.h"
#include "Texture.h"
#include "ShaderProperties.h"

class GameObjectRenderState;

class Material
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Material(const ShaderResource& resource, bool protect = false);
  ~Material();

  // =================================================================
  // delegate to shader
  // =================================================================
public:
  Material* Clone();
  Material* InitialClone();

  T_UINT8 Begin();
  void BeginPass(T_UINT8 path_id);
  void SetWorldMatrix(GameObjectRenderState* state);
  void CommitChanges();
  void EndPass();
  void End();

  // =================================================================
  // setter/getter
  // =================================================================
public:
  inline INativeShader* GetShader()
  {
    return this->shader_resource_->GetContents();
  }

  template <class T>
  T& GetShaderProperty(const std::string& property_name) const
  {
    T* ret = (T*)const_cast<Material*>(this)->properties_[property_name];
    if (!ret)
    {
      ret = new T();
      const_cast<Material*>(this)->properties_[property_name] = ret;
    }
    return *ret;
  }

  inline ShaderProperty_bool& BoolProperty(const std::string& property_name)
  {
    NATIVE_ASSERT(!this->protected_, "�ی삳�ꂽ�}�e���A����ύX���悤�Ƃ��܂���");
    return this->GetShaderProperty<ShaderProperty_bool>(property_name);
  }
  inline const ShaderProperty_bool& BoolProperty(const std::string& property_name) const
  {
    return this->GetShaderProperty<ShaderProperty_bool>(property_name);
  }

  inline ShaderProperty_int& IntProperty(const std::string& property_name)
  {
    NATIVE_ASSERT(!this->protected_, "�ی삳�ꂽ�}�e���A����ύX���悤�Ƃ��܂���");
    return this->GetShaderProperty<ShaderProperty_int>(property_name);
  }
  inline const ShaderProperty_int& IntProperty(const std::string& property_name) const
  {
    return this->GetShaderProperty<ShaderProperty_int>(property_name);
  }

  inline ShaderProperty_float& FloatProperty(const std::string& property_name)
  {
    NATIVE_ASSERT(!this->protected_, "�ی삳�ꂽ�}�e���A����ύX���悤�Ƃ��܂���");
    return this->GetShaderProperty<ShaderProperty_float>(property_name);
  }
  inline const ShaderProperty_float& FloatProperty(const std::string& property_name) const
  {
    return this->GetShaderProperty<ShaderProperty_float>(property_name);
  }

  inline ShaderProperty_vec2f& Vec2fProperty(const std::string& property_name)
  {
    NATIVE_ASSERT(!this->protected_, "�ی삳�ꂽ�}�e���A����ύX���悤�Ƃ��܂���");
    return this->GetShaderProperty<ShaderProperty_vec2f>(property_name);
  }
  inline const ShaderProperty_vec2f& Vec2fProperty(const std::string& property_name) const
  {
    return this->GetShaderProperty<ShaderProperty_vec2f>(property_name);
  }

  inline ShaderProperty_vec3f& Vec3fProperty(const std::string& property_name)
  {
    NATIVE_ASSERT(!this->protected_, "�ی삳�ꂽ�}�e���A����ύX���悤�Ƃ��܂���");
    return this->GetShaderProperty<ShaderProperty_vec3f>(property_name);
  }
  inline const ShaderProperty_vec3f& Vec3fProperty(const std::string& property_name) const
  {
    return this->GetShaderProperty<ShaderProperty_vec3f>(property_name);
  }

  inline ShaderProperty_vec4f& Vec4fProperty(const std::string& property_name)
  {
    NATIVE_ASSERT(!this->protected_, "�ی삳�ꂽ�}�e���A����ύX���悤�Ƃ��܂���");
    return this->GetShaderProperty<ShaderProperty_vec4f>(property_name);
  }
  inline const ShaderProperty_vec4f& Vec4fProperty(const std::string& property_name) const
  {
    return this->GetShaderProperty<ShaderProperty_vec4f>(property_name);
  }

  inline ShaderProperty_color& ColorProperty(const std::string& property_name)
  {
    NATIVE_ASSERT(!this->protected_, "�ی삳�ꂽ�}�e���A����ύX���悤�Ƃ��܂���");
    return this->GetShaderProperty<ShaderProperty_color>(property_name);
  }
  inline const ShaderProperty_color& ColorProperty(const std::string& property_name) const
  {
    return this->GetShaderProperty<ShaderProperty_color>(property_name);
  }

  inline ShaderProperty_matrix& MatrixProperty(const std::string& property_name)
  {
    NATIVE_ASSERT(!this->protected_, "�ی삳�ꂽ�}�e���A����ύX���悤�Ƃ��܂���");
    return this->GetShaderProperty<ShaderProperty_matrix>(property_name);
  }
  inline const ShaderProperty_matrix& MatrixProperty(const std::string& property_name) const
  {
    return this->GetShaderProperty<ShaderProperty_matrix>(property_name);
  }

  inline ShaderProperty_texture& TextureProperty(const std::string& property_name)
  {
    NATIVE_ASSERT(!this->protected_, "�ی삳�ꂽ�}�e���A����ύX���悤�Ƃ��܂���");
    return this->GetShaderProperty<ShaderProperty_texture>(property_name);
  }
  inline const ShaderProperty_texture& TextureProperty(const std::string& property_name) const
  {
    return this->GetShaderProperty<ShaderProperty_texture>(property_name);
  }

  inline void SetMainTexture(const Texture& texture)
  {
    NATIVE_ASSERT(!this->protected_, "�ی삳�ꂽ�}�e���A����ύX���悤�Ƃ��܂���");
    this->texture_ = &texture;
  }
  inline const Texture* GetMainTexture() const
  {
    return this->texture_;
  }

  inline void SetDiffuse(const Color4F& color)
  {
    NATIVE_ASSERT(!this->protected_, "�ی삳�ꂽ�}�e���A����ύX���悤�Ƃ��܂���");
    this->color_ = color;
  }
  inline void SetDiffuse(T_FLOAT r, T_FLOAT g, T_FLOAT b)
  {
    NATIVE_ASSERT(!this->protected_, "�ی삳�ꂽ�}�e���A����ύX���悤�Ƃ��܂���");
    this->color_.SetColor(r, g, b);
  }
  inline void SetDiffuse(T_FLOAT r, T_FLOAT g, T_FLOAT b, T_FLOAT a)
  {
    NATIVE_ASSERT(!this->protected_, "�ی삳�ꂽ�}�e���A����ύX���悤�Ƃ��܂���");
    this->color_.SetColor(r, g, b, a);
  }
  inline Color4F& GetDiffuse()
  {
    NATIVE_ASSERT(!this->protected_, "�ی삳�ꂽ�}�e���A����ύX���悤�Ƃ��܂���");
    return this->color_;
  }
  inline const Color4F& GetDiffuse() const
  {
    return this->color_;
  }

  inline void SetZTestLevel(T_UINT8 level)
  {
    NATIVE_ASSERT(!this->protected_, "�ی삳�ꂽ�}�e���A����ύX���悤�Ƃ��܂���");
    this->z_test_level_ = level;
  }
  inline T_UINT8 GetZTestLevel() const
  {
    return this->z_test_level_;
  }

  inline void SetBillboardingFlag(bool billboarding)
  {
    NATIVE_ASSERT(!this->protected_, "�ی삳�ꂽ�}�e���A����ύX���悤�Ƃ��܂���");
    this->billbording_ = billboarding;
  }

  inline bool IsBillboard() const
  {
    return this->billbording_;
  }
  // =================================================================
  // Data Member
  // =================================================================
protected:
  const bool protected_;
  const ShaderResource* const shader_resource_;
  std::unordered_map<std::string, ShaderProperty*> properties_;

  Color4F color_;
  const Texture* texture_;

  T_UINT8 z_test_level_;
  bool billbording_;

  std::vector<Material*> clones_;
};
