#pragma once

#include <Core/TextureRegion.h>
#include <Core/Mesh.h>
#include "Renderer.h"

class SpriteRenderer : public Renderer
{
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
  virtual void SetProperties(rcMaterial* material) const override;
  virtual void DrawSubset(T_UINT8 submesh_index) const override;
 
  // =================================================================
  // Method
  // =================================================================
public:
  virtual void FitToTexture();

  // =================================================================
  // setter/getter
  // =================================================================
public:
  void SetTextureRegion(rcTextureRegion* region);
  inline rcTextureRegion* GetTextureRegion()
  {
    return this->texture_region_;
  }

  void SetTexture(const rcTexture* texture);
  inline const rcTexture* GetTexture() const
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
  rcTextureRegion* texture_region_;
  rcMesh* mesh_;
  TSizef size_;

};