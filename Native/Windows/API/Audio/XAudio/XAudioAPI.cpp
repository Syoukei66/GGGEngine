#include "XAudioAPI.h"
#include "XAudioSound.h"

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL(XAudioAPI)
{
  HRESULT hr;

  // COMライブラリの初期化
  CoInitializeEx(NULL, COINIT_MULTITHREADED);

  // XAudio2オブジェクトの作成
  hr = XAudio2Create(&x_audio_2_, 0);
  if (FAILED(hr))
  {
    GG_ASSERT(false, "XAudio2オブジェクトの作成に失敗！");

    // COMライブラリの終了処理
    CoUninitialize();

    return false;
  }

  // マスターボイスの生成
  hr = x_audio_2_->CreateMasteringVoice(&mastering_voice_);
  if (FAILED(hr))
  {
    GG_ASSERT(false, "マスターボイスの生成に失敗！");

    if (x_audio_2_)
    {
      // XAudio2オブジェクトの開放
      x_audio_2_->Release();
      x_audio_2_ = NULL;
    }

    // COMライブラリの終了処理
    CoUninitialize();

    return false;
  }

  WAVEFORMATEXTENSIBLE wfx;
  IXAudio2SourceVoice* source;
  this->x_audio_2_->CreateSourceVoice(&source, &(wfx.Format));

  return true;
}

GG_DESTRUCT_FUNC_IMPL(XAudioAPI)
{
  // マスターボイスの破棄
  mastering_voice_->DestroyVoice();
  mastering_voice_ = NULL;

  if (x_audio_2_)
  {
    // XAudio2オブジェクトの開放
    x_audio_2_->Release();
    x_audio_2_ = NULL;
  }

  // COMライブラリの終了処理
  CoUninitialize();
  return true;
}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
UniqueRef<rcAudioClip> XAudioAPI::LoadSound(const char* path)
{
  return UniqueRef<rcAudioClip>(new NativeSound(path));
}
