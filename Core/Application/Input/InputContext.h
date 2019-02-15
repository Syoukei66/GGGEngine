#pragma once

#include <Core/Application/Input/EngineInputState.h>

struct InputSetting;
class InputState;
class InputAPI;
class Activity;

class InputContext
{
public:
  enum EnableState
  {
    ONLY_ON_FOCUS,
    ONLY_ON_MOUSE,
    ALWAYS,
  };

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  InputContext(const InputSetting& setting);
  ~InputContext();
  
  // =================================================================
  // Methods
  // =================================================================
public:
  void Update(const SharedRef<Activity>& activity, const SharedRef<InputAPI>& api);
  bool IsOnCursol();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE T_UINT8 GetStateCount()
  {
    return this->state_count_;
  }
  GG_INLINE InputState* GetState(T_UINT8 player_id)
  {
    return this->states_[player_id];
  }
  GG_INLINE EngineInputState* GetEngineInputState()
  {
    return &this->engine_input_state_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:

  EnableState enable_state_;
  T_UINT8 cursol_input_id_;
  T_UINT8 state_count_;
  InputState** states_;
  EngineInputState engine_input_state_;
};
