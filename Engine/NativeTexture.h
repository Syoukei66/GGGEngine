#pragma once

#include "NativeObject.h"
#include "Geometry.h"

class NativeTexture : public NativeObject
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  NativeTexture(const char* path);
  ~NativeTexture();

  // =================================================================
  // setter/getter
  // =================================================================
public:
  inline const TSize& GetSize() const
  {
    return this->size_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  TSize size_;

};