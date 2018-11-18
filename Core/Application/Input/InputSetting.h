#pragma once

#include <Core/Application/Input/EngineInput.h>
#include <Core/Application/Platform/API/Input/InputAPI.h>

struct InputEntity
{
  //コンストラクタその１　全入力タイプ
  InputEntity(
    T_UINT8 id,
    EngineInput::Digital::ID negative_button,
    EngineInput::Digital::ID positive_button,
    EngineInput::Analog::ID axis,
    T_UINT8 dimention
  )
    : input_id(id)
    , negative_button(negative_button)
    , positive_button(positive_button)
    , axis(axis)
    , dimention(dimention)
  {}

  //コンストラクタその２　ボタンのみタイプ
  InputEntity(
    T_UINT8 id,
    EngineInput::Digital::ID button
  )
    : input_id(id)
    , negative_button(-1)
    , positive_button(button)
    , axis(-1)
    , dimention(-1)
  {}

  //コンストラクタその３　アナログのみタイプ
  InputEntity(
    T_UINT8 id,
    EngineInput::Analog::ID axis,
    T_UINT8 dimention
  )
    : input_id(id)
    , negative_button(-1)
    , positive_button(-1)
    , axis(axis)
    , dimention(dimention)
  {}

  //コンストラクタその１　アナログ片側のみ入力タイプ
  InputEntity(
    T_UINT8 id,
    EngineInput::Digital::ID positive_button,
    EngineInput::Analog::ID axis,
    T_UINT8 dimention
  )
    : input_id(id)
    , negative_button(-1)
    , positive_button(positive_button)
    , axis(axis)
    , dimention(dimention)
  {}


  InputEntity()
    : input_id(-1)
    , negative_button(-1)
    , positive_button(-1)
    , axis(-1)
    , dimention(-1)
  {}

  T_INT8 input_id;
  T_INT8 positive_button;
  T_INT8 negative_button;
  T_INT8 axis;
  T_INT8 dimention;
};

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
