#pragma once

#include "ITexture.h"

class StaticTexture : public ITexture
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  //texture‚Ì‰ð•ú‚Ís‚¢‚Ü‚¹‚ñ
  StaticTexture(INativeTexture* native_texture);

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
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


  // =================================================================
  // Data Member
  // =================================================================
private:
  INativeTexture* native_texture_;
  TSize size_;

};