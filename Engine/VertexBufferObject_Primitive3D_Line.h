#pragma once

#include "IVertexBufferObject.h"

class VertexBufferObject_Primitive3D_Line : public IVertexBufferObject
{  
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  VertexBufferObject_Primitive3D_Line();

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

};