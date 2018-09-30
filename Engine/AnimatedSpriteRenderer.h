#pragma once

#include <Core/TiledTextureRegion.h>

#include "SpriteRenderer.h"

class AnimatedSpriteRenderer : public SpriteRenderer
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  AnimatedSpriteRenderer(GameObject* entity);

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual void Update() override;

  // =================================================================
  // setter/getter
  // =================================================================
public:
  void SetAnimateRange(T_UINT16 begin, T_UINT16 end);
  void Animate(T_UINT16 duration_frame);
  void SetCurrentIndex(T_UINT16 index);
  inline T_UINT16 GetCurrentIndex() const
  {
    return this->GetTiledTextureRegion()->GetCurrentIndex();
  }
  inline rcTiledTextureRegion* GetTiledTextureRegion() const
  {
    return (rcTiledTextureRegion*)this->texture_region_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  T_UINT16 frame_count_;
  T_UINT16 duration_frame_;
  T_UINT16 animation_begin_;
  T_UINT16 animation_end_;
};
