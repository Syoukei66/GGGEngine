#include "XAudioAPI.h"
#include "XAudioSound.h"

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL(XAudioAPI)
{
  HRESULT hr;

  // COM���C�u�����̏�����
  CoInitializeEx(NULL, COINIT_MULTITHREADED);

  // XAudio2�I�u�W�F�N�g�̍쐬
  hr = XAudio2Create(&x_audio_2_, 0);
  if (FAILED(hr))
  {
    GG_ASSERT(false, "XAudio2�I�u�W�F�N�g�̍쐬�Ɏ��s�I");

    // COM���C�u�����̏I������
    CoUninitialize();

    return false;
  }

  // �}�X�^�[�{�C�X�̐���
  hr = x_audio_2_->CreateMasteringVoice(&mastering_voice_);
  if (FAILED(hr))
  {
    GG_ASSERT(false, "�}�X�^�[�{�C�X�̐����Ɏ��s�I");

    if (x_audio_2_)
    {
      // XAudio2�I�u�W�F�N�g�̊J��
      x_audio_2_->Release();
      x_audio_2_ = NULL;
    }

    // COM���C�u�����̏I������
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
  return true;
}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
UniqueRef<rcAudioClip> XAudioAPI::LoadSound(const char* path)
{
  return UniqueRef<rcAudioClip>(new NativeSound(path));
}
