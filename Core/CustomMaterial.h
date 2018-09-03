#pragma once

#include <unordered_map>
#include "Material.h"
#include "ShaderProperties.h"
#include "MaterialData.h"

class rcCustomMaterial : public rcMaterial
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static rcCustomMaterial* Create(rcShader* resource, bool protect = false);
  static rcCustomMaterial* Create(const MaterialData& data);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  rcCustomMaterial(rcShader* resource, bool protect = false);
  ~rcCustomMaterial();

  // =================================================================
  // Methods
  // =================================================================
protected:
  virtual rcMaterial* CreateClone(rcShader* shader) override;
  virtual void CopyPropertiesToClone(rcMaterial* clone) override;
  virtual void SetProperties(rcShader* shader) override;

  // =================================================================
  // setter/getter
  // =================================================================
public:
  template <class T>
  T& GetShaderProperty(const std::string& property_name)
  {
    this->ProtectedAssertion();
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
    T* ret = (T*)const_cast<rcCustomMaterial*>(this)->properties_[property_name];
    if (!ret)
    {
      ret = new T();
      const_cast<rcCustomMaterial*>(this)->properties_[property_name] = ret;
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
  std::unordered_map<std::string, ShaderProperty*> properties_;
};
