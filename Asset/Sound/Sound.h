#pragma once

/*!
 * @brief サウンドデータ
 */
class rcSound : public GGAssetObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT_NAME(rcSound);

  // =================================================================
  // Factory Method
  // =================================================================
public:
  static UniqueRef<rcSound> CreateFromFile(const char* path);
  
  // =================================================================
  // Methods
  // =================================================================
public:
  virtual void Play(T_UINT8 loop_count = 0) = 0;
  virtual void Stop() = 0;
  virtual void Pause() = 0;
  virtual void Resume() = 0;

};