#pragma once

#include <Core/API/Input/InputAPI.h>

class DirectInputImplements;
class DirectInputDeviceManager;

class DirectInputAPI : public InputAPI
{
  // =================================================================
  // GGG Statement
  // =================================================================
public:
  GG_OBJECT_NAME(DirectInputAPI);
  GG_CREATE_FUNC_1(DirectInputAPI, const InputSetting&);
  GG_DESTRUCT_FUNC(DirectInputAPI);

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
protected:
  virtual void InputProcess(EngineInputState* state) override;

  // =================================================================
  // Data Member
  // =================================================================
private:
  DirectInputImplements* native_implements_;
  DirectInputDeviceManager* input_;

};