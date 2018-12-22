#pragma once

#include <Core/Application/Platform/API/Input/InputAPI.h>
#include <Core/Application/Input/InputEntity.h>

struct InputSetting
{
  InputSetting()
    : player_count_(1)
    , entities_()
    , enable_state_(InputAPI::EnableState::ALWAYS)
    , cursol_input_id_()
  {}
  T_UINT8 player_count_;
  std::deque<InputEntity> entities_;
  InputAPI::EnableState enable_state_;
  T_UINT8 cursol_input_id_;
};
