#pragma once

//TODO:アセット管理の変更に合わせていつか修正する
class AttachmentVertexes
{
public:
  AttachmentVertexes(T_UINT32 texture, T_UINT8 vertices_count);
  ~AttachmentVertexes();

public:
  TVec3f* positions_;
  TColor* colors_;
  TVec2f* uvs_;
  T_UINT8 size_;
  T_UINT32 texture_;
};