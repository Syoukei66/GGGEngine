#pragma once

#include "Primitive3D.h"
#include "Texture.h"
#include "Material.h"

class Shape3D : public Primitive3D
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Shape3D(IVertexBufferObject* vbo);
  virtual ~Shape3D();

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  void NativeDraw(GameObject3DRenderState* state) override;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline void SetTexture(const Texture* texture) 
  {
    this->texture_ = texture;
  }
  inline void SetTexture(const Texture& texture)
  {
    this->texture_ = &texture;
  }
  inline const Texture* GetTexture() const
  {
    return this->texture_;
  }
  inline Material* GetMaterial()
  {
    return this->material_;
  }
  inline const Material* GetMaterial() const
  {
    return this->material_;
  }
  inline void SetLightingEnabled(bool enabled)
  {
    this->lighting_enabled_ = enabled;
  }
  inline bool GetLightingEnabled() const
  {
    return this->lighting_enabled_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  Material* material_;
  const Texture* texture_;
  bool lighting_enabled_;

};