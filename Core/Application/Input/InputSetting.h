#pragma once

#include <Core/Application/Input/InputContext.h>
#include <Core/Application/Input/InputEntity.h>

struct InputSetting
{
  InputSetting()
    : player_count_(1)
    , entities_()
    , enable_state_(InputContext::EnableState::ALWAYS)
    , cursol_input_id_()
  {}
  T_UINT8 player_count_;
  std::deque<InputEntity> entities_;
  InputContext::EnableState enable_state_;
  T_UINT8 cursol_input_id_;
};
