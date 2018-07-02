#ifndef HAL_ENGINE_ENTITY_SHAPE_SPRITE_TEXTUREREGION_TEXTUREREGION_H_
#define HAL_ENGINE_ENTITY_SHAPE_SPRITE_TEXTUREREGION_TEXTUREREGION_H_

#include "NativeType.h"
#include "ITextureRegion.h"
#include "TextureResource.h"
#include "Material.h"

class TextureRegion : public ITextureRegion
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static TextureRegion* CreateWithMaterial(const Material& material);
  static TextureRegion* CreateWithResource(const TextureResource& texture);
  static TextureRegion* CreateWithTexture(const Texture* texture);

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
  virtual void OnUpdateTextureCoord(const Texture* texture) override;

};

#endif//HAL_ENGINE_ENTITY_SHAPE_SPRITE_TEXTUREREGION_TEXTUREREGION_H_

