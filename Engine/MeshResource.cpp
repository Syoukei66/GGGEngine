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
  delete this->mesh_;
  delete this->builder_;
}

// =================================================================
// Methods
// =================================================================
void MeshResource::Load()
{
  this->mesh_ = this->builder_->Create();
}

void MeshResource::Unload()
{
  delete this->mesh_;
}

