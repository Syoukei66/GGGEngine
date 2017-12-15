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

  //ITextureRegion�����炩���߃Z�b�g������Ԃ�Sprite�𐶐����܂��B
  //Sprite�̃T�C�Y(width/height)��LoopTextureRegion�ɏ��������̂ƂȂ�܂��B
  //�����œn����LoopTextureRegion�̉���͂��̃N���X�ł͍s���܂���B
  static LoopSprite* CreateWithTextureRegion(LoopTextureRegion* region);

  //Texture����LoopTextureRegion���쐬���A
  //��������Ƃ�LoopSprite�𐶐����܂��B
  //Sprite�̃T�C�Y��Texture��(width,height)�ɏ��������̂ƂȂ�܂��B
  //Texture�̉���͂��̃N���X�ł͍s���܂��񂪁A
  //�������ꂽLoopTextureRegion�̉���͂��̃N���X�ł͍s���܂��B
  static LoopSprite* CreateWithTexture(const ITexture* texture);

  //�w�肵��ID����Texture���擾���A
  //����Texture����LoopTextureRegion���쐬���A
  //��������Ƃ�LoopSprite�𐶐����܂��B
  //Sprite�̃T�C�Y��Texture��(width,height)�ɏ��������̂ƂȂ�܂��B
  //��������LoopTextureRegion�̉���͂��̃N���X�ł͍s���܂��B
  static LoopSprite* CreateFromAsset(T_UINT8 palette_id, T_UINT16 texture_id);

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