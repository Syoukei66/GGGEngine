#ifndef HAL_ENGINE_ENTITY_SHAPE_ANIMATEDSPRITE_H_
#define HAL_ENGINE_ENTITY_SHAPE_ANIMATEDSPRITE_H_

#include "Sprite.h"
#include "TiledTextureRegion.h"

class AnimatedSprite : public Sprite
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static AnimatedSprite* Create();

  //ITextureRegionをあらかじめセットした状態でSpriteを生成します。
  //Spriteのサイズ(width/height)はTiledTextureRegionに準じたものとなります。
  //引数で渡したTiledTextureRegionの解放はこのクラスでは行われません。
  static AnimatedSprite* CreateWithTextureRegion(TiledTextureRegion* region);

  //TextureからTiledTextureRegionを作成し、
  //それをもとにAnimatedSpriteを生成します。
  //SpriteのサイズはTextureの(width,height)をそれぞれ(x_num,y_num)で割ったものになります
  //Textureの解放はこのクラスでは行われませんが、
  //生成されたTiledTextureRegionの解放はこのクラスでは行われます。
  static AnimatedSprite* CreateWithTexture(const Texture* texture, T_UINT8 x_num, T_UINT8 y_num);

  //指定したIDからTextureを取得し、
  //そのTextureからTiledTextureRegionを作成し、
  //それをもとにSpriteを生成します。
  //SpriteのサイズはTextureの(width,height)をそれぞれ(x_num,y_num)で割ったものになります
  //生成されたTiledTextureRegionの解放はこのクラスで行われます。
  static AnimatedSprite* CreateFromAsset(T_UINT8 palette_id, T_UINT16 texture_id, T_UINT8 x_num, T_UINT8 y_num);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  AnimatedSprite();

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual void Init() override;
  virtual void PreDraw(GameObject2DRenderState* state) override;

  // =================================================================
  // Method
  // =================================================================
public:
  void Animate(T_UINT16 duration_frame);

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  void SetCurrentIndex(T_UINT16 index);
  inline T_UINT16 GetCurrentIndex() const
  {
    return ((TiledTextureRegion*)this->GetTextureRegion())->GetCurrentIndex();
  }
  inline TiledTextureRegion* GetTiledTextureRegion()
  {
    return (TiledTextureRegion*)this->GetTextureRegion();
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  T_UINT16 frame_count_;
  T_UINT16 duration_frame_;

};

#endif//HAL_ENGINE_ENTITY_SHAPE_ANIMATEDSPRITE_H_
