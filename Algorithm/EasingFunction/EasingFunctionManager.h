#pragma once

#include "EasingFunction.h"

class EasingFunctionManager
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SINGLETON(EasingFunctionManager);

  // =================================================================
  // Method
  // =================================================================
public:
  static void Load(T_UINT8 render_cycle);
  static void Unload();
  static T_FLOAT CalcByID(const char* function_id, const char* operator_id, T_FLOAT value);
  static T_FLOAT CalcByID(T_UINT8 func, T_UINT8 op, T_FLOAT value);

  // =================================================================
  // Data Member
  // =================================================================
private:
  EasingFunction::EasingFunction** function_table_;
};
