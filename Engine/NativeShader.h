#pragma once

#include <string>
#include "Geometry.h"
#include "NativeObject.h"
#include "Color.h"
#include "NativeMatrix.h"
#include "NativeTexture.h"

struct NativeShaderInstance { void* p; };

class INativeShader : public NativeObject<NativeShaderInstance>
{
  // =================================================================
  // Static Method
  // =================================================================
public:
  static INativeShader* Create(const char* path);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  INativeShader(NativeShaderInstance* instance)
    : NativeObject(instance)
  {}

  INativeShader() {}

  virtual ~INativeShader() {}

  //ƒRƒs[‹ÖŽ~
private:
  INativeShader(const INativeShader& shader) {}

  // =================================================================
  // Method 
  // =================================================================
public:
  virtual T_UINT8 Begin() = 0;
  virtual void BeginPass(T_UINT8 path_id) = 0;
  virtual void CommitChanges() = 0;
  virtual void EndPass() = 0;
  virtual void End() = 0;

  virtual void SetBool(const char* property_name, bool val) = 0;
  virtual void SetInt(const char* property_name, T_INT32 val) = 0;
  virtual void SetFloat(const char* property_name, T_FLOAT val) = 0;

  virtual void SetVec2f(const char* property_name, const TVec2f& vec) = 0;
  virtual void SetVec3f(const char* property_name, const TVec3f& vec) = 0;
  virtual void SetVec4f(const char* property_name, const TVec4f& vec) = 0;

  virtual void SetColor(const char* property_name, const Color4F& color) = 0;
  virtual void SetMatrix(const char* property_name, const NativeMatrixInstance* matrix) = 0;
  virtual void SetTexture(const char* property_name, NativeTextureInstance* texture) = 0;

  virtual void GetBool(const char* property_name, bool* dest) = 0;
  virtual void GetInt(const char* property_name, T_INT32* dest) = 0;
  virtual void GetFloat(const char* property_name, T_FLOAT* dest) = 0;

  virtual void GetVec2f(const char* property_name, TVec2f* dest) = 0;
  virtual void GetVec3f(const char* property_name, TVec3f* dest) = 0;
  virtual void GetVec4f(const char* property_name, TVec4f* dest) = 0;

  virtual void GetColor(const char* property_name, Color4F* dest) = 0;
  virtual void GetMatrix(const char* property_name, INativeMatrix* dest) = 0;
  virtual void GetTexture(const char* property_name, INativeTexture* dest) = 0;

public:
  inline void SetName(const std::string& name)
  {
    this->name_ = name;
  }
  inline const std::string& GetName() const
  {
    return this->name_;
  }

private:
  std::string name_;

};