#ifndef HAL_ENGINE_ENTITY_SHAPE_SPRITE_H_
#define HAL_ENGINE_ENTITY_SHAPE_SPRITE_H_

#include "Shape.h"
#include "SpriteVertexBufferObject.h"
#include "ITextureRegion.h"

class Sprite : public Shape
{  
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static Sprite* Create();
  static Sprite* CreateWithTextureRegion(ITextureRegion* region);
  static Sprite* CreateWithTexture(const Texture* texture);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  virtual ~Sprite();
protected:
  Sprite();

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual void Init() override;
  virtual void PreDraw(GameObject2DRenderState* state) override;
  virtual void PreNativeDraw(GameObject2DRenderState* state) override;
  virtual void NativeDraw(GameObject2DRenderState* state) override;
  virtual void PostDraw(GameObject2DRenderState* state) override;

  // =================================================================
  // Method
  // =================================================================
public:
  void OnTextureChanged();
  //Sprite�̃T�C�Y(width/height)��ITextureRegion�ɏ��������̂ɕύX���܂��B
  //ITextureRegion��NULL�̏ꍇ�A�T�C�Y��0*0�ɂȂ�܂��B
  void FitToTexture();

  // =================================================================
  // setter/getter
  // =================================================================
public:
  virtual IVertexBufferObject* GetVbo() const override;
  void SetTextureRegion(ITextureRegion* itr);
  inline ITextureRegion* GetTextureRegion() const
  {
    return this->texture_region_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  SpriteVertexBufferObject* vbo_;
  ITextureRegion* texture_region_;

protected:
  //TODO:KEN,�ǂ��ɂ�����
  bool delete_region_;
};

#endif//HAL_ENGINE_ENTITY_SHAPE_SPRITE_H_

