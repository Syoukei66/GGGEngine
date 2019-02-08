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
   * @brief ���͏���
   * ���͂������̎��ɓ��͂��~�ς��Ȃ��悤�ɓ��͂������ł��s����
   * @param handler
   * @param activity
   * @param state
   */
  virtual void InputProcess(T_UINT8 handler, const SharedRef<Activity>& activity, EngineInputState* state) = 0;

  /*!
   * @brief ���͂��G���W���p���͂ɓK�p���鏈��
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