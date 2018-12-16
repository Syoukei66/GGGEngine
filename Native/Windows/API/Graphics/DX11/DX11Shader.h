#pragma once

#if GG_GRAPHICS_API_DX11

#include <d3d11.h>
#include <Core/Application/Platform/API/_Asset/Shader/Shader.h>

class DX11Shader : public rcShader
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  DX11Shader(const char* path);
  ~DX11Shader();

  // =================================================================
  // Method for/from SuperClass/Interfaces
  // =================================================================
public:  
  virtual void SetInputLayout(const SharedRef<const rcVertexDeclaration>& declaration) override;
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

  // =================================================================
  // Data Members
  // =================================================================
private:
  ID3DBlob* vs_brob_;
  ID3D11VertexShader* vertex_shader_;
  std::unordered_map<T_UINT32, ID3D11InputLayout*> input_layouts_;

  ID3DBlob* ps_brob_;
  ID3D11PixelShader* pixel_shader_;

  ID3D11Buffer* constant_table_;

};


#endif
