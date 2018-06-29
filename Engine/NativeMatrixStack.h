#pragma once

#include "NativeObject.h"

#include "Matrix4x4.h"

struct NativeMatrixStackInstance { void* p; };

class INativeMatrixStack : public NativeObject<NativeMatrixStackInstance>
{
  // =================================================================
  // Static Method
  // =================================================================
public:
  static INativeMatrixStack* Create();

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  INativeMatrixStack(NativeMatrixStackInstance* instance)
    : NativeObject(instance)
  {}

  INativeMatrixStack() {}

  virtual ~INativeMatrixStack() {}

  // =================================================================
  // Assignment Operators
  // =================================================================
private:
  INativeMatrixStack(const INativeMatrixStack& obj) {}
  INativeMatrixStack& operator = (const INativeMatrixStack& obj) { return *this; }

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void Push(const Matrix4x4& mat) = 0;
  virtual void Pop() = 0;
  virtual const Matrix4x4& GetTop() = 0;

};