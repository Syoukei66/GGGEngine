#pragma once

#include <Core/Application/Activity/ActivityOption.h>
#include <Core/Application/Input/InputSetting.h>

/*!
 * @brief アプリケーションの初期化に必要なパラメータ群
 */
struct ApplicationOption
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_JSONABLE(ApplicationOption)
  {
    archive(cereal::make_nvp("FullScreenMode", full_screen_mode));
    archive(cereal::make_nvp("InputSetting", input_setting));
    archive(cereal::make_nvp("MainActivityOption", main_activity_option));
  }

public:
  bool full_screen_mode;
  InputSetting input_setting;
  ActivityOption main_activity_option;

};
