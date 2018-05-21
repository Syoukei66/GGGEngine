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
  NATIVE_ASSERT(SUCCEEDED(hr), "VertexBuffer�̍쐬�Ɏ��s���܂���");
}

NativeVertexBuffer::~NativeVertexBuffer()
{
  this->vertex_buffer_->Release();
}

// =================================================================
// Method
// =================================================================
template <class T>
static void VertexBufferLock(IDirect3DVertexBuffer9* vertex_buffer, T** vertices)
{
}

void NativeVertexBuffer::LoadMesh(const SubMesh& mesh)
{
  if (mesh.HasNormals())
  {

  }
 
  HRESULT hr = this->vertex_buffer_->Lock(0, 0, dest, 0);
  NATIVE_ASSERT(SUCCEEDED(hr), "VertexBuffer�̃��b�N�Ɏ��s���܂���");

  hr = this->vertex_buffer_->Unlock();
  NATIVE_ASSERT(SUCCEEDED(hr), "VertexBuffer�̃A�����b�N�Ɏ��s���܂���");
}

void NativeVertexBuffer::SetStreamSource() const
{
  LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)Director::GetInstance()->GetDevice();
  HRESULT hr = device->SetStreamSource(0, this->vertex_buffer_, 0, Vertex::VERTEX_SIZE[this->vertex_type_]);
  NATIVE_ASSERT(SUCCEEDED(hr), "VertexBuffer�̃Z�b�g�Ɏ��s���܂���");
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
  NATIVE_ASSERT(SUCCEEDED(hr), "�`��Ɏ��s���܂���");
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
  NATIVE_ASSERT(SUCCEEDED(hr), "�`��Ɏ��s���܂���");
}
