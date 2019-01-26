#pragma once

/*!
 * @brief Windows環境でのPlatformクラスのベースクラス
 */
class WindowsPlatform : public Platform
{
  // =================================================================
  // Methods from Platform
  // =================================================================
protected:
  virtual UniqueRef<AudioAPI> CreateAudioAPI() = 0;
  virtual UniqueRef<InputAPI> CreateInputAPI() = 0;

};