#pragma once

#include <Asset/Sprite/Sprite.h>
#include "Renderer.h"

class SpriteRenderer : public Renderer
{
  // =================================================================
  // FactoryMethod
  // =================================================================
public:
  static SpriteRenderer* Create(const SharedRef<rcSprite>& sprite, GameObject* obj);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  SpriteRenderer(GameObject* entity);
  ~SpriteRenderer();

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
protected:
  virtual bool SetStreamSource() const override;
  virtual void SetProperties(const SharedRef<rcShader>& shader) const override;
  virtual void DrawSubset(T_UINT8 submesh_index) const override;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE void SetSprite(const SharedRef<rcSprite>& sprite)
  {
    this->sprite_ = sprite;
  }
  GG_INLINE SharedRef<const rcSprite> GetSprite() const
  {
    return this->sprite_;
  }

  // =================================================================
  // Data Member
  // =================================================================
protected:
  SharedRef<rcSprite> sprite_;

};