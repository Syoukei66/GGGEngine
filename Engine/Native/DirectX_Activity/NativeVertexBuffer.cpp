#include "NativeVertexBuffer.h"
#include "Director.h"
#include "NativeConstants.h"

NativeVertexBuffer::NativeVertexBuffer(T_UINT16 vertex_count, INativeProcess_Graphics::VertexType vertex_type)
  : vertex_count_(vertex_count)
  , vertex_type_(vertex_type)
{
  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  HRESULT hr = device->CreateVertexBuffer(
    NativeConstants::VERTEX_SIZE[vertex_type] * vertex_count,
    0,
    NativeConstants::FVF_TYPES[vertex_type],
    D3DPOOL_MANAGED,
    &this->vertex_buffer_,
    NULL
  );
  NATIVE_ASSERT(hr, "VertexBuffer‚Ìì¬‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
}

void NativeVertexBuffer::Lock(void** dest)
{
  this->vertex_buffer_->Lock(0, 0, dest, 0);
}

void NativeVertexBuffer::Unlock()
{
  this->vertex_buffer_->Unlock();
}

void NativeVertexBuffer::Draw(INativeProcess_Graphics::PrimitiveType primitive_type)
{
  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  device->SetStreamSource(0, this->vertex_buffer_, 0, NativeConstants::VERTEX_SIZE[this->vertex_type_]);
  device->SetFVF(NativeConstants::FVF_TYPES[this->vertex_type_]);
  device->DrawPrimitive(
    NativeConstants::PRIMITIVE_TYPES[primitive_type],
    0,
    NativeConstants::PRIMITIVE_SURF_NUM(primitive_type, this->vertex_count_)
  );
}

void NativeVertexBuffer::DrawIndexed(const INativeIndexBuffer* index_buffer, INativeProcess_Graphics::PrimitiveType primitive_type)
{
  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  T_UINT32 vertex_count = index_buffer->GetVertexesCount();
  device->SetStreamSource(0, this->vertex_buffer_, 0, NativeConstants::VERTEX_SIZE[this->vertex_type_]);
  index_buffer->SetIndices();
  device->SetFVF(NativeConstants::FVF_TYPES[this->vertex_type_]);
  device->DrawIndexedPrimitive(
    NativeConstants::PRIMITIVE_TYPES[primitive_type],
    0,
    0,
    vertex_count,
    0,
    NativeConstants::PRIMITIVE_SURF_NUM(primitive_type, vertex_count)
  );
}
