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
  virtual void SetProperties(const SharedRef<rcShader>& shader) const override;
  virtual void DrawSubset(T_UINT8 submesh_index) const override;
 
  // =================================================================
  // Method
  // =================================================================
public:
  virtual void FitToTexture();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  void SetTextureRegion(const SharedRef<rcTextureRegion>& region);
  GG_INLINE const SharedRef<rcTextureRegion>& GetTextureRegion()
  {
    return this->texture_region_;
  }

  void SetTexture(const SharedRef<const rcTexture>& texture);
  GG_INLINE const SharedRef<const rcTexture>& GetTexture() const
  {
    return this->GetMaterial()->GetMainTexture();
  }

  GG_INLINE void SetSize(const TSizef& size)
  {
    this->size_ = size;
  }
  GG_INLINE void SetSize(T_FLOAT width, T_FLOAT height)
  {
    this->size_.width = width;
    this->size_.height = height;
  }
  GG_INLINE const TSizef& GetSize() const
  {
    return this->size_;
  }
  GG_INLINE void SetWidth(T_FLOAT width)
  {
    this->size_.width = width;
  }
  GG_INLINE T_FLOAT GetWidth() const
  {
    return this->size_.width;
  }
  GG_INLINE void SetHeight(T_FLOAT height)
  {
    this->size_.height = height;
  }
  GG_INLINE T_FLOAT GetHeight() const
  {
    return this->size_.height;
  }

  // =================================================================
  // Data Member
  // =================================================================
protected:
  SharedRef<rcTextureRegion> texture_region_;
  SharedRef<rcMesh> mesh_;
  TSizef size_;

};