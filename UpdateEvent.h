#ifndef HAL_ENGINE_SCENE_EVENT_UPDATE_UPDATEEVENT_H_
#define HAL_ENGINE_SCENE_EVENT_UPDATE_UPDATEEVENT_H_

#include "NativeType.h"

// =================================================================
// UpdateEventState
// =================================================================
class UpdateEventState
{
public:
  static UpdateEventState* GetInstance()
  {
    static UpdateEventState self;
    return &self;
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
private:
  UpdateEventState();

  // =================================================================
  // Method
  // =================================================================
public:
  void OnSceneChanged();
  void Update(T_UINT32 milliseconds_elapsed);
 
  // =================================================================
  // Setter/Getter
  // =================================================================
public:
  inline T_UINT32 GetFrameElapsedSinceSceneCreate() const
  {
    return this->frame_elapsed_since_scene_create_;
  }

  inline T_UINT32 GetMillisecondsElapsedSinceSceneCreate() const
  {
    return this->milliseconds_elapsed_since_scene_create_;
  }

  inline T_UINT32 GetDeltaTime() const
  {
    return this->delta_time_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  T_UINT32 frame_elapsed_since_scene_create_;
  T_UINT32 milliseconds_elapsed_since_scene_create_;
  //Œo‰ßƒ~ƒŠ•b
  T_UINT32 delta_time_;
};

#endif//HAL_ENGINE_SCENE_EVENT_UPDATE_UPDATEEVENT_H_
