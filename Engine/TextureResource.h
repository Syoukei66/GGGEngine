#ifndef HAL_ENGINE_RESOURCE_TEXTURE_H_
#define HAL_ENGINE_RESOURCE_TEXTURE_H_

#include <string>
#include "NativeTexture.h"
#include "FileResource.h"

class TextureResource : public FileResource<INativeTexture>
{
public:
  static TextureResource* DynamicLoad(const char* path);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  TextureResource(const char* path);

  // =================================================================
  // Methods
  // =================================================================
public:
  virtual INativeTexture* NativeLoadProcess(const std::string& path) override;

  // =================================================================
  // Setter / Getter
  // =================================================================
  inline T_UINT16 GetWidth() const
  {
    return this->GetContents()->GetWidth();
  }

  inline T_UINT16 GetHeight() const
  {
    return this->GetContents()->GetHeight();
  }

};

#endif//HAL_ENGINE_RESOURCE_TEXTURE_H_
