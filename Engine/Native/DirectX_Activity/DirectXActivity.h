#ifndef HAL_DIRECTX_DIRECTXACTIVITY_H_
#define HAL_DIRECTX_DIRECTXACTIVITY_H_

#include <BaseActivity.h>
#include "DirectXNativeImplements.h"
#include "DirectXInputDeviceManager.h"

class DirectXActivity : public BaseActivity
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  DirectXActivity(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
  virtual ~DirectXActivity();

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
protected:
  virtual INativeProcess_Graphics* SetupNativeProcess_Graphics() override;
  virtual INativeProcess_IO* SetupNativeProcess_IO() override;
  virtual INativeProcess_Time* SetupNativeProcess_Time() override;
  virtual bool ApplyEngineOption(const EngineOption* option) override;
  virtual bool Init(const EngineOption* option) override;
  virtual bool Uninit() override;
  virtual bool FrameEnabled() override;
  virtual void ImGuiNewFrame() override;
  virtual bool ContinueEnabled() override;
  virtual bool PreDraw() override;
  virtual void PostDraw() override;
  virtual void ImGuiEndFrame() override;
  virtual void InputProcess(EngineInputState* state) override;

private:
  void DrawFPS(const char* text, T_FLOAT x, T_FLOAT y, T_UINT32 color);

  // =================================================================
  // Method
  // =================================================================
public:
  static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM Parm);

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  virtual LP_DEVICE GetDevice() const override;

  inline WPARAM GetMsgWparam() const
  {
    return this->msg_.wParam;
  }
  inline HWND GetHWnd() const
  {
    return this->wnd_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  const HINSTANCE instance_;
  const HINSTANCE prev_instance_;
  const LPSTR cmdline_;
  const int show_cmd_;
  HWND wnd_;
  DWORD before_update_count_;
  RECT window_rect_;

  LPDIRECT3D9 d3d_;
  LPDIRECT3DDEVICE9 d3d_device_;

  DirectXNativeImplements* native_implements_;

  DirectXInputDeviceManager* input_;

  MSG msg_;

#ifdef _DEBUG
  LPD3DXFONT debug_font_;
#endif

};

#endif//HAL_DIRECTX_DIRECTXACTIVITY_H_