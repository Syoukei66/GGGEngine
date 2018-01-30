#include "IVertexBufferObject.h"
#include <stdlib.h>
#include "ITextureRegion.h"
#include "NativeMethod.h"

// =================================================================
// Constructor / Destructor
// =================================================================
IVertexBufferObject::IVertexBufferObject()
  : vertex_coord_dirty_(true)
{
}

IVertexBufferObject::~IVertexBufferObject()
{
}

// =================================================================
// Method
// =================================================================
void IVertexBufferObject::Init()
{
  this->OnInit();
  this->vertex_coord_dirty_ = true;
}

void IVertexBufferObject::UpdateCoord(GameObject* entity)
{
  if (!this->vertex_coord_dirty_)
  {
    return;
  }
  this->OnUpdateCoord(entity);
  this->vertex_coord_dirty_ = false;
}

void IVertexBufferObject::OnVertexCoordDirty()
{
  this->vertex_coord_dirty_ = true;
}
