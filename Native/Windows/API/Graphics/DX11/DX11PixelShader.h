#pragma once

#if GG_GRAPHICS_API_DX11

#include <d3d11.h>
#include <Core/Application/Platform/API/_Resource/PixelShader/PixelShader.h>

class DX11PixelShader : public rcPixelShader
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  DX11PixelShader(const std::vector<unsigned char>& byte_code);
  ~DX11PixelShader();

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

UniqueRef<rcPixelShader> rcPixelShader::Create(const std::vector<unsigned char>& byte_code)
{
  return UniqueRef<rcPixelShader>(new DX11PixelShader(byte_code));
}

#endif

