#pragma once

#include <INativeProcess_Material.h>

class NativeProcess_Material : public INativeProcess_Material
{
public:
  virtual LP_MATERIAL Material_Create() override;
  virtual void Material_Delete(LP_MATERIAL material) override;
  virtual void Material_SetDiffuse(LP_MATERIAL material, const Color& color) override;
  virtual void Material_SetAmbient(LP_MATERIAL material, const Color& color) override;
};
