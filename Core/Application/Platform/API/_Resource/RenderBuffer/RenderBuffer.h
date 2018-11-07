#pragma once

#include <Core/Application/Platform/API/_Resource/APIResourceObject.h>

class rcTexture;

/*!
 * @brief RenderBufferの基底クラス
 * プラットフォーム毎の処理を派生クラス側で定義する。
 */
class rcRenderBuffer : public GGAPIResourceObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT_NAME(rcRenderBuffer);

  // =================================================================
  // Factory Method
  // =================================================================
public:
  static UniqueRef<rcRenderBuffer> CreateColorBuffer(const SharedRef<const rcTexture>& texture);
  static UniqueRef<rcRenderBuffer> CreateDepthStencilBuffer(T_UINT16 width, T_UINT16 height, Graphics::PixelFormat format);
  static UniqueRef<rcRenderBuffer> Create(void* native_obj);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  rcRenderBuffer(void* native_obj);
  virtual ~rcRenderBuffer();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE void* GetNativeObject()
  {
    return this->native_obj_;
  }
  GG_INLINE const void* GetNativeObject() const
  {
    return this->native_obj_;
  }

  // =================================================================
  // Data Members
  // =================================================================
protected:
  void* native_obj_;

};