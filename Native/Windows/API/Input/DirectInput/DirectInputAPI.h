#pragma once

#include <Core/Application/Platform/API/Input/InputAPI.h>

class DirectInputImplements;
class DirectInputDeviceManager;

class DirectInputAPI : public InputAPI
{
  // =================================================================
  // GGG Statement
  // =================================================================
public:
  GG_OBJECT(DirectInputAPI);
  GG_CREATE_FUNC(DirectInputAPI);
  GG_DESTRUCT_FUNC(DirectInputAPI);

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
protected:
  virtual void InputProcess(const SharedRef<Activity>& activity, EngineInputState* state) override;
  virtual void CreateSubActivityResources(const SharedRef<Activity>& activity) override;

  // =================================================================
  // Data Member
  // =================================================================
private:
  DirectInputImplements* native_implements_;
  DirectInputDeviceManager* input_;

};