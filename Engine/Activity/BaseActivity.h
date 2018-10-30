#pragma once

class Engine;
struct EngineOption;
class EngineInputState;
class IEngineSetting;

typedef int* LP_DEVICE;

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

  // =================================================================
  // Data Member
  // =================================================================
private:
  Engine* engine_;

};
