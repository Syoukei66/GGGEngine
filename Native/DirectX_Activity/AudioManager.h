#pragma once
#include <XAudio2.h>

class AudioManager
{
public:
  static AudioManager& GetInstance()
  {
    static AudioManager self;
    return self;
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  AudioManager();
  ~AudioManager();

  // =================================================================
  // Method
  // =================================================================
public:
  HRESULT Init();
  void Uninit();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline IXAudio2* GetXAudio() const
  {
    return this->x_audio_2_;
  }
  inline IXAudio2MasteringVoice* GetXAudioMasteringVoice() const
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