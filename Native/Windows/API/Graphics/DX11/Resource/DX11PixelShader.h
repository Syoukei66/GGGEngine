#pragma once

#if GG_GRAPHICS_API_DX11

#include <d3d11.h>
#include <Core/Application/Platform/API/_Resource/PixelShader.h>

class DX11PixelShader : public rcPixelShader
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(DX11PixelShader);
  GG_CREATE_FUNC_1(DX11PixelShader, const std::vector<unsigned char>&, byte_code);
  GG_DESTRUCT_FUNC(DX11PixelShader);

  // =================================================================
  // Method for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual void SetShader() const override;

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::vector<unsigned char> byte_code_;
  ID3D11PixelShader* pixel_shader_;
};

#endif
