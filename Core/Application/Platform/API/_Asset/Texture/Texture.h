#pragma once

#include <Core/Application/Platform/API/_Asset/APIAssetObject.h>
#include <Core/Application/Platform/API/_Resource/RenderBuffer/RenderBuffer.h>
#include <Core/Application/Platform/API/_Resource/TextureResource.h>

class rcTexture : public GGAPIAssetObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(rcTexture);

  // =================================================================
  // Factory Method
  // =================================================================
public:
  static UniqueRef<rcTexture> CreateFromFile(const char* path);
  static UniqueRef<rcTexture> Create(T_UINT16 width, T_UINT16 height, const SharedRef<rcTextureResource>& texture_resource);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  rcTexture(T_UINT16 width, T_UINT16 height, const SharedRef<rcTextureResource>& texture_resource);
  virtual ~rcTexture();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE SharedRef<rcTextureResource> GetNativeResource()
  {
    return this->resource_;
  }
  GG_INLINE SharedRef<const rcTextureResource> GetNativeResource() const
  {
    return this->resource_;
  }

  GG_INLINE T_UINT16 GetWidth() const
  {
    return this->width_;
  }
  GG_INLINE T_UINT16 GetHeight() const
  {
    return this->height_;
  }
  GG_INLINE T_UINT16 GetTwoPoweredWidth() const
  {
    return two_powered_width_;
  }
  GG_INLINE T_UINT16 GetTwoPoweredHeight() const
  {
    return two_powered_height_;
  }
  GG_INLINE SharedRef<rcRenderBuffer> GetColorBuffer()
  {
    return this->color_buffer_;
  }
  GG_INLINE SharedRef<const rcRenderBuffer> GetColorBuffer() const
  {
    return this->color_buffer_;
  }

  // =================================================================
  // Data Members
  // =================================================================
protected:
  SharedRef<rcTextureResource> resource_;

  T_UINT16 width_;
  T_UINT16 height_;

  T_UINT16 two_powered_width_;
  T_UINT16 two_powered_height_;

  SharedRef<rcRenderBuffer> color_buffer_;
};