#pragma once

#include <Core/Application/Platform/API/APIObject.h>

class Activity;
class EngineInputState;

/*!
 * @brief 入力APIのベースクラス
 */
class InputAPI : public GGAPIObject
{
  // =================================================================
  // Methods from GGAPIObject
  // =================================================================
public:
  virtual void SetupModules() override;

  // =================================================================
  // Methods
  // =================================================================
public:
  virtual void InputProcess(const SharedRef<Activity>& activity, EngineInputState* state) = 0;
  virtual void ApplyProcess(const SharedRef<Activity>& activity, EngineInputState* state) = 0;
  virtual void CreateSubActivityResources(const SharedRef<Activity>& activity) = 0;

};