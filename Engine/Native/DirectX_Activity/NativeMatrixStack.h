#pragma once

#include <NativeMatrixStack.h>

class NativeMatrixStack : public INativeMatrixStack
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  NativeMatrixStack();
  ~NativeMatrixStack();

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void Push(NativeMatrixInstance* mat) override;
  virtual void Pop() override;
  virtual NativeMatrixInstance* GetTop() override;
};