#include "NativeVertexBuffer.h"
#include "Director.h"
#include "NativeConstants.h"

// =================================================================
// Constructor / Destructor
// =================================================================
NativeVertexBuffer::NativeVertexBuffer(T_UINT16 vertex_count, T_UINT16 polygon_count, Vertex::VertexType vertex_type)
  : vertex_count_(vertex_count)
  , polygon_count_(polygon_count)
  , vertex_type_(vertex_type)
{
  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  HRESULT hr = device->CreateVertexBuffer(
    Vertex::VERTEX_SIZE[vertex_type] * vertex_count,
    0,
    NativeConstants::FVF_TYPES[vertex_type],
    D3DPOOL_MANAGED,
    &this->vertex_buffer_,
    NULL
  );
  NATIVE_ASSERT(SUCCEEDED(hr), "VertexBuffer‚Ìì¬‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
}

NativeVertexBuffer::~NativeVertexBuffer()
{
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
  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  HRESULT hr = device->SetStreamSource(0, this->vertex_buffer_, 0, Vertex::VERTEX_SIZE[this->vertex_type_]);
  NATIVE_ASSERT(SUCCEEDED(hr), "VertexBuffer‚ÌƒZƒbƒg‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
  device->SetFVF(NativeConstants::FVF_TYPES[this->vertex_type_]);
}

void NativeVertexBuffer::DrawPrimitive(INativeProcess_Graphics::PrimitiveType primitive_type) const
{
  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  HRESULT hr = device->DrawPrimitive(
    NativeConstants::PRIMITIVE_TYPES[primitive_type],
    0,
    this->polygon_count_
  );
  NATIVE_ASSERT(SUCCEEDED(hr), "•`‰æ‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
}

void NativeVertexBuffer::DrawIndexedPrimitive(const INativeIndexBuffer* index_buffer, INativeProcess_Graphics::PrimitiveType primitive_type) const
{
  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  const T_UINT32 vertex_count = index_buffer->GetVertexesCount();
  HRESULT hr = device->DrawIndexedPrimitive(
    NativeConstants::PRIMITIVE_TYPES[primitive_type],
    0,
    0,
    vertex_count,
    0,
    this->polygon_count_
  );
  NATIVE_ASSERT(SUCCEEDED(hr), "•`‰æ‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
}
