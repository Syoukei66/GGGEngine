#pragma once

#include "Texture.h"
#include "SpriteVertexBufferObject.h"

class AttachmentVertexes
{
public:
  AttachmentVertexes(LP_TEXTURE texture, T_UINT8 vertexes_count);
  ~AttachmentVertexes();

public:
  SpriteVertex* vertexes_;
  T_UINT8 size_;
  LP_TEXTURE texture_;
};