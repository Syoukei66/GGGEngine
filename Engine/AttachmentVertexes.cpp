#include "AttachmentVertexes.h"

AttachmentVertexes::AttachmentVertexes(TextureResource* texture, T_UINT8 vertexes_count)
  : texture_(texture)
  , size_(vertexes_count)
{
  this->vertexes_ = new Vertex::VCT[vertexes_count]();
  for (T_UINT8 i = 0; i < vertexes_count; ++i)
  {
    this->vertexes_[i] = Vertex::VCT();
  }
}

AttachmentVertexes::~AttachmentVertexes()
{
  delete[] this->vertexes_;
}
