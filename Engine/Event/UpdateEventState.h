#pragma once

// =================================================================
// UpdateEventState
// =================================================================
class UpdateEventState
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SINGLETON(UpdateEventState);

  // =================================================================
  // Method
  // =================================================================
public:
  static void OnSceneChanged();
  static void Update(T_UINT32 milliseconds_elapsed);

  // =================================================================
  // Setter/Getter
  // =================================================================
public:
  static GG_INLINE T_UINT32 GetFrameElapsedSinceSceneCreate()
  {
    return Self().frame_elapsed_since_scene_create_;
  }

  static GG_INLINE T_UINT32 GetMillisecondsElapsedSinceSceneCreate()
  {
    return Self().milliseconds_elapsed_since_scene_create_;
  }

  static GG_INLINE T_UINT32 GetDeltaTime()
  {
    return Self().delta_time_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  T_UINT32 frame_elapsed_since_scene_create_;
  T_UINT32 milliseconds_elapsed_since_scene_create_;
  T_UINT32 delta_time_;
};
