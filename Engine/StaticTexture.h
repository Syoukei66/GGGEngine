#pragma once

#include "ITexture.h"

class StaticTexture : public ITexture
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  //texture‚Ì‰ð•ú‚Ís‚¢‚Ü‚¹‚ñ
  StaticTexture(LP_TEXTURE native_texture);

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline bool IsLoaded() const override
  {
    return this->native_texture_;
  }

  inline const LP_TEXTURE GetNativeTexture() const override
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
  LP_TEXTURE native_texture_;
  TSize size_;

};