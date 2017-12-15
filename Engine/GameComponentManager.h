#pragma once

#include "Singleton.h"

class GameComponentManager
{
public:
  static GameComponentManager* GetInstance()
  {
    return &singleton<GameComponentManager>::get_instance();
  }

private:
  GameComponentManager() {}

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:

};