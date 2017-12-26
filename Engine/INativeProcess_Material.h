#pragma once

#include "NativeType.h"
#include "NativeType.h"
#include "Material.h"

class INativeProcess_Material
{
  // =================================================================
  // Method
  // =================================================================
public:
  virtual LP_MATERIAL Material_Create() = 0;
  virtual void Material_Delete(LP_MATERIAL material) = 0;
  virtual void Material_SetDiffuse(LP_MATERIAL material, const Color& color) = 0;
  virtual void Material_SetAmbient(LP_MATERIAL material, const Color& color) = 0;

};
