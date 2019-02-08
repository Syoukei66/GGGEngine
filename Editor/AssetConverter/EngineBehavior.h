#pragma once

#include <Engine/Engine/IEngineBehavior.h>
#include "IAssetConverterAddIn.h"

class EngineBehavior : public IEngineBehavior
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  EngineBehavior(IAssetConverterAddIn* addin);
  virtual ~EngineBehavior();

  // =================================================================
  // Methods from IEngineBehavior
  // =================================================================
public:
  virtual void OnApplicationBegin() override;
  virtual void OnApplicationEnd() override;
  virtual void OnGameBegin() override;
  virtual void OnGameEnd() override;
  virtual void SetupApplicationOption(ApplicationOption& option) override;
  virtual void SetupMainActivityOption(ActivityOption& option) override;
  virtual void SetupEngineOption(EngineOption& option) override;
  virtual SharedRef<Scene> FirstScene() override;

  // =================================================================
  // Methods from IEngineBehavior
  // =================================================================
private:
  IAssetConverterAddIn* addin_;

};