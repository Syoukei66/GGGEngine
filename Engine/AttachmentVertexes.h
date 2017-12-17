#pragma once

#include "Texture.h"
#include "SpriteVertexBufferObject.h"

class AttachmentVertexes
{
public:
  AttachmentVertexes(Texture* texture, T_UINT8 vertexes_count);
  ~AttachmentVertexes();

public:
  SpriteVertex* vertexes_;
  T_UINT8 size_;
  Texture* texture_;
};