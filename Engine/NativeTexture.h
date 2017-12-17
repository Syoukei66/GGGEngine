#pragma once

#include "NativeObject.h"
#include "Geometry.h"

class NativeTexture : public NativeObject
{
public:
  NativeTexture(const char* path);
  ~NativeTexture();

public:
  inline const TSize& GetSize() const
  {
    return this->size_;
  }

private:
  TSize size_;

};