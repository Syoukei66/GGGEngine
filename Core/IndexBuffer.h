#pragma once

#include "Resource.h"

class rcIndexBuffer : public Resource
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static rcIndexBuffer* Create(T_UINT32 vertex_count);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  rcIndexBuffer() {}
  virtual ~rcIndexBuffer() {}

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