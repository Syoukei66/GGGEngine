#pragma once

#include "Sprite3D.h"
#include "TiledTextureRegion.h"

class AnimatedSprite3D : public Sprite3D
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static AnimatedSprite3D* CreateWithTexture(const Texture* texture, T_UINT8 x_num, T_UINT8 y_num);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  AnimatedSprite3D();

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual void Init() override;
  virtual void Update() override;

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