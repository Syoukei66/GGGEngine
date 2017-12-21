#pragma once

#include "NativeObject.h"
#include "Geometry.h"

class INativeTexture
{
public:
  INativeTexture(const char* path);
  ~INativeTexture();

<<<<<<< HEAD
  // =================================================================
  // Methods
  // =================================================================
public:
  virtual const TSize& GetSize() = 0;
=======
public:
  inline const TSize& GetSize() const
  {
    return this->size_;
  }

private:
  TSize size_;
>>>>>>> parent of 4f2c2e8... NativeMatrixクラスの作成

};