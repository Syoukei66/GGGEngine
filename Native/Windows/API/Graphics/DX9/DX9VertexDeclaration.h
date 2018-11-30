#pragma once

#if GG_GRAPHICS_API_DX9

#include <d3d9.h>
#include <d3dx9.h>

#include <Core/Application/Platform/API/_Resource/VertexDeclaration/VertexDeclaration.h>

class DX9VertexDeclaration : public rcVertexDeclaration
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  DX9VertexDeclaration(T_UINT32 format);
  ~DX9VertexDeclaration();

  // =================================================================
  // Method
  // =================================================================
public:
  virtual T_UINT32 GetFormat() const override;
  virtual T_UINT32 GetVertexSize() const override;
  virtual void SetVertexDeclaration() const override;

  // =================================================================
  // Data Member
  // =================================================================
private:
  const T_UINT32 format_;
  T_UINT32 stride_;
  IDirect3DVertexDeclaration9* vertex_declaration_;
};

#endif