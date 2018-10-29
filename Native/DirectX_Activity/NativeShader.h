#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <unordered_map>
#include <unordered_set>

#include <../Core/Shader.h>

class NativeShader : public rcShader 
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  NativeShader(LPD3DXEFFECT effect);
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

  virtual void SetTechnique(const std::string& technique) override;

  virtual void SetBool(const std::string& property_name, bool val) override;
  virtual void SetInt(const std::string& property_name, T_INT32 val) override;
  virtual void SetFloat(const std::string& property_name, T_FLOAT val) override;

  virtual void SetVec2f(const std::string& property_name, const TVec2f& vec) override;
  virtual void SetVec3f(const std::string& property_name, const TVec3f& vec) override;
  virtual void SetVec4f(const std::string& property_name, const TVec4f& vec) override;

  virtual void SetColor(const std::string& property_name, const TColor& color) override;
  virtual void SetMatrix(const std::string& property_name, const Matrix4x4& matrix) override;
  virtual void SetTexture(const std::string& property_name, const SharedRef<const rcTexture>& texture) override;

  virtual void GetBool(const std::string& property_name, bool* dest) override;
  virtual void GetInt(const std::string& property_name, T_INT32* dest) override;
  virtual void GetFloat(const std::string& property_name, T_FLOAT* dest) override;

  virtual void GetVec2f(const std::string& property_name, TVec2f* dest) override;
  virtual void GetVec3f(const std::string& property_name, TVec3f* dest) override;
  virtual void GetVec4f(const std::string& property_name, TVec4f* dest) override;

  virtual void GetColor(const std::string& property_name, TColor* dest) override;
  virtual void GetMatrix(const std::string& property_name, Matrix4x4* dest) override;
  virtual void GetTexture(const std::string& property_name, void* native_dest) override;

private:
  D3DXHANDLE GetHandle(const std::string& property_name);

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  virtual size_t GetMemorySize() const override
  {
    //TODO:Œµ–§‚¶‚á‚È‚¢
    return sizeof(NativeShader);
  }
  virtual size_t GetVideoMemorySize() const override
  {
    //TODO:Œµ–§‚¶‚á‚È‚¢
    return 0;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::unordered_map<std::string, D3DXHANDLE> property_handles_;
  std::unordered_set<std::string> bad_property_ids_;
  LPD3DXEFFECT effect_;

};