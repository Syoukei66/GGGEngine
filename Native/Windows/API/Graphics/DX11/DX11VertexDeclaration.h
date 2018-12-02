#pragma once

#if GG_GRAPHICS_API_DX11

#include <d3d11.h>

#include <Core/Application/Platform/API/_Resource/VertexDeclaration/VertexDeclaration.h>

class DX11VertexDeclaration : public rcVertexDeclaration
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  DX11VertexDeclaration(T_UINT32 format);
  ~DX11VertexDeclaration();

  // =================================================================
  // Method
  // =================================================================
public:
  virtual T_UINT32 GetFormat() const override;
  virtual T_UINT32 GetVertexSize() const override;
  virtual void SetInputLayout(const SharedRef<rcShader>& shader) const override;

  // =================================================================
  // Data Member
  // =================================================================
private:
  const T_UINT32 format_;
  T_UINT32 stride_;
  ID3D11InputLayout* input_layout_;

};

static UniqueRef<rcVertexDeclaration> rcVertexDeclaration::Create(T_UINT32 format)
{
  return UniqueRef<rcVertexDeclaration>(new DX11VertexDeclaration(format));
}

#endif
