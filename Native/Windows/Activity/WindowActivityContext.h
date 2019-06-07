#pragma once

#include "WindowsContext.h"

/*!
 * @brief Windows��Window������쐬����A�N�e�B�r�e�B
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