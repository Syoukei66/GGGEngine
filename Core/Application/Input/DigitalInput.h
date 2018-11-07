#pragma once

#include "EngineInput.h"

// =================================================================
// DigitalInputState
// �R���g���[���[�̃{�^����L�[�{�[�h����̓��͂�ێ����܂�
// Preserve input from controllers button and keybord
// =================================================================

class DigitalInputState
{
public:
  static const DigitalInputState NULL_INPUT;
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  DigitalInputState();

  // =================================================================
  // Methods
  // =================================================================
public:
  void Prepare();
  void PreInput(EngineInput::Digital::ID id);
  //���͂���������B�P�t���[�����łP�x�����Ă΂�Ȃ�����z��
  //Process input. Assume that it is called only once within one frame.
  void InputValue(EngineInput::Digital::ID id);
  void PostInput(EngineInput::Digital::ID id);

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE bool IsPrepareInput(T_UINT16 id) const
  {
    return this->input_prepared_[id];
  }

  //�����ꂽ�u��
  //The moment when it was pressed.
  GG_INLINE bool IsTrigger(T_INT16 id) const
  {
    return id != -1 && this->is_trigger_[id];
  }

  //�w�肵���t���[���ȏ�̊ԉ�����Ă邩�ǂ���
  //Whether or not it is pressed for more than the specified frame
  GG_INLINE bool IsHold(T_INT16 id, T_UINT16 frame = 1) const
  {
    return id != -1 && this->input_hold_[id] >= frame;
  }

  //�����ꂽ�u��
  //The moment when it was released.
  GG_INLINE bool IsRelease(T_INT16 id) const
  {
    return id != -1 && this->is_release_[id];
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  T_UINT32 old_state_;
  T_UINT32 now_state_;

  bool input_prepared_[EngineInput::Digital::ID_DIGITAL_MAX];
  bool is_trigger_[EngineInput::Digital::ID_DIGITAL_MAX];
  bool is_release_[EngineInput::Digital::ID_DIGITAL_MAX];
  T_UINT16 input_hold_[EngineInput::Digital::ID_DIGITAL_MAX];
};
