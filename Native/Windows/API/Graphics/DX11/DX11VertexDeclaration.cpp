#include "DX11VertexDeclaration.h"

#if GG_GRAPHICS_API_DX11

#include <Native/Windows/WindowsApplication.h>
#include "DX11Shader.h"

// =================================================================
// Constructor / Destructor
// =================================================================
DX11VertexDeclaration::DX11VertexDeclaration(T_UINT32 format)
  : format_(format)
{
  ID3D11Device* device = WindowsApplication::GetDX11Graphics()->GetDevice();
  std::vector<D3D11_INPUT_ELEMENT_DESC> elements = std::vector<D3D11_INPUT_ELEMENT_DESC>();

  WORD offset = 0;

  using namespace Vertex;

  if (format & V_ATTR_POSITION)
  {
    D3D11_INPUT_ELEMENT_DESC element = { 
      "POSITION", 0,
      DXGI_FORMAT_R32G32B32_FLOAT,
      0,
      offset,
      D3D11_INPUT_PER_VERTEX_DATA, 0 };
    elements.emplace_back(element);
    offset += V_ATTRSIZE_POSITION;
  }
  if (format & V_ATTR_NORMAL)
  {
    D3D11_INPUT_ELEMENT_DESC element = {
      "NORMAL", 0,
      DXGI_FORMAT_R32G32B32_FLOAT,
      0,
      offset,
      D3D11_INPUT_PER_VERTEX_DATA, 0 };
    elements.emplace_back(element);
    offset += V_ATTRSIZE_NORMAL;
  }
  if (format & V_ATTR_UV)
  {
    D3D11_INPUT_ELEMENT_DESC element = {
      "TEXCOORD", 0,
      DXGI_FORMAT_R32G32_FLOAT,
      0,
      offset,
      D3D11_INPUT_PER_VERTEX_DATA, 0 };
    elements.emplace_back(element);
    offset += V_ATTRSIZE_UV;
  }
  if (format & V_ATTR_UV2)
  {
    D3D11_INPUT_ELEMENT_DESC element = {
      "TEXCOORD", 1,
      DXGI_FORMAT_R32G32_FLOAT,
      0,
      offset,
      D3D11_INPUT_PER_VERTEX_DATA, 0 };
    elements.emplace_back(element);
    offset += V_ATTRSIZE_UV2;
  }
  if (format & V_ATTR_UV3)
  {
    D3D11_INPUT_ELEMENT_DESC element = {
      "TEXCOORD", 2,
      DXGI_FORMAT_R32G32_FLOAT,
      0,
      offset,
      D3D11_INPUT_PER_VERTEX_DATA, 0 };
    elements.emplace_back(element);
    offset += V_ATTRSIZE_UV3;
  }
  if (format & V_ATTR_UV4)
  {
    D3D11_INPUT_ELEMENT_DESC element = {
      "TEXCOORD", 3,
      DXGI_FORMAT_R32G32_FLOAT,
      0,
      offset,
      D3D11_INPUT_PER_VERTEX_DATA, 0 };
    elements.emplace_back(element);
    offset += V_ATTRSIZE_UV4;
  }
  if (format & V_ATTR_TANGENT)
  {
    D3D11_INPUT_ELEMENT_DESC element = {
      "TANGENT", 0,
      DXGI_FORMAT_R32G32B32A32_FLOAT,
      0,
      offset,
      D3D11_INPUT_PER_VERTEX_DATA, 0 };
    elements.emplace_back(element);
    offset += V_ATTRSIZE_TANGENT;
  }
  if (format & V_ATTR_COLOR)
  {
    D3D11_INPUT_ELEMENT_DESC element = { 
      "COLOR", 0,
      DXGI_FORMAT_R8G8B8A8_UINT,
      0,
      offset,
      D3D11_INPUT_PER_VERTEX_DATA, 0 };
    elements.emplace_back(element);
    offset += V_ATTRSIZE_COLOR;
  }

  this->stride_ = offset;

  HRESULT hr = device->CreateInputLayout(&elements[0], elements.size(), NULL, NULL, &this->input_layout_);
  GG_ASSERT(SUCCEEDED(hr), "頂点フォーマットの作成に失敗しました");
}

DX11VertexDeclaration::~DX11VertexDeclaration()
{
}

// =================================================================
// Method
// =================================================================
T_UINT32 DX11VertexDeclaration::GetFormat() const
{
  return T_UINT32();
}

T_UINT32 DX11VertexDeclaration::GetVertexSize() const
{
  return T_UINT32();
}

void DX11VertexDeclaration::SetInputLayout(const SharedRef<rcShader>& shader) const
{
  ID3D11Device* device = WindowsApplication::GetDX11Graphics()->GetDevice();
  SharedRef<DX11Shader>
    HRESULT hr = device->SetVertexDeclaration(this->vertex_declaration_);
  GG_ASSERT(SUCCEEDED(hr), "頂点宣言のセットに失敗しました");
}

#endif