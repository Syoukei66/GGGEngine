#include "AudioManager.h"
#include <NativeAssert.h>

// =================================================================
// Constructor / Destructor
// =================================================================
AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
}

// =================================================================
// Method
// =================================================================
HRESULT AudioManager::Init()
{
  HRESULT hr;

  // COMライブラリの初期化
  CoInitializeEx(NULL, COINIT_MULTITHREADED);

  // XAudio2オブジェクトの作成
  hr = XAudio2Create(&x_audio_2_, 0);
  if (FAILED(hr))
  {
    NATIVE_ASSERT(false, "XAudio2オブジェクトの作成に失敗！");

    // COMライブラリの終了処理
    CoUninitialize();

    return E_FAIL;
  }

  // マスターボイスの生成
  hr = x_audio_2_->CreateMasteringVoice(&mastering_voice_);
  if (FAILED(hr))
  {
    NATIVE_ASSERT(false, "マスターボイスの生成に失敗！");

    if (x_audio_2_)
    {
      // XAudio2オブジェクトの開放
      x_audio_2_->Release();
      x_audio_2_ = NULL;
    }

    // COMライブラリの終了処理
    CoUninitialize();

    return E_FAIL;
  }

  return S_OK;
}

void AudioManager::Uninit()
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
}
