#pragma once

#include <Core/Application/Platform/API/_Resource/APIResourceObject.h>

class rcTexture;

/*!
 * @brief RenderBuffer�̊��N���X
 * �v���b�g�t�H�[�����̏�����h���N���X���Œ�`����B
 */
class rcRenderBuffer : public GGAPIResourceObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(rcRenderBuffer);
  GG_CREATE_FUNC_1(rcRenderBuffer, void*);
  GG_DESTRUCT_FUNC(rcRenderBuffer);

  // =================================================================
  // Factory Method
  // =================================================================
public:
  static UniqueRef<rcRenderBuffer> CreateColorBuffer(const SharedRef<const rcTexture>& texture);
  static UniqueRef<rcRenderBuffer> CreateDepthStencilBuffer(T_UINT16 width, T_UINT16 height, Graphics::PixelFormat format);

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