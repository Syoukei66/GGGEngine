#pragma once

#include "Mesh.h"
#include "StaticMeshData.h"

class rcCustomMesh;

class rcStaticMesh : public rcMesh
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static rcStaticMesh* Create(rcVertexBuffer* vertex_buffer, rcIndexBuffer** index_buffers, T_UINT8 submesh_count, Graphics::PrimitiveType primitive_type = Graphics::PRIMITIVE_TRIANGLES);
  static rcStaticMesh* Create(const StaticMeshData& data);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  rcStaticMesh(rcVertexBuffer* vertex_buffer, rcIndexBuffer** index_buffers, T_UINT8 submesh_count, Graphics::PrimitiveType primitive_type);
  virtual ~rcStaticMesh();

};