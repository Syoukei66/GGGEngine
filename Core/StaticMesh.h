#pragma once

#include "Mesh.h"

class rcCustomMesh;

class rcStaticMesh : public rcMesh
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  static rcStaticMesh* Create(rcVertexBuffer* vertex_buffer, rcIndexBuffer** index_buffers, T_UINT8 submesh_count, Graphics::PrimitiveType primitive_type);

protected:
  rcStaticMesh(rcVertexBuffer* vertex_buffer, rcIndexBuffer** index_buffers, T_UINT8 submesh_count, Graphics::PrimitiveType primitive_type);
  virtual ~rcStaticMesh();

};