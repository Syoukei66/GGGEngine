#pragma once

#include "IVertexBufferObject.h"
#include "ITextureRegion.h"

class Sprite3D;

class VertexBufferObject_Sprite3D : public IVertexBufferObject
{
  enum SpriteVertexIndexes
  {
    V_VERTEX_V0,
    V_VERTEX_V1,
    V_VERTEX_V2,
    V_VERTEX_V3,
    V_VERTEX_MAX,
  };

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  VertexBufferObject_Sprite3D();

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
protected:
  virtual void OnInit() override;
  virtual void OnUpdateCoord(GameObject* entity) override;

public:
  virtual T_UINT32 GetVertexesCount() const override;
  virtual const void* GetVertexes() const override;
  virtual const T_UINT16* GetIndexes() const override;
  virtual INativeProcess_Graphics::PrimitiveType GetPrimitiveType() override;
  virtual INativeProcess_Graphics::VertexType GetVertexType() override;

  // =================================================================
  // Method
  // =================================================================
public:
  void OnVertexUvDirty();
  virtual void UpdateTexture(Sprite3D* entity, ITextureRegion* region);

  // =================================================================
  // Data Member
  // =================================================================
private:
  bool vertex_uv_dirty_;
  SpriteVertex vertexes_[V_VERTEX_MAX];
};
