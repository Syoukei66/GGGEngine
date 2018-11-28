#include "MeshBuilder_UvSphere.h"

// =================================================================
// Constructor / Destructor
// =================================================================
MeshBuilder_UvSphere::MeshBuilder_UvSphere(T_UINT32 format, T_FLOAT scale, T_UINT32 resolution_x, T_UINT32 resolution_y)
  : format_(format)
  , scale_(scale)
  , resolution_x_(resolution_x)
  , resolution_y_(resolution_y)
{
}

MeshBuilder_UvSphere::MeshBuilder_UvSphere()
  : format_(Vertex::V_FORMAT_PNUT)
  , scale_(1.0f)
  , resolution_x_(12)
  , resolution_y_(12)
{
}

// =================================================================
// Methods
// =================================================================
UniqueRef<rcDynamicMesh> MeshBuilder_UvSphere::CreateMesh() const
{
  return MeshFactory::UVSphere::Create(this->format_, this->scale_, this->resolution_x_, this->resolution_y_);
}
