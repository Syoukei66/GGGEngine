#pragma once

#include "GameObject2D.h"
#include "SpriteRenderer.h"
#include "TextureResource.h"

class Sprite : public GameObject2D
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static Sprite* Create();
  static Sprite* CreateWithResource(const TextureResource& texture);
  static Sprite* CreateWithTexture(const INativeTexture* texture);
  static Sprite* CreateWithTextureRegion(ITextureRegion* region, bool delete_region);
  static Sprite* CreateWithMaterial(Material& material);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  Sprite() {}

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
  inline void SetTexture(const INativeTexture* texture)
  {
    this->GetSpriteRenderer()->SetTexture(texture);
  }
  inline const INativeTexture* GetTexture() const
  {
    return this->GetSpriteRenderer()->GetTexture();
  }

  inline void SetTextureRegion(ITextureRegion* region, bool delete_region)
  {
    this->GetSpriteRenderer()->SetTextureRegion(region, delete_region);
  }
  inline ITextureRegion* GetTextureRegion()
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
