#pragma once

#include "NativeObject.h"
#include "Geometry.h"
#include "GameObjectRenderState.h"

struct NativeModelInstance { void* p; };

class INativeModel : public NativeObject<NativeModelInstance>
{
  // =================================================================
  // Static Method
  // =================================================================
public:
  //name�͊g���q���܂ރt�@�C����
  static INativeModel* Create(const char* directory_path, const char* name, const char* extension);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  INativeModel(NativeModelInstance* instance)
    : NativeObject(instance)
  {}
  virtual ~INativeModel() {}

  // =================================================================
  // Methods
  // =================================================================
public:
  virtual void Draw(GameObjectRenderState* state) const = 0;

};