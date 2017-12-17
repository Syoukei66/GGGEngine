#pragma once

#include "ITexture.h"

class StaticTexture : public ITexture
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  //texture‚Ì‰ð•ú‚Ís‚¢‚Ü‚¹‚ñ
  StaticTexture(NativeTexture* native_texture);

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline bool IsLoaded() const override
  {
    return this->native_texture_;
  }

  inline const NativeTexture* GetNativeTexture() const override
  {
    return this->native_texture_;
  }

  inline const TSize& GetSize() const override
  {
    return this->size_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  NativeTexture* native_texture_;
  TSize size_;

};