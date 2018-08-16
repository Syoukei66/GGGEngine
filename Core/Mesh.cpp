#include "Mesh.h"

// =================================================================
// Constructor / Destructor
// =================================================================
rcMesh::rcMesh()
  : primitive_type_()
{

}

rcMesh::~rcMesh()
{

}

// =================================================================
// Methods
// =================================================================
void rcMesh::SetStreamSource() const
{
  this->vertex_buffer_->SetStreamSource();
}

void rcMesh::DrawSubset(T_UINT8 index) const
{
  NATIVE_ASSERT(index < this->submesh_count_, "�C���f�b�N�X�w�肪�T�u���b�V���̍ő���𒴉߂��܂����B");
  this->index_buffers_[index]->SetIndices();
  this->vertex_buffer_->DrawIndexedPrimitive(this->index_buffers_[index], this->primitive_type_);
}
