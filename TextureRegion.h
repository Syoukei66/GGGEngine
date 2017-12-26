#ifndef HAL_ENGINE_ENTITY_SHAPE_SPRITE_TEXTUREREGION_TEXTUREREGION_H_
#define HAL_ENGINE_ENTITY_SHAPE_SPRITE_TEXTUREREGION_TEXTUREREGION_H_

#include "NativeType.h"
#include "ITextureRegion.h"

class TextureRegion : public ITextureRegion
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static TextureRegion* CreateWithTexture(const ITexture* texture);
  static TextureRegion* CreateFromAsset(T_UINT8 palette_id, T_UINT16 texture_id);

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
  virtual void OnUpdateTextureCoord() override;

};

#endif//HAL_ENGINE_ENTITY_SHAPE_SPRITE_TEXTUREREGION_TEXTUREREGION_H_

