#include "NativeVertexBuffer.h"

#include <vector>

#include "NativeConstants.h"

// =================================================================
// Constructor / Destructor
// =================================================================
NativeVertexBuffer::NativeVertexBuffer(T_UINT16 vertex_count, T_UINT32 format)
  : vertex_count_(vertex_count)
  , format_(format)
{
  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetDevice();

  std::vector<D3DVERTEXELEMENT9> elements = std::vector<D3DVERTEXELEMENT9>();

  WORD offset = 0;

  using namespace Graphics;

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

  HRESULT hr = device->CreateVertexBuffer(
    this->stride_ * vertex_count,
    0,
    0,
    D3DPOOL_MANAGED,
    &this->vertex_buffer_,
    NULL
  );
  NATIVE_ASSERT(SUCCEEDED(hr), "VertexBuffer‚Ìì¬‚ÉŽ¸”s‚µ‚Ü‚µ‚½");

  hr = device->CreateVertexDeclaration(&elements.front(), &this->vertex_declaration_);
  NATIVE_ASSERT(SUCCEEDED(hr), "’¸“_ƒtƒH[ƒ}ƒbƒg‚Ìì¬‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
}

NativeVertexBuffer::~NativeVertexBuffer()
{
  this->vertex_declaration_->Release();
  this->vertex_buffer_->Release();
}

// =================================================================
// Method
// =================================================================
void NativeVertexBuffer::Lock(void** dest)
{
  HRESULT hr = this->vertex_buffer_->Lock(0, 0, dest, 0);
  NATIVE_ASSERT(SUCCEEDED(hr), "VertexBuffer‚ÌƒƒbƒN‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
}

void NativeVertexBuffer::Unlock()
{
  HRESULT hr = this->vertex_buffer_->Unlock();
  NATIVE_ASSERT(SUCCEEDED(hr), "VertexBuffer‚ÌƒAƒ“ƒƒbƒN‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
}

void NativeVertexBuffer::SetStreamSource() const
{
  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetDevice();
  HRESULT hr = device->SetVertexDeclaration(this->vertex_declaration_);
  NATIVE_ASSERT(SUCCEEDED(hr), "’¸“_éŒ¾‚ÌƒZƒbƒg‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
  hr = device->SetStreamSource(0, this->vertex_buffer_, 0, this->stride_);
  NATIVE_ASSERT(SUCCEEDED(hr), "VertexBuffer‚ÌƒZƒbƒg‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
}

//void NativeVertexBuffer::DrawPrimitive(Graphics::PrimitiveType primitive_type) const
//{
//  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetDevice();
//  HRESULT hr = device->DrawPrimitive(
//    NativeConstants::PRIMITIVE_TYPES[primitive_type],
//    0,
//    this->polygon_count_
//  );
//  NATIVE_ASSERT(SUCCEEDED(hr), "•`‰æ‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
//}

void NativeVertexBuffer::DrawIndexedPrimitive(const SharedRef<const rcIndexBuffer>& index_buffer, Graphics::PrimitiveType primitive_type) const
{
  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetDevice();
  const T_UINT32 vertex_count = index_buffer->GetVertexesCount();
  const T_UINT32 polygon_count = index_buffer->GetPolygonCount();
  HRESULT hr = device->DrawIndexedPrimitive(
    NativeConstants::PRIMITIVE_TYPES[primitive_type],
    0,
    0,
    vertex_count,
    0,
    polygon_count
  );
  NATIVE_ASSERT(SUCCEEDED(hr), "•`‰æ‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
}

// =================================================================
// Getter / Setter
// =================================================================
size_t NativeVertexBuffer::GetMemorySize() const
{
  //TODO:Œµ–§‚¶‚á‚È‚¢‚©‚à
  return sizeof(NativeVertexBuffer);
}

size_t NativeVertexBuffer::GetVideoMemorySize() const
{
  //TODO:Œµ–§‚¶‚á‚È‚¢‚©‚à
  return this->stride_ * this->vertex_count_;
}
