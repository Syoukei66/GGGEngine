#pragma once

#include "Renderer.h"
#include "ITextureRegion.h"

class SpriteRenderer : public Renderer
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  SpriteRenderer(GameObject* entity, T_FLOAT image_scale);
  ~SpriteRenderer();

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual void EditProperty(T_UINT8 material_index, T_UINT8 pass_index, Material* material) override;
  virtual void DrawSubset(T_UINT8 material_index, T_UINT8 pass_index) override;

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void FitToTexture();

  // =================================================================
  // setter/getter
  // =================================================================
public:
  void SetTextureRegion(ITextureRegion* region, bool delete_region);
  inline ITextureRegion* GetTextureRegion()
  {
    return this->texture_region_;
  }

  void SetTexture(const INativeTexture* texture);
  inline const INativeTexture* GetTexture() const
  {
    return this->GetMaterial()->GetMainTexture();
  }

  inline void SetSize(const TSizef& size)
  {
    this->size_ = size;
  }
  inline void SetSize(T_FLOAT width, T_FLOAT height)
  {
    this->size_.width = width;
    this->size_.height = height;
  }
  inline const TSizef& GetSize() const
  {
    return this->size_;
  }
  inline void SetWidth(T_FLOAT width)
  {
    this->size_.width = width;
  }
  inline T_FLOAT GetWidth() const
  {
    return this->size_.width;
  }
  inline void SetHeight(T_FLOAT height)
  {
    this->size_.height = height;
  }
  inline T_FLOAT GetHeight() const
  {
    return this->size_.height;
  }

  // =================================================================
  // Data Member
  // =================================================================
protected:
  bool delete_region_;
  ITextureRegion* texture_region_;
  TSizef size_;
  T_FLOAT image_scale_;

};