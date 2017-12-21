#pragma once

#include "NativeMatrix.h"

class INativeMatrixStack
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  INativeMatrixStack();

  // =================================================================
  // Method
  // =================================================================
public:
  void Push(NativeMatrixInstance* mat);
  void Pop();
  NativeMatrixInstance* GetTop();

};