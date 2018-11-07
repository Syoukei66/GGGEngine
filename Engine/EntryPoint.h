#pragma once

#include <Core/Application/IPlatformSetting.h>
#include <Engine/Engine/IEngineBehavior.h>

class EntryPoint : public IPlatformSetting
{
  // =================================================================
  // Methods
  // =================================================================
public:
  void Run(IEngineBehavior* behavior);

};