#pragma once

/*!
 * @brief アプリケーションの初期化に必要なパラメータ群
 */
struct EngineOption
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_JSONABLE(EngineOption)
  {
    archive(cereal::make_nvp("EasingFunctionSamplingCount", easing_function_sampling_count_));
  }

  EngineOption()
    : easing_function_sampling_count_(120)
  {}

  T_UINT32 easing_function_sampling_count_;
};
