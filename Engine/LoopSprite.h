#ifndef HAL_ENGINE_ENTITY_SHAPE_LOOPSPRITE_H_
#define HAL_ENGINE_ENTITY_SHAPE_LOOPSPRITE_H_

#include "Sprite.h"
#include "LoopTextureRegion.h"

class LoopSprite : public Sprite
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static LoopSprite* Create();

  //ITextureRegionをあらかじめセットした状態でSpriteを生成します。
  //Spriteのサイズ(width/height)はLoopTextureRegionに準じたものとなります。
  //引数で渡したLoopTextureRegionの解放はこのクラスでは行われません。
  static LoopSprite* CreateWithTextureRegion(LoopTextureRegion* region);

  //TextureからLoopTextureRegionを作成し、
  //それをもとにLoopSpriteを生成します。
  //SpriteのサイズはTextureの(width,height)に準じたものとなります。
  //Textureの解放はこのクラスでは行われませんが、
  //生成されたLoopTextureRegionの解放はこのクラスでは行われます。
  static LoopSprite* CreateWithTexture(const Texture* texture);

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual void OnVertexCoordChanged();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline LoopTextureRegion* GetLoopTextureRegion()
  {
    return (LoopTextureRegion*)this->GetTextureRegion();
  }
};

#endif//HAL_ENGINE_ENTITY_SHAPE_LOOPSPRITE_H_