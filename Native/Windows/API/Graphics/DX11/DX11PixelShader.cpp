#include "DX11PixelShader.h"

#if GG_GRAPHICS_API_DX11

#include <Native/Windows/WindowsApplication.h>

// =================================================================
// Constructor / Destructor
// =================================================================
DX11PixelShader::DX11PixelShader(const std::vector<unsigned char>& byte_code)
  : byte_code_(byte_code)
{
  HRESULT hr = WindowsApplication::GetDX11Graphics()->GetDevice()->CreatePixelShader(
    this->byte_code_.data(),
    this->byte_code_.size(),
    NULL,
    &this->pixel_shader_
  );
  GG_ASSERT(SUCCEEDED(hr), "ピクセルシェーダーの作成に失敗しました");
}

DX11PixelShader::~DX11PixelShader()
{
  this->pixel_shader_->Release();
}

// =================================================================
// Method for/from SuperClass/Interfaces
// =================================================================
void DX11PixelShader::SetShader() const
{
  ID3D11DeviceContext* context = WindowsApplication::GetDX11Graphics()->GetImmediateContext();
  context->PSSetShader(this->pixel_shader_, NULL, 0);
}

#endif