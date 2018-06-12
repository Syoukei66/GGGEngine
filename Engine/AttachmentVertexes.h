#pragma once

#include "TextureResource.h"
#include "Color.h"

#include "Vector2.h"
#include "Vector3.h"

class AttachmentVertexes
{
public:
  AttachmentVertexes(TextureResource* texture, T_UINT8 vertices_count);
  ~AttachmentVertexes();

public:
  TVec3f* positions_;
  Color4F* colors_;
  TVec2f* uvs_;
  T_UINT8 size_;
  TextureResource* texture_;
};