#pragma once

class EngineInputState;
class Activity;

class InputDevice
{
public:
  InputDevice(T_UINT8 handler)
    : handler_(handler)
  {}
  virtual ~InputDevice() {}

  /*!
   * @brief 入力処理
   * 入力が無効の時に入力が蓄積しないように入力が無効でも行われる
   * @param handler
   * @param activity
   * @param state
   */
  virtual void InputProcess(T_UINT8 handler, const SharedRef<Activity>& activity, EngineInputState* state) = 0;

  /*!
   * @brief 入力をエンジン用入力に適用する処理
   * @param handler
   * @param activity
   * @param state
   */
  virtual void ApplyProcess(T_UINT8 handler, const SharedRef<Activity>& activity, EngineInputState* state) = 0;

public:
  GG_INLINE T_UINT8 GetHandler() const
  {
    return this->handler_;
  }

private:
  const T_UINT8 handler_;

};