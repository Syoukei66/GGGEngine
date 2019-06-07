#pragma once

#if GG_GRAPHICS_API_DX11

#include <d3d11.h>

#include <Core/Application/Platform/API/_Resource/VertexDeclaration.h>

class DX11VertexDeclaration : public rcVertexDeclaration
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  DX11VertexDeclaration(T_UINT32 format);
  ~DX11VertexDeclaration();

  // =================================================================
  // Method from rcVertexDeclaration
  // =================================================================
public:
  virtual T_UINT32 GetFormat() const override;
  virtual T_UINT32 GetVertexSize() const override;

  // =================================================================
  // Method
  // =================================================================
public:
  GG_INLINE const std::vector<D3D11_INPUT_ELEMENT_DESC>& GetElements() const
  {
    return this->elements_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  const T_UINT32 format_;
  T_UINT32 stride_;
  std::vector<D3D11_INPUT_ELEMENT_DESC> elements_;

};

#endif
