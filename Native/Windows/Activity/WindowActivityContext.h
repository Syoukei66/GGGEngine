#pragma once

#include "WindowsContext.h"

/*!
 * @brief WindowsのWindowを自ら作成するアクティビティ
 */
class WindowActivityContext : public WindowsContext
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(WindowActivityContext);
  GG_CREATE_FUNC(WindowActivityContext) { return true; }

  // =================================================================
  // Methods from ActivityContext
  // =================================================================
protected:
  virtual void OnStart(const ActivityOption& option) override;
  virtual void OnEnd() override;

};