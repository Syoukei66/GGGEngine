#pragma once

#include "NativeType.h"

class Texture
{
public:
  enum FilterMode
  {
    FILTER_POINT,
    FILTER_BILINEAR,
    FILTER_TRILINEAR,
  };

  enum WrapMode
  {
    WRAP_REPEAT,
    WRAP_CLAMP,
    WRAP_MIRROR,
    WRAP_MIRROR_ONCE
  };

public:
  Texture();
  ~Texture();

  // =================================================================
  // Getter / Setter
  // =================================================================
public:
  inline T_UINT16 GetWidth() const
  {
    return this->width_;
  }
  inline T_UINT16 GetHeight() const
  {
    return this->height_;
  }
  inline T_UINT16 GetTwoPoweredWidth() const
  {
    return 1 << two_powered_width_;
  }
  inline T_UINT16 GetTwoPoweredHeight() const
  {
    return 1 << two_powered_height_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  void* native_obj_;

  T_UINT16 width_;
  T_UINT16 height_;

  T_UINT8 two_powered_width_;
  T_UINT8 two_powered_height_;

  //ライトマップの更新などの為に、
  //テクスチャの変更を検出するのに使用
  T_UINT32 image_contents_hash_;

  T_UINT8 mip_count_;
  T_FLOAT mip_map_bias_;

  T_UINT8 aniso_level_;

  FilterMode filter_mode_;
  WrapMode wrap_mode_address_u_;
  WrapMode wrap_mode_address_v_;
};