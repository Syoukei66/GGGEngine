#pragma once

#include "EngineInputEvent.h"
#include "NativeType.h"

class InputDevice
{
public:
  InputDevice(T_UINT8 handler)
    : handler_(handler)
  {}
  virtual ~InputDevice() {}

  virtual void InputProcess(T_UINT8 handler, EngineInputState* state) = 0;

public:
  inline T_UINT8 GetHandler() const
  {
    return this->handler_;
  }

private:
  const T_UINT8 handler_;

};