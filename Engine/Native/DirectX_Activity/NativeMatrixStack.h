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
  virtual void Push(const Matrix4x4& mat) override;
  virtual void Pop() override;
  virtual const Matrix4x4& GetTop() override;
};