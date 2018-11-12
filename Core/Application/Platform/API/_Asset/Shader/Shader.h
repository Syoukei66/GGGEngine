#pragma once

#include <Core/Application/Platform/API/_Asset/APIAssetObject.h>

class rcTexture;

class rcShader : public GGAPIAssetObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(rcShader);

  // =================================================================
  // Factory Method
  // =================================================================
public:
  static UniqueRef<rcShader> CreateFromFile(const char* path);
  
  // =================================================================
  // Method 
  // =================================================================
public:
  virtual T_UINT8 Begin() = 0;
  virtual void BeginPass(T_UINT8 path_id) = 0;
  virtual void CommitChanges() = 0;
  virtual void EndPass() = 0;
  virtual void End() = 0;

  virtual void SetTechnique(const std::string& technique_name) = 0;

  virtual void SetBool(const std::string& property_name, bool val) = 0;
  virtual void SetInt(const std::string& property_name, T_INT32 val) = 0;
  virtual void SetFloat(const std::string& property_name, T_FLOAT val) = 0;

  virtual void SetVec2f(const std::string& property_name, const TVec2f& vec) = 0;
  virtual void SetVec3f(const std::string& property_name, const TVec3f& vec) = 0;
  virtual void SetVec4f(const std::string& property_name, const TVec4f& vec) = 0;

  virtual void SetColor(const std::string& property_name, const TColor& color) = 0;
  virtual void SetMatrix(const std::string& property_name, const Matrix4x4& matrix) = 0;
  virtual void SetTexture(const std::string& property_name, const SharedRef<const rcTexture>& texture) = 0;

  virtual void GetBool(const std::string& property_name, bool* dest) = 0;
  virtual void GetInt(const std::string& property_name, T_INT32* dest) = 0;
  virtual void GetFloat(const std::string& property_name, T_FLOAT* dest) = 0;

  virtual void GetVec2f(const std::string& property_name, TVec2f* dest) = 0;
  virtual void GetVec3f(const std::string& property_name, TVec3f* dest) = 0;
  virtual void GetVec4f(const std::string& property_name, TVec4f* dest) = 0;

  virtual void GetColor(const std::string& property_name, TColor* dest) = 0;
  virtual void GetMatrix(const std::string& property_name, Matrix4x4* dest) = 0;
  virtual void GetTexture(const std::string& property_name, void* native_dest) = 0;
};