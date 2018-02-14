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

  // COM���C�u�����̏�����
  CoInitializeEx(NULL, COINIT_MULTITHREADED);

  // XAudio2�I�u�W�F�N�g�̍쐬
  hr = XAudio2Create(&x_audio_2_, 0);
  if (FAILED(hr))
  {
    NATIVE_ASSERT(false, "XAudio2�I�u�W�F�N�g�̍쐬�Ɏ��s�I");

    // COM���C�u�����̏I������
    CoUninitialize();

    return E_FAIL;
  }

  // �}�X�^�[�{�C�X�̐���
  hr = x_audio_2_->CreateMasteringVoice(&mastering_voice_);
  if (FAILED(hr))
  {
    NATIVE_ASSERT(false, "�}�X�^�[�{�C�X�̐����Ɏ��s�I");

    if (x_audio_2_)
    {
      // XAudio2�I�u�W�F�N�g�̊J��
      x_audio_2_->Release();
      x_audio_2_ = NULL;
    }

    // COM���C�u�����̏I������
    CoUninitialize();

    return E_FAIL;
  }

  return S_OK;
}

void AudioManager::Uninit()
{
  // �}�X�^�[�{�C�X�̔j��
  mastering_voice_->DestroyVoice();
  mastering_voice_ = NULL;

  if (x_audio_2_)
  {
    // XAudio2�I�u�W�F�N�g�̊J��
    x_audio_2_->Release();
    x_audio_2_ = NULL;
  }

  // COM���C�u�����̏I������
  CoUninitialize();
}
