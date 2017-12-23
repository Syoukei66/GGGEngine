#ifndef HAL_ENGINE_RESOURCE_TEXTURE_H_
#define HAL_ENGINE_RESOURCE_TEXTURE_H_

#include <string>
#include "ITexture.h"

class Texture : public ITexture
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Texture(const std::string& path);
  ~Texture();

  // =================================================================
  // Methods
  // =================================================================
public:
  void Load();
  void Unload();

  // =================================================================
  // Setter / Getter
  // =================================================================
  inline bool IsLoaded() const override
  {
    return this->native_texture_;
  }

  inline const INativeTexture* GetNativeTexture() const override
  {
    return this->native_texture_;
  }

  inline T_UINT16 GetWidth() const override
  {
    return this->native_texture_->GetWidth();
  }

  inline T_UINT16 GetHeight() const override
  {
    return this->native_texture_->GetHeight();
  }

  inline const std::string& GetPath() const
  {
    return this->path_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  std::string path_;
  INativeTexture* native_texture_;
};

#endif//HAL_ENGINE_RESOURCE_TEXTURE_H_
