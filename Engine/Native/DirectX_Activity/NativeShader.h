#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include <NativeShader.h>

class NativeShader : public INativeShader 
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  NativeShader(const char* path);
  ~NativeShader();
  
  // =================================================================
  // Method for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual void Begin() override;
  virtual void End() override;

  virtual void SetBool(const char* property_name, bool val) override;
  virtual void SetInt(const char* property_name, T_INT32 val) override;
  virtual void SetFloat(const char* property_name, T_FLOAT val) override;

  virtual void SetVec2f(const char* property_name, const TVec2f& vec) override;
  virtual void SetVec3f(const char* property_name, const TVec3f& vec) override;
  virtual void SetVec4f(const char* property_name, const TVec4f& vec) override;

  virtual void SetColor(const char* property_name, const Color4F& color) override;
  virtual void SetMatrix(const char* property_name, const INativeMatrix& matrix) override;
  virtual void SetTexture(const char* property_name, const INativeTexture& texture) override;

  // =================================================================
  // Data Members
  // =================================================================
private:
  LPD3DXEFFECT effect_;

};