#pragma once

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
  virtual void Begin() = 0;
  virtual void End() = 0;

  virtual void SetBool(const char* property_name, bool val) = 0;
  virtual void SetInt(const char* property_name, T_INT32 val) = 0;
  virtual void SetFloat(const char* property_name, T_FLOAT val) = 0;

  virtual void SetVec2f(const char* property_name, const TVec2f& vec) = 0;
  virtual void SetVec3f(const char* property_name, const TVec3f& vec) = 0;
  virtual void SetVec4f(const char* property_name, const TVec4f& vec) = 0;

  virtual void SetColor(const char* property_name, const Color4F& color) = 0;
  virtual void SetMatrix(const char* property_name, const INativeMatrix& matrix) = 0;
  virtual void SetTexture(const char* property_name, const INativeTexture& texture) = 0;

};