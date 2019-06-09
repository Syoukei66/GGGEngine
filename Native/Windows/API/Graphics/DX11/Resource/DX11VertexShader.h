#pragma once

#if GG_GRAPHICS_API_DX11

#include <d3d11.h>
#include <Core/Application/Platform/API/_Resource/VertexShader.h>

class DX11VertexShader : public rcVertexShader
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(DX11VertexShader);
  GG_CREATE_FUNC_1(DX11VertexShader, const std::vector<unsigned char>&, byte_code);
  GG_DESTRUCT_FUNC(DX11VertexShader);

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

#endif
