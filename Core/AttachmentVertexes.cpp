#include "AttachmentVertexes.h"

AttachmentVertexes::AttachmentVertexes(T_UINT32 texture, T_UINT8 vertices_count)
  : texture_(texture)
  , size_(vertices_count)
{
  this->positions_ = new TVec3f[vertices_count]();
  this->uvs_ = new TVec2f[vertices_count]();
  this->colors_ = new TColor[vertices_count]();
}

AttachmentVertexes::~AttachmentVertexes()
{
  delete[] this->colors_;
  delete[] this->uvs_;
  delete[] this->positions_;
}
