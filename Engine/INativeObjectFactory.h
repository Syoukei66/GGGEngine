#pragma once

#include "NativeMatrix.h"

class INativeObjectFactory
{
public:
  virtual INativeMatrix* CreateMatrix() = 0;


};