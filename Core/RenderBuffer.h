#pragma once

#include "Resource.h"

class rcTexture;

class rcRenderBuffer : public Resource
{
public:
  enum Format
  {
    FORMAT_D16,
    FORMAT_D24S8,
    FORMAT_D32,
    FORMAT_R8G8B8A8,
    FORMAT_R16G16B16A16,
    FORMAT_R16G16B16A16F,

    FORMAT_DATANUM,
  };

  // =================================================================
  // Factory Method
  // =================================================================
public:
  static UniqueResource<rcRenderBuffer> CreateColorBuffer(const SharedRef<const rcTexture>& texture);
  static UniqueResource<rcRenderBuffer> CreateDepthStencilBuffer(T_UINT16 width, T_UINT16 height, Format format);
  static UniqueResource<rcRenderBuffer> Create(void* native_obj);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  rcRenderBuffer(void* native_obj);
  virtual ~rcRenderBuffer();

  // =================================================================
  // Getter / Setter
  // =================================================================
public:
  inline virtual const char* GetResourceName() override
  {
    return "RenderBuffer";
  }

  inline void* GetNativeObject()
  {
    return this->native_obj_;
  }
  inline const void* GetNativeObject() const
  {
    return this->native_obj_;
  }

  virtual size_t GetMemorySize() const override
  {
    //TODO:��������Ȃ�
    return sizeof(rcRenderBuffer);
  }
  virtual size_t GetVideoMemorySize() const override
  {
    //TODO:��������Ȃ�
    return 0;
  }

  // =================================================================
  // Data Members
  // =================================================================
protected:
  void* native_obj_;

};