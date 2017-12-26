#include "InputSetting.h"

InputSettingBuilder::InputSettingBuilder()
  : setting_()
{}

void InputSettingBuilder::Register(const InputEntity* entity, T_UINT8 size)
{
  for (T_UINT8 i = 0; i < size; ++i)
  {
    this->Register(entity[i]);
  }
}

void InputSettingBuilder::Register(const InputEntity& entity)
{
  this->setting_.entities_.push_back(entity);
}
