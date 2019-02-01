#pragma once

#include <Core/Application/IApplicationBehavior.h>
#include <Engine/Engine/IEngineBehavior.h>

/*!
 * @brief Sceneを用いてゲームを動作させるクラス
 */
class Engine : public IApplicationBehavior
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Engine(IEngineBehavior* engine_behavior);

  // =================================================================
  // Methods from IApplicationBehavior
  // =================================================================
protected:
  virtual void SetupApplicationOption(ApplicationOption& option) override;
  virtual void SetupMainActivityOption(ActivityOption& option) override;
  virtual void OnApplicationBegin() override;
  virtual void OnApplicationEnd() override;
  virtual void Init() override;
  virtual void Uninit() override;
  virtual SharedRef<Activity> CreateMainActivity() override;
  
  // =================================================================
  // Data Members
  // =================================================================
private:
  IEngineBehavior* engine_behavior_;

};