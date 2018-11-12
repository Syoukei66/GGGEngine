#pragma once

class EngineBehavior : public IEngineBehavior
{
public:
  virtual void SetupApplicationOption(ApplicationOption& option) override;
  virtual void SetupMainActivityOption(ActivityOption& option) override;
  virtual void SetupEngineOption(EngineOption& option) override;
  virtual SharedRef<Scene> FirstScene() override;
};