#ifndef HAL_ENGINE_ACTIVITY_BASEACTIVITY_H_
#define HAL_ENGINE_ACTIVITY_BASEACTIVITY_H_

#include <fbxsdk.h>
#include "Engine.h"
#include "EngineInput.h"

#include "INativeProcess_Graphics.h"
#include "INativeProcess_IO.h"
#include "INativeProcess_Time.h"

class BaseActivity
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  BaseActivity();
  virtual ~BaseActivity();

  // =================================================================
  // Method
  // =================================================================
public:
  bool Run(IEngineSetting* setting);

protected:
  virtual INativeProcess_Graphics* SetupNativeProcess_Graphics() = 0;
  virtual INativeProcess_IO* SetupNativeProcess_IO() = 0;
  virtual INativeProcess_Time* SetupNativeProcess_Time() = 0;

  virtual bool ApplyEngineOption(const EngineOption* option) = 0;
  virtual bool Init(const EngineOption* option) = 0;
  virtual bool Uninit() = 0;
  virtual bool FrameEnabled() = 0;
  virtual void ImGuiNewFrame() = 0;
  virtual bool ContinueEnabled() = 0;
  virtual bool PreDraw() = 0;
  virtual void PostDraw() = 0;
  virtual void ImGuiEndFrame() = 0;
  virtual void InputProcess(EngineInputState* state) = 0;
  bool Update();
  bool Draw();
  
  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  virtual LP_DEVICE GetDevice() const = 0;

  inline FbxManager* GetFbxManager() const
  {
    return this->fbx_manager_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  Engine* engine_;

  FbxManager* fbx_manager_;

};

#endif//HAL_ENGINE_ACTIVITY_BASEACTIVITY_H_
