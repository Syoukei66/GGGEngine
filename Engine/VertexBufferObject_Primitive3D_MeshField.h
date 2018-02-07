#pragma once

#include "IVertexBufferObject.h"

class VertexBufferObject_Primitive3D_MeshField : public IVertexBufferObject
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  VertexBufferObject_Primitive3D_MeshField(T_FLOAT width, T_FLOAT height, T_UINT16 x_num, T_UINT16 y_num);
  ~VertexBufferObject_Primitive3D_MeshField();

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
  // Data Member
  // =================================================================
private:
  T_UINT32 vertexes_count_;
  Vertex::VNCT* vertexes_;

  T_UINT32 indexes_count_;
  T_UINT16* indexes_;
};