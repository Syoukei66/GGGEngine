#pragma once

#include <Core/Application/Activity/ActivityOption.h>
#include <Core/Application/Input/InputSetting.h>

/*!
 * @brief �A�v���P�[�V�����̏������ɕK�v�ȃp�����[�^�Q
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
  }

public:
  bool full_screen_mode;
  InputSetting input_setting;

};
