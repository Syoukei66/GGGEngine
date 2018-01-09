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

  //ITextureRegion�����炩���߃Z�b�g������Ԃ�Sprite�𐶐����܂��B
  //Sprite�̃T�C�Y(width/height)��TiledTextureRegion�ɏ��������̂ƂȂ�܂��B
  //�����œn����TiledTextureRegion�̉���͂��̃N���X�ł͍s���܂���B
  static AnimatedSprite* CreateWithTextureRegion(TiledTextureRegion* region);

  //Texture����TiledTextureRegion���쐬���A
  //��������Ƃ�AnimatedSprite�𐶐����܂��B
  //Sprite�̃T�C�Y��Texture��(width,height)�����ꂼ��(x_num,y_num)�Ŋ��������̂ɂȂ�܂�
  //Texture�̉���͂��̃N���X�ł͍s���܂��񂪁A
  //�������ꂽTiledTextureRegion�̉���͂��̃N���X�ł͍s���܂��B
  static AnimatedSprite* CreateWithTexture(const Texture* texture, T_UINT8 x_num, T_UINT8 y_num);

  //�w�肵��ID����Texture���擾���A
  //����Texture����TiledTextureRegion���쐬���A
  //��������Ƃ�Sprite�𐶐����܂��B
  //Sprite�̃T�C�Y��Texture��(width,height)�����ꂼ��(x_num,y_num)�Ŋ��������̂ɂȂ�܂�
  //�������ꂽTiledTextureRegion�̉���͂��̃N���X�ōs���܂��B
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
