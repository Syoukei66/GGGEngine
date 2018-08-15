#pragma once

#include "../Core/NativeType.h"

class IMesh
{
public:
  virtual void SetStreamSource() const = 0;
  virtual void DrawSubset(T_UINT8 index) const = 0;

};
