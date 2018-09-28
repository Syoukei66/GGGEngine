#pragma once

#include "Asset.h"
#include "Model.h"

class ModelAsset : public BaseAsset<ModelAsset, rcModel>
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:

  // =================================================================
  // Methods
  // =================================================================
protected:
  virtual rcModel* LoadProcess(const std::string& path) override;

  // =================================================================
  // Data Member
  // =================================================================
private:
};
