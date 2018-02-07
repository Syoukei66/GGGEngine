#ifndef HAL_ENGINE_ENTITY_SHAPE_VBO_IVERTEXBUFFEROBJECT_H_
#define HAL_ENGINE_ENTITY_SHAPE_VBO_IVERTEXBUFFEROBJECT_H_

#include "NativeMethod.h"
#include "NativeType.h"
#include "Vertex.h"
#include "GameObject.h"

class IVertexBufferObject
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  IVertexBufferObject();
  virtual ~IVertexBufferObject();

  // =================================================================
  // Method
  // =================================================================
public:
  void Init();
  void UpdateCoord(GameObject* entity);
  void OnVertexCoordDirty();

protected:
  virtual void OnInit() = 0;
  virtual void OnUpdateCoord(GameObject* entity) = 0;

  // =================================================================
  // setter/getter
  // =================================================================
public:
  virtual T_UINT32 GetVertexesCount() const = 0;
  virtual const void* GetVertexes() const = 0;
  virtual const T_UINT16* GetIndexes() const = 0;
  virtual INativeProcess_Graphics::PrimitiveType GetPrimitiveType() = 0;
  virtual Vertex::VertexType GetVertexType() = 0;
  
  // =================================================================
  // Data Member
  // =================================================================
protected:
  bool vertex_coord_dirty_;

};

#endif//HAL_ENGINE_ENTITY_SHAPE_VBO_IVERTEXBUFFEROBJECT_H_
