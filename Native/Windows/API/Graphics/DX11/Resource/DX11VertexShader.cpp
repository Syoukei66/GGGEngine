#include "DX11VertexShader.h"

#if GG_GRAPHICS_API_DX11

#include <Native/Windows/WindowsApplication.h>
#include "DX11VertexDeclaration.h"

// =================================================================
// GGG Statement
// =================================================================
GG_NATIVE_CREATE_FUNC_IMPL_1(rcVertexShader, DX11VertexShader, const std::vector<unsigned char>&, byte_code);

GG_CREATE_FUNC_IMPL_1(DX11VertexShader, const std::vector<unsigned char>&, byte_code)
{
  this->byte_code_ = byte_code;
  HRESULT hr = WindowsApplication::GetPlatform()->GetDX11Graphics()->GetDevice()->CreateVertexShader(
    this->byte_code_.data(),
    this->byte_code_.size(),
    NULL,
    &this->vertex_shader_
  );
  GG_ASSERT(SUCCEEDED(hr), "頂点シェーダーの作成に失敗しました");
  return true;
}

GG_DESTRUCT_FUNC_IMPL(DX11VertexShader)
{
  this->vertex_shader_->Release();
  for (const auto& pair : this->input_layouts_)
  {
    pair.second->Release();
  }
  return true;
}

// =================================================================
// Method for/from SuperClass/Interfaces
// =================================================================
void DX11VertexShader::SetInputLayout(const SharedRef<const rcVertexDeclaration>& declaration) const
{
  ID3D11InputLayout* input_layout = nullptr;

  const auto& itr = this->input_layouts_.find(declaration->GetFormat());
  if (itr == this->input_layouts_.end())
  {
    const SharedRef<const DX11VertexDeclaration>& dx11_vertex_decl = SharedRef<const DX11VertexDeclaration>::StaticCast(declaration);

    ID3D11Device* device = WindowsApplication::GetPlatform()->GetDX11Graphics()->GetDevice();
    HRESULT hr = device->CreateInputLayout(
      dx11_vertex_decl->GetElements().data(), dx11_vertex_decl->GetElements().size(),
      this->byte_code_.data(), this->byte_code_.size(),
      &input_layout
    );
    GG_ASSERT(SUCCEEDED(hr), "InputLayoutの作成に失敗しました");

    const_cast<DX11VertexShader*>(this)->input_layouts_[declaration->GetFormat()] = input_layout;
  }
  else
  {
    input_layout = itr->second;
  }

  ID3D11DeviceContext* context = WindowsApplication::GetPlatform()->GetDX11Graphics()->GetImmediateContext();
  context->IASetInputLayout(input_layout);
}

void DX11VertexShader::SetShader() const
{
  ID3D11DeviceContext* context = WindowsApplication::GetPlatform()->GetDX11Graphics()->GetImmediateContext();
  context->VSSetShader(this->vertex_shader_, NULL, 0);
}

#endif