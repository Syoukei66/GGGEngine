#pragma once

#include "GameObject3D.h"
#include "SpriteRenderer.h"

class Sprite3D : public GameObject3D
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static Sprite3D* Create();
  static Sprite3D* CreateWithTexture(const rcTexture* texture);
  static Sprite3D* CreateWithTextureRegion(rcTextureRegion* region);
  static Sprite3D* CreateWithMaterial(rcMaterial& material);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  Sprite3D() {}

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline SpriteRenderer* GetSpriteRenderer() const
  {
    return (SpriteRenderer*)this->GetRenderer();
  }

  // =================================================================
  // delegate to SpriteRenderer
  // =================================================================
public:
  inline void FitToTexture()
  {
    this->GetSpriteRenderer()->FitToTexture();
  }
  inline void SetTexture(const rcTexture* texture)
  {
    this->GetSpriteRenderer()->SetTexture(texture);
  }
  inline const rcTexture* GetTexture() const
  {
    return this->GetSpriteRenderer()->GetTexture();
  }

  inline void SetTextureRegion(TextureRegion* region, bool delete_region)
  {
    this->GetSpriteRenderer()->SetTextureRegion(region, delete_region);
  }
  inline TextureRegion* GetTextureRegion()
  {
    return this->GetSpriteRenderer()->GetTextureRegion();
  }

  inline void SetSize(const TSizef& size)
  {
    this->GetSpriteRenderer()->SetSize(size);
  }
  inline void SetSize(T_FLOAT width, T_FLOAT height)
  {
    this->GetSpriteRenderer()->SetSize(width, height);
  }
  inline const TSizef& GetSize() const
  {
    return this->GetSpriteRenderer()->GetSize();
  }
  inline void SetWidth(T_FLOAT width)
  {
    this->GetSpriteRenderer()->SetWidth(width);
  }
  inline T_FLOAT GetWidth() const
  {
    return this->GetSpriteRenderer()->GetWidth();
  }
  inline void SetHeight(T_FLOAT height)
  {
    this->GetSpriteRenderer()->SetHeight(height);
  }
  inline T_FLOAT GetHeight() const
  {
    return this->GetSpriteRenderer()->GetHeight();
  }
};
