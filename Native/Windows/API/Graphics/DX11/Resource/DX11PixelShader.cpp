#include "DX11PixelShader.h"

#if GG_GRAPHICS_API_DX11

#include <Native/Windows/WindowsApplication.h>

// =================================================================
// GGG Statement
// =================================================================
GG_NATIVE_CREATE_FUNC_IMPL_1(rcPixelShader, DX11PixelShader, const std::vector<unsigned char>&, byte_code);

GG_CREATE_FUNC_IMPL_1(DX11PixelShader, const std::vector<unsigned char>&, byte_code)
{
  this->byte_code_ = byte_code;

  HRESULT hr = WindowsApplication::GetPlatform()->GetDX11Graphics()->GetDevice()->CreatePixelShader(
    this->byte_code_.data(),
    this->byte_code_.size(),
    NULL,
    &this->pixel_shader_
  );
  GG_ASSERT(SUCCEEDED(hr), "ピクセルシェーダーの作成に失敗しました");

  return true;
}

GG_DESTRUCT_FUNC_IMPL(DX11PixelShader)
{
  this->pixel_shader_->Release();

  return true;
}

// =================================================================
// Method for/from SuperClass/Interfaces
// =================================================================
void DX11PixelShader::SetShader() const
{
  ID3D11DeviceContext* context = WindowsApplication::GetPlatform()->GetDX11Graphics()->GetImmediateContext();
  context->PSSetShader(this->pixel_shader_, NULL, 0);
}

#endif