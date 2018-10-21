#pragma once

#include "Resource.h"

class rcIndexBuffer : public Resource
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static UniqueResource<rcIndexBuffer> Create(T_UINT32 vertex_count, T_UINT32 polygon_count);

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
  // Getter / Setter
  // =================================================================
public:
  inline virtual const char* GetResourceName() override
  {
    return "IndexBuffer";
  }

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  virtual T_UINT32 GetVertexesCount() const = 0;
  virtual T_UINT32 GetPolygonCount() const = 0;

};