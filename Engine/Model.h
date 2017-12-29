#pragma once

#include "GameObject3D.h"

class Model : public GameObject3D
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  //TODO:Œã‚ÅModelData‚Æ•ª‚¯‚é
  Model(const char* path);
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
  LP_MODEL model_;
  bool lighting_enabled_;
};