#pragma once

#include "WindowsActivity.h"

/*!
 * @brief Windows��Window������쐬����A�N�e�B�r�e�B
 */
class WindowActivity : public WindowsActivity
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(WindowActivity);
  GG_CREATE_FUNC_1(WindowActivity, const ActivityOption&);

};