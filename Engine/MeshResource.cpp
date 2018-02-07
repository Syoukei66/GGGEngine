#include "MeshResource.h"

// =================================================================
// Constructor / Destructor
// =================================================================
MeshResource::MeshResource(const MeshData& data)
  : data_(data)
  , mesh_(nullptr)
{
}

MeshResource::~MeshResource()
{
  delete this->mesh_;
}

// =================================================================
// Methods
// =================================================================
void MeshResource::Load()
{
  this->mesh_ = new Mesh(this->data_);
}

void MeshResource::Unload()
{
  delete this->mesh_;
}

