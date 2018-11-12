#pragma once

class EngineBehavior : public IEngineBehavior
{
// =================================================================
// Methods from IEngineBehavior
// =================================================================
public:
  virtual void OnApplicationBegin() override;
  virtual void OnApplicationEnd() override;
  virtual void SetupApplicationOption(ApplicationOption& option) override;
  virtual void SetupMainActivityOption(ActivityOption& option) override;
  virtual void SetupEngineOption(EngineOption& option) override;
  virtual Scene* FirstScene() override;
};