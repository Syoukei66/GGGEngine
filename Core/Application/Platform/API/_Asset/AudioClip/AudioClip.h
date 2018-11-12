#pragma once

#include <Core/Application/Platform/API/_Asset/APIAssetObject.h>

/*!
 * @brief サウンドデータ
 */
class rcAudioClip : public GGAPIAssetObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(rcAudioClip);

  // =================================================================
  // Factory Method
  // =================================================================
public:
  static UniqueRef<rcAudioClip> CreateFromFile(const char* path);
  
  // =================================================================
  // Methods
  // =================================================================
public:
  virtual void Play(T_UINT8 loop_count = 0) = 0;
  virtual void Stop() = 0;
  virtual void Pause() = 0;
  virtual void Resume() = 0;

};