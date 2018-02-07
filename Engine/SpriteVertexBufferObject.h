#ifndef HAL_ENGINE_SHAPE_SPRITE_VBO_SPRITEVERTEXBUFFEROBJECT_H
#define HAL_ENGINE_SHAPE_SPRITE_VBO_SPRITEVERTEXBUFFEROBJECT_H

#include "IVertexBufferObject.h"
#include "ITextureRegion.h"

class Shape;

class SpriteVertexBufferObject : public IVertexBufferObject
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
  // Factory Method
  // =================================================================
public:
  static SpriteVertexBufferObject* Create();

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  virtual ~SpriteVertexBufferObject() {};
protected:
  SpriteVertexBufferObject();

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
  virtual Vertex::VertexType GetVertexType() override;

  // =================================================================
  // Method
  // =================================================================
public:
  void OnVertexUvDirty();
  virtual void UpdateTexture(Shape* entity, ITextureRegion* region);

  // =================================================================
  // Data Member
  // =================================================================
private:
  bool vertex_uv_dirty_;
  Vertex::VCT vertexes_[V_VERTEX_MAX];
};

#endif//HAL_ENGINE_SHAPE_SPRITE_VBO_SPRITEVERTEXBUFFEROBJECT_H
