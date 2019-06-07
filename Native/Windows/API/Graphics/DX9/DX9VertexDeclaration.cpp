#include "DX9VertexDeclaration.h"

#if GG_GRAPHICS_API_DX9

#include <Native/Windows/WindowsApplication.h>

UniqueRef<rcVertexDeclaration> rcVertexDeclaration::Create(T_UINT32 format)
{
  return UniqueRef<rcVertexDeclaration>(new DX9VertexDeclaration(format));
}

// =================================================================
// Constructor / Destructor
// =================================================================
DX9VertexDeclaration::DX9VertexDeclaration(T_UINT32 format)
  : format_(format)
{
  LPDIRECT3DDEVICE9 device = WindowsPlatform::GetDX9Graphics()->GetDevice();
  std::vector<D3DVERTEXELEMENT9> elements = std::vector<D3DVERTEXELEMENT9>();

  WORD offset = 0;

  using namespace Vertex;

  if (format & V_ATTR_POSITION)
  {
    D3DVERTEXELEMENT9 element = { 0, offset,
      D3DDECLTYPE_FLOAT3,
      D3DDECLMETHOD_DEFAULT,
      D3DDECLUSAGE_POSITION,
      0 };
    elements.emplace_back(element);
    offset += V_ATTRSIZE_POSITION;
  }
  if (format & V_ATTR_NORMAL)
  {
    D3DVERTEXELEMENT9 element = { 0, offset,
      D3DDECLTYPE_FLOAT3,
      D3DDECLMETHOD_DEFAULT,
      D3DDECLUSAGE_NORMAL,
      0 };
    elements.emplace_back(element);
    offset += V_ATTRSIZE_NORMAL;
  }
  if (format & V_ATTR_UV)
  {
    D3DVERTEXELEMENT9 element = { 0, offset,
      D3DDECLTYPE_FLOAT2,
      D3DDECLMETHOD_DEFAULT,
      D3DDECLUSAGE_TEXCOORD,
      0 };
    elements.emplace_back(element);
    offset += V_ATTRSIZE_UV;
  }
  if (format & V_ATTR_UV2)
  {
    D3DVERTEXELEMENT9 element = { 0, offset,
      D3DDECLTYPE_FLOAT2,
      D3DDECLMETHOD_DEFAULT,
      D3DDECLUSAGE_TEXCOORD,
      1 };
    elements.emplace_back(element);
    offset += V_ATTRSIZE_UV2;
  }
  if (format & V_ATTR_UV3)
  {
    D3DVERTEXELEMENT9 element = { 0, offset,
      D3DDECLTYPE_FLOAT2,
      D3DDECLMETHOD_DEFAULT,
      D3DDECLUSAGE_TEXCOORD,
      2 };
    elements.emplace_back(element);
    offset += V_ATTRSIZE_UV3;
  }
  if (format & V_ATTR_UV4)
  {
    D3DVERTEXELEMENT9 element = { 0, offset,
      D3DDECLTYPE_FLOAT2,
      D3DDECLMETHOD_DEFAULT,
      D3DDECLUSAGE_TEXCOORD,
      3 };
    elements.emplace_back(element);
    offset += V_ATTRSIZE_UV4;
  }
  if (format & V_ATTR_TANGENT)
  {
    D3DVERTEXELEMENT9 element = { 0, offset,
      D3DDECLTYPE_FLOAT4,
      D3DDECLMETHOD_DEFAULT,
      D3DDECLUSAGE_TANGENT,
      0 };
    elements.emplace_back(element);
    offset += V_ATTRSIZE_TANGENT;
  }
  if (format & V_ATTR_COLOR)
  {
    D3DVERTEXELEMENT9 element = { 0, offset,
      D3DDECLTYPE_D3DCOLOR,
      D3DDECLMETHOD_DEFAULT,
      D3DDECLUSAGE_COLOR,
      0 };
    elements.emplace_back(element);
    offset += V_ATTRSIZE_COLOR;
  }

  elements.push_back(D3DDECL_END());
  this->stride_ = offset;

  HRESULT hr = device->CreateVertexDeclaration(&elements[0], &this->vertex_declaration_);
  GG_ASSERT(SUCCEEDED(hr), "頂点フォーマットの作成に失敗しました");
}

DX9VertexDeclaration::~DX9VertexDeclaration()
{
  this->vertex_declaration_->Release();
}

// =================================================================
// Method
// =================================================================
T_UINT32 DX9VertexDeclaration::GetFormat() const
{
  return this->format_;
}

T_UINT32 DX9VertexDeclaration::GetVertexSize() const
{
  return this->stride_;
}

void DX9VertexDeclaration::SetDeclaration() const
{
  LPDIRECT3DDEVICE9 device = WindowsPlatform::GetDX9Graphics()->GetDevice();
  HRESULT hr = device->SetVertexDeclaration(this->vertex_declaration_);
  GG_ASSERT(SUCCEEDED(hr), "頂点宣言のセットに失敗しました");
}

#endif