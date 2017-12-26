#pragma once

#include "NativeObject.h"
#include "NativeMatrix.h"

struct NativeMatrixStackInstance { void* p; };

class INativeMatrixStack : public NativeObject<NativeMatrixInstance>
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
  INativeMatrixStack(NativeMatrixInstance* instance)
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
  virtual void Push(NativeMatrixInstance* mat) = 0;
  virtual void Pop() = 0;
  virtual NativeMatrixInstance* GetTop() = 0;

};