#include "MeshResource.h"

// =================================================================
// Constructor / Destructor
// =================================================================
MeshResource::MeshResource(const MeshBuilder* builder)
  : builder_(builder)
  , mesh_(nullptr)
{
}

MeshResource::~MeshResource()
{
  if (this->mesh_)
  {
    this->mesh_->Release();
  }
  delete this->builder_;
}

// =================================================================
// Methods
// =================================================================
void MeshResource::Load()
{
  if (this->mesh_)
  {
    return;
  }
  this->mesh_ = this->builder_->CreateStaticMesh();
}

void MeshResource::Unload()
{
  if (!this->mesh_)
  {
    return;
  }
  this->mesh_->Release();
  this->mesh_ = nullptr;
}

