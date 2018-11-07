#pragma once

#include <XAudio2.h>
#include <Core/Application/Platform/API/Audio/AudioAPI.h>

class XAudioAPI : public AudioAPI
{
public:
  static GG_INLINE SharedRef<XAudioAPI> GetInstance()
  {
    return SharedRef<XAudioAPI>::StaticCast(Platform::GetAudioAPI());
  }

  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT_NAME(XAudioAPI);
  GG_CREATE_FUNC(XAudioAPI);
  GG_DESTRUCT_FUNC(XAudioAPI);

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual UniqueRef<rcAudioClip> LoadSound(const char* path) override;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE IXAudio2* GetXAudio() const
  {
    return this->x_audio_2_;
  }
  GG_INLINE IXAudio2MasteringVoice* GetXAudioMasteringVoice() const
  {
    return this->mastering_voice_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  // XAudio2オブジェクトへのインターフェイス
  IXAudio2 *x_audio_2_;
  // マスターボイス
  IXAudio2MasteringVoice *mastering_voice_;

};