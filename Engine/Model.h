#pragma once

#include "GameObject3D.h"
#include "ModelData.h"

class Model : public GameObject3D
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  //TODO:Œã‚ÅModelData‚Æ•ª‚¯‚é
  Model(const ModelData* data);
  ~Model();

  // =================================================================
  // Method
  // =================================================================
public:
  void NativeDraw(GameObject3DRenderState* state) override;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline void SetLightingEnabled(bool enabled)
  {
    this->lighting_enabled_ = enabled;
  }
  inline bool GetLightingEnabled() const
  {
    return this->lighting_enabled_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  const ModelData* data_;
  bool lighting_enabled_;
};