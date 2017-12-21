#pragma once

#include "NativeMatrix.h"
#include "NativeTexture.h"

class INativeObjectFactory
{
public:
  virtual INativeMatrix* CreateMatrix() = 0;
  virtual INativeTexture* CreateTexture(const char* path) = 0;

};