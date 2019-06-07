#pragma once

#include <Native/Windows/Activity/WindowActivityContext.h>
#include <Native/Windows/API/Audio/XAudio/XAudioAPI.h>
#include <Native/Windows/API/Input/DirectInput/DirectInputAPI.h>
#include <Native/Windows/API/Graphics/WindowsGraphicsAPI.h>

/*!
 * @brief Windowsネイティブ側で使用する
 * グローバルなアプリケーションへのインターフェース
 */
class WindowsPlatform : public Platform
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(WindowsPlatform);
  GG_CREATE_FUNC(WindowsPlatform) { return true; }

  // =================================================================
  // Methods from Platform
  // =================================================================
protected:
  virtual bool ContinueEnabled() override;
  virtual bool FrameEnabled() override;

  GG_INLINE virtual UniqueRef<GraphicsAPI> CreateGraphicsAPI(const ApplicationOption& op) const override
  {
#if GG_GRAPHICS_API_DX9
    return DX9GraphicsAPI::Create();
#elif GG_GRAPHICS_API_DX11
    return DX11GraphicsAPI::Create();
#endif
  }

  GG_INLINE virtual UniqueRef<AudioAPI> CreateAudioAPI(const ApplicationOption& op) const override
  {
    return XAudioAPI::Create();
  }

  GG_INLINE virtual UniqueRef<InputAPI> CreateInputAPI(const ApplicationOption& op) const override
  {
    return DirectInputAPI::Create();
  }

  GG_INLINE virtual ActivityContext* CreateMainActivityContext() const override
  {
    return new WindowActivityContext();
  }

  GG_INLINE virtual ActivityContext* CreateActivityContext() const override
  {
    return new WindowActivityContext();
  }

public:
  virtual void ImGuiNewFrame() override;

  // =================================================================
  // Methods
  // =================================================================
public:
  static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
#if GG_GRAPHICS_API_DX9
  GG_INLINE SharedRef<DX9GraphicsAPI> GetDX9Graphics()
  {
    return SharedRef<DX9GraphicsAPI>::StaticCast(this->GetGraphicsAPI());
  }
#elif GG_GRAPHICS_API_DX11
  GG_INLINE SharedRef<DX11GraphicsAPI> GetDX11Graphics()
  {
    return SharedRef<DX11GraphicsAPI>::StaticCast(this->GetGraphicsAPI());
  }
#endif

  GG_INLINE SharedRef<XAudioAPI> GetXAudio()
  {
    return SharedRef<XAudioAPI>::StaticCast(this->GetAudioAPI());
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  MSG msg_;

};