#pragma once

#include <unordered_map>
#include <list>
#include "InputSetting.h"

class InputState
{
public:
  InputState(T_UINT8 player_id, const InputSetting& setting);

public:
  void ClearCache();

public:
  bool AnyButton();
  bool AnyButtonDown();
  bool AnyButtonUp();
  bool AnyAxis();
  bool AnyAxisOrButton();
  T_FLOAT GetAxis(T_UINT8 id, T_FLOAT dead_range = 0.1f);
  T_FLOAT GetAxisDown(T_UINT8 id, T_FLOAT dead_range = 0.1f);
  T_FLOAT GetAxisUp(T_UINT8 id, T_FLOAT dead_range = 0.1f);
  T_FLOAT GetAxisDelta(T_UINT8 id);
  bool GetButton(T_UINT8 id);
  bool GetButtonDown(T_UINT8 id);
  bool GetButtonUp(T_UINT8 id);

private:
  T_UINT8 player_id_;
  std::unordered_map<T_UINT8, InputEntity> entities_;
};

class InputManager
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SINGLETON(InputManager);

public:
  static void Init(const InputSetting& setting);
  static void Uninit();

  static void ClearCaches();

public:
  static GG_INLINE T_UINT8 GetStateCount()
  {
    return Self().state_count_;
  }
  static GG_INLINE InputState* GetState(T_UINT8 player_id)
  {
    return Self().states_[player_id];
  }

private:
  T_UINT8 state_count_;
  InputState** states_;

};