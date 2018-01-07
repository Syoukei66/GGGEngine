#pragma once

#include "NativeObject.h"
#include "Geometry.h"

struct NativeModelInstance { void* p; };

class INativeModel : public NativeObject<NativeModelInstance>
{
  // =================================================================
  // Static Method
  // =================================================================
public:
  static INativeModel* Create(const char* directory_path, const char* name);

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
  virtual void Draw() const = 0;

};