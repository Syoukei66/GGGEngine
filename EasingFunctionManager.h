#ifndef HAL_ENGINE_UTIL_EASINGFUNCTION_EASINGFUNCTIONMANAGER_H_
#define HAL_ENGINE_UTIL_EASINGFUNCTION_EASINGFUNCTIONMANAGER_H_

#include "NativeType.h"
#include "EasingFunction.h"

class EasingFunctionManager
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static inline EasingFunctionManager* GetInstance()
  {
    static EasingFunctionManager self;
    return &self;
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
private:
  EasingFunctionManager();

  // =================================================================
  // Method
  // =================================================================
public:
  void Load(T_UINT8 render_cycle);
  void Unload();
  T_FLOAT CalcByID(const char* function_id, const char* operator_id, T_FLOAT value);
  T_FLOAT CalcByID(T_UINT8 func, T_UINT8 op, T_FLOAT value);

  // =================================================================
  // Data Member
  // =================================================================
private:
  EasingFunction::EasingFunction** function_table_;
};

#endif//HAL_ENGINE_UTIL_EASINGFUNCTION_EASINGFUNCTIONMANAGER_H_
