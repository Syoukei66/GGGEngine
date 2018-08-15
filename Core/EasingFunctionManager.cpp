#include "EasingFunctionManager.h"
#include <string.h>
#include "NativeAssert.h"

namespace
{

  const char* FunctionID[EasingFunction::FK_DATA_NUM] =
  {
    "liner",
    "quad",
    "cubic",
    "quart",
    "quint",
    "sin",
    "expo",
    "circ",
  };

  T_UINT8 GetFunctionKindByFunctionID(const char* id)
  {
    if (!id)
    {
      return EasingFunction::FK_DATA_NUM;
    }
    for (T_UINT8 i = 0; i < EasingFunction::FK_DATA_NUM; ++i)
    {
      if (strcmp(id, FunctionID[i]) == 0)
      {
        return i;
      }
    }
    return EasingFunction::FK_DATA_NUM;
  }

  const char* OperatorID[EasingFunction::EASE_DATA_NUM] =
  {
    "in",
    "out",
    "inout"
  };

  T_UINT8 GetOperatorKindByOperatorID(const char* id)
  {
    if (!id)
    {
      return EasingFunction::EASE_DATA_NUM;
    }
    for (T_UINT8 i = 0; i < EasingFunction::EASE_DATA_NUM; ++i)
    {
      if (strcmp(id, OperatorID[i]) == 0)
      {
        return i;
      }
    }
    return EasingFunction::EASE_DATA_NUM;
  }

  T_FLOAT CalcByEaseFunctionAndOperator(EasingFunction::EasingFunction* func, T_UINT8 op, T_FLOAT val)
  {
    if (op == EasingFunction::EASE_IN)
    {
      return func->In(val);
    }
    if (op == EasingFunction::EASE_OUT)
    {
      return func->Out(val);
    }
    if (op == EasingFunction::EASE_IN_OUT)
    {
      return func->InOut(val);
    }
    return val;
  }

  T_FLOAT CalcByEaseFunctionAndOperatorID(EasingFunction::EasingFunction* func, const char* operator_id, T_FLOAT val)
  {
    const T_UINT8 operator_kind = GetOperatorKindByOperatorID(operator_id);
    return CalcByEaseFunctionAndOperator(func, operator_kind, val);
  }

}

// =================================================================
// Constructor / Destructor
// =================================================================
EasingFunctionManager::EasingFunctionManager()
  : function_table_(NULL)
{}

// =================================================================
// Method
// =================================================================
void EasingFunctionManager::Load(T_UINT8 render_cycle)
{
  if (this->function_table_)
  {
    this->Unload();
  }
  this->function_table_ = new EasingFunction::EasingFunction*[EasingFunction::FK_DATA_NUM];
  this->function_table_[EasingFunction::FK_LINER] = &EasingFunction::Liner::GetInstance();
  this->function_table_[EasingFunction::FK_QUADRATIC] = &EasingFunction::Quadratic::GetInstance();
  this->function_table_[EasingFunction::FK_CUBIC] = &EasingFunction::Cubic::GetInstance();
  this->function_table_[EasingFunction::FK_QUARTIC] = &EasingFunction::Quartic::GetInstance();
  this->function_table_[EasingFunction::FK_QUINTIC] = &EasingFunction::Quintic::GetInstance();
  this->function_table_[EasingFunction::FK_SINUSOIDAL] = &EasingFunction::Sinusoidal::GetInstance();
  this->function_table_[EasingFunction::FK_EXPONENTIAL] = &EasingFunction::Exponential::GetInstance();
  this->function_table_[EasingFunction::FK_CIRCULAR] = &EasingFunction::Circular::GetInstance();

  for (T_UINT8 i = 0; i < EasingFunction::FK_DATA_NUM; ++i)
  {
    this->function_table_[i]->Load(render_cycle);
  }
}

void EasingFunctionManager::Unload()
{
  if (!this->function_table_)
  {
    return;
  }
  for (T_UINT8 i = 0; i < EasingFunction::FK_DATA_NUM; ++i)
  {
    this->function_table_[i]->Unload();
  }
  delete[] this->function_table_;
}

T_FLOAT EasingFunctionManager::CalcByID(const char* function_id, const char* operator_id, T_FLOAT value)
{
  const T_UINT8 function_kind = GetFunctionKindByFunctionID(function_id);
  NATIVE_ASSERT(function_kind != EasingFunction::FK_DATA_NUM, "EasingFunction‚ÌIDŽw’è‚ÉŒë‚è‚ª‚ ‚è‚Ü‚·");
  return CalcByEaseFunctionAndOperatorID(this->function_table_[function_kind], operator_id, value);
}

T_FLOAT EasingFunctionManager::CalcByID(T_UINT8 func, T_UINT8 op, T_FLOAT value)
{
  return CalcByEaseFunctionAndOperator(this->function_table_[func], op, value);
}
