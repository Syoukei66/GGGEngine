#pragma once

/*!
 * @brief Windows���ł�Platform�N���X�̃x�[�X�N���X
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