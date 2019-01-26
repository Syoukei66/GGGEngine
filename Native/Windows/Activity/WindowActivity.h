#pragma once

#include "WindowsActivity.h"

/*!
 * @brief WindowsのWindowを自ら作成するアクティビティ
 */
class WindowActivity : public WindowsActivity
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(WindowActivity);
  GG_CREATE_FUNC_1(WindowActivity, const ActivityOption&);

};