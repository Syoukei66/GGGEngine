#include "AttachmentVertexes.h"

AttachmentVertexes::AttachmentVertexes(Texture* texture, T_UINT8 vertexes_count)
  : texture_(texture)
  , size_(vertexes_count)
{
  this->vertexes_ = new SpriteVertex[vertexes_count]();
  for (T_UINT8 i = 0; i < vertexes_count; ++i)
  {
    this->vertexes_[i].Init();
  }
}

AttachmentVertexes::~AttachmentVertexes()
{
  delete[] this->vertexes_;
}