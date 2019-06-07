#pragma once

#if GG_GRAPHICS_API_DX11

#include <d3d11.h>
#include <Core/Application/Platform/API/_Resource/VertexShader.h>

class DX11VertexShader : public rcVertexShader
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  DX11VertexShader(const std::vector<unsigned char>& byte_code);
  ~DX11VertexShader();

  // =================================================================
  // Method for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual void SetInputLayout(const SharedRef<const rcVertexDeclaration>& declaration) const override;
  virtual void SetShader() const override;

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::vector<unsigned char> byte_code_;
  ID3D11VertexShader* vertex_shader_;
  std::unordered_map<T_UINT32, ID3D11InputLayout*> input_layouts_;
};

UniqueRef<rcVertexShader> rcVertexShader::Create(const std::vector<unsigned char>& byte_code)
{
  return UniqueRef<rcVertexShader>(new DX11VertexShader(byte_code));
}

#endif
