#pragma once

#include "TextureResource.h"
#include "Vertex.h"

class AttachmentVertexes
{
public:
  AttachmentVertexes(TextureResource* texture, T_UINT8 vertexes_count);
  ~AttachmentVertexes();

public:
  Vertex::VCT* vertexes_;
  T_UINT8 size_;
  TextureResource* texture_;
};