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
  virtual void Update(const UpdateEventState& state) override;
  virtual void Draw() override;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE SceneManager* GetSceneManager() const
  {
    return this->scene_manager_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  IEngineBehavior* engine_behavior_;
  SceneManager* scene_manager_;

};