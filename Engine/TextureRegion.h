#pragma once

#include "../Core/NativeType.h"
#include "../Asset/Material.h"
#include "ITextureRegion.h"

class TextureRegion : public ITextureRegion
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static TextureRegion* CreateWithMaterial(const Material& material);
  static TextureRegion* CreateWithTexture(const rcTexture* texture);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  TextureRegion();
  virtual ~TextureRegion();

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual void OnUpdateTextureCoord(const rcTexture* texture) override;

};


