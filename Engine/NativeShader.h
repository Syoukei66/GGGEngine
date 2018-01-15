#pragma once

#include "Geometry.h"
#include "NativeObject.h"

struct NativeShaderInstance { void* p; };

class INativeShader : public NativeObject<NativeShaderInstance>
{
  // =================================================================
  // Static Method
  // =================================================================
public:
  static INativeShader* Create();
  static INativeShader* Create(NativeShaderInstance* instance);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  INativeShader(NativeShaderInstance* instance)
    : NativeObject(instance)
  {}

  INativeShader() {}

  virtual ~INativeShader() {}

  //ÉRÉsÅ[ã÷é~
private:
  INativeShader(const INativeShader& mat) {}

  // =================================================================
  // Method 
  // =================================================================
public:
  virtual void SetBool(bool val);
  virtual void SetInt(T_INT32 val);
  virtual void SetUint(T_UINT32 val);
  virtual void SetFloat(T_FLOAT val);
  virtual void SetDouble(T_FLOAT val);
};