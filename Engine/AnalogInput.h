#ifndef HAL_ENGINE_SCENE_EVENT_ENGINEINPUT_ANALOGINPUTEVENT_H_
#define HAL_ENGINE_SCENE_EVENT_ENGINEINPUT_ANALOGINPUTEVENT_H_

#include <math.h>
#include "NativeType.h"
#include "EngineInput.h"

// =================================================================
// AnalogInputState
// �R���g���[���[��}�E�X����̃A�i���O�ȓ��͂�ێ����܂�
// ���͂�0.0�`1.0�̊Ԃŏ�������܂��B0.0�����̏ꍇ�͓��͖͂�������܂��B
// Preserve analog input from controller/mouse.
// Inputs are processed between 0.0 and 1.0.
// If it is less than 0.0, input is ignored.
// =================================================================

class AnalogInputState
{
public:
  static const AnalogInputState* NULL_INPUT;
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  AnalogInputState();

  // =================================================================
  // Method
  // =================================================================
public:
  void Prepare();
  void PreInput(EngineInput::Analog::ID id);
  //���͂�0.0�`1.0�̊ԂŃZ�b�g
  //Set the input between 0.0 and 1.0.
  void InputValue(EngineInput::Analog::ID id, T_UINT8 dimension, T_FLOAT value);
  void PostInput(EngineInput::Analog::ID id);

  // =================================================================
  // Setter/Getter
  // =================================================================
public:
  inline bool IsPrepareInput(T_UINT16 id) const
  {
    return this->input_prepared_[id];
  }

  //�ߋ��̓��͂̐�Βl��dead_range�ȉ��̏�Ԃ���
  //���݂̓��͂�dead_range�ȏ�ɂȂ����^�C�~���O��true�ɂȂ�܂��B
  //It becomes true when the absolute value of past input is dead_range or less and
  //the current input becomes dead_range or more.
  inline bool IsTrigger(T_INT16 id, T_UINT8 dimension, T_FLOAT dead_range = 0.0f) const
  {
    return id != -1 &&
      (fabs(this->old_input_[id][dimension]) <= dead_range && fabs(this->input_[id][dimension]) > dead_range);
  }

  //�ߋ��̓��͂̐�Βl��dead_range�ȏ�̏�Ԃ���
  //���݂̓��͂�dead_range�ȉ��ɂȂ����^�C�~���O��true�ɂȂ�܂��B
  //It becomes true when the absolute value of past input is dead_range or more and
  //the current input becomes dead_range or less.
  inline bool IsRelease(T_INT16 id, T_UINT8 dimension, T_FLOAT dead_range = 0.0f) const
  {
    return id != -1 &&
      (fabs(this->input_[id][dimension]) <= dead_range && fabs(this->old_input_[id][dimension]) > dead_range);
  }
  
  inline T_FLOAT GetValue(T_INT16 id, T_UINT8 dimension, T_FLOAT min = 0.0f, T_FLOAT max = 1.0f) const
  {
    if (id == -1 || this->input_[id][dimension] < 0.0f)
    {
      return (max + min) * 0.5f;
    }
    return this->input_[id][dimension] * (max - min) + min;
  }

  inline T_FLOAT GetOldValue(T_INT16 id, T_UINT8 dimension, T_FLOAT min = 0.0f, T_FLOAT max = 1.0f) const
  {
    if (id == -1 || this->old_input_[id][dimension] < 0.0f)
    {
      return this->input_[id][dimension];
    }
    return this->old_input_[id][dimension] * (max - min) + min;
  }

  inline T_FLOAT GetDelta(T_INT16 id, T_UINT8 dimension, T_FLOAT min = 0.0f, T_FLOAT max = 1.0f) const
  {
    if (id == -1 || this->old_input_[id][dimension] < 0.0f)
    {
      return (max - min) + min;
    }
    return (this->input_[id][dimension] - this->old_input_[id][dimension]) * (max - min) + min;
  }

  inline bool IsEnabled(T_INT16 id, T_UINT8 dimension) const
  {
    return id != -1 && this->input_[id][dimension] > 0.0f;
  }

  inline bool IsOldEnabled(T_INT16 id, T_UINT8 dimension) const
  {
    return id != -1 && this->old_input_[id][dimension] > 0.0f;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  //���͂�0.0�`1.0�̊Ԃŏ�������܂�
  //Inputs are processed between 0.0 and 1.0.
  bool input_prepared_[EngineInput::Analog::ID_ANALOG_MAX];
  T_FLOAT old_input_[EngineInput::Analog::ID_ANALOG_MAX][EngineInput::Analog::DIMENSION_DATANUM];
  T_FLOAT input_[EngineInput::Analog::ID_ANALOG_MAX][EngineInput::Analog::DIMENSION_DATANUM];
};

#endif//HAL_ENGINE_SCENE_EVENT_ENGINEINPUT_ANALOGINPUTEVENT_H_
