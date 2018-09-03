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
  static rcRenderBuffer* CreateColorBuffer(rcTexture* texture);
  static rcRenderBuffer* CreateDepthStencilBuffer(T_UINT16 width, T_UINT16 height, Format format);
  static rcRenderBuffer* Create(void* native_obj);

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
    //TODO:Œµ–§‚¶‚á‚È‚¢
    return sizeof(rcRenderBuffer);
  }
  virtual size_t GetVideoMemorySize() const override
  {
    //TODO:Œµ–§‚¶‚á‚È‚¢
    return 0;
  }

  // =================================================================
  // Data Members
  // =================================================================
protected:
  void* native_obj_;

};