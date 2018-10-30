#pragma once

#include <Engine/Event/EngineInputEvent.h>

struct InputEntity
{
  //�R���X�g���N�^���̂P�@�S���̓^�C�v
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

  //�R���X�g���N�^���̂Q�@�{�^���̂݃^�C�v
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

  //�R���X�g���N�^���̂R�@�A�i���O�̂݃^�C�v
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

  //�R���X�g���N�^���̂P�@�A�i���O�Б��̂ݓ��̓^�C�v
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
  {}
  T_UINT8 player_count_;
  std::deque<InputEntity> entities_;
};

class InputSettingBuilder
{
public:
  InputSettingBuilder();

public:
  void Register(const InputEntity* entity, T_UINT8 size);
  void Register(const InputEntity& entity);

public:
  GG_INLINE void SetPlayerCount(T_UINT8 count)
  {
    this->setting_.player_count_ = count;
  }
  GG_INLINE const InputSetting& Build() const
  {
    return this->setting_;
  }

private:
  InputSetting setting_;
};
