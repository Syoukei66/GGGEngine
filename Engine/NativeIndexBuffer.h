#pragma once

#include "Geometry.h"
#include "NativeObject.h"

struct NativeIndexBufferInstance { void* p; };

class INativeIndexBuffer : public NativeObject<NativeIndexBufferInstance>
{
  // =================================================================
  // Static Method
  // =================================================================
public:
  static INativeIndexBuffer* Create(T_UINT16 vertex_count);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  INativeIndexBuffer(NativeIndexBufferInstance* instance)
    : NativeObject(instance)
  {}

  INativeIndexBuffer() {}

  virtual ~INativeIndexBuffer() {}

  //ÉRÉsÅ[ã÷é~
private:
  INativeIndexBuffer(const INativeIndexBuffer& mat) {}

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void Lock(void** dest) = 0;
  virtual void Unlock() = 0;
  virtual void SetIndices() const = 0;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  virtual T_UINT16 GetVertexesCount() const = 0;

};