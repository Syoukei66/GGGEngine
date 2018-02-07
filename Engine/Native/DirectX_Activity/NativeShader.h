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
  virtual T_UINT8 Begin() override;
  virtual void BeginPass(T_UINT8 path_id) override;
  virtual void CommitChanges() override;
  virtual void EndPass() override;
  virtual void End() override;

  virtual void SetBool(const char* property_name, bool val) override;
  virtual void SetInt(const char* property_name, T_INT32 val) override;
  virtual void SetFloat(const char* property_name, T_FLOAT val) override;

  virtual void SetVec2f(const char* property_name, const TVec2f& vec) override;
  virtual void SetVec3f(const char* property_name, const TVec3f& vec) override;
  virtual void SetVec4f(const char* property_name, const TVec4f& vec) override;

  virtual void SetColor(const char* property_name, const Color4F& color) override;
  virtual void SetMatrix(const char* property_name, const NativeMatrixInstance* matrix) override;
  virtual void SetTexture(const char* property_name, NativeTextureInstance* texture) override;

  virtual void GetBool(const char* property_name, bool* dest) override;
  virtual void GetInt(const char* property_name, T_INT32* dest) override;
  virtual void GetFloat(const char* property_name, T_FLOAT* dest) override;

  virtual void GetVec2f(const char* property_name, TVec2f* dest) override;
  virtual void GetVec3f(const char* property_name, TVec3f* dest) override;
  virtual void GetVec4f(const char* property_name, TVec4f* dest) override;

  virtual void GetColor(const char* property_name, Color4F* dest) override;
  virtual void GetMatrix(const char* property_name, INativeMatrix* dest) override;
  virtual void GetTexture(const char* property_name, INativeTexture* dest) override;

  // =================================================================
  // Data Members
  // =================================================================
private:
  LPD3DXEFFECT effect_;

};