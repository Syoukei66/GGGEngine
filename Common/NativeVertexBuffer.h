#pragma once

#include <vector>

#include "Geometry.h"
#include "NativeObject.h"
#include "GraphicsConstants.h"
#include "NativeIndexBuffer.h"

struct NativeVertexBufferInstance { void* p; };

class INativeVertexBuffer : public NativeObject<NativeVertexBufferInstance>
{
  // =================================================================
  // Static Method
  // =================================================================
public:
  static INativeVertexBuffer* Create(T_UINT16 vertex_count, T_UINT16 polygon_count, T_UINT32 format);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  INativeVertexBuffer(NativeVertexBufferInstance* instance)
    : NativeObject(instance)
  {}

  INativeVertexBuffer() {}

  virtual ~INativeVertexBuffer() {}

  //ÉRÉsÅ[ã÷é~
private:
  INativeVertexBuffer(const INativeVertexBuffer& mat) {}

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void Lock(void** dest) = 0;
  virtual void Unlock() = 0;

  virtual void SetStreamSource() const = 0;

  virtual void DrawPrimitive(Graphics::PrimitiveType primitive_type) const = 0;
  virtual void DrawIndexedPrimitive(const INativeIndexBuffer* index_buffer, Graphics::PrimitiveType primitive_type) const = 0;

  virtual T_UINT32 GetMemorySize() const = 0;

};