#pragma once

#include <vector>

#include "Resource.h"
#include "GraphicsConstants.h"

#include "IndexBuffer.h"

class rcVertexBuffer : public Resource
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static UniqueResource<rcVertexBuffer> Create(T_UINT16 vertex_count, T_UINT16 polygon_count, T_UINT32 format);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  rcVertexBuffer() {}
  virtual ~rcVertexBuffer() {}

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void Lock(void** dest) = 0;
  virtual void Unlock() = 0;

  virtual void SetStreamSource() const = 0;

  virtual void DrawPrimitive(Graphics::PrimitiveType primitive_type) const = 0;
  virtual void DrawIndexedPrimitive(const SharedRef<const rcIndexBuffer>& index_buffer, Graphics::PrimitiveType primitive_type) const = 0;

  // =================================================================
  // Getter / Setter
  // =================================================================
public:
  inline virtual const char* GetResourceName() override
  {
    return "VertexBuffer";
  }

};