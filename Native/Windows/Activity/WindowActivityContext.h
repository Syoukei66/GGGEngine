#pragma once

#include "WindowsContext.h"

/*!
 * @brief WindowsのWindowを自ら作成するアクティビティ
 */
class WindowActivityContext : public WindowsContext
{
  // =================================================================
  // Methods from ActivityContext
  // =================================================================
protected:
  virtual void OnStart(const ActivityOption& option) override;
  virtual void OnEnd() override;

};