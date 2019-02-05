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

  virtual void InputProcess(T_UINT8 handler, const SharedRef<Activity>& activity, EngineInputState* state) = 0;

public:
  GG_INLINE T_UINT8 GetHandler() const
  {
    return this->handler_;
  }

private:
  const T_UINT8 handler_;

};